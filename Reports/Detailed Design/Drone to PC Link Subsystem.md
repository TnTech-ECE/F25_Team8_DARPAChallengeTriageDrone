# Drone to PC Link Subsystem

## Introduction

The Drone to PC Link subsystem enables all wireless communication between the triage drone and the operator’s laptop. The triage system uses the **Aurelia X4 Standard** multirotor platform, which supports the payload and power required to carry an onboard computing module such as the **NVIDIA Jetson Nano** **[1]**. The Jetson Nano processes Doppler radar vitals, microphone audio, and camera video in real time **[2]**.

The function of this subsystem is to transmit all processed data from the drone to the operator with high reliability, low latency, and full compliance with medical privacy requirements. Communication is achieved through **IEEE 802.11 based Wi Fi** using a compatible dual band USB adapter, such as a **TP Link Archer T4U Plus** class device that supports **802.11ac** **[3]**. Over this link, the subsystem delivers:

- Live video for visual triage assessment  
- Two way audio for cognitive testing  
- Processed heart rate, respiratory rate, and triage classification  
- Supporting telemetry for the user interface  

At the software level, the subsystem uses **WebRTC** for low latency audio and video streaming **[4]** and **WebSockets** for transmitting vitals and telemetry data. These technologies satisfy the requirement for real time, peer to peer communication without storing any patient related information, as required by medical privacy standards **[5]**.

Within the overall triage system, the Drone to PC Link serves as the communication bridge between airborne sensing subsystems and the Interfacing subsystem on the ground laptop. Accurate and timely triage decisions depend on the reliable transmission of this data.


## Function of the Subsystem

The Drone to PC Link subsystem enables all wireless data exchange between the triage drone and the operator’s laptop. Its core function is to ensure that the information generated on the drone by the **Jetson Nano**, including video, audio, vitals data, and telemetry, is delivered to the operator in real time **[2]**.

The subsystem performs the following roles:

### Transmit live video
Sends encoded camera video to the laptop for visual assessment during triage, using low latency streaming protocols **[4]**.

### Enable two way audio communication
Carries microphone audio from the drone to the laptop and sends operator audio back to the onboard speaker for cognitive testing [7].

### Deliver vitals and telemetry data
Transfers processed heart rate, respiratory rate, and triage classification from the signal processing subsystem using reliable data channels such as WebSockets [8].

### Provide a secure and standards compliant communication path
Uses **IEEE 802.11 Wi Fi** for wireless transport and encryption protocols built into WebRTC and WebSockets to protect transmitted data [9].

### Ensure real time transmission without data storage
Supports direct streaming only, complying with medical privacy requirements that prohibit storing patient related video, audio, or telemetry **[6]**.

By performing these functions, the subsystem acts as the bridge between airborne sensors and the operator, ensuring that all triage critical information reaches the ground station quickly and accurately.



## Constraints

- The subsystem **MUST** comply with **IEEE 802.11ac** or **IEEE 802.11n** wireless communication standards to ensure sufficient throughput and compatibility with the Jetson Nano and Wi Fi adapter [9].

- The subsystem **MUST** maintain an end to end latency of **less than 1 second** for video, audio, and telemetry transmission **[4]**.

- The subsystem **MUST** not store any patient related audio, video, or telemetry data on either the drone or the laptop to meet medical privacy requirements **[6]**.

- The subsystem **MUST** maintain a packet error rate of **less than 1 percent** during normal operation to ensure accurate transmission of triage critical data **[4]**.

- The subsystem **MUST** remain within the **power and payload limitations** of the Aurelia X4 Standard platform **[1]**.

- The subsystem **MUST** operate reliably within the expected triage scenario distance of **20 to 50 feet** under line of sight [7].

- The subsystem **MUST** avoid generating **RF interference** that would affect the Cube Orange flight controller or RC link [11].

- The subsystem **MUST** comply with **budget limitations** for the communication hardware [7].

