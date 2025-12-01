# Signal Processing Detailed Design

## Function of the Subsystem

This subsystem will thoroughly describe the design of the Triage Drone's
signal processing and interfacing. After reading this detailed design,
the reader should have a clear understanding of how this subsystem
integrates with the other subsystem solutions, the subsystem's
constraints and specifications, and how the solutions are constructed.
The system encompasses both the digital signal processing pipeline used
to extract heart and respiratory rate from Doppler radar data (Infineon Demo BGT60UTR11AIP)
and the interfacing pathway that transports those vitals \[1\].

## Specifications and Constraints

1.  The signal processing subsystem SHALL use digital signal processing
    techniques to determine respiratory rate (range 0.13 to 1.0 Hz) and
    heart rate (range 0.8 to 3.0 Hz) \[2\].

2.  The signal processing subsystem SHALL extract vital signs from at
    least one meter away \[3\]

3.  The signal processing algorithms SHALL process data and have it
    ready to transmit within 500ms of being received \[4\].
    
4. The subsystem SHALL operate using data samples at 100-200Hz from
   the Radar (Infineon Demo BGT60UTR11AIP).
    
## Overview of Proposed Solution

Research has demonstrated the reliability of Doppler and mmWave radar
for contactless readings of breathing and heart motion
\[1\],\[3\],\[5\],\[6\]. These systems sense small chest movements but
require additional processing to handle environmental disturbances,
motion, and drone vibrations. Radar data combined with accelerometer
data reduces these disturbances \[5\].

The proposed solution aboard the Aurelia X4 drone will include an
algorithm run through the Jetson Nano. The raw radar data will be
processed with a low-pass filter and decimation to reduce computational
load while preserving the necessary data. Then, Empirical Mode
Decomposition (EMD) is performed and combined with the accelerometer
data to identify and remove unwanted signal components arising from
disturbances \[7\],\[8\]. Lastly, isolating the frequency region where
respiratory and heart rate occur and determining the rates within those
regions using established methods. This processing approach meets the
subsystem's requirements by providing accurate data that can be
transmitted directly from the Jetson Nano to the User interface for
real-time display.

## Interfacing with other Subsystems

The signal processing and user interface subsystem functions directly
with the radar and heartbeat sensor subsystem via a USB connection to
the Jetson Nano, which provides the raw radar signal used for
respiratory and heart rate measurements. The sensor subsystem is highly
dependent on the power subsystem, so the Jetson Nano and the radar are
wired correctly, receive power safely, and are in position to function
as intended. Also, the operator subsystem will work with the radar
subsystem to mount the radar and accelerometer at an ideal position. It
will be responsible for flying the drone and maintaining desirable
hovering stability, target alignment, and drone-to-target distance for
accurate readings. Finally, after the signal processing subsystem
completes and the required data are acquired, the drone-to-PC link
subsystem transmits the processed values to the user.

## Operational Flow Chart

<img width="1687" height="1353" alt="Screenshot 2025-12-01 112741" src="https://github.com/user-attachments/assets/42b90888-8d5d-44eb-8036-9c1016e59e0d" />

## Bill of Materials (BOM)

