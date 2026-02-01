
# Drone to PC Link Subsystem

## Introduction

The Drone to PC Link subsystem is responsible for establishing and maintaining a reliable wireless communication pathway between the Aurelia X4 Standard drone [1] and the operator’s laptop running Windows 10 or higher. This subsystem enables the transmission of all mission-critical data generated onboard, including live video, real-time audio, telemetry, and processed triage results. To ensure stable performance and avoid interference with the drone's 2.4 GHz Herelink flight system, this link is explicitly designed to operate on the 5 GHz Wi-Fi band.

The system integrates a Jetson Nano onboard computer and uses shielded USB 3.0 cabling to mitigate electromagnetic noise that can impact 2.4 GHz RC sensitivity. For maximum bandwidth headroom and link reliability, the video stream is capped at 720p with a reduced frame rate.

This document provides a complete design description, explaining how the subsystem fits within the overall triage drone system and presenting all constraints and specifications that govern the design. It justifies major design choices using verifiable vendor documentation and established networking standards to ensure safe and accurate triage communication.

## Function of the Subsystem

The Drone to PC Link subsystem provides the primary data path between the airborne triage platform and the user’s laptop. It is responsible for collecting all mission critical information on the drone and delivering it to the operator in real time with stable, encrypted communication.

At the hardware level, the subsystem is built around the Aurelia X4 Standard multirotor platform, which uses a Cube Orange flight controller and supports professional payloads for inspection and similar applications [1]. The Cube Orange manages flight control and publishes telemetry such as position, altitude, attitude, and system status. A digital RF link such as Herelink, designed for the Cube ecosystem, carries RC commands, HD video, and telemetry between the air unit and a ground controller while protecting traffic with AES-128 encryption over a 2.4 GHz ISM band radio [2].

A companion **NVIDIA Jetson Nano** computer mounted on the Aurelia X4 receives raw or preprocessed data from the triage subsystems, including:

-   Vitals data from the Doppler radar based vitals sensor subsystem
-   Audio from the microphone subsystem
-   Video from the camera subsystem
-   START triage classification results from the signal processing subsystem
-   Navigation and state information from the Cube Orange flight controller

The Jetson Nano provides a quad core ARM CPU and integrated GPU suitable for real time video processing and data handling in embedded robotics applications [3].

The Drone to PC Link subsystem then exposes this information to the operator laptop over a short range, high throughput **IEEE 802.11** wireless LAN connection using a dual band 2.4 / 5 GHz adapter that supports 802.11ac PHY and MAC operation [4]. On top of this Wi-Fi link, the subsystem uses:

-   **WebRTC** for low latency streaming of camera video and microphone audio, as well as optional return audio from the operator to the drone for cognitive questioning [5].
-   A reliable data channel (for example WebRTC data channels or WebSockets over TCP) for vitals time series, triage labels, and selected telemetry to the user interface on the laptop.
    
Functionally, the Drone to PC Link subsystem:

1.  Aggregates data from the vitals sensor, microphone and speaker subsystem, camera subsystem, and programmable drone subsystem on the Jetson Nano.
2.  Packages this data into well defined audio, video, and data streams.
3.  Transmits the streams over an encrypted RF link and local Wi-Fi connection to the operator laptop.
4.  Maintains connection health by monitoring link quality (RSSI, packet loss, and latency) and applying retry or fallback behavior when thresholds are exceeded.
5.  Presents all data in a form usable by the Interfacing subsystem, which is responsible for final visualization on the laptop.

Within the overall system, this subsystem is therefore the communications backbone between airborne sensing and ground side visualization. If the Drone to PC Link fails, the drone may still fly safely under manual control, but the operator loses access to vitals, audio, video, and triage outputs, so maintaining this link is critical to the effectiveness of the triage solution.

## **Specifications and Constraints**

### **Specifications**

1.  **The subsystem SHALL transmit telemetry, vitals data, video, and audio from the drone to the operator laptop with stable wireless connectivity [4].**  
2.  **The subsystem SHALL support wireless transmission using IEEE 802.11 compliant hardware [4].**      
3.  **The subsystem SHALL wirelessly deliver triage signal processing data from the Jetson Nano to the laptop [5].**  
4.  **The subsystem SHALL wirelessly stream live video (capped at 720p resolution and ≤30 fps) and audio between the drone and the laptop to ensure maximum bandwidth headroom and low-latency delivery [6].**  
5.  **The subsystem SHALL support two way audio transmission to allow cognitive assessment commands from the operator [5].**
6.  **The subsystem SHALL be compatible with an operator laptop running Windows 10 or higher to ensure full driver support and stable operation of the IEEE 802.11ac wireless hardware.**

