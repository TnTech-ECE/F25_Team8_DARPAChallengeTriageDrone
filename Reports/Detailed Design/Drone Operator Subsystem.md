# Weight Distribution and Sensor Placement Detailed Design  
**DARPA Triage Drone – Aurelia X4 Standard Platform**

---

## 1. Subsystem Overview

In the DARPA Triage Drone project, the Weight Distribution and Sensor Placement subsystem is responsible for physically integrating all triage-related hardware onto the **Aurelia X4 Standard** multirotor and ensuring the modified drone remains safe, controllable, and within all mass and regulatory limits.

This subsystem:

- Mounts the triage payload into a **3D-printed “belly pack” module** under the Aurelia X4 airframe.
- Keeps total payload within the **1.5 kg (3.3 lb)** capability of the Aurelia X4 Standard and below the **UAV MTOW of 5.212 kg (11.49 lb)** for the standard battery configuration.
- Maintains the overall **center of gravity (CG)** near the geometric center of the quadcopter and near the rotor plane, so the flight controller still behaves as intended.
- Provides mounting locations and orientations for:
  - The vitals Doppler radar
  - Microphone and speaker (cognitive test subsystem)
  - Jetson reComputer J1020 v2 (signal processing)
  - ADC and analog front-end boards
  - Power converters and associated wiring

This design document describes the constraints, proposed mechanical solution, mass budget, CG methodology, and verification plan for this subsystem.

---

## 2. Applicable Requirements and Constraints

This detailed design inherits the high-level constraints from the conceptual design and adds new ones specific to weight distribution and sensor placement.

### 2.1 Drone Platform Constraints

From the Aurelia X4 Standard specifications:

- UAV Empty Weight (no battery): **2450 g (5.40 lb)**
- UAV Weight including standard battery: **3712 g (8.18 lb)**
- Payload capability: **1500 g (3.3 lb)**
- UAV MTOW with standard battery: **5212 g (11.49 lb)**
- Max flight speed: **35 mph (56 km/h)**
- Max wind resistance: **20 mph (32 km/h)**
- Max service ceiling: **3000 m ASL**

These values define the hard limits for any payload and mounting solution.

### 2.2 Weight & CG Requirements

For this subsystem, the following requirements are defined:

1. **[W-1] Payload mass limit**  
   The triage payload (Jetson, Doppler radar, ADC, mic/speaker module, converters, 3D-printed belly pack, and all wiring) **SHALL have total mass ≤ 1.5 kg** to stay within Aurelia X4 payload capability.

2. **[W-2] MTOW compliance**  
   The combined mass of **Aurelia X4 + standard battery + triage payload** **SHALL NOT exceed 5.212 kg**.

3. **[W-3] Vitals sensor mass**  
   The vitals sensor assembly (Doppler radar, analog front-end, ADC board, and local bracket) **SHALL weigh less than 0.5 lb (~0.227 kg)**, consistent with the original conceptual requirement on vitals hardware.

4. **[W-4] Lateral/longitudinal CG**  
   With payload installed, the aircraft **SHALL maintain its CG within ±5% of the motor-to-motor span** around the geometric center of the frame in both X (forward/back) and Y (left/right) axes. Practically, the design targets CG shifts of only a few millimeters.

5. **[W-5] Vertical CG**  
   The final CG **SHALL lie at or slightly below the rotor plane**. This follows multirotor best practice for stable attitude control and predictable hover.

6. **[W-6] Structural compatibility**  
   The payload mounting **SHALL use only manufacturer-provided mounting locations** (bottom plate holes, existing brackets, or rails) and **SHALL NOT** drill into structural arms or modify the Aurelia frame.

7. **[W-7] Ground clearance**  
   The 3D-printed belly pack **SHALL maintain sufficient ground clearance** so that the lowest point of the payload clears the ground during takeoff, landing, and minor uneven terrain. The design targets at least **40–50 mm** clearance below the lowest payload component.

### 2.3 Sensor Placement Requirements

8. **[S-1] Doppler geometry**  
   The Doppler radar **SHALL be mounted with boresight approximately normal to the ground** and aligned with the region where the victim’s chest will be located when the drone hovers at the specified 1 m standoff distance.

9. **[S-2] Acoustic coverage**  
   The speaker **SHALL face toward the victim** with minimal structural obstruction, and microphones **SHALL be oriented away from prop wash** as much as practical while still facing the victim.

10. **[S-3] Jetson accessibility**  
    The Jetson J1020 v2 **SHALL be mounted so that power, Ethernet/USB, and camera connections are accessible** and adequate airflow is available around its heatsink.

11. **[S-4] Power converter proximity**  
    High-current power converters **SHALL be mounted close to the Jetson and main power entry** to minimize resistive losses and keep heavy copper wiring short.

12. **[S-5] Cable management**  
    Wiring **SHALL be secured** to prevent movement that could shift CG in flight, snag on obstacles, or vibrate into the propellers.

These requirements tie back into the original system-level specifications such as remaining under 400 ft AGL and obeying FAA Part 107 small UAS rules.

---

## 3. Subsystem Context

The Weight Distribution and Sensor Placement subsystem interfaces with the project’s “Atomic Subsystems” as follows:

- **Programmable Drone Subsystem**  
  Provides the Aurelia X4 airframe and flight controller. This subsystem must preserve the drone’s stability and MTOW limits after adding payload.

- **Power and Circuitry Design Subsystem**  
  Supplies regulated power rails to the Jetson, Doppler radar, ADC, and mic/speaker module. Physical placement of converters and wiring must consider both CG and EMI.

