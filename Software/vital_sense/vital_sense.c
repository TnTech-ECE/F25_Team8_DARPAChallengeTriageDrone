#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "ifxAvian/Avian.h"
#include "ifxAlgo/FFT.h"
#include "ifxBase/Error.h"
#include "ifxBase/Version.h"
#include "ifxBase/Complex.h"

#ifdef _WIN32
#include <windows.h>
#define SLEEP_MS(ms) Sleep(ms)
#else
#include <unistd.h>
#define SLEEP_MS(ms) usleep((ms) * 1000)
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// ─── Radar Configuration ──────────────────────────────────────────────────────
#define NUM_RX_ANTENNAS         1
#define FRAME_RATE              20.0
#define NUMBER_OF_CHIRPS        8
#define SAMPLES_PER_CHIRP       64
#define FFT_SIZE_RANGE_PROFILE  (SAMPLES_PER_CHIRP * 2)

// ─── Vital Sign Configuration ─────────────────────────────────────────────────
#define PHASE_BUFFER_SIZE       256         // Must be a power of 2; 256/20 = 12.8 seconds of data at 20 Hz frame rate
#define FFT_SIZE_VITAL          1024        // Must be a power of 2; corresponds to 1.17 bpm per bin fair frequency resolution at 20 Hz sample rate
#define LOW_BREATHING           0.1f        // Hz (~6 breaths/min)
#define HIGH_BREATHING          0.6f        // Hz (~36 breaths/min)
#define LOW_HEART               0.85f       // Hz (~51 bpm)
#define HIGH_HEART              2.4f        // Hz (~144 bpm)
#define FILTER_ORDER            21
#define OBJECT_DIST_START       0.5         // meters — target distance window start
#define OBJECT_DIST_STOP        0.8         // meters — target distance window stop
#define MIN_BREATHING_BPM       6.0f        // Minimum valid breathing rate in bpm
#define MAX_BREATHING_BPM       36.0f       // Maximum valid breathing
#define MIN_HEART_BPM           51.0f       // Minimum valid heart rate in bpm
#define MAX_HEART_BPM           144.0f      // Maximum valid heart rate in bpm
#define MIN_TARGET_MAGNITUDE    0.0015f        // Minimum magnitude threshold for valid target detection

// ─── FIR Filter Coefficients ──────────────────────────────────────────────────
// Generated with scipy.signal.firwin(21, [0.1, 0.6], pass_zero=False, fs=20.0)
static const ifx_Float_t breathing_b[FILTER_ORDER] = {
    0.003666648997226839f,
    0.00579859898225822f,
    0.011223587041639586f,
    0.020634104316733796f,
    0.03396073980293704f,
    0.05031260293773419f,
    0.06807913465832723f,
    0.08517875142479377f,
    0.09940953215099006f,
    0.10883554383333031f,
    0.11213403886851984f,
    0.10883554383333031f,
    0.09940953215099006f,
    0.08517875142479377f,
    0.06807913465832723f,
    0.05031260293773419f,
    0.03396073980293704f,
    0.020634104316733796f,
    0.011223587041639586f,
    0.00579859898225822f,
    0.003666648997226839f
};

// Generated with scipy.signal.firwin(21, [0.85, 2.4], pass_zero=False, fs=20.0)
static const ifx_Float_t heart_b[FILTER_ORDER] = {
    0.0017645272119925642f,
    -0.0009666883792551834f,
    -0.010176268245414484f,
    -0.030766499778926905f,
    -0.05831137245551546f,
    -0.07476801518027178f,
    -0.056828655957276486f,
    0.006279361489023918f,
    0.09895901033453573f,
    0.1824654214931382f,
    0.21607567177986242f,
    0.1824654214931382f,
    0.09895901033453573f,
    0.006279361489023918f,
    -0.056828655957276486f,
    -0.07476801518027178f,
    -0.05831137245551546f,
    -0.030766499778926905f,
    -0.010176268245414484f,
    -0.0009666883792551834f,
    0.0017645272119925642f
};