These specifications are essential to ensure that all mission critical triage information is delivered accurately and without interruption, allowing the operator to make informed medical decisions in real time.

### **Constraints**

1.  **The subsystem MUST maintain a packet error rate below 1 percent [7].**      
2.  **The subsystem MUST maintain an end to end latency below 1 second for video, audio, and triage data [6].**      
3.  **The subsystem MUST not store any transmitted data, including video, audio, telemetry, or vitals [8].**  
4.  **The subsystem MUST encrypt all transmitted data [2].**  
5.  **The subsystem MUST operate within the RF limits and coexistence requirements of the Aurelia X4 wireless environment [9].**  
6.  **The subsystem MUST remain within the power budget provided by the Aurelia X4 payload system [10].**
7.  **The subsystem MUST use high-quality shielded USB 3.0 cabling for all peripheral connections to the Jetson Nano to mitigate electromagnetic interference (EMI) with the 2.4 GHz RC and telemetry links [11].**

It is important that these constraints are met due to the critical requirement for reliable, real time triage communication during life saving medical operations.

## **Overview of Proposed Solution**


The proposed solution for the Drone to PC Link subsystem uses a **dual wireless communication architecture** that combines the capabilities of the Aurelia X4 Standard’s integrated Herelink system with a high throughput IEEE 802.11ac Wi-Fi link. This approach is required because Herelink supports video and telemetry, but it does **not** support two way audio or continuous high rate custom data streams such as radar derived vitals.

The **Herelink system**, included with the Aurelia X4 Standard, provides encrypted long range transport for:

-   Flight control
-   Bidirectional MAVLink telemetry
-   Up to two 1080p HDMI video feeds
    

Herelink traffic is encrypted with AES 128 as documented by CubePilot [2]. It is built for flight critical tasks and is not intended to serve as a general purpose IP modem. While Herelink can transport **custom MAVLink packets**, this channel is limited to low bandwidth message based data exchange, which is unsuitable for streaming radar vitals or audio. Additionally, Herelink **does not support audio input on the air unit** and provides **no two way audio API**, so cognitive test audio cannot be carried over the link.

Because of these architectural limitations, Herelink can only support:

-   Telemetry
-   Command and control
-   HDMI video (optional)
-   Low rate vitals delivered as custom MAVLink messages

It cannot support:

-   Two way audio
-   High rate sensor streaming
-   Companion computer video streams
-   Real time WebRTC based communication

To provide these features, the subsystem introduces a **Jetson Nano Wi-Fi communication pathway**. A dual band IEEE 802.11ac adapter such as the TP Link Archer T4U Plus creates a high throughput short range wireless link to the operator’s laptop. IEEE 802.11ac supports PHY rates in the hundreds of megabits per second at distances of 20 to 50 ft, enabling low latency, low packet loss delivery of triage data [4][7].

On top of this Wi-Fi channel, the system uses **WebRTC and WebSockets**, which provide:

-   Real time video streaming with sub second latency [6]
-   Mandatory encryption through DTLS and SRTP [5]
-   Bidirectional audio capability
-   Efficient data channels for vitals and triage messages

The **Jetson Nano** combines data from the camera, microphone, Doppler radar vitals sensor, and triage processing subsystem. It then transmits all triage information through WebRTC and WebSockets to the operator laptop. The companion computer keeps all data volatile, discarding frames immediately after display to comply with DHA privacy requirements [8].

This results in a robust and medically compliant system where:

-   **Herelink** handles flight critical operations
-   **Wi-Fi + WebRTC/WebSockets** handle triage critical operations

Together, this architecture satisfies all specifications and constraints by:

-   Matching the physical and architectural limits of Herelink
-   Ensuring a guaranteed audio path for cognitive testing
-   Maintaining video and vitals latency under 1 second [6]
-   Operating within IEEE 802.11ac compatibility requirements [4]
-   Maintaining encryption from end to end across both links [2, 5]
-   Respecting medical privacy standards [8]

This dual link system is not optional but necessary due to the documented limitations of Herelink and the high throughput, low latency requirements of the triage mission.

To ensure mechanical flexibility, the design supports two hardware configurations: The TP-Link Archer T4U Plus is the primary choice due to its high-gain external antennas. However, the system is also compatible with an Intel 8265 M.2 Wireless Card. The M.2 variant serves as a weight-saving alternative if the payload's center of gravity or total mass exceeds the Aurelia X4's stability margins.

## **Interface with Other Subsystems**