- The subsystem **MUST** meet **ethical and socio economic requirements** by preserving victim privacy and transmitting only necessary information **[6]**.

It is important that these constraints are met due to the critical need for timely, accurate, and secure data transmission during emergency triage operations.


## Specifications

- The subsystem **SHALL** maintain **sub second transmission** of audio, video, and telemetry **[4]**.

- The subsystem **SHALL** support sustained wireless throughput of **at least 5 to 10 Mbps** for real time video and audio transmission [9].

- The subsystem **SHALL** achieve a packet error rate **lower than 1 percent** **[4]**.

- The subsystem **SHALL** integrate with the **Jetson Nano USB interface** and support compatible **802.11ac** wireless adapters under Linux **[2]**.

- The subsystem **SHALL** operate strictly on **IEEE 802.11ac or 802.11n** modes **[4]**.

- The subsystem **SHALL** transmit all media and telemetry without storing any of the data locally [9].

- The subsystem **SHALL** encrypt all transmitted data using **WebRTC security protocols** such as **DTLS** and **SRTP**, and secure WebSockets **[4]**.

- The subsystem **SHALL** maintain a stable wireless connection throughout the expected operational range described in the triage scenario [7].

These specifications and constraints are rationalized in the **Overview of Proposed Solution**.

## Overview of Proposed Solution

The Drone to PC Link subsystem is designed to provide a reliable, low latency, and secure wireless communication pathway between the onboard **Jetson Nano** and the operator’s laptop. The proposed solution uses **IEEE 802.11ac Wi Fi** with a dual band USB adapter installed on the Jetson Nano and a matching adapter on the laptop **[3]**. This wireless link provides enough bandwidth to transmit real time video, audio, and vitals data while meeting the latency and throughput requirements defined in the specifications.

To support real time triage operations, the subsystem uses two primary communication methods:

### WebRTC for audio and video streaming
WebRTC supports peer to peer transmission, hardware accelerated H.264 encoding, encryption, and typical sub second latency, making it suitable for transmitting camera video and microphone audio from the drone to the laptop **[4]**.

### WebSockets for vitals and telemetry data
WebSockets provide a persistent, low overhead data channel that reliably transmits processed heart rate, respiratory rate, and triage status from the Jetson Nano to the laptop interface [8].

These technologies collectively satisfy the requirement for continuous, real time data transfer without storing any transmitted media or telemetry on either device, aligning with medical privacy rules **[5]**.

The subsystem also includes encryption through WebRTC’s **DTLS** and **SRTP** protocols and secure WebSocket connections to prevent unauthorized access or interception **[4]**.

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
Structured numerical values representing vital signs and triage decisions. These values are encoded and transmitted using **WebSockets** or similar real time data channels [8].

**Communication Method:**  
Digital data exchange on the Jetson Nano (for example, UART, SPI, or direct memory transfer depending on implementation), followed by wireless transport.


### 2. Vitals Sensor Subsystem

**Input:**
- Raw Doppler radar signal data  
- Breathing and heartbeat frequency measurements  

**Transferred Data:**  
Raw or semi processed radar data is forwarded to the Signal Processing subsystem, but final processed values pass through the Drone to PC Link. The subsystem transmits the processed vitals to the laptop **[4]**.

**Communication Method:**  
Digital serial or SPI communication between sensor hardware and the Jetson Nano, followed by wireless transmission to the laptop.


### 3. Microphone and Speaker Subsystem

**Input:**
- Microphone audio data  
- Operator spoken audio returned to the drone speaker  

**Transferred Data:**  
Outgoing audio is streamed to the laptop for cognitive response checks. Incoming audio from the operator is routed back to the drone’s speaker. **WebRTC** supports both upstream and downstream audio streaming **[4]**.

**Communication Method:**  
Local digital audio interface on the Jetson Nano; WebRTC for wireless audio transmission.


### 4. Programmable Drone Subsystem (Aurelia X4 with Cube Orange)

**Input:**
- Telemetry data (GPS, attitude, battery status, flight status)  
- Optional camera feed if routed through the Jetson Nano  

