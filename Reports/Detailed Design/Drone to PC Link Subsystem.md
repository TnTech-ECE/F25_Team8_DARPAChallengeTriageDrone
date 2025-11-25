# Drone to PC Link Subsystem

## Introduction

The Drone to PC Link subsystem enables all wireless communication between the triage drone and the operator’s laptop. The triage system uses the **Aurelia X4 Standard** multirotor platform, which supports the payload and power required to carry an onboard computing module such as the **NVIDIA Jetson Nano** **[REF: Aurelia X4 specifications]**. The Jetson Nano processes Doppler radar vitals, microphone audio, and camera video in real time **[REF: Jetson Nano capabilities]**.

The function of this subsystem is to transmit all processed data from the drone to the operator with high reliability, low latency, and full compliance with medical privacy requirements. Communication is achieved through **IEEE 802.11 based Wi Fi** using a compatible dual band USB adapter, such as a **TP Link Archer T4U Plus** class device that supports **802.11ac** **[REF: adapter specifications]**. Over this link, the subsystem delivers:

- Live video for visual triage assessment  
- Two way audio for cognitive testing  
- Processed heart rate, respiratory rate, and triage classification  
- Supporting telemetry for the user interface  

At the software level, the subsystem uses **WebRTC** for low latency audio and video streaming **[REF: WebRTC characteristics]** and **WebSockets** for transmitting vitals and telemetry data **[REF]**. These technologies satisfy the requirement for real time, peer to peer communication without storing any patient related information, as required by medical privacy standards **[REF: DHA AI 6000.02]**.

Within the overall triage system, the Drone to PC Link serves as the communication bridge between airborne sensing subsystems and the Interfacing subsystem on the ground laptop. Accurate and timely triage decisions depend on the reliable transmission of this data.


## Function of the Subsystem

The Drone to PC Link subsystem enables all wireless data exchange between the triage drone and the operator’s laptop. Its core function is to ensure that the information generated on the drone by the **Jetson Nano**, including video, audio, vitals data, and telemetry, is delivered to the operator in real time **[REF: Jetson Nano capabilities]**.

The subsystem performs the following roles:

### Transmit live video
Sends encoded camera video to the laptop for visual assessment during triage, using low latency streaming protocols **[REF: WebRTC video characteristics]**.

### Enable two way audio communication
Carries microphone audio from the drone to the laptop and sends operator audio back to the onboard speaker for cognitive testing **[REF: subsystem cognitive test requirement]**.

### Deliver vitals and telemetry data
Transfers processed heart rate, respiratory rate, and triage classification from the signal processing subsystem using reliable data channels such as WebSockets **[REF: WebSocket suitability]**.

### Provide a secure and standards compliant communication path
Uses **IEEE 802.11 Wi Fi** for wireless transport and encryption protocols built into WebRTC and WebSockets to protect transmitted data **[REF: IEEE 802.11]**.

### Ensure real time transmission without data storage
Supports direct streaming only, complying with medical privacy requirements that prohibit storing patient related video, audio, or telemetry **[REF: DHA AI 6000.02]**.

By performing these functions, the subsystem acts as the bridge between airborne sensors and the operator, ensuring that all triage critical information reaches the ground station quickly and accurately.



## Constraints

- The subsystem **MUST** comply with **IEEE 802.11ac** or **IEEE 802.11n** wireless communication standards to ensure sufficient throughput and compatibility with the Jetson Nano and Wi Fi adapter **[REF: IEEE 802.11 specifications]**.

- The subsystem **MUST** maintain an end to end latency of **less than 1 second** for video, audio, and telemetry transmission **[REF: WebRTC latency characteristics]**.

- The subsystem **MUST** not store any patient related audio, video, or telemetry data on either the drone or the laptop to meet medical privacy requirements **[REF: DHA AI 6000.02]**.

- The subsystem **MUST** maintain a packet error rate of **less than 1 percent** during normal operation to ensure accurate transmission of triage critical data **[REF: WebRTC error correction documentation]**.

