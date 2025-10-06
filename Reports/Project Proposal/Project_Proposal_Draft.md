# Team 8 - DARPA Triage Drone Proposal

## Introduction
Aviation drones are useful tools in the modern age for scanning areas too difficult or dangerous for first responders to effectively search. These drones may assist in assessing the severity of an emergency and the conditions and locations of victims by leveraging on-board sensors and algorithms, allowing first responders to effectively triage the victims of a disaster. For minimum use of responders’ time, a drone could be semi-autonomous as well, automatically routing to victims and relaying their positions and conditions with little human input. Drones with these capabilities would save responders’ extremely valuable time and resources, saving lives in the process. Currently, no drones have the capability to analyze and prioritize victims of disasters by severity of injury, which is something the Defense Advanced Research Projects Agency (DARPA) has created a challenge to address.  

In search and rescue (SAR) operations, these drones could provide a semi-autonomous initial canvassing of an area to determine locations of human casualties and assess victims’ injuries and conditions. This could then be followed up with a helicopter and/or ground medical team to efficiently distribute aid to those most in need of it. This proposal will outline a project focused on designing and building a drone to meet these objectives. In the coming sections of this proposal, the more specific goals and objectives will be expanded upon as well as the specifications and constraints that the team will work around. The team will also examine current solutions to this problem and other approaches and then provide an argument of why this project is more effective than other contemporary solutions. 

## Challenges and Obstacles
- Weight: Adding/improving the necessary sensors and camera components 
- Degraded Sensing: Drone sensors reliably function through degraded conditions such as dust, fog, mist, smoke, loud sounds (explosives), hot spots and flashing lights 
- Flight Duration: Drones typically have a short flight duration, especially with the size and weight needed for this functionality. 
- Range: The distance a drone can travel is dependent on weather, battery size, and weight. 
- Pathfinding: Image processing or other sensing methods are necessary to give the drone semi-autonomous flight capabilities. 
- GPS Denial: Some areas have structures or obstacles that obscure, weaken, or block GPS signals, which means that the drone would have to rely on other methods to path find. 
- Geo-Location: Enhance or implement new sensors to detect and locate victims who may be partially or completely obscured. 

While the drone will retain manual control capabilities from the previous team’s design, there will be more of a focus semi-autonomous functionality in tandem with geo-location. This will allow greater efficiency in locating and determining the condition of individuals without the need for a manual operator.

## Specification
1. **The system shall obtain the presence of a heartbeat and its frequency (range 0.45 to 2.92 Hz).**  
   - Measure of success: Able to detect a simulated heartbeat accurately of a stationary target 70% of the time.
2. **The system shall accomplish all functionality from at least one meter away.**  
   - Measure of success: Drone completes all the listed measures of success from 1 meter away.
3. **The system shall obtain the breathing rate and frequency (range 0.13 to 1 Hz).**  
   - Measure of success: Using group members breathing at a set rate at room temperature as a control, the drone accurately reads this set rate within a 20% margin of error.
4. **The system shall give vocal commands using the speaker and listen for responses to evaluate the cognitive ability of a victim.**  
   - Measure of success: Being able to verbally communicate from operator to drone. The operator and victim should be able to clearly hear each other.
5. **The system shall limit the audio frequency received between 80 to 255 Hz.**  
   - Measure of success: Test different frequencies in and out of range to ensure the drone receives only specified frequencies.
6. **The system shall not store any voice recordings in compliance with the two-party consent laws for select states.**  
   - Measure of success: Provide documentation that the software does not save audio recordings in nondynamic memory.
7. **The system shall operate at full functionality for 15 to 60 minutes.**  
   - Measure of success: Time the drone in each operating condition until the drone runs out of battery. Drone will inform the user when the battery is below 10%.
8. **The system shall display triage results and vitals wirelessly.**  
   - Measure of success: Triage results will display accurate data on the controller interface that is readable for first responders.