**Transferred Data:**  
Telemetry values can be forwarded to the user interface for situational awareness. The subsystem may also receive small data packets such as operator commands or mode selections [11].

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
Data is delivered wirelessly using **IEEE 802.11ac** or **802.11n** Wi Fi with **WebRTC** for video and audio, and **WebSockets** for structured telemetry values **[4]**.

The Interfacing subsystem then displays all incoming information on the laptop’s graphical interface.

### Summary of Data Pathways
| Subsystem                      | Data Provided to Drone to PC Link                   | Transmission Method to Laptop             |
| ------------------------------ | --------------------------------------------------- | ----------------------------------------- |
| Signal Processing Subsystem    | Heart rate, respiratory rate, triage classification | WebSockets **[4]**                        |
| Vitals Sensor Subsystem        | Radar based vitals measurements                     | WebSockets after processing **[4]**       |
| Microphone/Speaker Subsystem   | Outgoing and incoming audio                         | WebRTC **[4]**                            |
| Programmable Drone Subsystem   | Telemetry and optional camera routing               | WebRTC or WebSockets **[4]**              |
| Interfacing Subsystem (Laptop) | Receives all transmitted data                       | Wi Fi plus WebRTC or WebSockets **[4]**   |

## Buildable Schematic

The Drone to PC Link subsystem is implemented using commercial off the shelf components: the **NVIDIA Jetson Nano** and a **USB dual band Wi Fi adapter**. The Power subsystem is responsible for generating a regulated **5 V** supply from the drone battery. This detailed design only uses that regulated supply and does not modify or redefine any power conversion circuitry.

All wiring in this schematic focuses on:

- The Jetson Nano (onboard computer).  
- A TP Link Archer T4U Plus USB Wi Fi adapter.  
- Simple wiring to receive regulated 5 V from the Power subsystem.  
- An optional status LED connected to a Jetson GPIO pin.  

For full details on how the 5 V supply is generated and protected, see the Power and Circuitry subsystem schematic **[Power subsystem link here - ASK WYATT]**.

## Schematic Overview