- The subsystem **MUST** remain within the **power and payload limitations** of the Aurelia X4 Standard platform **[REF: Aurelia X4 payload specifications]**.

- The subsystem **MUST** operate reliably within the expected triage scenario distance of **20 to 50 feet** under line of sight **[REF: triage scenario requirement]**.

- The subsystem **MUST** avoid generating **RF interference** that would affect the Cube Orange flight controller or RC link **[REF: Cube Orange integration guidelines]**.

- The subsystem **MUST** comply with **budget limitations** for the communication hardware **[REF: project budget allocation]**.

- The subsystem **MUST** meet **ethical and socio economic requirements** by preserving victim privacy and transmitting only necessary information **[REF: medical data ethics reference]**.

It is important that these constraints are met due to the critical need for timely, accurate, and secure data transmission during emergency triage operations.


## Specifications

- The subsystem **SHALL** maintain **sub second transmission** of audio, video, and telemetry **[REF]**.

- The subsystem **SHALL** support sustained wireless throughput of **at least 5 to 10 Mbps** for real time video and audio transmission **[REF: Wi Fi throughput]**.

- The subsystem **SHALL** achieve a packet error rate **lower than 1 percent** **[REF]**.

- The subsystem **SHALL** integrate with the **Jetson Nano USB interface** and support compatible **802.11ac** wireless adapters under Linux **[REF: Jetson Wi Fi adapter documentation]**.

- The subsystem **SHALL** operate strictly on **IEEE 802.11ac or 802.11n** modes **[REF]**.

- The subsystem **SHALL** transmit all media and telemetry without storing any of the data locally **[REF: DHA 6000.02]**.

- The subsystem **SHALL** encrypt all transmitted data using **WebRTC security protocols** such as **DTLS** and **SRTP**, and secure WebSockets **[REF: WebRTC security documentation]**.

- The subsystem **SHALL** maintain a stable wireless connection throughout the expected operational range described in the triage scenario **[REF]**.

These specifications and constraints are rationalized in the **Overview of Proposed Solution**.

## Overview of Proposed Solution

The Drone to PC Link subsystem is designed to provide a reliable, low latency, and secure wireless communication pathway between the onboard **Jetson Nano** and the operator’s laptop. The proposed solution uses **IEEE 802.11ac Wi Fi** with a dual band USB adapter installed on the Jetson Nano and a matching adapter on the laptop **[REF: adapter specifications]**. This wireless link provides enough bandwidth to transmit real time video, audio, and vitals data while meeting the latency and throughput requirements defined in the specifications.

To support real time triage operations, the subsystem uses two primary communication methods:

### WebRTC for audio and video streaming
WebRTC supports peer to peer transmission, hardware accelerated H.264 encoding, encryption, and typical sub second latency, making it suitable for transmitting camera video and microphone audio from the drone to the laptop **[REF: WebRTC characteristics]**.

### WebSockets for vitals and telemetry data
WebSockets provide a persistent, low overhead data channel that reliably transmits processed heart rate, respiratory rate, and triage status from the Jetson Nano to the laptop interface **[REF: WebSocket functionality]**.

These technologies collectively satisfy the requirement for continuous, real time data transfer without storing any transmitted media or telemetry on either device, aligning with medical privacy rules **[REF: DHA AI 6000.02]**.

The subsystem also includes encryption through WebRTC’s **DTLS** and **SRTP** protocols and secure WebSocket connections to prevent unauthorized access or interception **[REF: WebRTC security documentation]**.

By combining **802.11ac wireless capability** with **real time communication protocols**, the proposed solution meets all subsystem specifications. It provides the throughput needed for video, the reliability required for accurate vitals transmission, the security required by medical ethical standards, and the low latency required for timely triage decision making.

## Interface with Other Subsystems