The Drone to PC Link subsystem serves as the central communication pathway that transfers all mission critical triage information from the drone to the operator laptop. Because it interacts with every onboard subsystem, this section defines each interface precisely, including the type of data exchanged, the direction of communication, and the method of transmission. These interfaces ensure that video, audio, telemetry, and vitals data flow reliably to the operator for real time triage assessment.

### **1. Drone Operator Subsystem**

#### **Inputs to Drone to PC Link**

-   **Vehicle telemetry data** from the Cube Orange autopilot including GPS coordinates, altitude, attitude, battery status, and system health
    
    -   Provided as **MAVLink** telemetry messages [12]
    -   Routed through Herelink for flight safety

#### **Outputs from Drone to PC Link**

-   **Processed telemetry display data** sent to the operator laptop via WebSockets for visualization
-   **Link quality metrics** (RSSI, packet loss, latency) displayed on the operator interface to assist in flight decisions
    

#### **Communication Method**

-   MAVLink over Herelink for flight critical telemetry
-   WebSockets or WebRTC data channels over Wi-Fi for telemetry duplication to the interface subsystem


### **2. Power and Safety Subsystem**

#### **Inputs to Drone to PC Link**

-   **Power availability** to the Jetson Nano and Wi-Fi module
    -   The Jetson Nano requires approximately 5 to 10 W depending on workload [3]
    -   The Archer T4U Plus requires approximately 2.5 W peak [10]

Note:

If the M.2 card is used instead of the USB adapter, power is drawn directly from the Jetson Nano’s 3.3V rail via the M.2 slot, reducing the load on the USB 3.0 bus.       

#### **Outputs from Drone to PC Link**

-   No data output, but the subsystem monitors power consumption indirectly through Jetson software tools
    

#### **Communication Method**

-   Electrical power interface only
-   Jetson Nano reports internal power consumption to the operator interface through local system calls
    

### **3. Signal Processing Subsystem**

#### **Inputs to Drone to PC Link**

-   **Heart rate and respiratory rate** extracted from Doppler radar
-   **Triage classification results** following START rules
-   **Cognitive assessment results** processed locally on Jetson Nano
-   **Signal integrity metrics** such as confidence level or noise floor

#### **Outputs from Drone to PC Link**

-   **Encoded vitals data** transmitted to the operator via WebRTC data channels
-   **Triage decision packets** forwarded to the operator interface
-   **Low latency acknowledgements** to ensure correct packet ordering and reliability

#### **Communication Method**

-   Local data sharing on the Jetson Nano via shared memory or internal API
-   Wireless transmission using WebRTC channels over 802.11ac Wi-Fi [5]
    


### **4. Sensors Subsystem**

Includes Doppler radar, camera, and other physiological sensing equipment.

#### **Inputs to Drone to PC Link**

-   **Camera video frames** captured by the onboard camera
-   **Microphone audio** collected from the victim area
-   **Doppler radar raw vitals data**
-   **Environmental sensor readings** if included (temperature, noise level, etc.)

#### **Outputs from Drone to PC Link**

-   **Encoded video stream** sent to the operator using WebRTC
-   **Encoded audio stream** transmitted alongside video
-   **Vitals telemetry packets** sent over WebRTC or WebSockets
-   **Confidence and error reporting** returned to the sensor subsystem if needed
    

#### **Communication Method**

-   Direct data access through Jetson Nano I/O (CSI camera, I2S audio, UART or SPI radar interfaces)
-   WebRTC media channels for audio video streaming [5, 6]
    


### **5. Victim Communication Subsystem**

This subsystem includes the microphone and speaker used to communicate with the victim.

#### **Inputs to Drone to PC Link**

-   **Microphone audio data**
-   **Speaker command triggers** such as “Play cognitive prompt”
-   **Audio quality metrics** (optional)
    

#### **Outputs from Drone to PC Link**

-   **Two way audio streaming**
    -   Victim to operator (microphone to WebRTC stream)
    -   Operator to victim (WebRTC return audio to speaker subsystem)
-   **Session status messages** indicating active communication or link degradation
    

#### **Communication Method**

-   Bidirectional audio over WebRTC, which enforces DTLS and SRTP encryption [5]
-   Local routing through Jetson Nano to I2S or USB audio interfaces for the speaker and microphone
    


### **6. Interfacing Subsystem**

#### **Inputs from Drone to PC Link**

-   All triage relevant data including:
    -   Live video stream
    -   Live audio stream
    -   Two way audio return capability
    -   Vitals data packets
    -   Triage classification results
    -   Telemetry data duplicated or augmented for display
    -   Link quality statistics
        
#### **Outputs to Drone to PC Link**

-   **Operator commands**
    -   Cognitive test prompts
    -   Audio responses
