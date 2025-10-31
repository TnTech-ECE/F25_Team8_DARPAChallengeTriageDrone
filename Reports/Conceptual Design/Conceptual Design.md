# Team 8 - DARPA Triage Drone Conceptual Design

## Introduction
Aviation drones are useful tools in the modern age for scanning areas too difficult or dangerous for first responders to effectively search. These drones may assist in assessing the severity of an emergency and the conditions and locations of victims by leveraging on-board sensors and algorithms, allowing first responders to effectively triage the victims of a disaster. For minimum use of responders’ time, a drone could be semi-autonomous as well, automatically routing to victims and relaying their positions and conditions with little human input. Drones with these capabilities would save responders’ extremely valuable time and resources, saving lives in the process. Currently, no drones have the capability to analyze and prioritize victims of disasters by severity of injury, which is something the Defense Advanced Research Projects Agency (DARPA) has created a challenge to address **[[1](#References)]**.      

In search and rescue (SAR) operations, these drones could provide a semi-autonomous initial canvassing of an area to determine locations of human casualties and assess victims’ injuries and conditions. This could then be followed up with a helicopter and/or ground medical team to efficiently distribute aid to those most in need of it. This proposal will outline a project focused on designing and building a drone to meet these objectives. In the coming sections of this proposal, the more specific goals and objectives will be expanded upon as well as the specifications and constraints that the team will work around. The team will also examine current solutions to this problem and other approaches and then provide an argument of why this project is more effective than other contemporary solutions. 

## Restating the Fully Formulated Problem
The problem proposed is to develop a system capable of semi-autonomously flying and identifying victim(s) in emergency situations while measuring vital signs such as heart rate, respiratory rate, and cognitive responsiveness. The system must then relay this information to the user and rank the victim(s) according to the START triage method. To define the scope of the problem, the project follows the scenario established by the Fall 2024 Capstone team as outlined by their customer.        

    An individual has been working on a powerline when suddenly the powerline comes crashing down.  
    The individual is unresponsive and paramedics cannot get to the individual due to the active powerline.   
    The triage drone will be used to fly 20' away to the downed individual, attempt to communicate with the individual, 
    and read their vitals.   
    The powerline and the individual are in a clear field with no wind on a clear day.   

The acting customer, Mr. Christopher Johnson, has requested the introduction of additional variations to the test scenario to assess the adaptability of the drone system. These variations include conditions of limited visibility, such as fog or smoke, and the presence of wind within a defined range on the Beaufort scale.        

Since the project is inherited from the Fall 2024 Capstone team, the core specifications remain unchanged. The project operates under a limited set of constraints, which are detailed below along with their respective reasoning and reference standards:        

1. The drone SHALL be user-friendly. 

2. The drone SHALL have an integrated security system. 

3. The drone SHALL remain under 400 ft above ground level **[[2](#References)]**.  

4. The drone SHALL not exceed 100 mph **[[2](#References)]**.  

5. The drone SHALL be equipped with anti-collision lighting **[[2](#References)]**.  

6. The drone SHALL measure heart and respiratory rates by detecting vibrational frequencies of the heart and lungs in hertz, using Doppler sensing technology. 

7. The drone SHALL utilize encrypted wireless communication conforming to IEEE 802.11 standards for control and data transmission **[[3](#References)]**.  

8. The EMI test setup SHALL maintain all measurement tolerances within the limits specified by MIL-STD-461G § 4.3.1 **[[4](#References)]**.  

9. The system SHALL operate with semi-autonomous functionality equivalent to SAE J3016 Level 3 autonomy **[[5](#References)]**.  

## Comparative Analysis of Potential Solutions

### 1. Drone Design
  The drones considered for the solution: **Multi-Rotor Drone** & **Hybrid Drone**.

#### **Aurelia X4 Standard** **[[6](#References)]**
![Drone1](https://github.com/TnTech-ECE/F25_Team8_DARPAChallengeTriageDrone/blob/main/Reports/Conceptual%20Design/Drone%201.png)
   

**Description:** A light-framed, quad-rotor drone, open-source drone with path finding capabilities.  
**Pros:** High Payload Capacity, Vertical Takeoff and Landing Capability, Improved Control and Stability, Maneuverability, includes GPS and LiDAR, Versatile, and Open Source ArduPilot . 
**Cons:** No Horizontal Obstacle Sensor, Limited Flight Time.  

#### **Parrot ANAFI Ai** **[[7](#References)]**    
![Drone 2.image](https://github.com/TnTech-ECE/F25_Team8_DARPAChallengeTriageDrone/blob/main/Reports/Conceptual%20Design/Drone%202.jpg)      

**Description:** A compact drone with built-in obstacle avoidance cameras chosen and used by the previous capstone team.   
**Pros:** Already in our possession, WIFI Capabilities, Has Obstacle Avoidance Capabilities, and has a Compact Design.   
**Cons:** Damaged as is, Limited Payload, Limited Flight Time, and Closed Hardware System.   

#### Drone Design Solution: 

Looking at the pros and cons between the X4 and the ANAFI, the X4 seems to be the better choice for this project’s needs. While the ANAFI seems more polished, has some semi-autonomous capability, and includes several cameras, these systems are not easily modified by an outside system. Parrot did not intend for there to be an additional payload or system to be strapped to the ANAFI. This is where the X4 shines. It is made with the express purpose of carrying a payload, and it is much more open to modification than the other drone. This versatility from the X4 is extremely useful for our uses, so after much deliberation, the X4 is the drone that is the better choice for this project. 

*The photos above are for reference*

### 2. Computing Systems   
The computing systems considered were a **Raspberry Pi** and a **NVIDIA Jetson Nano** for the triage sensor system.    

#### **Raspberry Pi**    
![Pi.image](https://github.com/TnTech-ECE/F25_Team8_DARPAChallengeTriageDrone/blob/main/Reports/Conceptual%20Design/Pi.png)  

**Description:** Small, Low-Cost Computing Device.    
**Pros:** Cost-Friendly, Compact Size, Customizable, Low Power Consumption, and Versatility.    
**Cons:** Low-Performance Capabilities, Limited storage, Overheating, and Limited Connectivity.    

#### **NVIDIA Jetson Nano** 
![Jetson.image](https://github.com/TnTech-ECE/F25_Team8_DARPAChallengeTriageDrone/blob/main/Reports/Conceptual%20Design/Jetson.png)

**Description:** Small, powerful, and comprehensive computing system.    
**Pros:** AI capabilities, High performance, Expandable Storage, Graphics processing optimization, and Multiple I/O options.    
**Cons:** Power Consumption, Larger Size, Lack of built-in Wi-Fi, Complexity, and High Cost.    
  
#### Computing Systems Solution:
Considering both the Raspberry Pi and the NVIDIA Jetson Nano, the Jetson Nano is the best solution for a computing system. With its high-performance capabilities in graphics processing,  it is a necessity due to the on-board camera that will be used during triage. It also allows for more I/O options compared to the Raspberry Pi, making it the essential choice considering the number of sensors and systems needed for timely and accurate triage. Despite the higher cost of the Jetson Nano, it is capable of maintaining the project budget with the Jetson Nano, making it the clear choice.   

### 3. Controller Systems
The controller options were the **Default Drone Controller**, a **Mobile Device**, or a **PC System**.

#### **Default Drone Controller**
![Controller.image](https://github.com/TnTech-ECE/F25_Team8_DARPAChallengeTriageDrone/blob/main/Reports/Conceptual%20Design/Controller.png)

**Description:** It comes with the drone and is therefore low-cost, has less than ten buttons, and is handheld.    
**Pros:** Pre-Programmed, Cost-Friendly, Simple to Use.    
**Cons:** Not Flexible, No Display, Not Modifiable.    

#### **Mobile Device**
![Phone.image](https://github.com/TnTech-ECE/F25_Team8_DARPAChallengeTriageDrone/blob/main/Reports/Conceptual%20Design/Phone.png)

**Description:** A handheld, either a dedicated or personal device that can interact with the drone controls through the drone' default web APIs with moderate modifiability.    
**Pros:** Flexible, Potentially Cost-Friendly, Easy to Carry, Modifiable.    
**Cons:** Difficult to handle due to small display, Can't be easily used to program drone, Many potential device models.    

#### **PC System**
![PC.image](https://github.com/TnTech-ECE/F25_Team8_DARPAChallengeTriageDrone/blob/main/Reports/Conceptual%20Design/PC.png)

**Description:** Either a dedicated or personal device that can interact with the drone controls through the drone's default web APIs with high modifiability.    
**Pros:** Flexible, Potentially Cost-Friendly, Easy to Program, Provides more Buttons to Interface with.    
**Cons:** Large, Less Intuitive, Many potential device models.    

#### Controller Systems Solution:    
Due to the higher capabilities of a modern day personal computer, it is the ideal solution for this project. It will provide the most potential for how the drone can be controlled while keeping an adequate control system for the operator. It will be less intuitive than the other possibilities, but that can be mitigated. The other options are simply too limiting, especially since it will not only be the drone that is controlled by the operator, but also the radar, speaker, and mic.     

### 4. Path Finding / Obstacle Detection Systems - Radar    
The radar sensors considered were the Texas Instruments IWR6843AOPEVM, Ainstein US-D1 Pro Extended-Range Radar Altimeter, and Infineon DEMO BGT60TR13C.     

#### **Texas Instruments IWR6843AOPEVM**    
![Radar 1.image](https://github.com/TnTech-ECE/F25_Team8_DARPAChallengeTriageDrone/blob/main/Reports/Conceptual%20Design/Radar%201.png)    

**Description:** A 60–64 GHz mmWave radar sensor evaluation module featuring a single-chip solution for object detection, range estimation, and velocity measurement. It integrates transmitters, receivers, DSP, and MCU cores for autonomous processing, supporting up to 4 GHz bandwidth and onboard antennas.     
**Pros:** High range resolution, integrated processing (no external MCU required), low power consumption, compact FR4 antenna design, and strong SDK/software support (mmWave SDK, Radar Toolbox).     
**Cons:** Limited field of view compared to some alternatives (±60° typical), short-to-medium detection range (~50 m), requires software configuration expertise, and lacks environmental protection for outdoor all-weather operation.     

#### **Ainstein US-D1 Pro Extended-Range, All-Weather Radar Altimeter**    
![Radar 2.image](https://github.com/TnTech-ECE/F25_Team8_DARPAChallengeTriageDrone/blob/main/Reports/Conceptual%20Design/Radar%202.png)    

**Description:** An industrial-grade radar altimeter designed for UAVs and robotics, operating in 60 GHz band with advanced FMCW radar processing. Optimized for ground altitude and obstacle proximity detection in all-weather conditions (rain, fog, dust, snow).     
**Pros:** Extended detection range (up to 50 m+), high precision (< 2 cm), robust against environmental interference, ready-to-use hardware (IP67 housing), and plug-and-play interfaces (UART/CAN).     
**Cons:** High cost, limited modifiability, primarily designed for altitude sensing (not lateral obstacle mapping), and lower availability of open-source SDKs.     

#### **Infineon DEMO BGT60TR13C**
![Radar 3.image](https://github.com/TnTech-ECE/F25_Team8_DARPAChallengeTriageDrone/blob/main/Reports/Conceptual%20Design/Radar%203.png)    

**Description:** A 60 GHz radar transceiver demo board featuring 3 transmit and 4 receive antennas for 3D motion and presence sensing. Supports range-Doppler imaging, angle estimation, and can detect multiple objects simultaneously with an on-board microcontroller interface.    
**Pros:** High sensitivity and multi-target capability, wide field of view (≈120°), suitable for short-range mapping (< 20 m), excellent documentation and software tools (Radar Fusion GUI, MATLAB SDK), and strong community support.    
**Cons:** Shorter detection range than US-D1 Pro, requires USB/host interface for processing, not weatherproof, and higher power consumption during full operation.    

#### Path Finding / Obstacle Detection for Radar Solution:     
Considering the three radar sensors, the Texas Instruments IWR6843AOPEVM offers the best balance between capability, integration, and flexibility for drone-based pathfinding. Its onboard processing and SDK tools make it adaptable for autonomous obstacle detection and environment mapping, while maintaining reasonable cost and power efficiency. This sensor is the most practical and integrated radar solution for real-time obstacle detection and pathfinding in the drone system.     

### 4. Path Finding / Obstacle Detection Systems - LiDAR    
The LiDAR sensors considered were the RPLIDAR A1M8 and the Unitree 4D LiDAR L2.     

#### **RPLIDAR A1M8**    
![Lidar 1.image](https://github.com/TnTech-ECE/F25_Team8_DARPAChallengeTriageDrone/blob/main/Reports/Conceptual%20Design/Lidar%201.png)    

**Description:** A cost-effective 2D LiDAR (360° horizontal scan) by SLAMTEC designed primarily for indoor mapping, robotics navigation and obstacle detection.     
**Pros:** Provides full 360° omnidirectional scanning in a compact, lightweight, and affordable design. Has a moderate 12 m detection range suitable for small-scale mapping and navigation. Easily integrates with common interfaces such as UART or USB for quick prototyping. Consumes low power, making it ideal for mobile and battery-driven platforms.     
**Cons:** Limited to 2D plane detection, missing obstacles above or below the scan height. Operates best indoors since bright light or outdoor conditions reduce performance. Offers a slower scan rate (~5.5 Hz), limiting performance on fast-moving platforms. Has a relatively short range compared to advanced LiDAR options.   

#### **Unitree 4D LiDAR L2**      
![Lidar 2.image](https://github.com/TnTech-ECE/F25_Team8_DARPAChallengeTriageDrone/blob/main/Reports/Conceptual%20Design/Lidar%202.png)    

**Description:** An advanced 4D LiDAR offering 360° horizontal and 96° vertical scanning for full-environment 3D mapping and obstacle detection.     
**Pros:** Covers a full 360×96° field of view, enabling detection of obstacles from all angles. Delivers high point density for precise environment reconstruction and SLAM applications. Reaches up to 30 m range, allowing for mid- to long-range obstacle detection. Includes built-in IMU and is designed for seamless 3D navigation integration.     
**Cons:** Costs significantly more than entry-level LiDARs, increasing project budget. Generates large data volumes requiring a powerful processor for real-time use. Outdoor performance may still degrade under extreme lighting or weather conditions. Requires more careful integration due to its higher complexity and power needs.   

#### Path Finding / Obstacle Detection for LiDAR Solution: 

For the pathfinding and obstacle detection subsystem, the team has decided that a LiDAR sensor will be implemented due to its superior spatial resolution, precision, and environmental mapping capabilities compared to other sensor types. However, the specific model has not yet been finalized as the selection depends on budget availability, integration complexity, and performance trade-offs. 

The RPLIDAR A1M8 offers a cost-effective and lightweight option suitable for short-range 2D mapping in controlled environments, making it ideal for early testing and prototyping. On the other hand, the Unitree 4D LiDAR L2 provides a more advanced 360° × 96° 3D scanning capability with a longer 30 m range and higher point density, which would significantly enhance obstacle detection and situational awareness but at a higher cost and processing demand. 

### 5. Human Finding Systems 

#### **LWIR Camera**
![IR.image](https://github.com/TnTech-ECE/F25_Team8_DARPAChallengeTriageDrone/blob/main/Reports/Conceptual%20Design/IR.png)

**Description:** Longwave infrared camera module that is smaller than a dime and cost-effective. Modules have enabled thermal innovation and can depending on the module, offer either 80x60 (17 µm) or 160x120 (12 µm) pixel resolution, absolute temperature output, multiple field-of-view (FOV) options, and an expanded scene dynamic range for high-temperature scenes.   
**Pros:** Works in darkness and moderate smoke or fog, low processing demand, Human contrast due to heat, start around $200.   
**Cons:** Cheap models have low resolution, can’t penetrate glass, hot environments will create a lot of noise, good cameras are extremely expensive.   

#### **Radar (Millimeter-Wave)**
![Radar 1.image](https://github.com/TnTech-ECE/F25_Team8_DARPAChallengeTriageDrone/blob/main/Reports/Conceptual%20Design/Radar%201.png)

**Description:** Millimeter wave radar is used to detect objects and measure distance, speed, and motion by transmitting electromagnetic waves and analyzing the reflected signals to identify movement patterns. This method is highly effective for detecting human presence.    
**Pros:** Can sense things through light debris or smoke, unaffected by lighting or weather, very sensitive for presence data.
**Cons:** Lots of noise since it is a good presence detector, low spatial resolution so cannot get shape, can be affected by metallic or reflective objects, better modules are expensive and large.   

#### **RGB Camera + AI Integration**
![AI.image](https://github.com/TnTech-ECE/F25_Team8_DARPAChallengeTriageDrone/blob/main/Reports/Conceptual%20Design/RGB%20Cam%20plus%20ai.png)

**Description:** Combining a standard visual camera with an AI based processing tool on the already acquired Nvidia Jetson can classify Humans and objects in general by using real time camera feed and learning models. 
**Pros:** High resolution and detail, AI flexibility (can use multiple at once), some software is available for free, large range of detection 
**Cons:** High processing power, poor in darker or more obscure environments, harder integration, AI learning curve 

#### Human Finding Solution: 

For the Human-Finding Subsystem, each sensing method offers distinct advantages and limitations, meaning no single approach is universally superior. However, these technologies can complement each other to create a more robust and accurate detection system. 

The team plans to integrate an LWIR (Long-Wave Infrared) camera as the primary sensor, since it provides the most consistent human detection capability across diverse lighting and environmental conditions. Additionally, the Pathfinding/Obstacle Detection team will be implementing an mmWave radar module, which can be integrated with our subsystem to provide initial presence detection, even through fog, debris, or other visual obstructions. The radar data can then be validated and refined using the thermal imagery from the LWIR camera to confirm living targets. 

An existing RGB camera from the previous year’s drone platform will also be leveraged. By incorporating AI-based human detection models using, the RGB feed can serve as a tertiary verification layer, improving classification confidence and reducing false positives. 

Combining LWIR, mmWave radar, and AI-driven RGB vision enables multi-modal data fusion, resulting in a human-finding subsystem that is significantly more accurate, reliable, and adaptable than any single-sensor solution. 

## High-Level Solution

The solution to this problem requires an aviation drone as well as integrated sensors to record data. The drone will be manually flown to the victim and have the ability to hover 1 meter above the target. Attached to the drone will be a sensing system that can measure one's, heart rate and respiratory rate, and cognitiveness all without contacting the individual. The data gathered by the sensors will then be sent to the computing system. The information will be processed and the person will be categorized by severity of injuries in accordance with the START method, which is gone into further detail in the START Adult Triage Method section[4]. 

In order to do this, the design will be split up into devices:

**1. Power device <br />**
- A battery will be used to supply all necessary power to each device along with voltage regulators to adjust the voltage to the required amount for each sensing device. The battery will be the input to the voltage regulator circuit. The output of the regulator circuit will be wired to the heart rate / respiratory rate doppler, the voice detection system, and the computing system. 
        
**2. Signal Processing <br />**
- This processing unit (Jettson Nano) will process the data received from the microphone as well as the data from the heartbeat and respiratory doppler. The information will then be compared to the START triage method and the results will be wirelessly transmitted to the user interface. The processing unit will have serial or digital input lines coming from the doppler radar as well as an analog input line coming from the microphone. It will have a wireless radio frequency output going to the user control device. 
        
**3. User Control <br />**
- After the signals are processed the information will be sent to a telecommunication device that will transmit the victim's vitals as well as triage level back to the user. The information will be shown on an LCD display at the controller. This device will have one radio frequency signal input that comes from the signal processing device. 
    
**4. Cognitive test device <br />**
- The user will have a button to allow a procedure to occur using a speaker and a microphone. The speaker will send out a call prompt and the microphone will capture audio data and relay it back to the computing system. 
    
**5. Heartbeat/Respiratory doppler <br />** 
- The doppler radar is responsible for obtaining heartbeat and respiratory rate frequencies. The data acquired will also be sent to the computing system. 

**6. Path Finding / Obstacle Detection  <br />**
- This system will use the Texas Instruments IWR6843AOPEVM radar to detect and map obstacles in the drone’s flight path. The radar will be mounted at a 45-degree forward-facing angle to sense objects ahead and below the drone. The onboard processing capabilities of the radar will analyze range and velocity data to identify obstacles in real time and transmit the information to the computing system. This allows the control algorithm to adjust the drone’s trajectory dynamically, ensuring safe and efficient navigation in complex environments. 

- In addition to radar, a LiDAR sensor will be integrated into the system to enhance spatial mapping and improve obstacle detection accuracy. The specific LiDAR model has not yet been finalized, as the team is still evaluating options based on budget, processing requirements, range performance, and environmental adaptability. Once selected, the LiDAR will complement the radar by providing high-resolution distance and contour data, enabling more precise navigation and reliable operation under a wider range of conditions. 

**7. Human Finding <br />** 

- The Human-Finding subsystem is responsible for detecting and locating individuals within the drone’s field of operation. This system integrates multiple sensing technologies—Long-Wave Infrared (LWIR) imaging, millimeter-wave (mmWave) radar, and potentially RGB vision enhanced with AI-based detection—to ensure reliable performance in a variety of environmental conditions. 

- The LWIR camera serves as the primary sensor, detecting human heat signatures even in complete darkness or through moderate smoke and fog. It provides strong thermal contrast, allowing the system to identify living individuals with high confidence. Complementing this, the mmWave radar module (Texas Instruments IWR6843AOPEVM) enables detection of motion and presence through visual obstructions such as foliage or debris. Radar readings are used to trigger thermal confirmation from the LWIR camera, minimizing false positives and improving overall accuracy. 

- Additionally, a possible onboard RGB camera integrated with AI will give another layer of classification and visual confirmation. This layer enhances detection precision by using convolutional neural networks (CNNs) to distinguish humans from background objects or false heat sources. 

- By fusing data from radar, thermal, and visual sensors, the Human-Finding subsystem will achieve a high degree of accuracy, reliability, and environmental adaptability. This ensures that the drone can consistently identify and localize victims, providing critical input to the triage and assessment stages of the overall system. 

### Hardware Block Diagram
![Hardware Block Diagram Full.image](https://github.com/TnTech-ECE/F25_Team8_DARPAChallengeTriageDrone/blob/main/Reports/Conceptual%20Design/Block%20Diagram%20-%20Full.png)

![Hardware Block Diagram Computer.image](https://github.com/TnTech-ECE/F25_Team8_DARPAChallengeTriageDrone/blob/main/Reports/Conceptual%20Design/Block%20Diagram%20-%20Computer.png)

![Hardware Block Diagram Drone.image](https://github.com/TnTech-ECE/F25_Team8_DARPAChallengeTriageDrone/blob/main/Reports/Conceptual%20Design/Block%20Diagram%20-%20Drone.png)

The linked document contains the hardware block diagram created in Visio, centering on the drone and the computer. This visual breakdown outlines the division of our systems, focusing on the communication paths and additions between these components. We decided to omit the controller from the diagram, as no modifications are being made to it. As a result, the diagram shows the computer and drone systems. 

### Operational Flow Chart
![Operational Flow Chart.image](https://github.com/TnTech-ECE/F25_Team8_DARPAChallengeTriageDrone/blob/main/Reports/Conceptual%20Design/Operational%20Flow%20Chart.png)


Below is the link to the pdf of the above image. This rudimentary operational flow chart details how a user will operate the final product specific to the decisions he or she makes while using it. 

## Atomic Subsystem Specifications

### **Programmable Drone subsystem**
#### **Connections**
The drone will be wirelessly connected to a controller that flies the drone. 
The drone will also be wirelessly connected to an LCD screen. 
The drone's telecommunication system will be connected to the signal processing system. 

#### **Specifications**
The drone shall accomplish all functionality from at least one meter away from the subject.  
The drone shall be able to operate at full performance for at least 15 minutes.  
The drone shall weigh less than 20 pounds even after the team makes modifications to the drone.  
The drone shall operate during daylight hours on a clear day with no wind.  

#### **Description**
The drone will be bought and be ready to fly. Senors and a processing unit will be added to the drone to expand the capabilities of the drone. The drone will be able to fly to a victim and use the attached sensors to check vitals and cognitiveness and sort the injured person into a triage category. 

![Programmable Drone Subsystem Flowchart.image](https://github.com/TnTech-ECE/F25_Team8_DARPAChallengeTriageDrone/blob/main/Reports/Conceptual%20Design/Programmable%20Drone%20Subsystem.png)


### **Power and Circuitry design subsystem**
#### **Connections**
Power signal to connect the signal processing subsystem

#### **Specifications**
  The power subsystem SHALL supply a minimum voltage of 4.75v and a maximum voltage of 5.25v to power the Jetson Nano and its peripherals. **[[8](#References)]**   
  The power subsystem SHALL supply up to 4A to power the Jetson Nano and its peripherals. **[[8](#References)]**  
  The power subsystem SHALL optimally use the battery on the drone to prevent unnecessary discharge.  
  The power subsystem SHALL not have exposed wiring to ensure safety.  
  The power subsystem SHALL protect client circuits with fuses.  

#### **Description**
The power subsystem will be responsible for converting power from the battery to the signal processing subsystem and other peripherals on the drone. The following flow chart describes the steps to meet the specifications.


<img width="250" alt="power subsystem" src="https://github.com/user-attachments/assets/e48fe624-972f-47ee-875b-66390ba27317">

### **Signal Processing subsystem**
#### **Connections**
  Digital connection to programmable Drone.  
    Digital signal to the doppler sensor.

#### **Specifications**
  The signal processing subsystem SHALL use signal processing to determine heart rate (range 0.45 to 2.92Hz) and respiratory rate (range 0.13 to 1 Hz).    
  The signal processing subsystem SHALL be able to get accurate readings from 1 meter away.  
  The signal processing algorithms SHALL process data and have it ready to transmit within 500ms of being received.    

#### **Description**

The signal processing subsystem carries the heart of the project. It will employ signal processing algorithms to extract useful information about the heart rate and respiratory rate. The subsystem will have to be fast and accurate. The system will connect data to the drone so that the drone can transmit the data back to the pilot. The following flow chart describes the steps to meet the specifications.

<img width="433" alt="Computing system (1)" src="https://github.com/user-attachments/assets/080f6b0c-3eb2-43e6-9002-d479ab09ed63">


### **Vitals' Sensor subsystem**

#### **Connections**
The vitals sensor will be wired to the signal processing subsystem on board the drone. It will be communicating digitally, most likely, via serial communications. It will be sending data to the signal processing subsystem that it has acquired through no-contact radar sensing.

#### **Specifications**
The subsystem SHALL be operational from a distance of at least one meter.    
The subsystem SHALL weigh less than half a pound.  
The subsystem SHALL not pose any threat to its subject.   
The subsystem SHALL obtain the presence of a heartbeat and its frequency (range 0.45 to 2.92Hz).  
The subsystem SHALL obtain the breathing rate and frequency (range 0.13 to 1 Hz).  

#### **Description**
The Vitals Sensors subsystem is dedicated to obtaining accurate readings from each sensor and ensuring that these readings are transmitted effectively to the computer for further analysis. The subsystem comprises of a radar doppler, likely of continuous wave (CW) type. It will send a periodic radio signal and listen for that same signal. Measuring how out of phase the sending and receiving signals are, the subsystem will provide the data required to compute the frequency of the breathing and heart rate of the subject. It will be paired with circuitry to filter noise and other disruptive signals.

![image](https://github.com/user-attachments/assets/0e9d64a5-9dac-4c05-89bc-5f9c991b3add)

### Interfacing Subsystem
#### **Connections**
Wireless connection between drone and client computer.  

#### **Specifications**
This subsystem SHALL display data from the signal processing subsystem onto a laptop screen.   
This subsystem SHALL use the wireless capability of the programmable drone.  
This subsystem SHALL run a program on a laptop that will allow the laptop to connect to the drone.  
This subsystem SHALL display triage results and vitals wirelessly.  

#### **Description**
This subsystem will utilize the programmable nature of the drone to connect to a laptop and display heart rate and breathing rate information onto the screen. This subsystem will need to write a program on the laptop in order to connect to the drone as well. This program should be portable between computer to computer. 

<img width="200" alt="Drawing (1)" src="https://github.com/user-attachments/assets/0d697553-49c6-4af9-b213-ad698e1283d0">

### **Microphone and speaker subsystem**

#### **Connections**
Digital connection to the microphone from the drone.
Digital connection to the speaker from the drone.

#### **Specifications**
The subsystem SHALL ensure two-way communication from the pilot to the victim.    
The subsystem SHALL communicate wirelessly via the drone.    
The subsystem SHALL communicate through a speaker that will output 80 dB SPL.  
The subsystem SHALL give vocal commands using the speaker and listen for responses to evaluate the cognitive ability of a victim.  

#### **Description**

The microphone and speaker subsystem is extremely important as it allows the pilot to determine the cognitive ability of the triage patient. This subsystem will have to figure out how the microphones will connect to the drone and the drone controller and figure out how to send data through the interfaces with the drone.  
![image](https://github.com/user-attachments/assets/68573382-bda0-4339-88e8-ce6fc51a3382)

### **Path Finding / Obstacle Detection Subsystem**

#### **Connections**

The Path Finding / Obstacle Detection subsystem will connect digitally to the signal processing subsystem for data communication and control signals. It will also interface with the programmable drone subsystem to provide real-time obstacle data for autonomous or assisted navigation. The radar sensor will be powered through the power and circuitry subsystem, sharing a regulated 5V supply line. 

#### **Specifications**

The subsystem SHALL detect obstacles within a range of at least 50 meters.     
The subsystem SHALL have a horizontal field of view (FoV) of at least 120° and a vertical FoV of at least 80°.     
The subsystem SHALL update range and motion data at a minimum rate of 10 Hz.     
The subsystem SHALL operate reliably in low-visibility conditions such as fog, light rain, or dust.     
The subsystem SHALL communicate detection data to the signal processing subsystem with latency less than 200 ms.     
The subsystem SHALL have onboard processing capability to filter noise and identify multiple obstacles simultaneously.     
The subsystem SHALL weigh less than 1 pound including its mounting hardware.     

#### **Description** 

The Path Finding / Obstacle Detection subsystem will utilize the Texas Instruments IWR6843AOPEVM radar module. Mounted at a 45° forward-facing angle, this sensor will detect obstacles and terrain features along the drone’s flight path. The radar will use frequency-modulated continuous wave (FMCW) processing to measure range, velocity, and angle of nearby objects. Data from the radar will be transmitted to the signal processing subsystem, where it will be integrated into the flight control logic. This enables the drone to autonomously adjust its flight trajectory to avoid collisions and maintain stability in complex environments. 

![Path Finding flowchart.image](https://github.com/TnTech-ECE/F25_Team8_DARPAChallengeTriageDrone/blob/main/Reports/Conceptual%20Design/Path%20Finding%20Subsystem.png)

### **Human Detection Subsystem**

#### **Connections** 

The Human Detection subsystem will connect digitally to the Signal Processing Subsystem for sensor data transmission and control commands. It will also interface with the Computing System to share detection outputs that inform triage classification and victim localization. Power for all sensors will be provided by the Power and Circuitry Subsystem, using regulated 5V and 3.3V supply lines as required by each component. The subsystem will also communicate with the Path Finding / Obstacle Detection Subsystem to coordinate detection zones and avoid sensor interference between radar modules. 

#### **Specifications**

The subsystem SHALL detect human presence within a range of at least 10 meters under standard ambient conditions.     
The subsystem SHALL operate effectively in both daylight and low-visibility environments such as fog, smoke, or low light.     
The subsystem SHALL integrate data from multiple sensor modalities (LWIR, mmWave radar, and RGB camera).     
The subsystem SHALL output detection data to the Signal Processing Subsystem with latency less than 500 ms.     
The subsystem SHALL be capable of operating for at least 20 minutes of continuous flight without thermal overload or sensor drift.     

#### **Description** 

The Human Detection Subsystem is responsible for identifying and locating individuals within the operational area of the drone. It employs a multi-sensor fusion approach combining a Long-Wave Infrared (LWIR) camera, a millimeter-wave (mmWave) radar, and an RGB camera with AI processing. 

The LWIR camera serves as the primary detection device, identifying human heat signatures even in complete darkness or through moderate smoke and fog. The mmWave radar module supplements this by detecting motion and presence through visual obstructions and triggering thermal confirmation from the LWIR camera to verify living bodies. The RGB camera provides visual context and AI-driven classification, distinguishing humans from background objects using real-time inference on the Jetson Nano computing platform. 

Data from all three sensors will be transmitted to the Signal Processing Subsystem, where it will be time-synchronized and fused into a unified detection output. This ensures the system maintains a high confidence level in identifying victims across variable environments, supporting accurate triage assessment, and enabling reliable coordination with other drone subsystems during search-and-rescue operations. 

![Human Detection flowchart.image](https://github.com/TnTech-ECE/F25_Team8_DARPAChallengeTriageDrone/blob/main/Reports/Conceptual%20Design/Human%20Finder%20Flowchart%20Subsystem.png)


## Ethical, Professional, and Standards Considerations
###	**Culture**  
\-	Advances in drone triage technology represent an ethical opportunity to reshape the cultural perception of drones from tools of surveillance or warfare into instruments of humanitarian aid. By applying engineering knowledge toward disaster relief and lifesaving missions, this project promotes a culture of responsible innovation in which high technology is aligned with moral purpose. Demonstrating drones as tools that save lives encourages public trust and fosters a cultural shift toward acceptance of autonomous and semi-autonomous systems in sensitive applications. Ethically, engineers must ensure transparency in system design and operation to maintain this trust, while prioritizing safety, privacy, and accountability in every phase of development.

##	**Society**  
\-	The deployment of semi-autonomous triage drones affects society by redefining how humans interact with machines in high-stakes environments. Drones extend the capability of first responders, providing real-time visual, thermal, and radar data before humans can safely enter a hazardous zone. This technological integration raises ethical responsibilities around reliability, data handling, and equitable access. Engineers must ensure that the system’s algorithms and sensors perform consistently under diverse conditions and that triage data is transmitted securely to prevent misuse or bias. Professionally, this technology should uphold the IEEE Code of Ethics by prioritizing the welfare of both victims and responders while creating new professional roles such as drone medical technicians, AI navigators, and emergency robotics specialists.    

##	**Environment**  
\-	From an ethical standpoint, this system must balance technological benefit with ecological responsibility. Traditional search-and-rescue operations often cause disruption to fragile ecosystems through the use of ground vehicles, human foot traffic, or heavy machinery. Drones, by contrast, can perform these missions with minimal physical intrusion, reducing habitat disturbance and energy consumption. The engineering team bears the responsibility of designing the drone to operate efficiently, using lightweight materials and optimized flight algorithms to minimize its carbon footprint. Ethical sustainability also extends to end-of-life considerations, including responsible disposal or recycling of batteries and electronic components. 

##	**Public Health and Safety**  
\-	Public safety is at the core of this project’s ethical mission. Semi-autonomous triage drones directly protect both victims and rescuers by operating in areas too dangerous for humans, such as structurally unstable buildings, toxic spill zones, or wildfire regions. Real-time vital sign detection and data transmission enable more accurate and timely prioritization of medical care, potentially saving lives in time-critical emergencies. Ethical practice demands rigorous testing, fail-safe protocols, and adherence to aviation and medical data standards such as FAA drone operation laws and HIPAA-equivalent data privacy standards. Engineers must also ensure the system operates reliably under low-visibility conditions, preventing false detections that could endanger responders or delay aid. 

##	**Economy**  
\-	Economically, the development and implementation of triage drones introduce an ethical balance between cost-efficiency and accessibility. While automation reduces the resource demands of traditional search-and-rescue teams, engineers must ensure that such technology does not exclude less wealthy regions or agencies from its benefits. Ethical economic design calls for scalable systems that can be adapted to local budgets without sacrificing reliability or safety. Professionally, this technology supports job creation in AI development, sensor design, drone maintenance, and disaster logistics, while also encouraging collaboration between public and private sectors. The long-term economic benefit, through reduced response costs, improved disaster outcomes, and industry growth, must always align with the moral responsibility to prioritize human life over profit. 

**START Adult Triage Method** [4]     
During times of disaster, good ethical decisions and considerations are often compromised. However, the START Method can better the decision-making for individuals in these situations. The Drone’s Triage system considers the START Method, thus influencing the design and selection of each subsystem to easily navigate the START Method for better and more ethical  life-saving decisions.
[](https://www.google.com/url?sa=i&url=https%3A%2F%2Fchemm.hhs.gov%2Fstartadult.htm&psig=AOvVaw0y8xkEmUV6EMQKV7fnoMyg&ust=1729839169189000&source=images&cd=vfe&opi=89978449&ved=0CBQQjRxqFwoTCLDd8Ju3pokDFQAAAAAdAAAAABAE)![image](https://github.com/user-attachments/assets/3f9fa7fc-3093-4bae-8b61-276a595ef9d1)  

### **Standards**
#### WI-FI Standard
The design will have to comply with IEEE standard 802.11 [5] which defines how WI-FI networks are set up and communicate. This will affect our design as the team will have to ensure the drone complies with this standard to successfully connect to the internet and communicate with the web app accessed by most browsers. The programmable drone API will most likely handle the low-level hardware-specific implementation of the standard. The higher level implementation will need to be tackled by the team. This will also define how the web app is designed as well as how the information is transmitted in packets and what protocols the video feed will be transmitted with.

#### Videography and Audio Recording Standard
The design and project must comply with the **DEFENSE HEALTH AGENCY's [DHA]** _ADMINISTRATIVE INSTRUCTION **NUMBER** 6000.02_ [6]. Systems responsible for videotaping, filming, recording, and imaging of patients must comply with this instruction and policy to ensure lawful and ethical use of videography and audio recordings. The video and audio recording system must record and delete any data taken, ensuring no data is stored. Any video and audio recording date exploited will be a violation of the **DHA**'s standard.

#### Drone Standard
The drone must comply with the **Federal Aviation Administration** _Small Unmanned Aircraft Systems (UAS) Regulations (Part 107)_. Any system following these operating limits is required to meet the standard criteria for lawful operation. Through careful consideration, the team selected a drone specific to these detailed standards. This is to ensure that the drone is flight-ready per the **FAA**. Waivers and permits for flight may be required in certain areas, which can be obtained through Part 107 of the **FAA**'s _Small Unmanned Aircraft Systems (UAS) Regulations_.

## Resources

### Budget

| SUBSYSTEM                     | PART NUMBER                | DESCRIPTION                                                                 | MANUFACTURER NAME         | QUANTITY | COST PER ITEM | TOTAL COST OF QUANTITY |
|-------------------------------|-----------------------------|------------------------------------------------------------------------------|----------------------------|-----------|----------------|------------------------|
| Path Finding / Obstacle Detection | 296-IWR6843AOPEVM-ND        | IWR6843AOPEVM 60–64 GHz mmWave Radar EVM                                    | Texas Instruments          | 1         | $249.00        | $249.00                |
| Path Finding / Obstacle Detection | TBD (RPLIDAR A1M8 or Unitree L2) | LiDAR sensor (model pending; evaluating RPLIDAR A1M8 vs Unitree 4D L2)       | Slamtec / Unitree          | 1         | $120 – $450    | $120 – $450            |
| Target Acquisition             | TBD                         | Thermal camera module                                                       | Lepton                         | 1         | $200 – $250             | $200 – $250                    |
| Mechanical / Mounting          | PLA-1KG                     | PLA filament 1.75 mm (1 kg spool)                                           | Generic                    | 2         | $20.00         | $40.00                 |
| Power & Circuitry              | CF14J1K00TR-ND              | 1 k Ω 5% ¼ W axial resistor                                                | Stackpole Electronics      | 10        | $0.10          | $1.00                  |
| Power & Circuitry              | CF14J10K00TR-ND             | 10 k Ω 5% ¼ W axial resistor                                               | Stackpole Electronics      | 10        | $0.10          | $1.00                  |
| Power & Circuitry              | 338-2641-ND                 | Mica 56 pF 5% 500 V radial capacitor                                       | Cornell Dubilier Electronics | 5       | $1.79          | $8.95                  |
| Power & Circuitry              | 338-3057-ND                 | Mica 8200 pF 5% 500 V radial capacitor                                     | Cornell Dubilier Electronics | 5       | $13.47         | $67.35                 |
| Power & Circuitry              | 3017                        | DC-DC 5 A Buck Converter Module                                            | Valefod                    | 1         | $4.89          | $4.89                  |
| Power & Circuitry              | DD39AJPA                    | ± Dual Output Power Supply Module                                          | eletechsup                 | 1         | $9.99          | $9.99                  |
| Wiring & Connectors            | B08THSDF4S                  | 20 pcs DC Power Cable 5 A 12 V DC                                          | CENTROPOWER                | 1 set     | $9.29          | $9.29                  |
| Wiring & Connectors            | 22-GAWIRE-KIT               | 22 AWG Stranded Hook-Up Wire Kit (6 Colors)                                | BNTECHGO                   | 1         | $15.00         | $15.00                 |
| Miscellaneous                  | B091TRMFYT                  | NP-F Battery Adapter Plate                                                 | SmallRig                   | 1         | $26.99         | $26.99                 |

The following budget was decided by this team, and these are the additional items that are anticipated to be required to complete our project.


### Division of Labor

#### Skills

The team is comprised of three Electrical Engineers (Kasey Dyess, Zenkline Elle, and Wyatt Wheeler) and three Computer Engineers (Job Flores, Gideon Befekadu, and Brody Smith). Each team member brings a unique technical background and experience to ensure the success of the project. 

  
**Kasey Dyess**

**Skills:** Coding (C++, Python, Arduino), Code Design, Microcomputer Systems, Digital Logic, Wiring, Power Transmission 

Kasey will lead the control and power subsystem of the project due to his knowledge of power transmission, circuit wiring, and control logic. He will ensure reliable power distribution throughout the system and will assist with hardware integration where necessary. Wyatt Wheeler will act as the customer for this subsystem because of his similar experience with power systems and digital logic. 

  
**Zenkline Elle**

**Skills:** Coding (C, C++, Python, VHDL), Schematic Design, Wiring Design, 3D Design, Microcomputer Systems, Digital System Design, PCB Design 

Zenkline will lead the sensor interfacing and circuit integration subsystem, responsible for wiring design, schematic layout, and PCB development. His role also includes connecting the vital and environmental sensors to the drone’s computational system. Brody Smith will act as the customer for this subsystem due to his background in logic design and microcomputer systems. 

 
**Wyatt Wheeler** 

**Skills:** Programming (C/C++/Python/SOME Rust), Google Suite, Microcomputer Systems, Autodesk Inventor 3D Modeling, Power Systems, Digital Logic, Soldering, Technical Writing 

Wyatt will head the drone chassis and hardware integration subsystem, combining his 3D modeling and soldering skills to design the physical layout for the drone and its electronic components. His power systems experience will also assist Kasey in verifying power distribution efficiency. Kasey Dyess will serve as Wyatt’s customer for this subsystem.  

 

**Job Flores**

**Skills:** Telecommunications, Microcomputer Systems, Embedded Systems, Coding (C, C++, Python, VHDL), Software (VS Code, STM32Cube), Digital System Design/FPGA, Artificial Intelligence 

Job will direct the communication and processing subsystem, handling embedded systems, data transmission, and signal processing between sensors and the onboard computer. His telecommunications and FPGA expertise will ensure seamless communication between modules. Gideon Befekadu will act as the customer for this subsystem because of his background in controls and microcomputer systems. 


**Gideon Befekadu**

**Skills:** Controls, Coding (C, C++), Microcomputer Systems 

Gideon will manage the control stability and feedback subsystem, developing algorithms for precise motor control and stable flight operation. His control systems background makes him well-suited for this task. Job Flores will act as the customer due to his expertise in embedded systems and signal integration. 


**Brody Smith**

**Skills:** Logic Design, Coding, Microcomputer Systems 

Brody will oversee the logic and decision-making subsystem, responsible for developing the logic flow, control algorithms, and decision pathways that guide the drone’s autonomous behavior. Zenkline Elle will serve as his customer because of his familiarity with circuit and wiring design, ensuring that logical design decisions align with physical integration constraints. 

If new findings arise during subsystem development, or if a team member’s expertise becomes more aligned with another area, roles may be reassigned upon team consensus or with advisement from the faculty mentors. 

### Timeline

![Gantt Chart.image](https://github.com/TnTech-ECE/F25_Team8_DARPAChallengeTriageDrone/blob/main/Reports/Conceptual%20Design/Gantt%20Chart.png)

## References

[1] “DARPA Triage Challenge,” [Triagechallenge.darpa.mil] 

[2] Federal Aviation Administration. (n.d.). Small Unmanned Aircraft System (sUAS). In Aeronautical Information Manual, Chapter 11, Section 2. Retrieved from [FAA](https://www.faa.gov/air_traffic/publications/atpubs/aim_html/chap11_section_2.html)

[3] IEEE, IEEE Standard for Information Technology—Telecommunications and Information Exchange Between Systems Local and Metropolitan Area Networks—Specific Requirements—Part 11: Wireless LAN Medium Access Control (MAC) and Physical Layer (PHY) Specifications—Amendment 1: Enhancements for High-Efficiency WLAN, in IEEE Std 802.11ax-2021 (Amendment to IEEE Std 802.11-2020), vol., no., pp. 1–767, May 19, 2021, doi: 10.1109/IEEESTD.2021.9442429. 

[4] U.S. Department of Defense, MIL-STD-461G: Requirements for the Control of Electromagnetic Interference Characteristics of Subsystems and Equipment, Washington, D.C., 2015. Available: [NASA](https://s3vi.ndc.nasa.gov/ssri-kb/static/resources/MIL-STD-461G.pdf)   

[5] SAE International. (2021). J3016: Taxonomy and Definitions for Terms Related to Driving Automation Systems for On-Road Motor Vehicles. SAE International, Warrendale, PA. Available: [SAE](https://www.sae.org/standards/content/j3016_202104/) 

[6] Aurelia Technologies Inc., “Aurelia X4 Standard Drone and User Manual (Rev. 4.2).” Aurelia Aerospace, 2025. [Online]. Available: [Aurelia](https://aurelia-aerospace.com/products/aurelia-x4-standard?variant=44599339745468). [Accessed: 28-Oct-2025]. 

[7] Parrot Drones S.A.S., “Parrot ANAFI Ai Drone and User Manual (v7.4.0.0).” Parrot, 2025. [Online]. Available: [Parrot](https://www.parrot.com/en/drones/anafi-ai) 

[8] "START Adult Triage Method." [CHEMM](https://chemm.hhs.gov/startadult.htm) 

‌[9] "802.11 "IEEE Standard for Information Technology--Telecommunications and Information Exchange between Systems - Local and Metropolitan Area Networks--Specific Requirements - Part 11: Wireless LAN Medium Access Control (MAC) and Physical Layer (PHY) Specifications," in IEEE Std 802.11-2020 (Revision of IEEE Std 802.11-2016) , vol., no., pp.1-4379, 26 Feb. 2021, doi: 10.1109/IEEESTD.2021.9363693" [IEEE](https://ieeexplore.ieee.org/stamp/stamp.jsp?tp=&arnumber=9363693&isnumber=9363692)  

[10] "Defense Health Agency" [DHA](https://www.health.mil/Reference-Center/DHA-Publications/2022/08/05/DHA-AI-6000-02)  

[11] "Federal Aviation Administration" [FAA](https://www.faa.gov/newsroom/small-unmanned-aircraft-systems-uas-regulations-part-107)

[12] "Power supply considerations for Jetson Nano Developer Kit" [NVIDIA](https://forums.developer.nvidia.com/t/power-supply-considerations-for-jetson-nano-developer-kit/71637) 

## Statement of Contributions

**Kasey Dyess:** Human Finding 

**Job Flores:** F24 System Integration, Drone Comparative Analysis, Problem Introduction 

**Wyatt Wheeler:** F24 System Integration, Introduction 

**Gideon Befekadu:** Path finding comparative analysis, path finding subsystem, hardware block diagram, operational flowchart, path finding high-level solution  

**Zenkline Elle:** Path finding comparative analysis, path finding subsystem, managing project budget, path finding flowchart, operational flowchart, identifying necessary skills for project execution, path finding high-level solution. 

**Brody Smith:** Human finding subsystem component comparative analysis, solution description, and high-level design description. 


