# Signal Processing Detailed Design

## Function of the Subsystem

This subsystem will provide a detailed description of the Triage Drone's signal processing and interfacing. After reading this detailed design, the reader should have a clear understanding of how this subsystem integrates with other subsystem solutions, its constraints and specifications, and how the solutions are constructed. The system comprises a digital signal processing pipeline that extracts heart and respiratory rates from Doppler radar data without contact \[1\].

## Specifications and Constraints

1.	The signal processing subsystem SHALL use digital signal processing techniques \[2\]
    - to determine respiratory rate (range 0.13 to 1.0 Hz) 
    - heart rate (range 0.8 to 3.0 Hz).


2.  The signal processing subsystem SHALL extract vital signs from at least one meter away \[3\].

3. DSP SHALL complete within 500ms per update cycle \[4\].
    
4. The subsystem SHALL operate using data samples at 100-200Hz from the Infineon BGT60UTR11AIP \[5\].

5. The subsystem SHALL perform all DSP steps locally aboard the Aurelia X4 drone.

6. If no valid heart or respiration rate is detected, the subsystem SHALL let the user know.
    
## Overview of Proposed Solution

Radar-based vitals detection research has shown that respiration and cardiac motion can be extracted from Doppler Radar measurements using digital signal processing techniques \[1\]. Because the Aurelia X4 drone maintains a stable hover through its flight control subsystem, the DSP subsystem assumes minimal platform error \[4\]. The subsystem will extract vital signs directly from the radar using an efficient on-board DSP pipeline implemented through the Jetson Nano.

### Radar Data ### 

  The Infineon BGT60UTR11AIP radar provides raw data at 100-200 Hz, capturing chest motions associated with respiratory and heart rates \[5\].

### Low Pass Filtering ### 

   A finite impulse response (FIR) low-pass filter with a cutoff at about 5 Hz to remove high frequencies and any unnecessary noise \[6\]. Since all physiological content lies at or below 3 Hz, the cut-off         ensures clean conditioning \[2\].

### Decimation ###

   After filtering, the signal will then be down sampled to 10-20 Hz to reduce computational load while retaining all relevant physiological information \[6\]. This allows the Jetson Nano to meet the 500ms         update cycle processing requirements \[4\].

### Heart and Respiration Rate Bandpass Filtering ###

   Two FIR bandpass filters will be utilized to isolate the respective vitals \[2\]:

   -   Respiration Rate: 0.13-1.0 Hz
   -   Heart Rate: 0.8-3.0 Hz

### Fast Fourier Transform (FFT) ###

   Each bandpass-filtered signal will be transformed with an FFT. In the frequency domain, respiration and heart rates appear as peaks within their respective band \[1\].

### Peak Detection ###

   The subsystem validates peaks using these criteria \[7\]:

   -   The peak must lie within the physiological band.
   -   The peak must exceed a noise floor threshold, and if no peak can be detected, the system will report the vital sign as unreliable and therefore unable to be detected.

### Vitals Extraction ### 

  The peak frequency will then be converted to breaths per minute (BPM) or beats per minute (BPM) \[7\].

  $$\text{BPM} = 60 \times f_{\text{peak}}$$


This solution is lightweight and efficient, and it incorporates only the radar and Jetson Nano. Using these DSP techniques, this subsystem will be able to meet the requirements in practice.

## Interfacing with other Subsystems ##

### Radar Subsystem ###

   The Infineon BGT60UTR11AIP radar subsystem will deliver raw radar data via a USB connection to the Jetson Nano. The drone operatory subsystem will mount the radar downward toward the victim, providing ideal     measurements of chest motion.

### Power Subsystem ###

   The power subsystem will supply regulated power to both the NVIDIA Jetson Nano and the radar. The Jetson Nano will host all DSP workloads and requires sufficient power.

### Drone Operator Subsystem ###

   This subsystem will mount cameras, microphones, speakers, and the radar. Will maintain a one-meter distance to ensure adequate radar readings and processing, as well as safe drone flight and hovering.

### Victim Communication Subsystem ### 

   Will be selecting a camera and mic to locate and communicate with victims and navigate. Relies on the drone operator subsystem for flight and mounting, and the power subsystem for reliable power to devices.

### Drone to PC Link ###

   This subsystem will transmit vital signs and other information, such as camera feed and audio, to the PC ground station.

## Operational Flow Chart ##

<img width="531" height="1287" alt="Screenshot 2025-12-09 205129" src="https://github.com/user-attachments/assets/b5ab1b18-1a78-48fe-aad8-976dee7edeb0" />

## MATLAB DSP Validation ##

A MATLAB simulation was performed to illustrate the DSP pipeline using ideal physiological signals.

**Table 1. Simulation Parameters:** A sample chest motion signal was generated to demonstrate how the DSP pipeline performs ideally. The radar is modeled from a respiration and heart rate sinusoid at 100 Hz