// ─── State ────────────────────────────────────────────────────────────────────
static ifx_Float_t phase_buffer[PHASE_BUFFER_SIZE];  // stores unwrapped phase
static int   phase_index    = 0;     // circular write head
static int   phase_count    = 0;     // how many samples collected so far
static int   estimate_count = 0;
static ifx_Float_t last_raw_phase = 0.0f;   // last raw atan2 output
static ifx_Float_t unwrap_offset  = 0.0f;   // cumulative correction

// ─────────────────────────────────────────────────────────────────────────────
// Helper functions
// ─────────────────────────────────────────────────────────────────────────────
// Remove mean + linear trend
static void detrend(ifx_Float_t* signal, int len)
{
    if (len < 3) return;

    double sum = 0.0, sum_t = 0.0, sum_tt = 0.0, sum_ts = 0.0;
    for (int i = 0; i < len; i++) {
        double t = (double)i;
        sum    += signal[i];
        sum_t  += t;
        sum_tt += t * t;
        sum_ts += t * signal[i];
    }
    double n = (double)len;
    double slope = (n * sum_ts - sum_t * sum) / (n * sum_tt - sum_t * sum_t);
    double mean  = sum / n;
    double t_mean = sum_t / n;

    for (int i = 0; i < len; i++) {
        double t = (double)i;
        signal[i] -= (ifx_Float_t)(mean + slope * (t - t_mean));
    }
}

// Quadratic interpolation for precise peak frequency
static double quadratic_peak_bin(const ifx_Complex_t* fft, int low, int high)
{
    double max_mag = 0.0;
    int peak = low;
    for (int i = low; i <= high; i++) {
        double re = IFX_COMPLEX_REAL(fft[i]);
        double im = IFX_COMPLEX_IMAG(fft[i]);
        double mag = sqrt(re * re + im * im);
        if (mag > max_mag) {
            max_mag = mag;
            peak = i;
        }
    }
    if (peak == low || peak == high) return (double)peak;   // edge case, no interpolation

    double m1 = sqrt(IFX_COMPLEX_REAL(fft[peak-1]) * IFX_COMPLEX_REAL(fft[peak-1]) +
                     IFX_COMPLEX_IMAG(fft[peak-1]) * IFX_COMPLEX_IMAG(fft[peak-1]));
    double m0 = max_mag;
    double m2 = sqrt(IFX_COMPLEX_REAL(fft[peak+1]) * IFX_COMPLEX_REAL(fft[peak+1]) +
                     IFX_COMPLEX_IMAG(fft[peak+1]) * IFX_COMPLEX_IMAG(fft[peak+1]));

    double delta = 0.5 * (m1 - m2) / (m1 - 2.0 * m0 + m2);
    return (double)peak + delta;
}

// Incrementally unwrap phase and store in circular buffer
static void push_phase(ifx_Float_t raw_phase)
{
    // Unwrap incrementally against the last sample
    ifx_Float_t dp = raw_phase - last_raw_phase;
    if (dp >  (ifx_Float_t)M_PI) unwrap_offset -= 2.0f * (ifx_Float_t)M_PI;
    if (dp < -(ifx_Float_t)M_PI) unwrap_offset += 2.0f * (ifx_Float_t)M_PI;

    last_raw_phase = raw_phase;

    ifx_Float_t unwrapped = raw_phase + unwrap_offset;

    // Reject obvious outliers (phase jump > ~π/2 from previous stored value)
    if (phase_count > 0) {
        ifx_Float_t last_stored = phase_buffer[(phase_index + PHASE_BUFFER_SIZE - 1) % PHASE_BUFFER_SIZE];
        if (fabs(unwrapped - last_stored) > 1.5f * (ifx_Float_t)M_PI) {
            // Replace with last good value instead of injecting jump
            unwrapped = last_stored;
        }
    }

    // Store the continuously unwrapped value
    phase_buffer[phase_index] = raw_phase + unwrap_offset;
    phase_index = (phase_index + 1) % PHASE_BUFFER_SIZE;
    if (phase_count < PHASE_BUFFER_SIZE) phase_count++;
}