| **Part Number** | **Description** | **Manufacturer Name** | **Purpose** | **Quantity** | **Cost Per Item** | **Total Cost of Quantity** |
|:----------:|:-----------:|:-----------:|:--------:|:--------:|:-----:|:-------:|
| J1020 V2 | [Jetson Nano Developer Kit](https://www.seeedstudio.com/reComputer-J1020-v2-p-5498.html) | Nvidia | Offers computational ability | 1 | $279.00 | $279.00 |
| ADXL203EB | [Dual Axis Accelerometer](https://www.digikey.ee/en/products/detail/analog-devices-inc/ADXL203EB/665382) | Analog Devices | Measure drone movement to remove unwanted data later | 1 | $56.59 | $56.59 |
|  |  |  |  |  | **Total Expenses** | $335.59 |
|  |  |  |  |  | **Total Quantity** | 2 |

## Analysis

The proposed signal processing and user interface subsystem meets the
need for accurate, real-time, non-contact extraction of vital signs from
the mounted Aurelia X4 drone. The design begins with radar sampling at
100–200 Hz, which provides sufficient data to capture small chest motion
and supports Empirical Mode Decomposition (EMD) without aliasing
\[4\],\[9\]. Initial conditioning, including noise reduction, decimation
to 10-20 Hz, and detrending, which reduces computational load while
preserving the low-frequency content where respiration and heart rate
occur. A high-pass filter with a cutoff between 0.05 and 0.1 Hz is then
applied to suppress very low-frequency disturbances (such as the drone’s
hover drift) while maintaining the frequencies of respiration and heart
rate \[10\]. This prevents low-frequency disturbances from impacting the
decomposition.

The use of EMD allows the radar's chest motion signal to be decomposed
into a set of Intrinsic Mode Functions (IMFs), with each IMF
representing a different oscillatory component of the motion signal
\[11\]. By aligning the radar and accelerometer data in time and
computing the relationship between each IMF and the accelerometer
signal, the subsystem can identify IMFs that are dominated by drone
motion or other factors. IMFs that are closely similar to the
accelerometer are removed, while IMFs that are not similar to the
accelerometer signal are retained and reconstructed. Combining radar
with inertial sensing significantly improves the extraction of vital
signs from disturbances.

After disturbance removal, the reconstructed signal is filtered to
isolate the low-frequency band associated with respiration and heart
rate. Respiration is obtained at 0.13-1.0 Hz, and heart rate is measured
at 0.8-3.0 Hz.

The NVIDIA Jetson Nano provides computational services to execute
everything within the 500ms processing window specified by the subsystem
requirements. This ensures that vital signs are updated frequently
enough for real-time operation. Overall, the chosen algorithm, sampling
rates, filter ranges, and hardware platform are appropriate for the
Arelia X4 drone and allow the intended functionality.

## Refrences

\[1\] Droitcour, Amy & Lubecke, Victor & Lin, Jenshan & Boric-Lubecke,
O.. (2001). A microwave radio for Doppler radar sensing of vital signs.
IEEE MTTS Int Microwave Symp Dig. 1. 175 - 178 vol.1.
10.1109/MWSYM.2001.966866.

\[2\] C. Li and J. Lin, "Random Body Movement Cancellation in Doppler
Radar Vital Sign Detection," in *IEEE Transactions on Microwave Theory
and Techniques*, vol. 56, no. 12, pp. 3143-3152, Dec. 2008, doi:
10.1109/TMTT.2008.2007139

\[3\] Application brief: 60 GHz radar sensors enable better health and
medical care. (n.d.).
<https://www.ti.com/lit/an/swra810/swra810.pdf?ts=1763315625230>

\[4\] Hu X, Jin T. Short-Range Vital Signs Sensing Based on EEMD and CWT
Using IR-UWB Radar. Sensors (Basel). 2016 Nov 30;16(12):2025. doi:
10.3390/s16122025. PMID: 27916877; PMCID: PMC5191006.

\[5\] S. M. M. Islam, L. Oba and V. M. Lubecke, "Empirical Mode
Decomposition (EMD) for Platform Motion Compensation in Remote Life
Sensing Radar," *2022 IEEE Radio and Wireless Symposium (RWS)*, Las
Vegas, NV, USA, 2022, pp. 41-44, doi: 10.1109/RWS53089.2022.9719920

\[6\] J. Cha, K. Yoo, D. Choi and Y. Kim, "Human Presence Detection
Using Ultrashort-Range FMCW Radar Based on DCNN," in *IEEE Sensors
Journal*, vol. 24, no. 16, pp. 26258-26265, 15 Aug.15, 2024, doi:
10.1109/JSEN.2024.3425719.

\[7\] C. Gu, “Short-Range Noncontact Sensors for Healthcare and Other
Emerging Applications: A Review,” *Sensors*, vol. 16, no. 8, p. 1169,
Jul. 2016, doi: <https://doi.org/10.3390/s16081169>.

\[8\] I. Mostafanezhad, E. Yavari, O. Boric-Lubecke, V. M. Lubecke, and
D. P. Mandic, “Cancellation of Unwanted Doppler Radar Sensor Motion
Using Empirical Mode Decomposition,” *IEEE Sensors Journal*, vol. 13,
no. 5, pp. 1897–1904, May 2013,
doi: <https://doi.org/10.1109/jsen.2013.2238376>.

‌‌\[9\] G. M. Brooker, “Understanding Millimetre Wave FMCW Radars ,” Nov.
21,
2005. <https://www.researchgate.net/profile/Graham-Brooker/publication/228979037_Understanding_millimetre_wave_FMCW_radars/links/02e7e514a21ca686df000000/Understanding-millimetre-wave-FMCW-radars.pdf> (accessed
Nov. 25, 2024).

‌\[10\] J. Verbeke and S. Debruyne, “Vibration analysis of a UAV
multirotor frame.”
Available: <https://past.isma-isaac.be/downloads/isma2016/papers/isma2016_0797.pdf>

‌\[11\] N. E. Huang *et al.*, “The empirical mode decomposition and the
Hilbert spectrum for nonlinear and non-stationary time series
analysis,” *Proceedings of the Royal Society of London. Series A:
Mathematical, Physical and Engineering Sciences*, vol. 454, no. 1971,
pp. 903–995, Mar. 1998, doi: <https://doi.org/10.1098/rspa.1998.0193>.
