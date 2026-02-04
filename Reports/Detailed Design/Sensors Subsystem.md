# Vitals Sensor

Selecting and correctly configuring a radar sensor remains a vital aspect to this project the Triage Method is reliant on the device's ability to sense a person's heart and respiratory rate. This design document is written to outline the how to make the most use out of the sensor that this team, F25, has inherited from the previous team, F24. For the sake of coherency, the terms radar sensor and vitals sensor may be used interchangeably as they refer to the same system.

## Function of the Subsystem

This subsystem will be how the drone gathers most of the data for it or it's operators to rank victims based on the START Triage method. This method ranks patient priority based on three observations: Respiration, Perfusion, and Mental Status [1]. The first two observations will be acquired through this subsystem. Respiration will be based on respiration rate. Perfusion is how well the patient's body circulates blood, and this will be based on radial pulse, which is the pulse felt on the patient's wrist.
  
This subsystem will provide access to that information and transmit it to the Signal Processing Subsystem for further evaluation.

## Constraints
These constraints are derived from the project's Conceptual Design and from the F24's vital sense subsystem constraints:  
  - The system MUST not push the project budget to exceed roughly $5,000 (target is less than $200).
    - Keeping this subsystem under $200, ensures greater flexibility to add more subsystems and functionality in futer iterations
  - The system MUST not weigh enough to significantly disturb the drone (target is less than 0.5lb or 230g).
    - A light-weight subsystem reduces the complexity of the problem of payload weight distribution for increased stability in flight.
  - The system MUST not consume so much power as to seriously impact the drone's flight-time.
    - A low-power subsystem ensures that the drone can stay out and search for victims for a longer duration.
  - The system MUST not exceed an Effective Isotropic Radiated Power (EIRP) of 40 dBm as per the standard the Federal Communications Commission (FCC) has dictated for devices operating in the 57-71 GHz band [2].
    - This is to ensure that the subsystem is not itself a danger to patients.

## Specifications
These specifications are derived from the project's Conceptual Design:  
  - The system SHALL accurately detect a heart-rate from at least a meter away.
  - The system SHALL accurately detect respiration from at least a meter away.
  - The system SHALL be able to interface and provide data to a processor.
  - The system SHALL function despite inconsistent target positions.

## Overview of Proposed Solution 

The Infineon Demo BGT60UTR11AIP radar sensor is the solution that will fulfill all the previously mentioned constraints and specifications. It is a 60GHz Frequency Modulated Continuous Wave (FMCW) radar; however, it also possesses the capability to operate in a Continuous Wave (CW) mode. [3]
  
The sensor is attached to an Infineon Radar Baseboard MCU7 Plus which is roughly 3 inches by 1 inch and weighs less than a gram. It can be operated via pins on the board or through a micro-usb connection. Infineon provides an extensive SDK for using this technology as well as a ready-to-go GUI.  

This solution has the range, sensitivity, and programmable capabilities as well as weight limitations ideal for fulfilling the role of this submodel.

## Interface with other Subsystems
The vitals sensor subsystem will solely interface with the signal processing subsystem. This will be done by connecting the micro-usb port of the Infineon board to one of the multiple Jetson Nano USB ports. The data this system provides will be used by other systems, but only after being processed by the Jetson.  

The micro-usb to USB connection works as a serial port. The other pins on the board may or may not be utilized as a form of digital communication if the need arises. If the pins are used, the team can choose to communicate to the board via SPI (pins A9, A11-A14, A17, and D31) or I2C (pins D28 and D27).[4]

## Printed Circuit Board Layout
### The MCU7 Plus