The Drone to PC Link subsystem serves as the communication bridge between the onboard components of the triage drone and the operator’s laptop. It interacts directly with several subsystems by receiving their output data, packaging it into appropriate transmission formats, and sending it wirelessly to the Interfacing subsystem on the laptop. The interfaces below describe the inputs, outputs, and data pathways in detail.

## Upstream Inputs to the Drone to PC Link Subsystem

### 1. Signal Processing Subsystem

**Input:**
- Processed heart rate  
- Processed respiratory rate  
- Triage classification data  
- Filtered Doppler radar waveform metrics  

**Transferred Data:**  
Structured numerical values representing vital signs and triage decisions. These values are encoded and transmitted using **WebSockets** or similar real time data channels **[REF: WebSocket functionality]**.

**Communication Method:**  
Digital data exchange on the Jetson Nano (for example, UART, SPI, or direct memory transfer depending on implementation), followed by wireless transport.


### 2. Vitals Sensor Subsystem

**Input:**
- Raw Doppler radar signal data  
- Breathing and heartbeat frequency measurements  

**Transferred Data:**  
Raw or semi processed radar data is forwarded to the Signal Processing subsystem, but final processed values pass through the Drone to PC Link. The subsystem transmits the processed vitals to the laptop **[REF]**.

**Communication Method:**  
Digital serial or SPI communication between sensor hardware and the Jetson Nano, followed by wireless transmission to the laptop.


### 3. Microphone and Speaker Subsystem

**Input:**
- Microphone audio data  
- Operator spoken audio returned to the drone speaker  

**Transferred Data:**  
Outgoing audio is streamed to the laptop for cognitive response checks. Incoming audio from the operator is routed back to the drone’s speaker. **WebRTC** supports both upstream and downstream audio streaming **[REF: WebRTC audio behavior]**.

**Communication Method:**  
Local digital audio interface on the Jetson Nano; WebRTC for wireless audio transmission.


### 4. Programmable Drone Subsystem (Aurelia X4 with Cube Orange)

**Input:**
- Telemetry data (GPS, attitude, battery status, flight status)  
- Optional camera feed if routed through the Jetson Nano  

**Transferred Data:**  
Telemetry values can be forwarded to the user interface for situational awareness. The subsystem may also receive small data packets such as operator commands or mode selections **[REF: Cube Orange telemetry integration]**.

**Communication Method:**  
MAVLink or similar protocol forwarded to the Jetson Nano; WebSockets or WebRTC data channels for wireless transmission.

## Downstream Output to the Interfacing Subsystem (Laptop)

The Interfacing subsystem receives all information transmitted by the Drone to PC Link, including:

- Live video stream from the onboard camera  
- Live audio from the drone microphone  
- Operator audio returned to the drone speaker  
- Processed heart rate and respiratory rate  
- Triage classification information  
- Telemetry and status data  

**Communication Method:**  
Data is delivered wirelessly using **IEEE 802.11ac** or **802.11n** Wi Fi with **WebRTC** for video and audio, and **WebSockets** for structured telemetry values **[REF]**.

The Interfacing subsystem then displays all incoming information on the laptop’s graphical interface.

### Summary of Data Pathways
| Subsystem                      | Data Provided to Drone to PC Link                   | Transmission Method to Laptop               |
| ------------------------------ | --------------------------------------------------- | ------------------------------------------- |
| Signal Processing Subsystem    | Heart rate, respiratory rate, triage classification | WebSockets **[REF]**                        |
| Vitals Sensor Subsystem        | Radar based vitals measurements                     | WebSockets after processing **[REF]**       |
| Microphone/Speaker Subsystem   | Outgoing and incoming audio                         | WebRTC **[REF]**                            |
| Programmable Drone Subsystem   | Telemetry and optional camera routing               | WebRTC or WebSockets **[REF]**              |
| Interfacing Subsystem (Laptop) | Receives all transmitted data                       | Wi Fi plus WebRTC or WebSockets **[REF]**   |


