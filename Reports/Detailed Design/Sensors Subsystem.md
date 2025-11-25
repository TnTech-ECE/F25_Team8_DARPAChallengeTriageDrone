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
  - The system MUST not exceed a Effective Isotropic Radiated Power (EIRP) of 10 dBm as per the standard the Federal Communications Commission (FCC) has dictated [2].
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
![Screenshot 2024-11-27 at 14-13-56 Radar Baseboard MCU7 Plus - Infineon-UG155750_Radar_Baseboard_MCU7_Plus-UserManual-v01_10-EN pdf](https://github.com/user-attachments/assets/539a4d73-efa8-49ba-b2a5-1d3741bd2c0d) [4]
### The Infineon BGT60UTR11AIP Shield
![Screenshot 2024-11-27 at 14-15-46 BGT60UTR11AIP shield - Infineon-UG091947_BGT60UTR11AIP_shield-UserManual-v02_00-EN pdf](https://github.com/user-attachments/assets/dbb881b1-d0e5-415a-84e5-36553a94b0ad) [5]
### The Shield on the MCU
![BGT60UBOARD](https://github.com/user-attachments/assets/f1d708ee-65c7-43d5-9d63-6a0106a353eb) [5]

## Conceptual Schematic
![Screenshot 2024-11-27 at 14-24-46 BGT60UTR11AIP - Infineon-BGT60UTR11AIP-DataSheet-v01_00-EN pdf](https://github.com/user-attachments/assets/055f3a14-bc56-4fa8-a496-5f588c475fac)
 [6]

## Operational Flowchart
![Drawing 3-1(1)](https://github.com/user-attachments/assets/b36b84c4-8f24-4b3e-ab12-278e8f50576c)


## BOM
Since the majority of the engineering required for this subsystem is operation and not construction, there are only two required pieces of equipment.

| PART NUMBER            | DESCRIPTION     | MANUFACTURER NAME | QUANTITY | COST PER ITEM | TOTAL COST OF QUANTITY |
| :---:                  | :---:           | :---:             | :---:    | :---:         | :---:                  |
 DEMOBGT60UTR11AIPTOBO1               | [Infineon Demo BGT60UTR11AIP](https://www.seeedstudio.com/reComputer-J1020-v2-p-5498.html](https://www.infineon.com/cms/en/product/evaluation-boards/demo-bgt60utr11aip/)) | Infineon | 1 | $177.37 | $177.37|
| 7T9MV4              | [Micro-USB Cable](https://www.digikey.ee/en/products/detail/analog-devices-inc/ADXL203EB/665382](https://www.amazon.com/Amazon-Basics-Charging-Transfer-Gold-Plated/dp/B07232M876/ref=sr_1_1_ffob_sspa?crid=3NYG1TYD80F2E&dib=eyJ2IjoiMSJ9.BTH-JaqRBvQbWEP_82nsg3yEMXYNI64nU1zKdoVJWozaRJLjffc2AxH49bpUSKMxRmhycVZ-cl4f3JYFXJR7O-3Ep6gIb74Q28Zai-27w_6wIuGL0XXqfFrfD50MVW2j8NuEYlM7A9VtHiTLiQdeKxmE8xwIcwvhPZrYZnz8vqIc6Mny7I9Ial4L6WIZNb2fiShtVv-b9LdoFAx3AEaVMsWlQ0dKs3R5FriiQQhb82U.-ba0OBlMVvDP-XYOVvnkis2BssC956V1D6XXpyLtQnw&dib_tag=se&keywords=microusb%2Busb%2Bcable&qid=1732739767&sprefix=microusb%2Caps%2C107&sr=8-1-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9hdGY&th=1)) | Amazon | 1 | $7.59 | $7.59 |

## Analysis
There are multiple ways to read the heart rate and respiration rate of a patient using radar. IEEE Xplore has reported at least 2200 papers on this topic [6], and the interest in this challenge has continued to this day. Researching what to use to fulfill the roles of this subsystem was challenging as there are truly many options to choose from. However, the Infineon BGT60UTR11AIP and the MCU7 Plus are feature rich and are capable of abiding by the previously mentioned constraints and fulfilling the previously mentioned specifications.  

Many projects have utilized continuous wave radars for vitals sesing; however, this introduces a limitation in that CW radars can only detect phase differences in its readings. The Infineon radar sensor is a Frequency Modulated Continuous Wave radar, which means that on top of detecting phase changes it can detect frequency changes as well [7]. This gives the signal processor more data to work with which can lead to greater precision.

The solution is low-cost and small enough, both in volume and in mass, to fit the constraints.The other systems will not suffer from the Infineon device's power consumption either as it boasts a fairly low power consumption when in use; upon initialization the sensor draws around 149 mA, 3.2 mA in idle, and between 110 mA and 220 mA while active, though typical consumption is around 174 mA. With an operating voltage of around 1.8 V and calculating using (1) this leads to a maximum power draw of 396 mW and a typical draw of around 313 mW. These figures are based on the BGT60UTR11AIP datasheet from Infineon [8].

$$
P = I \cdot V \tag{1}
$$

The device has a range of 15m, which is more than enough to meet the proposed specification. In addition, because the radar sensor operates in the 60 GHz band, namely 57.4 GHz minimum to 63.0 GHz maximum, it is considered a mm-Wave radar device. This means that it can detect changes within a few millimeters, which is ideal for heart rate detection as a heartbeat causes displacement in this scale.  

The Infineon radar is also a safe solution for patients. Using the relationship in (2), numbers from the sensor datasheet [8], and assuming negilgible losses, effective isotropic radiated power (EIRP) is found to be $EIRP (dBm) = P_{\text{TX}} + G_{\text{TX}} - L = 5.0\,\text{dBm} + 3.0\,\text{dBi}- 0 = 8.0\,\text{dBm}$. Given that the FCC sets the power limit for this band at 10 dBm, the BGT60UTR11AIP meets the FCC's EIRP standard for sensors operating in the 60 GHz band. Plainly, the power output of the radar is low, and patients subjected to the sensor will not be hit with harmful levels of radiation.  

$$
EIRP (dBm) = P_{\text{TX}} + G_{\text{TX}} - L \tag{2}
$$
  
Lastly, the added MCU7 Plus provides users with the ability to use Infineon's radar SDK. It is capable of some on-board processing that allows for the data to be acquired in different modes (FMCW or CW) as well as to what measure would a user like the data to already be processed. One can obtain completely raw data from the device, but the board and SDK also allows users to receive data in specifically organized objects or classes so further processing is simplified.
Users can opt to receive raw data or organize the data into objects or classes to simplify later processing. This advantage allows for quicker development through flexibility, and this will simplify part of the data processing for the signal processing system.

As a side note, this is a single-input single-output sensor, meaning it has only one TX and one RX pin. Having multiple RX pins allow for the ability to determine the angle of the object in question; however, there is no reason to believe that this capability could provide further use in calculating a heart and respiratory rate.

## References
[1]https://www.cert-la.com/downloads/education/english/start.pdf

[2]https://www.federalregister.gov/documents/2023/07/24/2023-15367/fcc-empowers-short-range-radars-in-the-60-ghz-band  
  
[3]https://www.infineon.com/cms/en/product/evaluation-boards/demo-bgt60utr11aip/  
  
[4]https://www.infineon.com/dgdl/Infineon-UG155750_Radar_Baseboard_MCU7_Plus-UserManual-v01_10-EN.pdf?fileId=8ac78c8c88704c7a01888bb70e617c92  
  
[5]https://www.infineon.com/dgdl/Infineon-UG091947_BGT60UTR11AIP_shield-UserManual-v02_00-EN.pdf?fileId=8ac78c8c88704c7a01888bade09f7c8b  
  
[6][2025_Radar_Challenge_DynamicHR.pdf](https://github.com/user-attachments/files/17950353/2025_Radar_Challenge_DynamicHR.pdf)  
  
[7]https://pmc.ncbi.nlm.nih.gov/articles/PMC9104941/#B29-sensors-22-03106

[8]https://www.infineon.com/dgdl/Infineon-BGT60UTR11AIP-DataSheet-v01_00-EN.pdf?fileId=8ac78c8c88ae21230188d3eb8b9307b3  

