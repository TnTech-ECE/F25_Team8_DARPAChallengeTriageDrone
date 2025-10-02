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
- Geo-Location: Improve/add sensors to identify and locate fully or partially obscured individuals, to completely obscured in cases of being buried. 

While the drone will retain manual control capabilities from the previous team’s design, there will be more of a focus semi-autonomous functionality in tandem with geo-location. This will allow greater efficiency in locating and determining the condition of individuals without the need for a manual operator. 

As equipment is added to the drone, it can become heavier so balancing budget, and weight is an important factor. Safety and preventative measures will also have to be taken to safely charge the drone. Overcharging Lithium Polymer batteries can be very dangerous. This is especially of concern as Li-Po batteries are a popular choice for drones. 

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
3. The drone SHALL remain under 400 ft above ground level **[[9](#references)]**.  
4. The drone SHALL not exceed 100 mph **[[9](#references)]**.  
5. The drone SHALL be equipped with anti-collision lighting **[[9](#references)]**.  

## Relevant Literature
The team will have to research the following fields of study to build a successful search and rescue (SAR) drone:
- Vitals detecting via radar  
- Image processing  
- Drone programming  

### Radar
The National Library of Medicine has already done research into reading a subject's vitals at a distance. From their research, it is clear that the team will need to consider the following during the engineering process of the product:
- How to fine-tune the signal to avoid noise generated by the drone or any other external movement.  
- How to differentiate between a heart rate and a breathing rate.  
- How to consume minimal power with acceptable performance.  

### Image Processing
NVIDIA has an article on using the chip the drone will be working with, a Jetson Nano, for search and rescue purposes. From the text, several steps in the image computing process include **[[6](#references)]**:
- Prioritizing speed over detail when observing the landscape.  
- Cropping images with likely targets to optimize processing.  
- Using an algorithm to train the data.  

### Drone Programming
Since the drone will spend the majority of its time searching, it is important to consider potential strategies for navigating any potential terrain. The IEEE explains some important considerations regarding this:
- SAR drones are built to be safe and reliable, following UN regulations.  
- SAR drones should avoid disrupting the flow of traffic or any other service.  
- SAR drones can optimize their routes to better their performance.  

Above are the references and considerations from the previous group’s proposal. Not sure if we want to keep all of them or not. Below is or are the added considerations for the additions that we are planning for.

## UAV Path Planning
Since the drone should be able to decide on and follow a path on its own, with minimal input from an operator, algorithms must be employed to find the best path in a dynamic environment. Methods and challenges are highlighted and discussed in an MDPI journal review [8]. Key considerations that the team is faced with include:
- Deciding on the right path-planning approach: classical algorithm, bio-inspired, or AI or ML techniques.  
- Balance energy efficiency with computational load due to battery and computer constraints.  
- Ensuring robustness in dynamic environments is imperative to get to potential victims in the quickest time possible in spite of obstacles.  

## Timeline and Resources    
![https://raw.githubusercontent.com/ZenElle/F25_Team8_DARPAChallengeTriageDrone/main/Documentation/Gantt_Chart_1.png](https://github.com/TnTech-ECE/F25_Team8_DARPAChallengeTriageDrone/blob/9d5123e59a0d8adad053d43163a8aa5c8298888b/Documentation/Gantt_Chart_1.png)


<div align = "center">
  
| SUBSYSTEM   | DESCRIPTION            | QUANTITY | COST PER ITEM  | TOTAL COST OF QUANTITY |
| :---------: | :--------------------: | :------: | :------------: | :--------------------: |
| Geolocation | GPS Module             |    1     | $30            | $30                    |
| Geolocation | Microphone             |    2     | $10            | $20                    |
| Path Finding| Lidar Sensor           |    1     | $350           | $350                   |
| Drone Parts | Motor Replacement      |    1     | $150           | $150                   |
| 3D Filament | Sensor Casing/Mounting |    2     | $50            | $100                   |
| **Total**   |                        |          |                | **$650**               |

</div>


## Set Goals
1. **Ensure Cost-Effectiveness and Budget Optimization**  
   - Objective: Manage and allocate funds and budget to balance the drone’s capabilities and performance.  
   - Measurement: How well the team tracks and accounts for each financial decision made throughout the project. How well the team is capable of conducting an analysis comparing the cost of products to the benefits that will provide to the drone’s performance.

2. **Maximize Drone Effectiveness**  
   - Objective: Enhance the capabilities of the drone making it as effective as possible with the materials we order.  
   - Measurement: Analyze how close the drone comes to achieving the measures of success. Routinely evaluate the trajectory of the team to ensure the timeline is kept and project scope is kept within bounds.

3. **Ensure Usability and Safety**  
   - Objective: Optimize the drone's features to create a more user-friendly device that operates safely.  
   - Measurement: The success rate of how well the drone operates without failure. How easy and effective the drone’s operation is when operated by different users. How effective the instruction on the drone’s usage is.

4. **Ensure Reliable Semi-Autonomous Flight**  
   - Objective: Optimize the drone’s semi-autonomous flight capabilities, especially pathfinding and obstacle avoidance.  
   - Measurement: The reaction time of the drone when an obstacle appears in its path. How fast the drone can correct its course if moved off in any way. How quickly the drone can find a path and arrive at potential victims.

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
[[1](#specification)] DARPA Triage Challenge. [Online]. Available: https://triagechallenge.darpa.mil/. [Accessed: 26-Jan-2024].    
    
[2] “DTC: FAQ,” DTC | FAQ. [Online]. Available: https://triagechallenge.darpa.mil/faq. [Accessed: 26-Jan-2024].    
    
[3] R. Kloet and P. Mulder, "Drones in Search and Rescue: A New Era in Emergency Response," Journal of Unmanned Vehicle Systems, MDPI. [Online]. Available: https://www.mdpi.com/2072-4292/15/13/3266. [Accessed:30-Sep-2024].    
    
[[4](#constraints)] Federal Aviation Administration, “Airspace 101 – Rules of the Sky | Federal Aviation Administration,” Faa.gov, 2021. https://www.faa.gov/uas/getting_started/where_can_i_fly/airspace_101  
    
[[5](#relevant-literature)] “Autonomous Vehicles for Emergency Response and Disaster Relief - IEEE Public Safety Technology Initiative,” Ieee.org, 2024. https://publicsafety.ieee.org/topics/autonomous-vehicles-for-emergency-response-and-disaster-relief    
    
[[6](#relevant-literature)] “Deep Learning in Aerial Systems Using Jetson | NVIDIA Technical Blog,” NVIDIA Technical Blog, Nov. 03, 2016. https://developer.nvidia.com/blog/deep-learning-in-aerial-systems-jetson/ (accessed Oct. 01, 2024).    
    
[[7](#relevant-literature)] M. Kebe, R. Gadhafi, B. Mohammad, M. Sanduleanu, H. Saleh, and M. Al-Qutayri, “Human Vital Signs Detection Methods and Potential Using Radars: A Review,” Sensors, vol. 20, no. 5, p. 1454, Mar. 2020, doi: https://doi.org/10.3390/s20051454.    
    
[8] W. Meng, X. Zhang, L. Zhou, H. Guo, and X. Hu, "Advances in UAV Path Planning: A Comprehensive Review of Methods, Challenges, and Future Directions," Drones, vol. 9, no. 5, p. 376, May 2025, doi: 10.3390/drones9050376.     
    
[[9](#constraints)] Federal Aviation Administration. (n.d.). Small Unmanned Aircraft System (sUAS). In Aeronautical Information Manual, Chapter 11, Section 2. Retrieved from https://www.faa.gov/air_traffic/publications/atpubs/aim_html/chap11_section_2.html     

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