![Screenshot 2024-11-27 at 14-13-56 Radar Baseboard MCU7 Plus - Infineon-UG155750_Radar_Baseboard_MCU7_Plus-UserManual-v01_10-EN pdf](https://github.com/TnTech-ECE/F25_Team8_DARPAChallengeTriageDrone/blob/jflores43-vital-sense-subsystem-patch-1/Reports/Detailed%20Design/Vital%20Sense%20Images/MCU7Plus.png?raw=true) [4]

Top and bottom veiws of the microcontroller used to process data from the sensor shield. Pins are labelled on the pcb. Note the gray mounting connectors P41 and P40 on the middle of the top side of the MCU. These interface with the sensor shield.


### The Infineon BGT60UTR11AIP Shield

![Screenshot 2024-11-27 at 14-15-46 BGT60UTR11AIP shield - Infineon-UG091947_BGT60UTR11AIP_shield-UserManual-v02_00-EN pdf](https://github.com/TnTech-ECE/F25_Team8_DARPAChallengeTriageDrone/blob/jflores43-vital-sense-subsystem-patch-1/Reports/Detailed%20Design/Vital%20Sense%20Images/BGT60UTR11AIP_Shield.png?raw=true) [5]

Front and back view of the sensor shield mounted on the MCU. Pinouts are labelled as well as the connectors, P3 and P4, used to mount and interface with the MCU.
### The Shield on the MCU

![BGT60UBOARD](https://github.com/TnTech-ECE/F25_Team8_DARPAChallengeTriageDrone/blob/jflores43-vital-sense-subsystem-patch-1/Reports/Detailed%20Design/Vital%20Sense%20Images/Shield+MCU.png?raw=true) [5]

This shows how the shield looks once mounted on the MCU. P4 on the shield inserts into P41 on the MCU, and P3 into P40.

## Conceptual Schematic

![Screenshot 2024-11-27 at 14-24-46 BGT60UTR11AIP - Infineon-BGT60UTR11AIP-DataSheet-v01_00-EN pdf](https://github.com/TnTech-ECE/F25_Team8_DARPAChallengeTriageDrone/blob/jflores43-vital-sense-subsystem-patch-1/Reports/Detailed%20Design/Vital%20Sense%20Images/conceptual_schematic.png?raw=true)

This schematic is found in the BGT60UTR11AIP data sheet [6]. This shows the block diagram of the sensor shield which illustrates its key subsystems like the 60 GHz frontend, the reciever and transmitter antennas, ramp generator, and power management. The main areas of focus for this paper is the first-in-first-out (FIFO) data buffer for read data and the SPI interface for radar configuration and data output.

## Operational Flowchart
![Drawing 3-1(1)](https://github.com/TnTech-ECE/F25_Team8_DARPAChallengeTriageDrone/blob/jflores43-vital-sense-subsystem-patch-1/Reports/Detailed%20Design/Vital%20Sense%20Images/operational_flowchart.png?raw=true)


The BGT60UTR11AIP supports two radar modes: continuous-wave (CW) and frequency-modulated continuous-wave (FMCW). The operational sequence begins when the sensor is supplied with power. The radar's operational mode is then configured via SPI:
- **CW mode** - a constant transmit frequency is set on the TX channel. This will be the mode utilized for this subsystem.
- **FMCW mode** - a linear frequency ramp (chirp), a range, is defined. This enables distance and velocity measurements. Not as relevant to this subsystem.

Once configured, the transmitter emits the radar signal and the receiver pin captures the reflected echo. The onboard baseband and ADC digitize the recieved signal. They are then buffered FIFO, then this data is sent to the signal processing subsystem.

## BOM
Since the majority of the engineering required for this subsystem is operation and not construction, there are only two required pieces of equipment. Note that the Infineon Demo BGT60UTR11AIP falls in and out of stock, so a substitution may be necessary. An alternative from the same manufacturer is listed, the DEMO BGT60TR13C, which is priced higher than the module that the previous team left behind. It is also boasts a richer featureset which may or may not be beneficial to this project. In the spirit of keeping costs down, another option is the MR60FDA1 from Seeed Technology Limited, which is marketed as a "fall detection module," but since it is based on the same underlying technology, mmWave Radar sensing, it should be able to be reconfigured as a respiratory/circulatory sensor.

| PRODUCT NAME            | DESCRIPTION     | MANUFACTURER NAME | QUANTITY | COST PER ITEM | TOTAL COST OF QUANTITY |
| :---:                  | :---:           | :---:             | :---:    | :---:         | :---:                  |
 BGT60UTR11AIP               | Demo kit with XENSIV™ BGT60UTR11AIP 60 GHz radar sensor | Infineon | 1 | $183.65 | $183.65 |
  BGT60TR13C*               | [Demo kit with XENSIV™ BGT60TR13C 60 GHz radar sensor](https://www.infineon.com/evaluation-board/DEMO-BGT60TR13C) | Infineon | 1 | $212.04 | $212.04|
  MR60FDA1*               | [MR60FDA1 Radar Sensor Development Board](https://www.arrow.com/en/products/101990981/seeed-technology-limited) | Seeed Technology | 1 | $51.06 | $51.06|
| 7T9MV4              | [Micro-USB Cable](https://a.co/d/gDfOkrQ) | Amazon | 1 | $8.29 | $8.29 |

\* denotes alternative options

As this sensor kit, the Demo BGT60UTR11AIP, is already in the team's possession, it remains the radar sensor for the Fall 2025 iteration of the drone payload.

## Analysis
There are multiple ways to read the heart rate and respiration rate of a patient using radar. IEEE Xplore has reported at least 2200 papers on this topic [7], and the interest in this challenge has continued to this day. Researching what to use to fulfill the roles of this subsystem was challenging as there are truly many options to choose from. However, the Infineon BGT60UTR11AIP and the MCU7 Plus are feature rich and are capable of abiding by the previously mentioned constraints and fulfilling the previously mentioned specifications.

The sensor and shield easily fit within physical size and weight specifications: the mcu baseboard is only $64\!\times\!25.4\;mm^2$ and the shield is $19\!\times\!12.7\;mm^2$ which gives the two together a fairly small footprint. A UK vendor also lists the package's weight to be $45.359\;g$ which falls within this subsystem's constraints [8].

Many projects have utilized continuous wave radars for vitals sesing; however, this introduces a limitation in that CW radars can only detect phase differences in its readings. The Infineon radar sensor is a Frequency Modulated Continuous Wave radar, which means that on top of detecting phase changes it can detect frequency changes as well [9]. This gives the signal processor more data to work with which can lead to greater precision.

The solution is low-cost and small enough, both in volume and in mass, to fit the constraints.The other systems will not suffer from the Infineon device's power consumption either as it boasts a fairly low power consumption when in use; upon initialization the sensor draws around 149 mA, 3.2 mA in idle, and between 110 mA and 220 mA while active, though typical consumption is around 174 mA. With an operating voltage of around 1.8 V and calculating using (1) this leads to a maximum power draw of 396 mW and a typical draw of around 313 mW. These figures are based on the BGT60UTR11AIP datasheet from Infineon [6].

<p align="center">
  <img src="https://latex.codecogs.com/svg.image?\dpi{120}P=I\cdot%20V\quad(1)" />
</p>


The device has a range of 15 m, which is more than enough to meet the proposed specification. In addition, because the radar sensor operates in the 60 GHz band, namely 57.4 GHz minimum to 63.0 GHz maximum, it is considered a mm-Wave radar device. This means that it can detect changes within a few millimeters, which is ideal for heart rate detection as a heartbeat causes displacement in this scale.  

The Infineon radar is also a safe solution for patients. Using the relationship in (2), numbers from the sensor datasheet [6], and assuming negilgible losses, effective isotropic radiated power (EIRP) is found to be $EIRP (dBm) = P_{\text{TX}} + G_{\text{TX}} - L = 5.0\,\text{dBm} + 3.0\,\text{dBi}- 0 = 8.0\,\text{dBm}$. Given that the FCC sets the power limit for this band at 40 dBm, the BGT60UTR11AIP meets the FCC's EIRP standard for sensors operating in the 60 GHz band [2]. Plainly, the power output of the radar is low, and patients subjected to the sensor will not be hit with harmful levels of radiation.  


<p align="center">
  <img src="https://latex.codecogs.com/svg.image?EIRP(dBm)=P_{TX}+G_{TX}-L\quad(2)">
</p>

The equation above outlines how EIRP of the sensor is the sum of the power consumed by the transmitter and the gain of the transmitter's antenna. Losses are also taken into account by subtracting them from the sum. All quantities are in decibels.

Lastly, the added MCU7 Plus provides users with the ability to use Infineon's radar SDK. It is capable of some on-board processing that allows for the data to be acquired in different modes (FMCW or CW) as well as to what measure would a user like the data to already be processed. One can obtain completely raw data from the device, but the board and SDK also allows users to receive data in specifically organized objects or classes so further processing is simplified.
Users can opt to receive raw data or organize the data into objects or classes to simplify later processing. This advantage allows for quicker development through flexibility, and this will simplify part of the data processing for the signal processing system.

As a side note, this is a single-input single-output sensor, meaning it has only one TX and one RX pin. Having multiple RX pins allow for the ability to determine the angle of the object in question; however, there is no reason to believe that this capability could provide further use in calculating a heart and respiratory rate.

## Pseudocode
```
// High-Level Pseudocode: Heart Rate Sensing from Drone (1 m above target, CW Mode)

BEGIN

    // 1. Setup Phase (run once when drone is in position)
    Power_on_sensor()
    Reset_sensor()
    Configure_sensor_for_CW_mode()          // Fixed frequency, no chirps
    Enable_continuous_transmit_and_receive()
    Set_ADC_to_continuous_sampling()

    // 2. Main Sensing Loop (repeat while hovering)
    WHILE (drone_is_hovering_stably)

        Collect_raw_samples_for_10_to_20_seconds()   // Buffer of baseband Doppler data

        // Simple onboard processing
        Remove_DC_offset_and_noise()
        Bandpass_filter(0.8 Hz to 2.5 Hz)            // Isolate heartbeat band

        Perform_FFT_on_filtered_data()
        Find_strongest_frequency_peak_in_heartbeat_band()

        Convert_peak_frequency_to_BPM()             // BPM = peak_freq_Hz * 60

        IF (signal_quality_is_good)
            Send_heart_rate_BPM_to_drone_telemetry()
        END IF

        Wait_a_few_seconds_before_next_measurement()  // e.g., update every 10 s

    END WHILE

END
```
## References
[1]https://www.cert-la.com/downloads/education/english/start.pdf

[2]https://www.law.cornell.edu/cfr/text/47/15.255
  
[3]https://www.infineon.com/cms/en/product/evaluation-boards/demo-bgt60utr11aip/  
  
[4]https://www.infineon.com/dgdl/Infineon-UG155750_Radar_Baseboard_MCU7_Plus-UserManual-v01_10-EN.pdf?fileId=8ac78c8c88704c7a01888bb70e617c92  
  
[5]https://www.infineon.com/dgdl/Infineon-UG091947_BGT60UTR11AIP_shield-UserManual-v02_00-EN.pdf?fileId=8ac78c8c88704c7a01888bade09f7c8b  

[6]https://www.infineon.com/dgdl/Infineon-BGT60UTR11AIP-DataSheet-v01_00-EN.pdf?fileId=8ac78c8c88ae21230188d3eb8b9307b3    

[7][2025_Radar_Challenge_DynamicHR.pdf](https://github.com/user-attachments/files/17950353/2025_Radar_Challenge_DynamicHR.pdf)  

[8][UK Distributor Demo Kit listing](https://uk.farnell.com/infineon/demobgt60utr11aiptobo1/demo-board-radar-sensor/dp/4410806)
  
[9]https://pmc.ncbi.nlm.nih.gov/articles/PMC9104941/#B29-sensors-22-03106