-   **Interface acknowledgment packets** confirming recieved data

#### **Communication Method**

-   WebRTC media channels for video and audio
-   WebSockets or WebRTC data channels for vitals and metadata
-   Local browser based visualization compliant with W3C WebRTC standards [5]

## Buildable Schematic

The Drone to PC Link subsystem uses only commercial off the shelf (COTS) modules and standard cables, so the “schematic” is best expressed as a detailed wiring diagram that specifies each connector, signal type, and interconnect. 

### 1. Subsystem Components (Electrical)

The Drone to PC Link schematic includes the following electronic blocks:

1.  **Jetson Nano Developer Kit (J1020 V2 or equivalent)**
    
    -   5 V DC input on barrel jack or 40 pin header
    -   4x USB 3.0 Type A ports for Wi Fi adapter, USB audio, and optional camera
    -   Gigabit Ethernet port (optional future use)
    -   40 pin expansion header for GPIO and UART if needed [3]
        
2.  **Wi Fi Adapter (TP Link Archer T4U Plus class 802.11ac USB adapter)**
    
    -   USB 3.0 Type A male connector
    -   Two external antennas for improved range [10]
        
3.  **USB Audio Interface (or USB microphone and USB DAC to speaker)**
    
    -   USB 2.0 or 3.0 Type A male connector
    -   Line or headphone level output to amplifier plus speaker
    -   Microphone input for victim side audio capture
        
4.  **Camera**
    
    -   Either a USB UVC camera (USB Type A) or CSI camera supported by Jetson Nano
    -   Chosen by the Sensors subsystem, but physically connected to Jetson Nano
        
5.  **Power Input from Power and Safety Subsystem**
    
    -   Regulated 5 V supply, minimum 4.75 V to 5.25 V, current capacity ≥ 4 A as recommended for Jetson Nano with peripherals [8]
    -   Overcurrent and fuse protection implemented in the Power and Safety subsystem
        
6.  **Aurelia X4 / Cube Orange / Herelink Stack (Existing Drone Platform)**
    
    -   Flight controller and Herelink are powered and wired by the Drone Operator and Power subsystems
    -   Optional UART or Ethernet from Cube Orange to Jetson Nano for telemetry if those teams decide to forward MAVLink locally, but this is not required if telemetry is only mirrored coming from the PC side
        


### 2. Power Wiring

The Jetson Nano and communications peripherals receive power from the regulated 5 V rail provided by the Power and Safety subsystem.

**Connections:**

1.  **Power Subsystem 5 V output** → **Jetson Nano 5 V input**
    
    -   If using the barrel jack:
        -   +5 V from power subsystem to Jetson Nano barrel jack center pin
        -   Ground from power subsystem to Jetson Nano barrel jack sleeve
    -   If using the 40 pin header:
        -   +5 V to pin 2 and/or pin 4 (5V0)
        -   GND to any ground pin (for example pin 6)
        -   Current capacity must follow NVIDIA power guidance for external supplies [3, 8]
            
2.  **Peripherals power**
    
    -   Archer T4U Plus, USB audio, and USB camera are powered directly from Jetson Nano USB ports
    -   Total USB peripheral current must stay within Jetson Nano USB port limits (nominally up to 900 mA per USB 3.0 port). If additional current is required, an externally powered USB hub can be inserted between Jetson Nano and the peripherals.

No separate regulators are drawn for this subsystem because all regulation is handled in the Power and Safety subsystem. Their schematic will show buck converters and protection.


### 3. Data Wiring

#### 3.1 Wi Fi Link

-   **Jetson Nano USB 3.0 Port 1 → TP Link Archer T4U Plus USB Plug**
    
    -   Interface: USB 3.0 SuperSpeed
    -   Purpose: Provides IEEE 802.11ac Wi Fi connectivity from Jetson Nano to operator laptop over 2.4 or 5 GHz band [4, 10]

This is a single cable connection:

-   U1: Jetson Nano module
-   J1: USB 3.0 Type A female (on Jetson)
-   U2: Archer T4U Plus (represented as a single block with USB data and power pins)
-   D+ / D− and SuperSpeed pairs routed inside the cable, not custom wired

#### 3.2 Audio

Combined USB Microphone and USB Speaker**

-   **Jetson Nano USB port → USB microphone**
-   **Jetson Nano USB port → USB speaker or headset DAC**

This is electrically even simpler and can be captured with two USB connections.

#### 3.3 Camera

**USB Camera**

-   **Jetson Nano USB 3.0 Port 3 → USB UVC camera**
    -   Interface: USB 2.0 or 3.0
    -   No extra electronics inside this subsystem