| Category | Parameter | Values | Description |
| --- | --- | --- | --- |
| Sampling | Input Sampling Rate | 100 Hz | Raw radar sampling |
|  | Decimation Rate | 20 Hz | Down sampling after low pass filtering |
|  | Signal Duration | 30 s | Length of Data |
| Vitals Setting (Actual) | Respiration Frequency | 0.25 Hz | 15 BPM (Breaths per minute) |
|  | Heart Rate Frequency | 1.20 Hz | 72 BPM (Beats per minute) |
| Amplitude Settings | Respiration Amplitude | 0.8 | Chest Motion |
|  | Heart Rate Amplitude | 0.2 | Cardiac Motion |
| Peak Detections | SNR threshold | 6dB |  |

<img width="1955" height="1246" alt="Screenshot 2025-12-09 220306" src="https://github.com/user-attachments/assets/c6180381-64d0-4814-95ab-25b3b470278c" />

**Figure 1.** Chest motion signal used for DSP, composed of a 0.25 Hz respiration and a 1.20 Hz heart rate component.

<br><br>

**Table 2. FIR Filters:** The pipeline uses one lowpass filter and two bandpass filters. The lowpass filter prevents aliasing, and the bandpass filter, which is the decimation, isolates respiratory and heart rates.

| Filter | Length | Sampling Rate | Frequency Range |
| --- | --- | --- | --- |
| Lowpass | 128 | 100 Hz | 0-5 Hz |
| Respiration Bandpass (Decimation) | 128 | 20 Hz | 0.13-1.0 Hz |
| Heart Rate Bandpass (Decimation) | 128 | 20 Hz | 0.8-3.0 Hz |
<img width="1929" height="1234" alt="Screenshot 2025-12-09 220320" src="https://github.com/user-attachments/assets/8952bc31-41f8-4cea-a9cd-6d024cbfc57c" />

**Figure 2.** Magnitude responses for the lowpass and respective bandpass filters.

<br><br>

**Bandpass Filtered Signals:** After low-pass filtering and decimation, the heart and respiratory rate bandpass filters are applied to isolate the respective components.
<img width="1929" height="1240" alt="Screenshot 2025-12-09 220331" src="https://github.com/user-attachments/assets/2fadd7ca-5406-4f0f-ac29-41c1aa2b381a" />
**Figure 3.** Filtered respiration and heart rate signals clearly illustrate slow and fast oscillations, showing how both physiological phenomena are expected to look.

<br><br>

**FFT Application:** FFT is applied to each filtered signal to identify frequency peaks. The respiration FFT peak is at about 0.23 Hz, and the heart rate is at 1.20 Hz.

<img width="1965" height="1241" alt="Screenshot 2025-12-09 220344" src="https://github.com/user-attachments/assets/495b4b09-55b4-4ce8-a804-641b9826e8bf" />

**Figure 4.** The FFT spectrum for respiration has a signal peak at about 0.23 Hz

<br><br>

<img width="2006" height="1236" alt="Screenshot 2025-12-09 220355" src="https://github.com/user-attachments/assets/603624b7-83bf-455b-9ca1-f5451e8e4a2d" />

**Figure 5.** The FFT spectrum for heart rate has a signal peak at about 1.20 Hz

<br><br>

**Table 3. Extracted Vitals:** After FFT peak extractions, convert to respective BPMs. Then, both measurements exceed the minimum SNR threshold, so they are considered reliable.

| Signal Type | Target Frequency | FFT Peak (Hz) | BPM | Reliability |
| --- | --- | --- | --- | --- |
| Respiration | 0.25 Hz | 0.23 Hz | 14 BPM | Reliable |
| Heart Rate | 1.20 Hz | 1.20 Hz | 72 BPM | Reliable |

### Summary ###

The MATLAB simulations illustrate the ideal case for the pipeline. While in practice the graphs were separated, showing respiration and heart rate, the difference won't be known until peak detection during FFT and conversion of peak frequencies to BPM.


## Bill of Materials (BOM)