9. **The system shall weigh less than 20 pounds as per DARPA’s requirements for the Drone Triage Challenge or DTC **[[1](#references)]**.**
    - Measure of success: The drone will be placed on a scale and will read under 20 lbs.
10. **The system shall display results in close to real time.**
    - Measure of success: Using synced stopwatches, two group members will be placed at the max range away. The drone will then take simulated measurements, and the results will be analyzed to find the average latency for measurements. Ensure this latency does not exceed 1000 ms at full range.
11. **The drone shall operate during daylight hours on a clear day without wind.**
     - Measure of success: The drone shall be able to operate in clear conditions, with wind speeds less than 10 mph.
12. **The drone shall operate in low visibility conditions.**
     - Measure of success: The drone shall be able to operate in low visibility conditions such as fog or smoke with the same capability as clear conditions.
13. **The drone shall operate under mildly windy conditions.**
     - Measure of success: The drone shall operate outdoors on a mildly windy day, or while having a fan pointed at the drone without loss of stability or sensing accuracy.
14. **The system shall allow a human operator to assume full manual control of the drone at any time, overriding autonomous functions.**
     - Measure of success: In a simulated failure mode, operator override occurs within ≤ 2 seconds and drone responds accordingly.
15. **The drone shall enter a safe hover or auto-land mode if communication with the operator is lost for more than 10 seconds.**
     - Measure of success: Communication link is cut during test flights; drone executes pre-programmed fail-safe procedure.

## Constraints
1. The drone SHALL be user-friendly.  
2. The drone SHALL have an integrated system for security.  
3. The drone SHALL remain under 400 ft above ground level **[[9](#references)][[10](#references)]**.  
4. The drone SHALL not exceed 100 mph **[[9](#references)][[10](#references)]**.  
5. The drone SHALL be equipped with anti-collision lighting **[[9](#references)][[11](#references)]**.  
6. The drone SHALL utilize encrypted wireless communication conforming to IEEE 802.11 standards for control and data transmission **[[15](#references)]**.
7. The EMI test setup shall maintain all measurement tolerances within the limits specified by MIL-STD-461G § 4.3.1 **[[16](#references)]**.
8. The system shall operate at an autonomy level functionally equivalent to SAE J3016 Level 3, where the drone can perform mission tasks under limited conditions while maintaining continuous human oversight **[[17](#references)]**.

## Relevant Literature
The team will have to research the following fields of study to build a successful search and rescue (SAR) drone:
- Vitals detecting via radar  
- Image processing  
- Drone programming  


### Radar

#### General Overview
The National Library of Medicine has conducted research into reading a subject's vital signs remotely. Their findings highlight several engineering challenges that must be addressed when integrating radar into SAR drones. These include minimizing signal noise from drone movement, distinguishing between heart rate and respiration, and maintaining low power consumption while ensuring reliable performance.


#### Key Considerations

- Fine-tuning radar signals to avoid interference from drone vibrations or external motion.
- Differentiating between heart rate and breathing rate, both of which fall within the 0.1–3 Hz frequency range.
- Designing for minimal power consumption without sacrificing signal fidelity.
- Implementing onboard processing to reduce latency and improve real-time responsiveness.


#### Example: Hovering UAV with Ultra-Wideband Radar
In [15], a hovering UAV was equipped with an Ultra-wideband radar system capable of detecting small chest movements caused by breathing and heartbeat. Because the radar operates in the same frequency range as drone-induced vibrations, the system faced interference challenges. To overcome this, the project implemented a data-driven motion cancellation technique called **signal of opportunity**, which uses echoes from stationary surfaces (e.g., ground or buildings) as reference signals.

The UAV estimates its own vibration signature using these references, applies a spatial filter to isolate noise, and then uses a differential noise cancellation filter to clean the signal. For power efficiency, the drone includes onboard digital signal processing (DSP) hardware to handle filtering and analysis in real time.

- **Benefits**:
  - Enables non-contact vital sign detection in disaster zones.
  - Uses environmental reflections to cancel drone-induced noise.
  - Incorporates onboard DSP for low-latency signal processing.

- **Drawbacks**:
  - Sensitive to cluttered environments and reflective interference.
  - Requires precise calibration and filter tuning.
  - Adds computational and hardware complexity to the drone system.

- **Key Takeaways**:
  - Use signal of opportunity techniques to mitigate UAV vibration interference.
  - Design spatial and differential filters tailored to SAR environments.
  - Integrate low-power DSP modules to handle radar signal processing onboard.

*Additional radar configurations and filtering strategies will be explored as part of the sensor integration phase.*


### Image Processing

#### General Overview
NVIDIA has published guidance on using the Jetson Nano for search and rescue applications [6]. Their recommendations emphasize real-time image processing strategies that prioritize speed and efficiency — critical for onboard systems in time-sensitive missions. Key steps include reducing image complexity, focusing on likely targets, and training detection algorithms for rapid inference.

#### Key Considerations

- Prioritizing speed over detail when scanning large landscapes.
- Cropping images to isolate regions with likely human targets.
- Training detection algorithms on SAR-specific datasets.
- Managing Jetson Nano’s limited processing power for real-time performance.


#### Example: YOLOv5 on Jetson Nano for Victim Detection
Ciccone and Ceruti [10] implemented YOLOv5 on Jetson Nano to detect human figures in disaster zones. Their system achieved real-time detection at 2FPS, demonstrating a compact and deployable solution for autonomous victim identification. However, the Jetson Nano’s limited processing speed posed challenges for complex triage operations, especially in cluttered or high-resolution environments.

- **Benefits**:
  - Enables real-time detection on low-cost, embedded hardware.
  - Compact and energy-efficient for field deployment.
  - Proven effectiveness in daylight and open terrain scenarios.

- **Drawbacks**:
  - Frame rate limitations restrict responsiveness in fast-moving or complex scenes.
  - Struggles with high-resolution input or multi-target detection.
  - May require external acceleration or hardware upgrades for advanced tasks.

- **Key Takeaways**:
  - Use YOLOv5 for lightweight, real-time detection in SAR missions.
  - Crop and downscale input images to reduce computational load.
  - Consider Jetson Xavier or external GPU modules for higher throughput.
  - Train models on SAR-specific datasets to improve detection accuracy.

*Additional image processing models and hardware configurations will be evaluated as part of system optimization.*


### Deep Learning for Object Detection

#### General Overview
Deep learning models — especially YOLO (You Only Look Once) — are widely used in SAR missions for real-time object detection. These models excel at identifying small, partially obscured targets such as human figures in rubble, forested areas, or disaster zones. When deployed on edge computing platforms like NVIDIA Jetson, they enable onboard inference without relying on remote servers — a critical capability for time-sensitive rescue operations [13][6].

#### Key Considerations

- Selecting the right model architecture (e.g., YOLOv5 vs. YOLOv8) based on speed vs. accuracy trade-offs.
- Training on SAR-specific datasets to improve detection of obscured or partially visible human targets.
- Managing thermal and power constraints when deploying on embedded systems like Jetson Nano.
- Integrating multi-modal sensor data (e.g., radar, thermal) to improve detection in low-visibility conditions.

#### Example: YOLOv5 on Jetson Nano for Victim Detection
In [13], YOLOv5 was deployed on drones to detect small human figures in rubble with real-time performance. The system achieved high recall rates in daylight conditions but struggled in smoke-filled or low-light environments. To address this, the team integrated thermal sensors and radar overlays to improve detection reliability.

- **Benefits**:
  - Real-time detection of small objects with high frame rates [13].
  - Efficient deployment on embedded systems like Jetson, reducing latency [6].
  - Scalable across diverse environments with proper dataset tuning.

- **Drawbacks**:
  - Accuracy drops in low-light, foggy, or cluttered scenes.
  - Requires large, SAR-specific datasets to minimize false positives.
  - Deep learning models are often opaque, making decisions hard to interpret.

- **Key Takeaways**:
  - Use SAR-augmented datasets and synthetic data generation to improve detection reliability.
  - Fuse YOLO outputs with radar and thermal sensors to enhance detection in obscured conditions [7].
  - Implement confidence scoring and ensemble methods to reduce false alarms.
  - Optimize Jetson deployment for power and thermal constraints [6].

*Additional model comparisons and sensor fusion strategies will be explored in future iterations of the system design.*


### UAV Path Planning

#### General Overview
To enable autonomous navigation with minimal operator input, SAR drones must employ robust path-planning algorithms capable of adapting to dynamic environments. A comprehensive MDPI review [8] outlines the major approaches and challenges in this domain. Effective path planning ensures the drone reaches potential victims quickly and safely, even in unpredictable terrain.


#### Key Considerations

- Choosing the right path-planning approach: classical algorithms (e.g., A*), bio-inspired methods (e.g., ant colony optimization), or AI/ML techniques (e.g., reinforcement learning).
- Balancing energy efficiency with computational load, given battery and onboard processor constraints.
- Ensuring robustness in dynamic environments, including obstacle avoidance and terrain variability.

#### Example: Lantern Explorer Project
The Lantern Explorer project [11] demonstrates a LiDAR-based navigation system using the Livox Mid-360 sensor. It combines LiDAR inertial odometry for mapping, velocity, and orientation, and uses the Fuel 360 algorithm for adaptive path optimization.

- **Benefits**:
  - High-resolution mapping and real-time obstacle avoidance.
  - Autonomous route planning in cluttered or unknown environments.

- **Drawbacks**:
  - LiDAR systems are power-intensive and add weight.
  - May be cost-prohibitive for lightweight or budget-constrained platforms.

- **Key Takeaways**:
  - Use LiDAR for precision mapping in complex terrain.
  - Combine inertial odometry with adaptive algorithms for robust navigation.
  - Optimize scan frequency and processing to conserve battery life.

*Additional path-planning models (e.g., SARSA, hybrid A\*/D\* Lite, terrain-aware segmentation) are covered in the full research summary.*
 

## Timeline and Resources    
![https://raw.githubusercontent.com/ZenElle/F25_Team8_DARPAChallengeTriageDrone/main/Documentation/Gantt_Chart_1.png](https://github.com/TnTech-ECE/F25_Team8_DARPAChallengeTriageDrone/blob/9d5123e59a0d8adad053d43163a8aa5c8298888b/Documentation/Gantt_Chart_1.png)


<div align = "center">
  
| SUBSYSTEM   | DESCRIPTION            | QUANTITY | COST PER ITEM | TOTAL COST OF QUANTITY | JUSTIFICATION |
| :---------: | :--------------------- | :------: | :------------ | :--------------------- | :------------ |
| Geolocation | GPS Module             |    1     | $30           | $30                    | Provides coordinates for victim geotagging and operator situational awareness, which supports triage reporting and near real-time display (Specs 8 and 10). Also aids return-to-home and link-loss behaviors that depend on position data (Spec 15). |
| Geolocation | Microphone             |    2     | $10           | $20                    | Enables voice prompts and response capture for cognitive checks (Spec 4). Can be filtered to the 80–255 Hz band per specification (Spec 5). Recordings will not be stored to comply with two-party consent (Spec 6). |
| Path Finding| Lidar Sensor           |    1     | $350          | $350                   | Core perception input for obstacle detection and semi-autonomous path planning in dynamic scenes, especially in low-visibility conditions (Specs 12 and 13). Directly addresses Pathfinding and Degraded Sensing challenges and aligns with the UAV path-planning literature. |
| Drone Parts | Motor Replacement      |    1     | $150          | $150                   | Maintains propulsion reliability during integration and field tests with added payload mass. Reduces schedule risk from hardware failures and supports meeting the 15–60 minute operational testing window (Spec 7) and safe manual override testing (Spec 14). |
| 3D Filament | Sensor Casing/Mounting |    2     | $50           | $100                   | Custom mounts for LiDAR, GPS, and microphones to control orientation and reduce vibration-induced noise. Necessary for robust sensing accuracy in motion, which supports Specs 1, 3, 10, 12, and 13 and addresses the integration aspects called out in radar and image-processing sections. |
| **Total**   |                        |          |               | **$650**               |               |

</div>

## Set Goals

1. **Achieve Semi-Autonomous Flight**
   - **Objective:** Develop a drone capable of semi-autonomous operation through GPS-based waypoint navigation and environmental sensing technologies such as LIDAR or similar systems. The goal is for the drone to plan, generate, and follow its own safe flight paths with minimal human input.    
   - **Success Measurement:** The drone can independently navigate a predefined area using generated waypoints while avoiding obstacles and maintaining stable flight without continuous manual control.    

2. **Implement Voice-Based User Interaction**      
   - **Objective:** Expand and validate the system’s voice recognition and command features to enable human users to communicate status or identity directly to the drone (e.g., stating who they are or confirming if they are okay).    
   - **Success Measurement:** The drone successfully recognizes and responds to at least 90% of spoken commands in field conditions, supporting identification and communication in emergency or triage scenarios.    

3. **Increase Environmental Resilience** 
   - **Objective:** Design the drone to operate reliably in adverse environmental conditions, including smoke, wind, and low-visibility situations common in emergency response environments.    
   - **Success Measurement:** The drone maintains flight stability and sensor functionality in controlled tests simulating moderate wind speeds and reduced visibility (e.g., smoke or fog).    

4. **Enhance Search and Detection Capabilities** 
   - **Objective:** Integrate advanced sensing and processing methods that allow the drone to detect and locate individuals in obstructed or harsh conditions where normal visual detection is limited.   
   - **Success Measurement:** The drone successfully identifies and locates human subjects under partial visibility or interference conditions in at least 80% of test trials. 

## Impacts of a Rescue Drone

### Culture
- Advances in drone triage technology represent a shift in public perception of drones, from recreation or military use towards humanitarian and medical applications.  
- By demonstrating that drones can save lives in disasters, society begins to view high-tech innovation as lifesaving rather than disruptive.  
- This cultural acceptance can accelerate adoption of drones in other public safety domains, such as firefighting, hazardous waste monitoring, and disaster prevention.  

### Society
- Semi-autonomous drones extend the first responder's capabilities by providing eyes, ears, and sensors in hazardous zones before humans can safely enter.  
- Communities gain a higher sense of security, knowing that technology can rapidly detect victims in collapsed buildings, chemical spills, or wildfires.  
- New roles may emerge in emergency services, such as drone triage operators, AI navigator specialists, and drone medical responders.  
- Faster victim prioritization reduces mortality rates in disasters where time is the single most critical resource.  

### Environment
- Ground-based SAR operations often disturb ecosystems, requiring vehicles, cutting through forests, or heavy foot traffic.  
- Drones, especially lightweight UAVs, minimize the environmental footprint, flying above terrain instead of disturbing it.  
- Thermal and radar sensing allow for less intrusive detection of victims, avoiding unnecessary land disruption.  
- Semi-autonomous systems optimize flight paths, further reducing wasted energy and emissions compared to traditional rescue mobilizations.  

### Public Safety
- Rescue drones with low-visibility operations enable response in situations where helicopters cannot fly and humans cannot safely enter.  
- Real-time triage information reduces confusion and prevents wasted resources, ensuring the most critical victims are prioritized.  
- By preventing rescuers from entering dangerous areas prematurely, drones also protect the first responders’ lives.  

### Economy
- Traditional SAR methods require large teams, specialized vehicles, and high fuel cost. A single semi-autonomous drone can cut costs while covering more ground.  
- The development of SAR-specific drones fosters growth in the tech and manufacturing sectors, creating jobs in AI programming, sensor design, and drone maintenance.  
- Local economies benefit when advanced drone capabilities are incorporated into regional disaster response toolkits (fire departments, EMS, FEMA partnerships).  
- By demonstrating cost-effectiveness, drones may eventually reduce insurance costs related to disaster response, benefiting municipalities and taxpayers.  

## References
[[1](#specification)] DARPA Triage Challenge. [Online]. Available: [DARPA](https://triagechallenge.darpa.mil/). Accessed: 26-Jan-2024.    
    
[2] “DTC: FAQ,” DTC | FAQ. [Online]. Available: [DARPA](https://triagechallenge.darpa.mil/). Accessed: 26-Jan-2024.    
    
[3] R. Kloet and P. Mulder, "Drones in Search and Rescue: A New Era in Emergency Response," Journal of Unmanned Vehicle Systems, MDPI. [Online]. Available: [MDPI](https://www.mdpi.com/2072-4292/15/13/3266). Accessed: 30-Sep-2024.    
    
[[4](#constraints)] Federal Aviation Administration, “Airspace 101 – Rules of the Sky | Federal Aviation Administration,” Faa.gov, 2021. [FAA](https://www.faa.gov/uas/getting_started/where_can_i_fly/airspace_101) 
    
[[5](#relevant-literature)] “Autonomous Vehicles for Emergency Response and Disaster Relief - IEEE Public Safety Technology Initiative,” Ieee.org, 2024. [IEEE](https://publicsafety.ieee.org/topics/autonomous-vehicles-for-emergency-response-and-disaster-relief)    
    
[[6](#relevant-literature)] “Deep Learning in Aerial Systems Using Jetson | NVIDIA Technical Blog,” NVIDIA Technical Blog, Nov. 03, 2016. [NVIDIA](https://developer.nvidia.com/blog/deep-learning-in-aerial-systems-jetson/) Accessed Oct. 01, 2024.    
    
[[7](#relevant-literature)] M. Kebe, R. Gadhafi, B. Mohammad, M. Sanduleanu, H. Saleh, and M. Al-Qutayri, “Human Vital Signs Detection Methods and Potential Using Radars: A Review,” Sensors, vol. 20, no. 5, p. 1454, Mar. 2020, [DOI](https://doi.org/10.3390/s20051454).    
    
[8] W. Meng, X. Zhang, L. Zhou, H. Guo, and X. Hu, "Advances in UAV Path Planning: A Comprehensive Review of Methods, Challenges, and Future Directions," Drones, vol. 9, no. 5, p. 376, May 2025, [DOI](https://doi.org/10.3390/drones9050376).     
    
[[9](#constraints)] Federal Aviation Administration. (n.d.). Small Unmanned Aircraft System (sUAS). In Aeronautical Information Manual, Chapter 11, Section 2. Retrieved from [FAA](https://www.faa.gov/air_traffic/publications/atpubs/aim_html/chap11_section_2.html)     

[[10](#constraints)] Electronic Code of Federal Regulations, "14 CFR §107.51 Operating limitations for small unmanned aircraft." Available: [eCFR](https://www.ecfr.gov/current/title-14/chapter-I/subchapter-F/part-107/subpart-B/section-107.51?utm). Accessed: 04-Oct-2025. 

[[11](#constraints)] Electronic Code of Federal Regulations, "14 CFR §107.29 Operation at night." Available: [eCFR](https://www.ecfr.gov/current/title-14/chapter-I/subchapter-F/part-107/subpart-B/section-107.29?utm). Accessed: 04-Oct-2025.

[12] Federal Aviation Administration, "Remote Identification of Drones - 14 CFR Part 89 overview and toolkit." Available: [FAA](faa.gov/uas/getting_started/remote_id). Accessed: 04-Oct-2025.      

[[13](#relevant-literature)] F. Ciccone and A. Ceruti, “Real-Time Search and Rescue with Drones: A Deep Learning Approach for Small-Object Detection Based on YOLO,” Drones, vol. 9, no. 8, p. 514, 2025, [DOI](https://doi.org/10.3390/drones9080514 )

[[14](#relevant-literature)] L. Zhu, R. Zhong, D. Xie, and X. Yuan, “Lantern-Explorer: A Collision-Avoidance Autonomous Exploration Drone System Based on Laser SLAM with Optimized Hardware and Software,” ISPRS Annals of the Photogrammetry, Remote Sensing and Spatial Information Sciences, vol. X-G-2025, pp. 1077–1084, 2025, [DOI](https://doi.org/10.5194/isprs-annals-X-G-2025-1077-2025).	

[[15](#constraints)] IEEE, IEEE Standard for Information Technology—Telecommunications and Information Exchange Between Systems Local and Metropolitan Area Networks—Specific Requirements—Part 11: Wireless LAN Medium Access Control (MAC) and Physical Layer (PHY) Specifications—Amendment 1: Enhancements for High-Efficiency WLAN, in IEEE Std 802.11ax-2021 (Amendment to IEEE Std 802.11-2020), vol., no., pp. 1–767, May 19, 2021, [DOI](https://doi.org/10.1109/IEEESTD.2021.9442429). 

[[16](#constraints)] U.S. Department of Defense, MIL-STD-461G: Requirements for the Control of Electromagnetic Interference Characteristics of Subsystems and Equipment, Washington, D.C., 2015. Available: [NASA](https://s3vi.ndc.nasa.gov/ssri-kb/static/resources/MIL-STD-461G.pdf)   

[[17](#constraints)] SAE International. (2021). J3016: Taxonomy and Definitions for Terms Related to Driving Automation Systems for On-Road Motor Vehicles. SAE International, Warrendale, PA. Available: [SEA](https://www.sae.org/standards/content/j3016_202104/)      

## Statement of Contribution
The team worked on this proposal as a team through multiple revisions. Specifications and the Gantt chart were worked on together as a group while other sub-sections were delegated to individual members of the group. For revisions, the team met together to discuss changes that needed to be made. During revisions, different members were delegated to different sections to get a fresh set of eyes on each part of the document. The following breakdown shows who worked on what sections of the current version of the document:

- **Introduction:** Wyatt Wheeler  
- **Challenges and Obstacles:** Job Flores, Gideon Befekadu  
- **Specification:** Brody Smith  
- **Relevant Literature:** Job Flores  
- **Timeline:** Team Effort  
- **Resources:** Team Effort  
- **Constraints:** Brody Smith  
- **Set Goals:** Job Flores  
- **Impacts of Drone:** Zenkline Elle  
- **Master Editing:** Kasey Dyess