### 4. Logical Block Schematic

<p align="center">
  <img width="70%" alt="Jetson Nano Top" src="https://github.com/user-attachments/assets/595f22e6-3dba-4799-8200-a30e3608075e" />
</p>

<p align="center"><img width="40%" alt="Logical Block Schematic" src="https://github.com/user-attachments/assets/c762c5a7-5e97-4cd7-9768-dc177ccfc6c6" /> </p>


-   WiFi block = Archer T4U Plus
-   Audio block = USB audio interface or USB microphone / speaker pair
-   Camera blocks = USB camera

### 5. Implementation Notes

1.  **Cable Management and EMI**
    
    -   USB cables should be kept as short as practical to reduce EMI and latency issues.
    -   USB 3.0 is known to generate significant noise in the 2.4 GHz spectrum, which can desensitize the drone’s RC receiver and Herelink air unit. To prevent this, all USB 3.0 cables (including the Wi-Fi adapter extension) must be double-shielded. Additionally, the cables should be kept as short as practical and routed away from the drone's antennas [4].
        
2.  **Mounting Constraints**
    
    -   Physical mounting of Jetson Nano, Wi Fi adapter, camera, and audio hardware is coordinated with the Drone Operator subsystem, but all connectors must remain accessible for assembly and debug.
        
3.  **Thermal Considerations**
    
    -   Jetson Nano can reach high temperatures under sustained GPU load, so airflow or heatsinking must be provided according to NVIDIA guidelines [3].
  
4. **Video Configuration**

    - The Jetson Nano software (GStreamer or OpenCV pipeline) must be configured to downscale the raw camera input to 1280x720 before encoding to H.264. This ensures that the Wi-Fi link is never saturated by high-resolution raw data [13].
  
5. **Alternative M.2 Mounting**
    - In the M.2 configuration, the Archer T4U Plus is replaced by an Intel 8265 card installed in the J11 slot under the Jetson module. This requires the addition of two U.FL-to-SMA pigtail cables and two lightweight 5GHz dipole antennas mounted to the drone frame.

## **Flowchart**

The operational flowchart for this subsystem illustrates the sequence of processes required to establish and maintain a reliable wireless communication channel between the drone mounted Jetson Nano and the operator’s laptop. This workflow outlines all major stages from powering the system to validating real time data transmission, including fault recovery when connection quality degrades.

The flow begins with powering the Jetson Nano and connecting all required peripherals, including the Wi Fi adapter **[10]**, USB microphone, USB speaker, and camera. Once the system is initialized, the subsystem attempts to establish a wireless IEEE 802.11ac link and initiate the WebRTC and WebSocket communication interfaces used for transmitting video, audio, telemetry, and vitals data **[5]**.

Upon a successful connection, the subsystem verifies that live video, audio, telemetry, and vitals feeds are accessible through the client application. The system then continuously monitors link quality by analyzing latency, packet loss, and data integrity **[6]**. If high latency or packet loss is detected, the system executes a retry routine to reestablish a stable communication channel. If the connection remains healthy, the subsystem proceeds with uninterrupted real time transmission.

<p align="center"> <img width="671" height="951" alt="Operational Flowchart" src="https://github.com/user-attachments/assets/667cf4a7-b97e-481e-be8b-d5a64c25d012" /> </p>

This flowchart ensures that all critical communication elements are validated before triage data is delivered to the operator, and that recovery mechanisms are in place to protect the system from wireless degradation or interruption.


## Bill of Materials (BOM)


### **Bill of Materials (BOM)**

