# Power & Safety Detailed Design

This document analyzes how power will be safely distributed throughout the drone. It will outline the constraints and specifications required for function. An estimation of battery life will be performed to ensure reasonable flight time capabilities. 

This is an unfinished version of the document; not enough information is known at this time to have a particularly in-depth solution and power analysis.


## Constraints & Specifications

### Constraints
1. The power MUST last for at least 10 minutes.
2. The power draws MUST NOT be overloaded with voltage or current. 
3. All conductors MUST be insulated and impossible to short for safety. 

### Specifications
1. Power SHALL be routed as efficiently and with as light components as is possible for maximum flight time.
2. Power SHALL be sourced from the standard 22.2V 15C 10,000 mAh drone battery for all components.
3. Power SHALL be delivered to the Jetson Nano via barrel jack.


## Proposed Solution

#### Voltage Correction
The Nvidia Jetson Nano will have its power sourced from the **22.2V** 15C 10,000 mAh battery **[1]**. The microcontroller can only accept **12V** at 2A **[2]**. A step-down converter is required to supply the correct voltage to the Nano. 

The **TPS56637 Buck Converter** has a maximum Vin of 28V, a maximum Vout of 13V, and a maximum current of 6A **[3]**. A similar buck converter may be what is actually used, depending on what is available. In any case, this converter fits the specifications to step down the voltage for the Jetson Nano. 

#### Connections
The battery will need to have its positive and negative terminals split in two directions. One direction will be the Aurelia X4 and will require a larger gauge of wire than the other direction, to the buck converter. 

The buck converter may connect to the battery with approximately 26AWG wire, as its ampacity is 2.2A for simple chassis wiring **[4]**. The drone shall use the stock connector to the battery for simplicity and cost.

#### Implementation
Partway through the wires between the battery and the connector, the insulation on the wires shall be cut (after fully discharging the battery) to allow the 26AWG to make a solid connection. It shall hold its connection (and remain insulated after the original insulation's removal) with electrical tape after the copper threads in the 26AWG are securely wrapped around it.

The other ends of this 26AWG will connect to the Vin and PGND pins on the buck converter.

To power the Jetson Nano, a barrel jack cable will have its wire cut and stripped and its live and neutral lines will be connected to the Vout and PGND pins respectively on the buck converter.


## Power Sinks

#### Jetson Nano Usage
All peripherals will, at the time of writing, be sourcing all of their power from the Nvidia Jetson Nano. This microcontroller takes in a maximum of 2A at 12V **[2]**, or 24W total. The 22.2V to 12V buck converter is nominally approximately 90% efficient **[3]**, so both parts will use 24W/0.9 = **27W maximum**.

#### Base Drone Usage 
Using the maximum flight time and battery capacity **[1]**, we can approximate the current draw as: 10Ah/\[25 minutes/(60 minutes/hr)] = 24A.
This current draw at 22.2V is approximately **533W**.

#### Relative Power Consumption
\[533W/(533W+27W)]⋅100% = 95.2% of the power goes to the drone ⇒ 4.8% of the power goes to the Jetson Nano and buck converter. From this information, we can assume that the maximum flight time will not significantly decrease with the added components; around **20 minutes of flight time** should be expected considering the extra load on the drone both directly through power consumption by the microcontroller and peripherals and indirectly through the added weight of the parts.


## Power Tree

![Drone Power Tree](https://github.com/TnTech-ECE/F25_Team8_DARPAChallengeTriageDrone/blob/wewheeler42-patch-1/.github/images/image.png?raw=true "Drone Power Tree")


## Interface With Other Subsystems

#### Weight Distribution
* The buck converter and added connections will add mass to the drone which will be an important consideration when balancing the drone.


## References
**[1]** [Aurelia X4 Specifications](https://uavsystemsinternational.com/products/aurelia-x4-standard)\
**[2]** [Jetson Nano Specifications](https://www.seeedstudio.com/reComputer-J1020-v2-p-5498.html)\
**[3]** [Buck Converter Datasheet](https://www.ti.com/lit/ds/symlink/tps56637.pdf)\
**[4]** [Max Current for Wire Gauge](https://www.powerstream.com/Wire_Size.htm)