// ─────────────────────────────────────────────────────────────────────────────
// FIR filter (direct form convolution)
// ─────────────────────────────────────────────────────────────────────────────
static void fir_filter(const ifx_Float_t* b, int b_len,
                       const ifx_Float_t* input, int input_len,
                       ifx_Float_t* output)
{
    for (int n = 0; n < input_len; n++) {
        ifx_Float_t acc = 0.0f;
        for (int k = 0; k < b_len; k++) {
            if (n - k >= 0)
                acc += b[k] * input[n - k];
        }
        output[n] = acc;
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// Phase unwrapping
// ─────────────────────────────────────────────────────────────────────────────
/*
static void unwrap_phase(ifx_Float_t* phase, int len)
{
    for (int i = 1; i < len; i++) {
        ifx_Float_t dp = phase[i] - phase[i - 1];
        if (dp > (ifx_Float_t)M_PI) {
            for (int j = i; j < len; j++)
                phase[j] -= 2.0f * (ifx_Float_t)M_PI;
        } else if (dp < -(ifx_Float_t)M_PI) {
            for (int j = i; j < len; j++)
                phase[j] += 2.0f * (ifx_Float_t)M_PI;
        }
    }
    printf("Phase range: %f to %f\n", phase[0], phase[len - 1]);
}
*/
// ─────────────────────────────────────────────────────────────────────────────
// Vital sign estimation from buffered phase data
// ─────────────────────────────────────────────────────────────────────────────
/*
static void process_vital_signs(const ifx_Float_t* phase_buf, int len)
{
    int i;

    // Unwrap phase
    // ifx_Float_t unwrapped[PHASE_BUFFER_SIZE];
    // for (i = 0; i < len; i++)
    //     unwrapped[i] = phase_buf[i];
    // unwrap_phase(unwrapped, len);

    // Apply bandpass FIR filters
    ifx_Float_t filtered_breathing[PHASE_BUFFER_SIZE] = {0};
    ifx_Float_t filtered_heart[PHASE_BUFFER_SIZE]     = {0};
    fir_filter(breathing_b, FILTER_ORDER, phase_buf, len, filtered_breathing);
    fir_filter(heart_b,     FILTER_ORDER, phase_buf, len, filtered_heart);


    // Zero-pad into FFT input buffers
    ifx_Float_t* bp_in    = (ifx_Float_t*)calloc(FFT_SIZE_VITAL, sizeof(ifx_Float_t));
    ifx_Float_t* heart_in = (ifx_Float_t*)calloc(FFT_SIZE_VITAL, sizeof(ifx_Float_t));
    if (!bp_in || !heart_in) {
        fprintf(stderr, "Memory allocation failed\n");
        free(bp_in); free(heart_in);
        return;
    }
    for (i = 0; i < len; i++) {
        bp_in[i]    = filtered_breathing[i];
        heart_in[i] = filtered_heart[i];
    }

    // Allocate FFT output
    int fft_out_len = FFT_SIZE_VITAL / 2 + 1;
    ifx_Complex_t* bp_fft    = (ifx_Complex_t*)malloc(fft_out_len * sizeof(ifx_Complex_t));
    ifx_Complex_t* heart_fft = (ifx_Complex_t*)malloc(fft_out_len * sizeof(ifx_Complex_t));
    if (!bp_fft || !heart_fft) {
        fprintf(stderr, "FFT memory allocation failed\n");
        free(bp_in); free(heart_in); free(bp_fft); free(heart_fft);
        return;
    }

    // Create FFT instances (must be power of 2)
    ifx_FFT_t* bp_inst    = ifx_fft_create(IFX_FFT_TYPE_R2C, FFT_SIZE_VITAL);
    ifx_FFT_t* heart_inst = ifx_fft_create(IFX_FFT_TYPE_R2C, FFT_SIZE_VITAL);
    if (!bp_inst || !heart_inst) {
        fprintf(stderr, "Failed to create FFT instances\n");
        free(bp_in); free(heart_in); free(bp_fft); free(heart_fft);
        return;
    }

    ifx_fft_raw_rc(bp_inst,    bp_in,    bp_fft);
    ifx_fft_raw_rc(heart_inst, heart_in, heart_fft);

    // Find peak within valid frequency bands only
    double freq_res = FRAME_RATE / (double)FFT_SIZE_VITAL;

    int bp_low  = (int)(LOW_BREATHING  / freq_res);
    int bp_high = (int)(HIGH_BREATHING / freq_res);
    int hr_low  = (int)(LOW_HEART      / freq_res);
    int hr_high = (int)(HIGH_HEART     / freq_res);

    // Clamp to valid range
    if (bp_high >= fft_out_len) bp_high = fft_out_len - 1;
    if (hr_high >= fft_out_len) hr_high = fft_out_len - 1;

    double bp_max = 0.0, hr_max = 0.0, num = 0.0, den = 0.0;
    //Use weighted average for breathing rate to get more stable estimates, since breathing can be weak and noisy

    for (i = bp_low; i <= bp_high; i++) {
        double mag = sqrt(IFX_COMPLEX_REAL(bp_fft[i]) * IFX_COMPLEX_REAL(bp_fft[i]) +
                          IFX_COMPLEX_IMAG(bp_fft[i]) * IFX_COMPLEX_IMAG(bp_fft[i]));
        num += i * mag;
        den += mag;
    }
    double hr_num = 0.0, hr_den = 0.0;
    for (i = hr_low; i <= hr_high; i++) {
        double mag = sqrt(IFX_COMPLEX_REAL(heart_fft[i]) * IFX_COMPLEX_REAL(heart_fft[i]) +
                        IFX_COMPLEX_IMAG(heart_fft[i]) * IFX_COMPLEX_IMAG(heart_fft[i]));
        hr_num += i * mag;
        hr_den += mag;
    }   
    double br_center = (den > 0.0) ? (num / den) : bp_low;         // Avoid division by zero
    double hr_center = (hr_den > 0.0) ? (hr_num / hr_den) : hr_low;
    double breathing_bpm = br_center * freq_res * 60.0;
    double heart_bpm = hr_center * freq_res * 60.0;

    // print debug info
    printf("BP bins: low=%d high=%d center=%.2f | HR bins: low=%d high=%d center=%.2f\n",
           bp_low, bp_high, br_center, hr_low, hr_high, hr_center);

    // Validate estimates
    if (breathing_bpm < MIN_BREATHING_BPM || breathing_bpm > MAX_BREATHING_BPM)
        breathing_bpm = 0.0f; // Invalid breathing rate
    if (heart_bpm < MIN_HEART_BPM || heart_bpm > MAX_HEART_BPM)
        heart_bpm = 0.0f; // Invalid heart rate


    printf("[%d] Breathing: %.1f bpm | Heart: %.1f bpm\n",
           estimate_count++, breathing_bpm, heart_bpm);

    // Cleanup
    ifx_fft_destroy(bp_inst);
    ifx_fft_destroy(heart_inst);
    free(bp_fft);
    free(heart_fft);
    free(bp_in);
    free(heart_in);
}
*/
// ─────────────────────────────────────────────────────────────────────────────
// Vital sign estimation from buffered phase data (improved + detrending + quadratic interpolation)
// ─────────────────────────────────────────────────────────────────────────────
static void process_vital_signs(const ifx_Float_t* phase_buf, int len)
{
    int i;

    // Copy to working buffer
    ifx_Float_t ordered[PHASE_BUFFER_SIZE];
    for (i = 0; i < len; i++)
        ordered[i] = phase_buf[i];

    // === NEW: Remove drift before filtering ===
    detrend(ordered, len);

    // Apply bandpass FIR filters
    ifx_Float_t filtered_breathing[PHASE_BUFFER_SIZE] = {0};
    ifx_Float_t filtered_heart[PHASE_BUFFER_SIZE]     = {0};
    fir_filter(breathing_b, FILTER_ORDER, ordered, len, filtered_breathing);
    fir_filter(heart_b,     FILTER_ORDER, ordered, len, filtered_heart);

    // Debug: show actual signal strength after filtering
    // ifx_Float_t max_bp_amp = 0.0f, max_hr_amp = 0.0f;
    // for (i = 0; i < len; i++) {
    //     if (fabs(filtered_breathing[i]) > max_bp_amp) max_bp_amp = fabs(filtered_breathing[i]);
    //     if (fabs(filtered_heart[i])     > max_hr_amp) max_hr_amp = fabs(filtered_heart[i]);
    // }
    // printf("Filtered amp -> BP: %.4f  HR: %.4f\n", max_bp_amp, max_hr_amp);

    // Hamming window + zero-pad
    ifx_Float_t* bp_in    = (ifx_Float_t*)calloc(FFT_SIZE_VITAL, sizeof(ifx_Float_t));
    ifx_Float_t* heart_in = (ifx_Float_t*)calloc(FFT_SIZE_VITAL, sizeof(ifx_Float_t));
    if (!bp_in || !heart_in) {
        free(bp_in); free(heart_in);
        return;
    }
    for (i = 0; i < len; i++) {
        double w = 0.54 - 0.46 * cos(2.0 * M_PI * i / (len - 1));
        bp_in[i]    = filtered_breathing[i] * (ifx_Float_t)w;
        heart_in[i] = filtered_heart[i]     * (ifx_Float_t)w;
    }

    int fft_out_len = FFT_SIZE_VITAL / 2 + 1;
    ifx_Complex_t* bp_fft    = (ifx_Complex_t*)malloc(fft_out_len * sizeof(ifx_Complex_t));
    ifx_Complex_t* heart_fft = (ifx_Complex_t*)malloc(fft_out_len * sizeof(ifx_Complex_t));
    if (!bp_fft || !heart_fft) {
        free(bp_in); free(heart_in); free(bp_fft); free(heart_fft);
        return;
    }

    ifx_FFT_t* bp_inst    = ifx_fft_create(IFX_FFT_TYPE_R2C, FFT_SIZE_VITAL);
    ifx_FFT_t* heart_inst = ifx_fft_create(IFX_FFT_TYPE_R2C, FFT_SIZE_VITAL);
    if (!bp_inst || !heart_inst) {
        free(bp_in); free(heart_in); free(bp_fft); free(heart_fft);
        return;
    }

    ifx_fft_raw_rc(bp_inst,    bp_in,    bp_fft);
    ifx_fft_raw_rc(heart_inst, heart_in, heart_fft);

    double freq_res = FRAME_RATE / (double)FFT_SIZE_VITAL;

    int bp_low  = (int)(LOW_BREATHING  / freq_res + 0.5);
    int bp_high = (int)(HIGH_BREATHING / freq_res + 0.5);
    int hr_low  = (int)(LOW_HEART      / freq_res + 0.5);
    int hr_high = (int)(HIGH_HEART     / freq_res + 0.5);
    if (bp_high >= fft_out_len) bp_high = fft_out_len - 1;
    if (hr_high >= fft_out_len) hr_high = fft_out_len - 1;

    // === NEW: Quadratic peak interpolation (no more low bias) ===
    double br_center = quadratic_peak_bin(bp_fft, bp_low, bp_high);
    double hr_center = quadratic_peak_bin(heart_fft, hr_low, hr_high);

    double breathing_bpm = br_center * freq_res * 60.0;
    double heart_bpm     = hr_center * freq_res * 60.0;

    printf("BP peak=%.2f bin (%.2f Hz) | HR peak=%.2f bin (%.2f Hz)\n",
           br_center, br_center * freq_res, hr_center, hr_center * freq_res);

    if (breathing_bpm < MIN_BREATHING_BPM || breathing_bpm > MAX_BREATHING_BPM)
        breathing_bpm = 0.0f;
    if (heart_bpm < MIN_HEART_BPM || heart_bpm > MAX_HEART_BPM)
        heart_bpm = 0.0f;

    printf("[%d] Breathing: %.1f bpm | Heart: %.1f bpm\n",
           estimate_count++, breathing_bpm, heart_bpm);

    ifx_fft_destroy(bp_inst);
    ifx_fft_destroy(heart_inst);
    free(bp_fft); free(heart_fft);
    free(bp_in); free(heart_in);
}
// ─────────────────────────────────────────────────────────────────────────────
// Range FFT — extracts complex range profile from one frame
// ─────────────────────────────────────────────────────────────────────────────
static void calc_range_fft(ifx_Cube_R_t* frame, ifx_Complex_t* out)
{
    int num_chirps  = NUMBER_OF_CHIRPS;
    int num_samples = SAMPLES_PER_CHIRP;
    int fft_len     = SAMPLES_PER_CHIRP;
    int out_len     = fft_len / 2;

    // Zero output
    for (int bin = 0; bin < out_len; bin++) {
        out[bin].data[0] = 0.0f;
        out[bin].data[1] = 0.0f;
    }

    // Allocate chirp sum buffer
    ifx_Complex_t* chirp_sum = (ifx_Complex_t*)calloc(out_len, sizeof(ifx_Complex_t));
    if (!chirp_sum) {
        fprintf(stderr, "Memory allocation failed in calc_range_fft\n");
        return;
    }

    ifx_FFT_t* fft_inst = ifx_fft_create(IFX_FFT_TYPE_R2C, fft_len);
    if (!fft_inst) {
        fprintf(stderr, "Failed to create range FFT instance\n");
        free(chirp_sum);
        return;
    }

    int fft_out_len = fft_len / 2 + 1;
    ifx_Complex_t* fft_out = (ifx_Complex_t*)malloc(fft_out_len * sizeof(ifx_Complex_t));
    ifx_Float_t*   signal  = (ifx_Float_t*)malloc(fft_len * sizeof(ifx_Float_t));
    if (!fft_out || !signal) {
        fprintf(stderr, "Memory allocation failed in calc_range_fft\n");
        free(chirp_sum); free(fft_out); free(signal);
        ifx_fft_destroy(fft_inst);
        return;
    }

    for (int chirp = 0; chirp < num_chirps; chirp++) {
        //ifx_Float_t* chirp_data = frame->data + (chirp * num_samples);
        ifx_Float_t* chirp_data = &IFX_CUBE_AT(frame, 0, chirp, 0);

        // DC offset removal
        double sum = 0.0;
        for (int s = 0; s < num_samples; s++)
            sum += chirp_data[s];
        double avg = sum / num_samples;

        // Blackman-Harris window + DC removal
        for (int s = 0; s < num_samples; s++) {
            double w = 0.35875
                     - 0.48829 * cos((2.0 * M_PI * s) / (num_samples - 1))
                     + 0.14128 * cos((4.0 * M_PI * s) / (num_samples - 1))
                     - 0.01168 * cos((6.0 * M_PI * s) / (num_samples - 1));
            signal[s] = (ifx_Float_t)((chirp_data[s] - avg) * w);
        }

        ifx_fft_raw_rc(fft_inst, signal, fft_out);

        // Accumulate chirps
        for (int bin = 0; bin < out_len; bin++) {
            chirp_sum[bin].data[0] += fft_out[bin].data[0] / num_samples * 2.0f;
            chirp_sum[bin].data[1] += fft_out[bin].data[1] / num_samples * 2.0f;
        }
    }

    // Average across chirps and copy to output
    for (int bin = 0; bin < out_len; bin++) {
        out[bin].data[0] = chirp_sum[bin].data[0] / num_chirps;
        out[bin].data[1] = chirp_sum[bin].data[1] / num_chirps;
    }

    ifx_fft_destroy(fft_inst);
    free(fft_out);
    free(signal);
    free(chirp_sum);
}

// ─────────────────────────────────────────────────────────────────────────────
// Process one radar frame
// ─────────────────────────────────────────────────────────────────────────────
static void process_frame(ifx_Cube_R_t* frame, double max_range)
{
    ifx_Complex_t range_fft[SAMPLES_PER_CHIRP / 2];
    calc_range_fft(frame, range_fft);

    // === GLOBAL SEARCH but skip near-field clutter (< 0.3 m) ===
    #define MIN_TARGET_DISTANCE 0.3f          // ← change if you want
    int min_bin = (int)(MIN_TARGET_DISTANCE / max_range * (SAMPLES_PER_CHIRP / 2.0) + 0.5f);
    if (min_bin < 0) min_bin = 0;

    int    range_bin = 0;
    double max_val   = 0.0;
    for (int i = min_bin; i < SAMPLES_PER_CHIRP / 2; i++) {
        double mag = sqrt(IFX_COMPLEX_REAL(range_fft[i]) * IFX_COMPLEX_REAL(range_fft[i]) +
                          IFX_COMPLEX_IMAG(range_fft[i]) * IFX_COMPLEX_IMAG(range_fft[i]));
        if (mag > max_val) {
            max_val = mag;
            range_bin = i;
        }
    }

    double distance = (double)range_bin / (SAMPLES_PER_CHIRP / 2.0) * max_range;

    // Debug print — you will now see real magnitude values again
    // printf("Range bin: %d (from bin %d) | Distance: %.2f m | Magnitude: %.8f\n",
    //       range_bin, min_bin, distance, max_val);

    // === CUT VALUES WHEN NOTHING IN RANGE ===
    if (max_val < MIN_TARGET_MAGNITUDE) {
        printf("[%d] No target detected (mag=%.8f) -> Breathing: 0.0 bpm | Heart: 0.0 bpm\n",
               estimate_count++, max_val);
        return;                    // skip phase buffer + vital signs
    }

    // === Real target present -> extract phase and process ===
    ifx_Float_t phase = (ifx_Float_t)atan2(
        IFX_COMPLEX_IMAG(range_fft[range_bin]),
        IFX_COMPLEX_REAL(range_fft[range_bin])
    );

    push_phase(phase);

    // Process vital signs only when buffer is full enough
    if (phase_count >= PHASE_BUFFER_SIZE &&
        (phase_count == PHASE_BUFFER_SIZE || (phase_count % 32) == 0))
    {
        ifx_Float_t ordered[PHASE_BUFFER_SIZE];
        int start = phase_index;
        for (int i = 0; i < PHASE_BUFFER_SIZE; i++)
            ordered[i] = phase_buffer[(start + i) % PHASE_BUFFER_SIZE];

        process_vital_signs(ordered, PHASE_BUFFER_SIZE);
    }
}
/*
static void process_frame(ifx_Cube_R_t* frame, double max_range)
{
    ifx_Complex_t range_fft[SAMPLES_PER_CHIRP / 2];
    calc_range_fft(frame, range_fft);

    // Find peak bin within target distance window
    int start_bin = (int)(OBJECT_DIST_START / max_range * (SAMPLES_PER_CHIRP / 2));
    int stop_bin  = (int)(OBJECT_DIST_STOP  / max_range * (SAMPLES_PER_CHIRP / 2));

    // Clamp
    if (start_bin < 0) start_bin = 0;
    if (stop_bin >= SAMPLES_PER_CHIRP / 2) stop_bin = SAMPLES_PER_CHIRP / 2 - 1;

    int    range_bin = start_bin;
    double max_val   = 0.0;
    for (int i = start_bin; i <= stop_bin; i++) {
        double mag = sqrt(IFX_COMPLEX_REAL(range_fft[i]) * IFX_COMPLEX_REAL(range_fft[i]) +
                          IFX_COMPLEX_IMAG(range_fft[i]) * IFX_COMPLEX_IMAG(range_fft[i]));
        if (mag > max_val) { max_val = mag; range_bin = i; }
    }

    // Debug: print start/stop/range bins and corresponding distance
    printf("Start bin: %d | Stop bin: %d | ", start_bin, stop_bin);
    printf("Range bin: %d | Distance: %.2f m | Magnitude: %.8f\n",
           range_bin, (double)range_bin / (SAMPLES_PER_CHIRP / 2) * max_range, max_val);


    // Extract phase from peak bin
    ifx_Float_t phase = (ifx_Float_t)atan2(
        IFX_COMPLEX_IMAG(range_fft[range_bin]),
        IFX_COMPLEX_REAL(range_fft[range_bin])
    );

    // Buffer phase
    //if (phase_index < PHASE_BUFFER_SIZE)
    //    phase_buffer[phase_index++] = phase;
    push_phase(phase);

    // When full, estimate vital signs and reset
    if (phase_count >= PHASE_BUFFER_SIZE &&
        (phase_count == PHASE_BUFFER_SIZE || (phase_count % 32) == 0))
    {
        ifx_Float_t ordered[PHASE_BUFFER_SIZE];
        int start = phase_index; // oldest sample
        for (int i = 0; i < PHASE_BUFFER_SIZE; i++)
            ordered[i] = phase_buffer[(start + i) % PHASE_BUFFER_SIZE];
        process_vital_signs(ordered, PHASE_BUFFER_SIZE);
    }
}
*/
// ─────────────────────────────────────────────────────────────────────────────
// Main
// ─────────────────────────────────────────────────────────────────────────────
int main(void)
{
    ifx_Avian_Device_t* device = ifx_avian_create();
    if (!device) {
        fprintf(stderr, "Failed to create device: %s\n",
                ifx_error_to_string(ifx_error_get()));
        return -1;
    }

    printf("SDK:    %s\n", ifx_sdk_get_version_string_full());
    printf("Board:  %s\n", ifx_avian_get_board_uuid(device));
    printf("Sensor: %u\n", ifx_avian_get_sensor_type(device));

    // Configure radar
    ifx_Avian_Config_t config;
    ifx_avian_get_config_defaults(device, &config);

    config.sample_rate_Hz          = 4000000;
    config.rx_mask                 = 1;
    config.tx_mask                 = 1;
    config.tx_power_level          = 31;
    config.if_gain_dB              = 33;
    config.start_frequency_Hz      = 57400000000.0;
    config.end_frequency_Hz        = 63000000000.0;
    config.num_samples_per_chirp   = SAMPLES_PER_CHIRP;
    config.num_chirps_per_frame    = NUMBER_OF_CHIRPS;
    config.chirp_repetition_time_s = 0.001f;
    config.frame_repetition_time_s = 1.0f / FRAME_RATE;

    ifx_avian_set_config(device, &config);
    if (ifx_error_get() != IFX_OK) {
        fprintf(stderr, "Config error: %s\n", ifx_error_to_string(ifx_error_get()));
        ifx_avian_destroy(device);
        return -1;
    }

    double bandwidth = config.end_frequency_Hz - config.start_frequency_Hz;
    double range_res = 3e8 / (2.0 * bandwidth);
    double max_range = range_res * SAMPLES_PER_CHIRP / 2.0;

    printf("Range resolution: %.3f m\n", range_res);
    printf("Max range:        %.3f m\n", max_range);
    printf("Phase buffer:     %d samples (%.1f seconds)\n",
           PHASE_BUFFER_SIZE, PHASE_BUFFER_SIZE / FRAME_RATE);
    printf("Waiting for data...\n\n");

    // Main loop
    while (1) {
        ifx_Cube_R_t* frame = ifx_avian_get_next_frame(device, NULL);
        if (!frame) {
            fprintf(stderr, "Frame acquisition failed: %s\n",
                    ifx_error_to_string(ifx_error_get()));
            break;
        }

        process_frame(frame, max_range);
        ifx_cube_destroy_r(frame);

        SLEEP_MS(1);
    }

    ifx_avian_destroy(device);
    return 0;
}