![Jetson Nano Labels](https://github.com/user-attachments/assets/3c6912ec-956d-412d-822a-08875b2d18f8)


<p align="center"> <img width="601" height="1051" alt="Connection Diagram" src="https://github.com/user-attachments/assets/3e07892b-6bc6-459c-ae91-a0f173bc4c7b" /> </p>

## Notes

- **+5V_REG** and **GND** are provided by the Power subsystem and treated as external inputs.
- **J1** represents the Jetson Nano module, which is part of the Drone to PC Link + Signal Processing environment.  
- **U1** is the USB dual band Wi Fi adapter used to establish the IEEE 802.11 link.  
- Wireless communication is represented as a logical, not physical, connection.  


## Jetson Nano Power Interface

The Jetson Nano is powered directly from the regulated **5 V** output provided by the Power subsystem:

- **+5V_REG → J1 5 V input pin** or barrel connector, according to Jetson Nano carrier documentation **[2]**.  
- **GND → J1 ground pin(s)** and chassis ground **[4]**.

All details about how +5V_REG is produced (buck converter, protection circuits, battery interface) are defined in the Power subsystem schematic **Powersubsystemlinkhere**.


## USB Wi Fi Adapter Connection

The USB Wi Fi adapter is connected to a USB host port on the Jetson Nano:

- **J1 USB0 (Type A) → U1 USB plug**  
- Signals: **USB_VBUS**, **USB_D+**, **USB_D−**, **GND**

No additional components are required between J1 and U1 because the Jetson carrier board already includes USB protection and required terminations **[2]**.


## Data Interfaces to Other Subsystems

### To Signal Processing Subsystem

- **Interface:** Ethernet, UART, SPI, or other digital bus  
- **Purpose:** Receive processed vitals and telemetry data for packaging and wireless transmission **[4]**

### To Programmable Drone Subsystem (Cube Orange / FC)

- **Interface:** MAVLink over UART or UDP  
- **Purpose:** Optionally forward telemetry values to the laptop interface **[4]**

These detailed interfaces are defined in each subsystem’s documentation. The schematic above shows only the necessary attachment points for wireless transmission.


## Net List Summary

| Net Name        | Description                                 | Source                    | Destination                               |
|-----------------|---------------------------------------------|---------------------------|--------------------------------------------|
| +5V_REG         | Regulated 5 V from Power subsystem          | Power subsystem output    | J1 5 V input                               |
| GND             | Common ground                               | Power subsystem / drone   | J1 GND, U1 GND                             |
| USB_VBUS        | USB 5 V from Jetson USB host port           | J1 USB0                   | U1 USB VBUS                                |
| USB_D+ / D−     | USB 2.0 data lines                          | J1 USB0                   | U1 USB D+ / U1 USB D−                      |
| ETH_TX / RX *   | Ethernet differential pairs (if used)       | J1 Ethernet               | Signal Processing / Drone Comms subsystem  |
| UART_TX / RX *  | UART serial lines (if used)                 | J1 UART                   | Flight controller / Signal Processing      |

\* Exact use of Ethernet or UART is defined in the corresponding subsystem detailed designs.

This schematic provides enough detail for physical assembly of the Drone to PC Link subsystem, assuming the builder follows the Power subsystem schematic and the Jetson Nano documentation for pinout and mounting **[4]**.

## Flowchart

The Drone to PC Link subsystem includes software that runs on both the Jetson Nano (airborne) and the laptop (ground). The goal of this logic is to:

- Establish a secure Wi Fi connection.  
- Set up WebRTC for audio and video streaming **[4]**.  
- Set up WebSockets for vitals and telemetry **[4]**.  
- Ensure that no patient related data is stored at any point **[5]**.  

The flowcharts below describe the high level behavior. They are not tied to a specific language and can be implemented using Python, JavaScript, and HTML as outlined in the Interfacing Detailed Design.

All audio, video, and vitals are processed and streamed in memory only. No file writes or persistent storage are performed to comply with privacy constraints **[5]**.

<p align="center"> <img width="671" height="951" alt="Operational Flowchart" src="https://github.com/user-attachments/assets/703d66f5-0a35-4aae-934d-0cb3f852e2aa" /> </p>

This flow ensures that:

- All media and vitals data are streamed in real time.  
- Any disconnection leads to reconnection attempts and visible error reporting.  
- No received media or telemetry is written to disk, which maintains compliance with medical privacy and data handling requirements **[4]**.  

## Bill of Materials (BOM)

- The **Jetson Nano** is already budgeted in the Signal Processing or Computing subsystem.  
- The **Power subsystem** already includes all DC DC converters, battery interfaces, fuses, and protection circuitry.  
- Only the Wi Fi adapter and small optional interface components are included here.

| Item | Designator(s) | Description                                           | Manufacturer | Manufacturer P/N | Distributor | Qty | Unit Price (USD) | Notes |
| :--: | :-----------: | ----------------------------------------------------- | :----------: | :--------------: | :---------: | :-: | :--------------: | :---- |
| 1    | U1            | TP Link Archer T4U Plus USB Wi Fi Adapter            | TP Link      | Archer T4U Plus  | [Amazon](https://www.amazon.com/dp/B08KHV7H1S) | 1   | $29.99          | Primary Wi Fi adapter for Jetson Nano providing 802.11ac wireless link. |
| 2 (optional) | W1     | Hookup wire, 22–24 AWG, stranded                    | Generic      | N/A              | [Amazon](https://www.amazon.com/0-35mm%C2%B2-Electrical-Colors-Tinned-breadboard/dp/B09WHQ18KL) | 1   | $7.88           | Optional for short power or GPIO wiring to LED. |
| 3 (optional) | R1     | Series resistor for status LED (1 kΩ – 2.2 kΩ)       | Generic      | N/A              | [Amazon](https://www.amazon.com/Resistor-Tolerance-Resistors-Limiting-Certificated/dp/B08QRPRVMJ) | 1   | $5.49           | Current limiting resistor for optional LED. |
| 4 (optional) | LED1   | 3 mm or 0603 green LED for link status              | Generic      | N/A              | [Amazon](https://www.amazon.com/Blinking-Flashing-Electronics-Components-Indicator/dp/B0895MYM4F) | 1   | $5.99           | Optional indicator LED for link or streaming status. |


**Cost Summary**

- **Required Total:** $29.99  
- **Optional Total:** $19.36  
- **Grand Total (Required + Optional):** $49.35  


### Notes

- No PCB fabrication is required unless the project team chooses to add a small breakout board.  
- No additional USB protection components are listed because the Jetson Nano carrier board already includes USB protection circuitry.  
- Only one Archer T4U Plus is strictly required for the drone; the laptop may use built in Wi Fi.

This BOM represents the **minimum required hardware** for the Drone to PC Link subsystem.

## Analysis

This section provides a quantitative analysis showing that the Drone to PC Link subsystem can satisfy the latency, throughput, and reliability requirements using the Jetson Nano and the TP Link Archer T4U Plus Wi Fi adapter.

All numerical values below are **design assumptions** for analysis and must be validated experimentally during testing.


## 1. Throughput and Data Rate Analysis

We need to confirm that the Wi Fi link can carry:

- One compressed video stream  
- One audio stream  
- Telemetry and vitals data  

with comfortable margin.

### 1.1 Video bit rate

Assume the onboard camera streams H.264 video at:

- Resolution: 1280 × 720 (720p)  
- Frame rate: 30 fps  
- Compressed bit rate:  

`R_video = 3 Mbit/s`

This is a common design target for real time video at 720p with moderate quality.

### 1.2 Audio bit rate

Assume mono audio:

- Sample rate: 48 kHz  
- Sample size: 16 bits  
- Mono channel  

Raw bit rate:

`R_audio_raw = 48,000 × 16 = 768,000 bit/s = 0.768 Mbit/s`

With a typical audio codec such as Opus you can compress significantly. To be conservative, assume:

`R_audio ≈ 0.1 Mbit/s`

### 1.3 Vitals and telemetry bit rate

Assume vitals and telemetry are sent as small JSON messages at 10 Hz:

- Payload per message: 200 bytes (heart rate, respiratory rate, triage class, timestamps, flags)  
- Frequency: 10 messages per second  

Bit rate:

`R_telemetry = 200 bytes/msg × 8 bit/byte × 10 msg/s = 16,000 bit/s = 0.016 Mbit/s`

### 1.4 Total application payload rate

Total payload rate:

`R_total,payload = R_video + R_audio + R_telemetry  
                  = 3.0 + 0.1 + 0.016  
                  = 3.116 Mbit/s`

Even after adding protocol overhead (RTP, SRTP, UDP, IP, MAC headers), you can conservatively scale by a factor of 2:

`R_total,link ≈ 2 × 3.116 = 6.232 Mbit/s`

So if the wireless link can reliably support at least

`R_required ≈ 7 Mbit/s`

then your specification “The subsystem SHALL support a minimum sustained throughput of 5 to 10 Mbps” is justified.

Short range 802.11ac links under line of sight are typically capable of tens of Mbit/s or more, so 7 Mbit/s is well within realistic capability, with margin.



## 2. Latency Budget

The specification requires **end to end latency < 1 second** for video, audio, and data. We can break total latency into:

`T_total = T_capture + T_encode + T_network + T_decode + T_render`

We consider a reasonable design target for each term:

1. **Capture latency**  
   Camera exposure plus buffering:

   `T_capture ≈ 10 ms`

2. **Encode latency (Jetson Nano)**  
   Hardware H.264 encoder (NVENC) on Jetson is typically on the order of a few frames of delay.  
   For 30 fps, one frame period is:

   `T_frame = 1 / 30 s ≈ 33.3 ms`

   If the encoder introduces at most 2 frames of pipeline delay, then:

   `T_encode ≈ 2 × 33.3 ms ≈ 67 ms`

3. **Network latency (Wi Fi + WebRTC)**  
   For short range 802.11ac Wi Fi plus WebRTC over UDP, one way latency is typically in the tens of milliseconds if the link is not congested.  
   Assume:

   `T_network ≈ 50 ms`

4. **Decode latency (laptop)**  
   Hardware accelerated H.264 decode on a modern laptop can be assumed similar to encode, about 1 to 2 frames of latency:

   `T_decode ≈ 33 ms`

5. **Render latency**  
   Display pipeline on the OS and browser might add another frame of delay:

   `T_render ≈ 33 ms`

Now estimate total one way latency:

`T_total ≈ T_capture + T_encode + T_network + T_decode + T_render  
         ≈ 10 + 67 + 50 + 33 + 33 ms  
         ≈ 193 ms`

This is about:

`T_total ≈ 0.19 s`

which is well below 1 second. Even if real world conditions double this estimate, you still remain under the 1 second requirement:

`0.19 s × 2 = 0.38 s < 1 s`

So the latency specification is supported by conservative assumptions.



## 3. Packet Error Rate and Reliability

The constraint requires a packet error rate (PER) below 1 percent.

Let:

- `p` be the probability that a single packet is lost or corrupted on the link.  
- Suppose that at the MAC/PHY level, raw PER is around 5 percent in a conservative case due to collisions or interference.  
- Higher layers (WebRTC with FEC, NACKs, retransmissions) can reduce effective application level PER.

If we model application level PER as:

`p_app = p_raw × (1 − recovery_efficiency)`

Assume recovery mechanisms can correct or conceal 80 percent of lost packets:

`recovery_efficiency = 0.8`

then:

`p_app = 0.05 × (1 − 0.8)  
       = 0.05 × 0.2  
       = 0.01 = 1%`

Under typical short range, line of sight conditions, raw PER will usually be much lower than 5 percent, so this calculation shows that even in a conservative case the system can meet the **< 1 percent** application level PER constraint, assuming WebRTC’s built in FEC and retransmission model functions as designed.

For telemetry sent via WebSocket over TCP, the effective PER at the application level is essentially zero in normal operation, since TCP will retransmit until success or connection failure.



## 4. Range Considerations

The triage scenario specifies a drone distance of about 20–50 ft from the victim and operator. This is a relatively short range compared to typical indoor or outdoor Wi Fi.

If we treat the link as operating in free space for a rough estimate, the free space path loss at 5 GHz can be approximated by:

`FSPL (dB) = 20 log10(d) + 20 log10(f) + 32.44`

where:

- `d` is the distance in kilometers  
- `f` is the frequency in MHz  

For `d = 15 m = 0.015 km` and `f = 5000 MHz`:

`FSPL ≈ 20 log10(0.015) + 20 log10(5000) + 32.44  
      ≈ 20 (−1.824) + 20 (3.699) + 32.44  
      ≈ −36.48 + 73.98 + 32.44  
      ≈ 69.94 dB`

Typical 802.11ac systems can tolerate path losses significantly higher than 70 dB with standard transmit power and antenna gains, so at 15 m the link margin is comfortable. This supports the assumption that the throughput and latency performance used above is realistic for the 20–50 ft triage range.



## 5. Power and USB Constraints

The Archer T4U Plus draws power entirely from the Jetson Nano USB host port. For a basic power check:

Assume:

- Maximum current draw of the Archer T4U Plus:  
  `I_WiFi ≈ 500 mA`  
  (typical upper bound for a USB powered adapter; actual value should be checked in product documentation).  

- USB port rating on Jetson Nano: up to around 900 mA at 5 V for a USB 3.0 port in many designs (to be confirmed with Jetson documentation).

Then the power draw:

`P_WiFi = V × I = 5 V × 0.5 A = 2.5 W`

As long as the Power subsystem has budgeted at least this much extra current on the 5 V rail for the Jetson USB port, the constraint “The subsystem MUST remain within the power and payload limits” is achievable.



## 6. Summary of Constraint Satisfaction

- **Latency < 1 s**  
  Estimated `T_total ≈ 0.19 s` with generous safety margin.

- **Throughput ≥ 5–10 Mbit/s**  
  Required `R_total,link` is about `6.232 Mbit/s`, which is well below typical short range 802.11ac capacity.

- **Error rate < 1 percent**  
  Combination of short range, strong signal, and WebRTC recovery mechanisms supports this constraint.

- **No storage of patient data**  
  Achieved by using streaming only (WebRTC, WebSockets) and by not implementing any file based recording in software.

- **Range (20–50 ft)**  
  Free space path loss calculations show that this distance is trivial for 5 GHz Wi Fi with the assumed hardware.

Overall, these calculations support the conclusion that the proposed Drone to PC Link design can meet the specified performance and ethical constraints, provided that implementation follows the design assumptions and is verified in field tests.

----

## References

[1] "Aurelia X4 Standard - Ready To Fly," UAV Systems International, product page, accessed Nov. 24, 2025. [LINK](https://uavsystemsinternational.com/products/aurelia-x4-standard)  

[2] "Jetson Nano Developer Kit," NVIDIA Developer, board overview, documentation, and power requirements, accessed Nov. 24, 2025. [LINK](https://developer.nvidia.com/embedded/jetson-nano-developer-kit)  

[3] "Archer T4U Plus - AC1300 High Gain Dual Band USB Adapter," TP-Link product page, accessed Nov. 24, 2025. [LINK](https://www.tp-link.com/us/home-networking/usb-adapter/archer-t4u-plus/)  

[4] World Wide Web Consortium (W3C), "WebRTC 1.0: Real-Time Communication Between Browsers," Recommendation, accessed Nov. 24, 2025. [LINK](https://www.w3.org/TR/webrtc/)  

[5] Defense Health Agency, "DHA Administrative Instruction 6000.02: Photography, Videotaping, Filming, Recording, and Imaging of Patients, Visitors, and Staff," policy and fact sheet, accessed Nov. 24, 2025. (Available via the Defense Health Agency publications site.)  

[6] U.S. Department of Health and Human Services, "Summary of the HIPAA Privacy Rule," and related Privacy Rule resources, accessed Nov. 24, 2025. [LINK](https://www.hhs.gov/hipaa/for-professionals/privacy/index.html)  

[7] F24 DARPA Triage Drone Team, "Conceptual Design" and customer specification (scenario description, triage requirements, and internal performance targets), GitHub repository, accessed Nov. 24, 2025.  [LINK](https://github.com/TnTech-ECE/F24_Team5_DARPA_Triage_Drone/blob/main/Reports/Conceputal%20Design%20Final/Conceptual%20Design.md)

[8] I. Fette and A. Melnikov, "The WebSocket Protocol," RFC 6455, Internet Engineering Task Force (IETF), Dec. 2011. [LINK](https://datatracker.ietf.org/doc/html/rfc6455)  

[9] IEEE Computer Society, "IEEE Standard for Information Technology - Telecommunications and information exchange between systems - Local and metropolitan area networks - Specific requirements - Part 11: Wireless LAN Medium Access Control (MAC) and Physical Layer (PHY) Specifications," IEEE Std 802.11-2020, Feb. 2021.  

[10] Nanocosmos, "WebRTC Latency: Comparing Low-Latency Streaming Protocols," blog and related materials, accessed Nov. 24, 2025. [LINK](https://www.nanocosmos.de/blog/webrtc-latency/)  

[11] PX4 Autopilot Project, "Companion Computers" and MAVLink telemetry integration guides, accessed Nov. 24, 2025. [LINK](https://docs.px4.io/)  