- **Signal Processing Subsystem**  
  Hosts the Jetson J1020 v2, which processes data from the Doppler radar and microphone, and outputs triage classifications.

- **Vitals’ Sensor Subsystem**  
  Uses a 24 GHz Doppler radar module plus analog front-end and ADC to measure heart and respiratory rates from at least 1 m away.

- **Microphone and Speaker Subsystem**  
  Uses a USB speaker and analog MEMS microphone breakout to evaluate cognitive response and provide prompts.

The weight distribution design decides where and how each of these physical components sits relative to the Aurelia X4 center, and how they connect mechanically to the drone.

---

## 4. Drone Platform Characteristics

For reference, the Aurelia X4 Standard’s key physical and performance characteristics are summarized below (standard battery configuration):

| Parameter                      | Value                         |
|--------------------------------|-------------------------------|
| UAV empty weight              | 2450 g (5.40 lb)              |
| UAV weight incl. std. battery | 3712 g (8.18 lb)              |
| Payload capability            | 1500 g (3.3 lb)               |
| UAV MTOW (std. battery)       | 5212 g (11.49 lb)             |
| Max flight speed              | 35 mph (56 km/h)              |
| Max wind resistance           | 20 mph (32 km/h)              |
| Max flight time (std. batt)   | 25 min                        |

The payload design in this document always assumes the **standard battery** configuration. If the team later switches to the Long Endurance battery, the same 1.5 kg payload capability still applies.

---

## 5. Payload Architecture – 3D-Printed Belly Pack

### 5.1 Concept

The triage payload is consolidated into a **3D-printed belly pack module** that mounts under the central fuselage of the Aurelia X4. The goals of this approach are:

- Keep heavy components clustered around the drone’s CG.
- Make installation/removal of the triage system easy without permanent changes to the airframe.
- Enable structured wiring and mechanical protection for the Doppler, Jetson, speaker, microphone, and power converters.

### 5.2 Mechanical Layout

The belly pack consists of:

- A **3D-printed base tray** that bolts to the Aurelia X4 bottom plate using existing mounting points.
- Integrally printed **stiffening ribs** and mounting bosses for:
  - Jetson J1020 v2 (top surface of tray)
  - Power converters and NP-F battery plate (adjacent to Jetson)
  - Doppler radar module (on the underside, facing downward)
  - Speaker and microphone ports (on the underside, facing forward and downward)
- A removable **printed cover** or partial shroud to protect wiring while leaving the Jetson heatsink exposed.

#### Recommended 3D-Print Parameters

- Material: **PETG or ABS** (better temperature and impact performance than PLA).
- Wall thickness: **2–3 perimeters (~2–3 mm)**.
- Infill: **30–40% grid or gyroid** for good stiffness.
- Layer height: **0.2–0.3 mm**.
- Include fillets on corners and ribs to avoid stress concentrations near mounting screws.

### 5.3 Mounting to the Aurelia X4

- Use the existing bottom-plate screw pattern shown in the X4 user manual.
- Replace stock screws with slightly longer M3/M4 screws if needed and add **nylock nuts** or thread-locker to prevent loosening.
- Install at least four mounting points near the corners of the tray to spread loads during flight and landings.

No structural arms or motor mounts are modified; the entire triage payload can be removed by unbolting the printed tray.

---

## 6. Mass Budget

Because this is a detailed design stage rather than final as-built, component masses are handled as a **budget** based on datasheets and typical values. Each component will be weighed during integration to confirm that the actual payload remains under the 1.5 kg limit.

### 6.1 Component-Level Budget

Approximate triage payload mass budget:

| Subsystem / Component                  | Example Part(s)                            | Budgeted Mass (g) |
|----------------------------------------|--------------------------------------------|-------------------|
| Jetson computing unit                  | reComputer J1020 v2                        | 600               |
| Doppler radar + analog front-end      | 24 GHz radar module + OP07 + filters + ADC | 200               |
| Microphone board                       | Analog MEMS microphone breakout            | 1                 |
| Speaker                                | Mini USB stereo speaker                    | 195               |
| Power converters & NP-F plate          | Buck converter, dual supply, NP-F plate    | 250               |
| 3D-printed belly pack (tray + cover)   | PETG tray, ribs, bosses                    | 250               |
| Wiring and strain relief               | Harnesses, USB/power cables, zip ties      | 100               |
| **Estimated payload subtotal**         |                                            | **~1,596**        |

This budget is intentionally **conservative** (heavy side) to prevent accidentally exceeding the 1.5 kg payload capability. During integration, if measured masses are lower than budgeted, the actual payload will easily satisfy [W-1] and [W-2].

> If the actual measured payload mass approaches 1.5 kg, either the budget or the design must be adjusted (e.g., lighter print, smaller speaker enclosure) to regain margin.

---

## 7. Coordinate System and CG Calculations (Reformatted)

### 7.1 Coordinate Definition

A body-fixed coordinate system is defined as follows:

- Origin: **current CG of the Aurelia X4 with standard battery and no triage payload**
- **+X axis**: forward (toward the front arms)
- **+Y axis**: to the right (starboard)
- **+Z axis**: upward (toward the propellers)

Each added component *i* is described by:

- Mass: `m_i` (kg)
- Position: `(x_i, y_i, z_i)` (meters), measured from the origin

Let:

- `m0` = base mass of Aurelia X4 + standard battery (3.712 kg)

Total mass:

```text
M_total = m0 + Σ(m_i)