| Item | Description | Manufacturer | Part Number | Distributor | Qty | Unit Cost | Total Cost |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **Wi-Fi Adapter (Primary)** | Dual Band USB 3.0 Wi-Fi Adapter (802.11ac) with high-gain antennas | TP-Link | Archer T4U Plus | [Amazon](https://www.amazon.com/dp/B08KHV7H1S) | 1 | $29.99 | $29.99 |
| **USB 3.0 Cable (Primary)** | Double-shielded USB 3.0 extension (to mitigate 2.4GHz EMI) | Cable Matters | 202001-BLK-1m | [Amazon](https://www.amazon.com/dp/B00C7S2FRE) | 1 | $8.99 | $8.99 |
| **Wi-Fi Card (Contingency)** | Intel Dual Band Wireless-AC 8265, M.2 2230, Key E (Weight-saving alternative) | Intel | 9260.NGWG.NV | [Amazon](https://www.amazon.com/dp/B0721MLM8B) | (1)* | $17.09 | $17.09 |
| **RF Pigtail Cables (Contingency)** | U.FL to RP-SMA Female Bulkhead (Required for M.2 variant) | Highfine | HF-KIT-9260 | [Amazon](https://www.amazon.com/dp/B0CS6KBDJJ/) | (2)* | $7.99 | $7.99 |
| **Antennas (Contingency)** | 2.4GHz/5GHz Dual Band Antennas (Required for M.2 variant) | TREADALT-TEC | DB-ANT-SMA | [Amazon](https://www.amazon.com/dp/B08X45Q44Z) | (2)* | $6.99 | $6.99 |
| **Plan A Cost** | | | | | | | **$38.98** |
| **Plan B Cost** | | | | | | | **$32.07** |
| **Plan A+B Cost** | | | | | | | **$71.05** |

**BOM Notes:**
- **(*) Contingency Items:** These components are listed for design flexibility. They will only be procured if weight/size constraints require a transition from the USB adapter to the internal M.2 slot.
- **EMI Mitigation:** All USB cabling must be double-shielded per Design Constraint 7 to protect the 2.4 GHz Herelink sensitivity.
- No PCB fabrication is required unless the project team chooses to add a small breakout board.
- Laptop hardware must support Windows 10+ for compatibility with the Archer T4U Plus Wi-Fi adapter


## **Analysis**

The purpose of the Drone to PC Link subsystem is to provide a reliable, low latency, and encrypted wireless communication channel capable of transmitting all mission critical triage data from the drone mounted Jetson Nano to the operator’s laptop. This includes live video, two way audio, vitals data, sensor metadata, and telemetry. The subsystem must meet strict performance constraints, most notably maintaining an error rate under 1 percent and achieving end to end latency below one second for all streamed data.

### **1. Wireless Link Selection and Justification**

The subsystem uses a TP Link Archer T4U Plus class Wi Fi adapter, which supports IEEE 802.11ac operation in the 5 GHz band. The 802.11ac standard provides higher physical layer throughput and reduced interference compared to 2.4 GHz systems, allowing reliable transmission of simultaneous media streams, telemetry, and vitals data. The FCC certification data for the Archer T4U Plus confirms its compliance with required RF output limits and channel behavior, ensuring predictable performance under standard operating conditions [10].

### **2. Latency Analysis**

WebRTC is used as the primary transport for video, audio, and data. According to W3C’s WebRTC specification, transport is encrypted using DTLS and media is encrypted using SRTP, while interactive connectivity is negotiated using ICE [5]. WebRTC implementations typically achieve latencies below 100 ms under local network conditions, well below the subsystem maximum latency specification of 1 second. Independent WebRTC performance analyses further verify that the protocol can sustain real time audio and video streaming with acceptable jitter under moderate wireless load [6].

The latency budget for this subsystem consists of:

-   Camera capture or audio sampling delay    
-   Encoding delay (H.264 hardware accelerated on Jetson Nano)    
-   Wi Fi transmission delay (variable with RSSI and interference)    
-   WebRTC jitter buffering    
-   Decoding delay on the operator’s laptop    

Under IEEE 802.11ac, typical single stream latency remains below 20 ms when RSSI exceeds –65 dBm. The antenna extension and USB 3.0 repositioning cable included in the BOM ensure that the Wi Fi adapter can be mounted away from carbon fiber structures or motor interference, improving signal strength and helping keep end to end latency within the subsystem constraint.

### **3. Reliability and Error Rate**

WebRTC incorporates built in mechanisms for reducing packet loss including forward error correction (FEC) and retransmission strategies suited for real time media [5]. The subsystem also uses the Archer T4U Plus, which supports beamforming and dual external antennas. These features improve link quality and reduce the probability of packet loss below the 1 percent required threshold when operating within typical drone to operator distances (<50–70 m in unobstructed line of sight).

The use of a USB 3.0 extension cable allows the Wi Fi adapter to be placed in a position with improved visibility relative to the operator’s ground station, preventing shadowing caused by drone components. This directly contributes to meeting both error rate and latency specifications.

### **4. Encryption and Medical Data Protection**

Submissions and communications involving patient data must comply with medical privacy guidelines. The Defense Health Agency Administrative Instruction 6000.02 requires that systems handling patient audio or video avoid storage and use secure transport [8]. WebRTC inherently satisfies this requirement by using DTLS for signaling encryption and SRTP for media encryption, while this subsystem performs no local recording. All media and data are transmitted in encrypted form and discarded after playback or display.

### **5. Throughput Requirements and Bandwidth Allocation**

The combined bandwidth demand for:

-   H.264 encoded video (0.5–2.0 Mbps)    
-   Opus audio (<100 kbps)    
-   Vitals and telemetry (<50 kbps)    

remains well within the typical usable throughput of consumer grade 802.11ac adapters, which often exceed 50 Mbps at short range. The FCC documentation for the Archer T4U Plus confirms that its modulation and coding scheme capabilities support channel bandwidths suitable for this application [10].

### **6. Absence of Custom PCB**

Because all required components interface digitally using USB or CSI connectors and the Jetson Nano’s carrier board already provides proper power distribution, grounding, and high speed routing, no PCB is required for this subsystem. The Power and Safety subsystem regulates the 5 V rail, and the Jetson Nano manages all internal electrical requirements. Therefore, introducing a custom PCB would not improve performance or reliability and would violate the subsystem’s minimal hardware philosophy.

### **7. Summary of Compliance with Specifications and Constraints**

The analysis confirms that the selected hardware and communication architecture satisfy all subsystem constraints and performance specifications while maintaining compliance with security, ethical, and regulatory requirements.

### **8. Quantitative Analysis**

#### **8.1 Link Budget and Maximum Range**

For a line of sight 5 GHz Wi Fi link, the Free Space Path Loss (FSPL) in decibels as a function of distance and frequency is commonly written as [12]:

`FSPL(dB) = 32.44 + 20 log10(d_km) + 20 log10(f_MHz)`

Where:
- `d_km` is the distance in kilometers
- `f_MHz` is the frequency in megahertz  

The Archer T4U Plus operates at 5 GHz with a maximum EIRP of about 20 dBm in the 5 GHz band according to the TP-Link datasheet [10].  
Receive sensitivity at 802.11ac VHT80 (80 MHz channel) is approximately:

Maximum allowable FSPL is derived as:

`FSPL_max = P_tx,EIRP - P_rx,sens  `

`FSPL_max = 20 dBm - (-60 dBm) = 80 dB`

Solving for maximum range by substituting `f_MHz = 5000 MHz`:

`20 log10(d_km) = 80 - 32.44 - 20 log10(5000) `

`d_km,max = 10^((80 - 32.44 - 20 log10(5000)) / 20)`

Evaluated numerically:

`d_km,max ≈ 0.0478 km ≈ 47.8 m ≈ 48 m`

A sample FSPL evaluation at 40 m:

`FSPL_40m = 32.44 + 20 log10(0.04) + 20 log10(5000) ≈ 78.5 dB`  

`P_rx at 40m ≈ 20 dBm - 78.5 dB ≈ -58.5 dBm`

Since:

`-58.5 dBm > -60 dBm`

The link is sufficient at 40 m with small margin [7][10].


#### **8.2 Bandwidth Requirement vs 802.11ac Capacity**

By capping the video at 720p, the required application bitrate (`R_video`) is stabilized at approximately 1.5 to 2.0 Mbps. This is a reduction from the 5–8 Mbps typically required for 1080p, providing a significant "buffer" that prevents packet congestion during rapid drone maneuvers or when the signal encounters physical obstructions.

This link carries:

- Compressed H.264 video
- Opus two way audio
- Low rate vitals & telemetry

Representative worst case media allocation:

`R_video ≈ 2.0 Mbps (720p low-medium bitrate)` 

`R_audio ≈ 64 kbps (two-way Opus audio)`  

`R_data ≈ 10 kbps (telemetry + vitals)`

`R_total,app = 2.0 + 0.064 + 0.01 ≈ 2.074 Mbps`

Accounting for overhead (2× PHY safety factor):

`R_required,PHY ≈ 2 × 2.074 ≈ 4.15 Mbps`

Archer T4U Plus max PHY rate at 5 GHz:

`R_PHY,max = 867 Mbps`

Estimated worst case usable rate at 10% real world efficiency:

`R_usable ≈ 0.1 × 867 ≈ 86.7 Mbps`

Since:

 `87 Mbps >> 4.15 Mbps`
 
 802.11ac provides more than enough bandwidth margin [4][10].


#### **8.3 Latency Budget Derivation**

WebRTC glass to glass worst case pipeline model:

`T_total = T_capture + T_encode + T_network + T_jitter + T_decode`

`T_capture ≤ 50 ms (camera and vitals capture @30 fps)`

`T_encode ≤ 30 ms (H.264 hardware accelerated encode)`

`T_network ≤ 20 ms (local 802.11ac transport, good RSSI)`

`T_jitter ≤ 150 ms (WebRTC jitter buffer worst case)`

`T_decode ≤ 50 ms (decode + render on laptop)`

`T_total,max = 50 + 30 + 20 + 150 + 50 = 300 ms ≈ 0.3 s`

Since:

`0.3 s < 1.0 s constraint`

The subsystem meets the latency requirement of `<1 s` with margin [2][5][6].

#### **8.4 Error Rate and Packet Loss Compliance**

Constraint:

`Error Rate < 1%` 

`Packet delivery ratio ≥ 99% IP layer after MAC retries + WebRTC FEC recovery`

Justified by design components:

- 802.11ac MAC layer retransmissions
- WebRTC FEC and packet loss concealment [5][6]
- Link margin budget derived above
- AES–128 secure RF transport [2][9]

If IP packet delivery ratio is 99%+ (expected under 40m design range as shown above), then recovered media streams remain within the `<1% error rate constraint` after MAC retries and WebRTC recovery [5][6].  

#### **8.5 Weight and Payload Sensitivity Analysis**
To ensure the subsystem remains within the Aurelia X4's payload limits while maintaining maximum performance, a weight-reduction trade-off was performed between the primary and contingency hardware configurations:
- Primary (USB): The TP-Link Archer T4U Plus weighs approximately 170g (including integrated cables and high-gain antennas). This configuration is prioritized for its superior link margin and 5dBi signal gain.
- Contingency (M.2): The Intel 8265 M.2 alternative weighs <30g (including U.FL pigtails and lightweight dipole antennas).

While the USB adapter provides the best communication stability, the M.2 card offers a 140g weight saving. This contingency path is maintained to ensure the subsystem can be optimized if the overall drone flight time or center of gravity is significantly compromised during final assembly.


## References
[1] UAV Systems International, “Aurelia X4 Standard – Ready To Fly,” product page, accessed Dec. 2, 2025. [Online]. Available: [Link](https://uavsystemsinternational.com/products/aurelia-x4-standard)

[2] Cubepilot, “Herelink FAQ,” documentation site, section “Herelink encryption,” accessed Dec. 2, 2025. [Online]. Available: [LINK](https://docs.cubepilot.org/user-guides/herelink/herelink-faq)

[3] NVIDIA, “Jetson Nano Developer Kit User Guide,” DA_09402_003, Dec. 2019. [Online]. Available: [LINK](https://developer.download.nvidia.com/embedded/L4T/r32-3-1_Release_v1.0/Jetson_Nano_Developer_Kit_User_Guide.pdf)

[4] IEEE, “IEEE Std 802.11-2020: IEEE Standard for Information Technology – Telecommunications and Information Exchange Between Systems – Local and Metropolitan Area Networks – Specific Requirements – Part 11: Wireless LAN Medium Access Control (MAC) and Physical Layer (PHY) Specifications,” Feb. 2021. [Online]. Available: [LINK](https://standards.ieee.org/ieee/802.11/7028/)

[5] W3C, “WebRTC 1.0: Real-Time Communication Between Browsers and Devices,” W3C Recommendation, Mar. 13, 2025. [Online]. Available: [LINK](https://www.w3.org/TR/webrtc/)

[6] Nanocosmos, “What is WebRTC Latency,” Technical Article, Accessed Dec. 2, 2025.Available: [LINK](https://www.nanocosmos.de/blog/webrtc-latency/)

[7] Cisco Systems, “Understanding WLAN Packet Error Rate versus RSSI,” Technical Documentation, Accessed Dec. 2, 2025. Available: [LINK](https://www.cisco.com/)  

[8] Defense Health Agency, “DHA Administrative Instruction 6000.02: Audio and Video Recording of Patients,” Aug. 5, 2022.  Available: [LINK](https://www.health.mil/Reference-Center/DHA/Publications/2022/08/05/DHA-AI-6000-02 ) 

[9] CubePilot, “Herelink Air Unit Specifications,” Cubepilot Product Page, Accessed Dec. 2, 2025.  Available: [LINK](https://cubepilot.org/)

[10] Federal Communications Commission, “FCC Test Report: TP Link Archer T4U Plus,” FCC Filing Database, Accessed Dec. 2, 2025. Available: [LINK](https://fccid.io/)

[11] Intel Corp., "USB 3.0* Radio Frequency Interference Impact on 2.4 GHz Wireless Devices," White Paper, Apr. 2012. [Online]. Available: [LINK](https://www.usb.org/sites/default/files/327216.pdf)

[12] ArduPilot Development Team, “MAVLink Telemetry Streams,” ArduPilot Documentation, Accessed Dec. 2, 2025.  Available: [LINK](https://ardupilot.org/)

[13] OpenCV Team, "Getting Started with Video," OpenCV 4.x Documentation, 2024. [Online]. Available: [LINK](https://docs.opencv.org/4.x/dd/d43/tutorial_py_video_display.html)