| Part Number | Description | Manufacturer Name | Purpose | Quantity | Cost Per Item | Total Cost of Quantity |
| --- | --- | --- | --- | --- | --- | --- |
| J1020 V2 |[Jetson Nano Developer Kit](https://www.seeedstudio.com/reComputer-J1020-v2-p-5498.html)| Nvidia | CPU for drone and support on board DSP | 1 | $279.00 | $279.00 |
|  |  |  |  |  | Total Expenses | $279.00 |
|  |  |  |  |  | Total Quantity | 1 |

## Analysis ##

This section describes the mathematical and physical justification for the DSP pipeline of this subsystem.

### 1. Chest Motion ###

The radar measures chest motion, which can be modeled as:

$$x(t) = A_{\text{resp}} \sin(2\pi f_{\text{resp}} t) + A_{\text{heart}} \sin(2\pi f_{\text{heart}} t) + n(t)$$


As seen in the simulations, respiration produces large but slow oscillations, and heart rate produces small and rapid oscillations \[3\].

### 2. Sampling ###

The radar is sampled $$f_s = 100\text{--}200 \text{ Hz}$$
, the content of interest lies below about 3 Hz therefore, the radar's sampling is higher than what is necessary \[5\].

### 3. Low Pass Filter ###

Before decimation, a lowpass filter (0-5 Hz) is applied to retain the required frequency bands. Respiration goes up to about 1 Hz, and Heart rate up to about 3 Hz therefore, to prevent aliasing and anything irrelevant \[2\].

### 4. Decimation ###

The subsystem requirement allows reducing the sampling rate to 10-20 Hz \[6\]. A decimation factor of 5 will be used, so 100 Hz will be downsampled to 20 Hz. Nyquist sampling will then be 10 Hz, which is well above the 3 Hz upper bound.

### 5. Bandpass Filtering ###

Two bandpass filters will be applied to isolate the respiration and heart rate components \[2\].

Respiration Rate: 0.13-1.0 Hz

Heart Rate: 0.8-3.0 Hz

A bandpass filter will improve overall clarity and clean the signal before applying an FFT.

### 6. FFT ###

After the data is filtered with a bandpass, an FFT will be applied to identify dominant frequency peaks in each signal. The FFT will convert the waveform y\[n\] to a frequency spectrum \[1\].

$$Y[k] = \sum_{n=0}^{N-1} y[n]e^{-j\frac{2\pi}{N}kn}$$


Each FFT bin corresponds to a frequency.

$$f_k = \frac{k}{N} \times 20 \text{ Hz}$$


20 Hz comes after decimations. Then the subsystem will search for the largest peak within each physiological band, respiration (0.13-1.0 Hz) and heart rate (0.8-3.0 Hz). Since chest motion is sinusoidal, the FFT peaks are directly linked to respiratory and heart rates.

### 7. BPM Conversion ###

$$\text{BPM} = 60 \times f_{\text{peak}}$$


### 8. SNR Threshold ###

$$\text{SNR}_{\text{dB}} = 20 \log_{10} \left( \frac{|Y[\text{peak}]|}{\text{Noise Floor}} \right)$$


This formula functions as a peak reliability test, and finally, SNR<sub>dB</sub>
 has to be greater than 6dB, which is about twice as large as the noise floors, for peak values to be reliable \[7\].

### Summary ###

This analysis supports the subsystem's proposed solution for DSP. When measured data fall below 3 Hz, a 0-5 Hz lowpass filter ensures anti-aliasing. Then, decimation by 5, reducing sampling from 100 Hz to 20 Hz, satisfies requirements and efficiency. Bandpass filters isolate respiration and heart rates, followed by an FFT to detect frequency peaks. Finally, the peaks are converted to BPM and will be prepared to be sent out.

## References ##

\[1\] Kebe, M., Gadhafi, R., Mohammad, B., Sanduleanu, M., Saleh, H., & Al-Qutayri, M. (2020). Human Vital Signs Detection Methods and Potential Using Radars: A Review. Sensors, 20(5), 1454. [https://doi.org/10.3390/s20051454](https://doi.org/10.3390/s20051454)

\[2\] G. Vinci et al., "Six-Port Radar Sensor for Remote Respiration Rate and Heartbeat Vital-Sign Monitoring," in IEEE Transactions on Microwave Theory and Techniques, vol. 61, no. 5, pp. 2093-2100, May 2013, doi: 10.1109/TMTT.2013.2247055

\[3\] Gao, Z., Ali, L., Wang, C., Liu, R., Wang, C., Qian, C., Sung, H., & Meng, F. (2022). Real-Time Non-Contact Millimeter Wave Radar-Based Vital Sign Detection. _Sensors_, _22_(19), 7560. [https://doi.org/10.3390/s22197560](https://doi.org/10.3390/s22197560)

\[4\] A. R. Dwinanda, A. Adya Pramudita, B. S. Nugroho and A. Ayu Dhiyani, "Effects of Drone Height Fluctuations on Detection of Respiratory Vital Signs Using FMCW Radar," 2023 IEEE International Symposium On Antennas And Propagation (ISAP), Kuala Lumpur, Malaysia, 2023, pp. 1-2, doi: 10.1109/ISAP57493.2023.10388930

\[5\] Infineon Technologies, "XENSIV™ 60 GHz BGT60UTR11AIP Radar Sensor Product Brief," Infineon Technologies AG, Munich, Germany, 2023

\[6\] M. Alizadeh, G. Shaker, J. C. M. D. Almeida, P. P. Morita and S. Safavi-Naeini, "Remote Monitoring of Human Vital Signs Using mm-Wave FMCW Radar," in IEEE Access, vol. 7, pp. 54958-54968, 2019, doi: 10.1109/ACCESS.2019.2912956

\[7\] Kim, J.-Y., Park, J.-H., Jang, S.-Y., & Yang, J.-R. (2019). Peak Detection Algorithm for Vital Sign Detection Using Doppler Radar Sensors. _Sensors_, _19_(7), 1575. [https://doi.org/10.3390/s19071575](https://doi.org/10.3390/s19071575)
