# Power & Safety Detailed Design

This document analyzes how power will be safely distributed throughout the drone system. It will outline the constraints and specifications required for function. An estimation of battery life will be performed to ensure reasonable flight time capabilities. 


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
The battery will need to have its positive and negative terminals split in two directions. One direction will be the Aurelia X4 and will require a larger gauge of wire than the other direction, to the buck converter. This is achievable through a terminal block splitting the 2 battery leads into 4.

The buck converter may connect to the terminal block with 17AWG wire, as its ampacity is 2.9 A for power transmission, over double the expected 1.2 A maximum **[4]** (27 W max buck converter power usage (calculated under Jetson Nano Usage), 22.2 V supply ⇒ 26 W/22.2 V = 1.2 A). The drone shall use the stock connector to the battery for simplicity and cost.

#### Implementation
Partway through the wire between the battery and the connector several cuts will be made (after fully discharging the battery). First, each line will be separated into two parts - one part with the connector to the drone and the other part with the battery. One part of each line will then be cut again to make a short length of wire so as to bridge 2 terminals each on the terminal block and effectively split the wire. 

The connection from the battery to the terminal block will be made with the battery side of the spliced wire. 

The connection between the drone and the terminal block will be made with the connector side of the split wire.

The connection from the terminal block to the buck converter will be made with the aforementioned 17AWG wire.

To power the Jetson Nano, a barrel jack cable will have its wire cut and stripped at the end and its live and neutral lines will be connected to the Vout and PGND pins respectively on the buck converter. 

The fuse will connect directly to the terminal and on its other end will be the positive side battery lead. The reverse current protection module will be inline on the neutral side battery lead.

Every connection outside of the insulated **[7]** terminal block will be covered in heat shrink so as to insulate the circuit and mitigate the risk of electrical shock. The chassis will hold the components securely in a manner which will not strain connections nor provide an opportunity for a loose wire to be caught; collaboration with that subsystem will be required.


## Part Specifications

#### LiPo Battery Module **[1]**
* Lithium-ion polymer, lightweight and high-capacity construction
* Sustains 22.2 V
* 10,000mAh capacity
* 15C discharge rate ⇒ 150 A maximum output with its capacity
#### Reverse Polarity Protection Module **[6]**
* 60 A maximum current
* 40 V maximum reverse voltage
* 1 mΩ on-resistance, negligible power loss at the &lt;30 A expected to go through the module
#### Littelfuse 0298060 60A Fuse **[5]**
* 32 V maximum voltage
* Breaks circuit (and itself) at 60 A
#### Screw Terminal Block Strip **[7]**
* 8 insulated screw terminals with 4 positions
* 600 V maximum voltage
* 60 A maximum current
#### TPS56637 Step-Down Voltage Converter (Buck Converter) **[3]**
* 4.5-28 V input, 0.6-13 V output
* 6 A maximum continuous output current
* 92% efficiency at 2 A out
* At 12 V and 2 A as will be used in this application, approx 2 W heat is generated (26 W total calculated in Jetson Nano Usage under Power sinks minus 24 W total from the Jetson Nano itself). With airflow from the moving drone, dissipating 2 W of heat should naturally occur. Coordination with the chassis subsystem will be required to ensure it gets that airflow from the rotors, preferably, or from simply having a path for air to flow to it through the chassis.
#### Jetson Nano SBC **[2]**
* DC barrel jack powering the Nano supports 12 V at 2 A nominally. No other relevant information is listed in the documents, but given that the buck converter supports up to 6 A transient power increases should be supported.
#### Aurelia X4 Drone **[1]**
* No information on this power consumption past an average that can be calculated using flight time and standard battery capacity
* Estimate that it pulls an average of 24 A and consumes an average of 533 W (calculated in Base Drone Usage under Power Sinks)
* &gt;30 A overhead through power infrastructure for transient power usage increases, but **testing should be done regardless** when the drone is available in the seemingly unlikely (however possible, Murphy's Law) event that the rotors and other draws on the drone pull approx &ge;60 A under extreme usage scenarios.

## Power Sinks

#### Jetson Nano Usage
All peripherals will be sourcing all of their power from the Nvidia Jetson Nano. This SBC takes in a maximum of 2A at 12V **[2]**, or 24W total. The 22.2V to 12V buck converter is nominally approximately 92% efficient at 2 A out **[3]**, so both parts will use 24W/0.92 = **26W maximum**.

#### Base Drone Usage 
Using the maximum flight time and battery capacity **[1]**, we can approximate the current draw as: 10Ah/\[25 minutes/(60 minutes/hr)] = 24A.
This current draw at 22.2V is approximately **533W**.

#### Relative Power Consumption
\[533W/(533W+26W)]⋅100% = 95.3% of the power goes to the drone ⇒ 4.7% of the power goes to the Jetson Nano and buck converter. From this information, we can assume that the maximum flight time will not significantly decrease with the added components; around (25 mins ⋅ 95.3% = 23.8 mins, rounding down for a more certain minimum flight time) **20 minutes of flight time** should be expected considering the extra load on the drone both directly through power consumption by the microcontroller and peripherals and indirectly through the added weight of the parts.


## Power Tree

![Drone Power Tree](https://github.com/TnTech-ECE/F25_Team8_DARPAChallengeTriageDrone/blob/aa0dc53c5409cec489e5b653b28f1e0dc82d3b92/.github/images/powertree.png?raw=true "Drone Power Tree")


## Wiring Diagram
![Drone Wiring Diagram](https://github.com/TnTech-ECE/F25_Team8_DARPAChallengeTriageDrone/blob/aa0dc53c5409cec489e5b653b28f1e0dc82d3b92/.github/images/WiringDiagram.drawio.svg?raw=true "Drone Wiring Diagram")

## Interface With Other Subsystems

#### Weight Distribution
* The buck converter, fuse, polarity protector, terminal block, and added connections will add to the drone which will be an important consideration when balancing the drone and creating a chassis to hold the parts.


## References
**[1]** [Aurelia X4 Specifications](https://uavsystemsinternational.com/products/aurelia-x4-standard)\
**[2]** [Jetson Nano Specifications](https://www.seeedstudio.com/reComputer-J1020-v2-p-5498.html)\
**[3]** [Buck Converter Datasheet](https://www.ti.com/lit/ds/symlink/tps56637.pdf)\
**[4]** [Max Current for Wire Gauge](https://www.powerstream.com/Wire_Size.htm)\
**[5]** [Fuse Specifications](https://www.amazon.com/Littelfuse-0298060-Bolt-Down-Delay/dp/B01M6UA7BZ)\
**[6]** [Reverse Polarity Protection Specifications](https://www.fruugo.us/reverse-polarity-protection-module-300a-mosfet-60a-dual-channel-ultra-low-resistance-battery-protector/p-458434232-966043862)\
**[7]** [Screw Terminal Block Strip](https://www.newegg.com/p/2YK-005A-006C4)
