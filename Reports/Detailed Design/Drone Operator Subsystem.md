# Weight Distribution and Sensor Placement Detailed Design  
**DARPA Triage Drone – Aurelia X4 Standard Platform**

---

## 1. Subsystem Overview

In the DARPA Triage Drone project, the Weight Distribution and Sensor Placement subsystem is responsible for physically integrating all triage­-related hardware onto the **Aurelia X4 Standard** multirotor and ensuring the modified drone remains safe, controllable, and within all mass and regulatory limits.

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

These requirements tie back into the original system-level specifications such as remaining under 400 ft AGL, obeying Part 107 small UAS rules, and supporting accurate vitals sensing with the Doppler subsystem.

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
  Uses SparkFun COM-18343 USB speaker and BOB-19389 analog MEMS microphone breakout to evaluate cognitive response and provide prompts.

The weight distribution design decides where and how each of these physical components sits relative to the Aurelia X4 center, and how they connect mechanically to the drone.

---

## 4. Drone Platform Characteristics

For reference, the Aurelia X4 Standard’s key physical and performance characteristics are summarized below (standard battery configuration):

| Parameter                     | Value                         |
|------------------------------|-------------------------------|
| UAV empty weight             | 2450 g (5.40 lb)              |
| UAV weight incl. std. battery| 3712 g (8.18 lb)              |
| Payload capability           | 1500 g (3.3 lb)               |
| UAV MTOW (std. battery)      | 5212 g (11.49 lb)             |
| Max flight speed             | 35 mph (56 km/h)              |
| Max wind resistance          | 20 mph (32 km/h)              |
| Max flight time (std. batt)  | 25 min                        |

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
- Wall thickness: **2–3 perimeters (≈2–3 mm)**.  
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

| Subsystem / Component                 | Example Part(s)                            | Budgeted Mass (g) |
|--------------------------------------|--------------------------------------------|-------------------|
| Jetson computing unit                | reComputer J1020 v2                        | 600               |
| Doppler radar + analog front-end    | 24 GHz radar module + OP07 + filters + ADC | 200               |
| Microphone board                     | SparkFun BOB-19389                         | 1                 |
| Speaker                              | SparkFun COM-18343 Mini USB Stereo Speaker | 195               |
| Power converters & NP-F plate        | Buck converter, dual supply, NP-F plate    | 250               |
| 3D-printed belly pack (tray + cover) | PETG tray, ribs, bosses                    | 250               |
| Wiring and strain relief             | Harnesses, USB/power cables, zip ties      | 100               |
| **Estimated payload subtotal**       |                                            | **~1,596**        |

This budget is intentionally **conservative** (heavy side) to prevent accidentally exceeding the 1.5 kg payload capability. During integration, if measured masses are lower than budgeted, the actual payload will easily satisfy [W-1] and [W-2].

> Note: If the actual measured payload mass approaches 1.5 kg, either the budget or the design must be adjusted (e.g., lighter print, smaller speaker enclosure) to regain margin.

---

## 7. Coordinate System and CG Calculations

### 7.1 Coordinate Definition

Define a body-fixed coordinate system:

- Origin at the **current CG of the Aurelia X4 with standard battery and no triage payload** (nominally the geometric center of the frame).
- **+X** axis: forward, toward the front arms.
- **+Y** axis: to the right (starboard).
- **+Z** axis: upward, toward the propellers.

Each added component *i* is represented by:

- Mass \( m_i \) (kg)  
- Position vector \( \mathbf{r}_i = \langle x_i, y_i, z_i \rangle \) (meters), measured from the origin.

Let:

- \( m_0 \) = base mass of Aurelia X4 + standard battery (3.712 kg).

Then:

**Total mass**
- M_total = m₀ + Σ mᵢ

**Center of gravity (vector form)**
- r_CG = ( m₀⟨0,0,0⟩ + Σ mᵢ rᵢ ) / M_total
- Since the origin is defined at the base-aircraft CG, ⟨0,0,0⟩, this simplifies to:
  - r_CG = ( Σ mᵢ rᵢ ) / M_total

Where rᵢ = ⟨xᵢ, yᵢ, zᵢ⟩ (meters).

**Component form**
- x_CG = (Σ mᵢ xᵢ) / M_total
- y_CG = (Σ mᵢ yᵢ) / M_total
- z_CG = (Σ mᵢ zᵢ) / M_total

### 7.2 Placement Strategy

The placement rules used in this design:

1. The **Jetson** sits at the geometric center of the belly tray (small \( x_i \), \( y_i \)).  
2. **Doppler radar** is directly below the center of the tray, boresight downward.  
3. **Speaker** is placed slightly forward of center (positive X) but within a few centimeters to minimize CG shift.  
4. **Microphone board** is mounted close to the speaker, but slightly offset laterally to reduce direct airflow noise.  
5. **Power converters** are positioned adjacent to the Jetson, generally along the Y axis so their mass effect is symmetric front-to-back.  
6. Wiring mass is treated as distributed near the tray center.

With this scheme, the forward CG shift is small, and the vertical CG moves slightly downward (which is acceptable as long as it remains near the rotor plane).

### 7.3 Spreadsheet Implementation

To implement CG calculations in practice:

1. Create a spreadsheet with columns:  
   `Component | Mass (kg) | x (m) | y (m) | z (m) | m·x | m·y | m·z`.
2. Fill in each payload component’s approximate location measured from the drone’s center.
3. Sum the `m·x`, `m·y`, and `m·z` columns and divide by total mass to get \( x_{\text{CG}}, y_{\text{CG}}, z_{\text{CG}} \).
4. Compare against requirement [W-4]:
   - \(|x_{\text{CG}}|, |y_{\text{CG}}| \leq 0.05 L\), where \(L\) is motor-to-motor distance.
5. Adjust component positions (or add small counterweights) as needed until CG is within bounds.

---

## 8. Sensor Placement Details

### 8.1 Doppler Radar (Vitals’ Sensor Subsystem)

- Located in the **center of the belly pack underside**, pointing straight down.  
- The mounting flange is designed so that, when the drone is hovering ~1 m above ground, the radar is approximately 0.9–1.0 m above the victim’s chest, satisfying the non-contact sensing requirement.
- The 3D-printed tray includes:
  - A circular or rectangular cutout for the radar antenna aperture.
  - Standoffs for the radar PCB to maintain a fixed distance from the tray.

The radar’s analog front-end and ADC board are mounted just above the radar module, inside the tray, to keep lead lengths short and reduce noise pickup.

### 8.2 Microphone and Speaker (Cognitive Test Subsystem)

**Speaker:**

- The SparkFun COM-18343 speaker is mounted near the **front edge of the belly pack**, oriented forward and slightly downward.
- The printed tray forms a shallow speaker cavity with grill openings facing the victim.
- Aiming angle is chosen so the speaker’s main lobe hits the region where the victim’s head and upper torso will be located at 1 m standoff.

**Microphone:**

- The SparkFun BOB-19389 microphone board is placed near the speaker but slightly offset laterally and shielded from direct prop wash.
- The printed tray includes a small acoustic port or mesh opening aligned with the victim region.
- The microphone is located near the drone’s center to limit its contribution to CG shift.

### 8.3 Jetson J1020 v2 (Signal Processing Subsystem)

- Mounted on the **top side of the belly tray**, centered in both X and Y.
- The tray has a flat mounting surface with four bosses or inserts matching the Jetson case mounting holes.
- The Jetson’s aluminum case and heatsink are exposed to ambient airflow; any printed covers stop short of the heatsink to avoid trapping heat.
- USB, HDMI, and Ethernet ports are oriented to face a side where cables can be routed without interfering with props or landing gear.

### 8.4 Power Converters and NP-F Plate

- DC-DC buck converter, dual-output module, and NP-F adapter plate are mounted adjacent to the Jetson on the tray.
- High-current paths from the drone battery into the converters and then to the Jetson and radar are kept as short and straight as possible.
- Wiring bundles are routed along the tray surface and up into the airframe through existing holes, secured with cable ties and printed clips.

---

## 9. Mechanical and Structural Considerations

### 9.1 Structural Load Path

The 3D-printed belly tray transmits loads from the payload to the Aurelia X4 bottom plate through:

- The four (or more) mounting screw locations.
- Printed ribs that distribute local loads from heavy components (Jetson and speaker) into the tray.

Landing shocks are primarily absorbed by the landing gear, but any vertical accelerations act on the belly tray through these mounts. For robustness:

- Screw sizes and tray thickness are selected to provide a **safety factor of at least 2** against static loads and mild impact loads.
- Corners and rib junctions are filleted rather than sharp to avoid crack initiation.

### 9.2 Vibration and Noise

- The Aurelia X4 includes a rangefinder and onboard electronics that already handle some vibration.  
- To prevent additional vibrations from degrading the Doppler or microphone performance:
  - The radar PCB may be mounted on **soft standoffs or rubber grommets**.  
  - The microphone board can be isolated using a small piece of foam between the board and tray.
- Cable bundles are tied down to avoid “whipping” in turbulent air.

---

## 10. Verification and Validation Plan

### 10.1 Mass Verification

1. Weigh each payload component (Jetson, Doppler module, ADC board, speaker, mic, converters, 3D-printed tray, wiring) using a digital scale.  
2. Sum the measured masses to obtain **actual payload mass**.  
3. Verify:
   - Payload mass ≤ 1.5 kg (requirement [W-1]).  
   - Total aircraft mass (3712 g + payload) ≤ 5212 g (requirement [W-2]).

### 10.2 CG Verification – Bench Test

1. With the payload installed, perform a **hang test**:
   - Suspend the drone from two different points (e.g., opposite arms) and trace vertical plumb lines. The intersection approximates the true CG in the X–Y plane.
2. Compare the observed CG location to the geometric center and to the spreadsheet prediction.
3. If the CG is out of bounds for [W-4]:
   - Move lighter components or wiring bundles to the opposite side.  
   - If necessary, add a small counterweight close to the frame center to correct residual imbalance.

### 10.3 Ground Clearance and Fit Check

1. Place the drone on a flat surface and measure the distance from the ground to both:
   - The lowest point on the 3D-printed tray.  
   - The lowest point on the Doppler radar and speaker housings.
2. Confirm that the clearance is at least 40–50 mm and that the belly pack does not contact the ground when gently rocking the drone.

### 10.4 Flight Test

1. Begin with low-altitude hover tests (1–2 m AGL) in calm conditions.  
2. Observe:
   - Required trim inputs (roll/pitch) to maintain hover.  
   - Any oscillations or sluggish responses.  
   - Any signs of landing gear interference or belly pack vibration.
3. Tune payload placement or autopilot gains if necessary, keeping within the constraints of the Pixhawk configuration provided with the Aurelia X4.

---

## 11. Safety Considerations

This subsystem directly impacts flight safety because it changes aircraft mass properties, adds external hardware, and introduces additional wiring and electronics. The following safety items SHALL be treated as design constraints during integration and flight test.

### 11.1 Flight and Operational Safety (Part 107 Context)

- **Secure external load:** The belly-pack module is an external payload and MUST be attached such that it cannot shift, detach, or interfere with controllability.
- **Preflight inspection:** Before each flight, inspect:
  - All mounting screws/nuts (no loosening, cracks, or missing hardware).
  - Cable routing (no slack near props, no abrasion points).
  - Battery retention and connector strain relief.
- **Hover-first test philosophy:** Any time the payload layout changes, perform a low-altitude hover check (1–2 m AGL) before any mission-like flight.

### 11.2 Mechanical Safety

- **Fastener retention:** Use nylock nuts and/or thread-locker on belly-pack fasteners. Mark fasteners with witness paint to detect loosening.
- **Vibration management:** Add rubber grommets/soft standoffs where appropriate (radar PCB, microphone PCB) to reduce fatigue and measurement noise.
- **Sharp edges and snag hazards:** Deburr printed parts and avoid protrusions that could snag on vegetation, clothing, or landing gear.
- **Impact tolerance:** Treat the belly pack as a sacrificial structure; the tray/cover should protect electronics during minor hard landings.

### 11.3 Electrical and Thermal Safety

- **Short-circuit protection:** All power branches feeding Jetson, radar/ADC, and audio boards MUST be fused or current-limited per the Power/Circuitry subsystem design.
- **Thermal margins:** Avoid PLA for structural parts close to heat sources or direct sun exposure. PETG is recommended for general use; ASA is preferred for higher temperature/UV environments.
- **Heatsink airflow:** Ensure the Jetson heatsink has clearance and ventilation; do not fully enclose it in a sealed printed cover.

### 11.4 RF / Sensor Emission Safety

- **Radar emission limits:** Configure the Doppler subsystem to operate within safe human-exposure limits and follow manufacturer guidance for antenna orientation and standoff distance.
- **EMI considerations:** Route high-current lines away from sensitive analog front ends and microphone traces. Where needed, add shielding and maintain good grounding practices.


---

## 12. Bill of Materials (Subsystem)

> Note: The team indicated that most electronics are already purchased. The BOM below includes **integration hardware** and **3D-print filament** that the team may still need to procure. Items marked **TBD** depend on final selection by other subsystems.

### 12.1 Major Components (from Conceptual Design)

| Item | Qty | Part / Description | Link | Status |
|---|---:|---|---|---|
| Edge compute | 1 | Seeed Studio reComputer J1020 v2 (Jetson Nano 4GB) | https://www.seeedstudio.com/reComputer-J1020-v2-p-5498.html | Purchased (team) |
| Speaker | 1 | SparkFun Mini USB Stereo Speaker (COM-18343) | https://www.sparkfun.com/mini-usb-stereo-speaker.html | Purchased (team) |
| Microphone | 1 | SparkFun Analog MEMS Microphone Breakout (BOB-19389) | https://www.sparkfun.com/sparkfun-analog-mems-microphone-breakout-sph8878lr5h-1.html | Purchased (team) |
| Doppler radar module | 1 | 24 GHz Doppler radar module (exact part TBD by Vitals subsystem) | TBD | TBD |
| ADC board | 1 | ADC / analog front-end interface (exact part TBD by Vitals subsystem) | TBD | TBD |
| DC-DC converters | 1–2 | Buck/boost converters sized for Jetson + sensors (exact parts TBD by Power subsystem) | TBD | TBD |
| Battery plate | 1 | NP-F style battery plate / connector (exact part TBD by Power subsystem) | TBD | TBD |

### 12.2 Mechanical Integration Hardware

| Item | Qty | Specification | Link (example supplier) | Notes |
|---|---:|---|---|---|
| Mounting screws | 1 kit | M3/M4 assorted, stainless | https://www.mcmaster.com/ | Match X4 bottom-plate pattern; confirm final size during fit check |
| Nylock nuts | 1 kit | M3/M4 nylon-insert lock nuts | https://www.mcmaster.com/ | Vibration resistance |
| Washers | 1 kit | M3/M4 flat washers | https://www.mcmaster.com/ | Load spreading on printed plastic |
| Rubber grommets / isolators | 1 kit | small grommets or silicone standoffs | https://www.mcmaster.com/ | Vibration isolation for radar/mic |
| Heat-set inserts (optional) | 1 kit | M3 brass heat-set inserts | https://www.mcmaster.com/ | Improves thread durability in plastic |
| Zip ties | 1 pack | 4–6 in, black | https://www.mcmaster.com/ | Cable management |
| Hook-and-loop straps | 1 pack | 10–12 in straps | https://www.mcmaster.com/ | Battery and cable retention |
| Foam tape (optional) | 1 roll | thin EVA/PU foam tape | https://www.mcmaster.com/ | Microphone isolation / rattle prevention |

### 12.3 3D-Print Filament (Recommended)

| Filament | Qty | Why | Link |
|---|---:|---|---|
| PETG (functional, general-purpose) | 1–2 spools (1 kg) | Tough, good layer adhesion, better heat performance than PLA; suitable for belly-pack structure | https://polymaker.com/product/polylite-petg/ |
| PETG (premium, tight tolerance) | 0–1 spool (1 kg) | Very consistent diameter; good if dimensional accuracy is critical for mounting holes | https://www.prusa3d.com/product/prusament-petg-jet-black-1kg/ |
| ASA (optional, high-temp/UV) | 0–1 spool (1 kg) | Better UV/weather resistance than ABS; useful if the tray is exposed to sun/heat | https://shop.polymaker.com/products/polymaker-asa |


---

## 13. Summary

The Weight Distribution and Sensor Placement subsystem consolidates all triage hardware into a 3D-printed belly pack mounted under the Aurelia X4 Standard drone. By carefully locating heavy components near the frame center, aligning the Doppler and acoustic sensors with the victim region, and respecting the 1.5 kg payload and 5.212 kg MTOW limits, the design preserves flight performance while enabling the vital sensing and cognitive test capabilities required by the DARPA Triage Drone project.

This detailed design defines:

- Quantitative mass and CG requirements.  
- A mechanical architecture (3D-printed tray) compatible with the Aurelia X4.  
- Placement strategies for Jetson, Doppler radar, microphone, speaker, and power hardware.  
- A repeatable process to compute and verify center of gravity.  
- Bench and flight tests to validate that the modified aircraft remains safe and controllable.

Once the physical components are available and the 3D-printed tray is finalized, the team will verify that actual measured masses and CG align with this design and update the project documentation accordingly.

---

## 14. References

### 14.1 Regulations & Standards

1. Federal Aviation Administration (FAA). *Small Unmanned Aircraft Systems (UAS) Regulations (Part 107).* https://www.faa.gov/newsroom/small-unmanned-aircraft-systems-uas-regulations-part-107
2. ISO. *ISO 21384-3:2023 — Unmanned aircraft systems — Part 3: Operational procedures.* https://www.iso.org/standard/80124.html
3. ISO. *ISO 14971:2019 — Medical devices — Application of risk management to medical devices.* https://www.iso.org/standard/72704.html
4. IEEE Standards Association. *IEEE 802.11ax-2021.* https://standards.ieee.org/ieee/802.11ax/7180/
5. U.S. Department of Defense. *MIL-STD-461G: Requirements for the Control of Electromagnetic Interference Characteristics of Subsystems and Equipment.* https://s3vi.ndc.nasa.gov/ssri-kb/static/resources/MIL-STD-461G.pdf

### 14.2 Components and Vendor Documentation

6. Aurelia Aerospace. *Aurelia X4 Standard specifications and technical resources.* https://aurelia-aerospace.com/products/aurelia-x4-standard
7. Seeed Studio. *reComputer J1020 v2 (Jetson Nano 4GB).* https://www.seeedstudio.com/reComputer-J1020-v2-p-5498.html
8. SparkFun Electronics. *Mini USB Stereo Speaker (COM-18343).* https://www.sparkfun.com/mini-usb-stereo-speaker.html
9. SparkFun Electronics. *SparkFun Analog MEMS Microphone Breakout - SPH8878LR5H-1 (BOB-19389).* https://www.sparkfun.com/sparkfun-analog-mems-microphone-breakout-sph8878lr5h-1.html

### 14.3 Materials (3D Printing)

10. Polymaker. *PolyLite™ PETG.* https://polymaker.com/product/polylite-petg/
11. Original Prusa. *Prusament PETG (1 kg).* https://www.prusa3d.com/product/prusament-petg-jet-black-1kg/
12. Polymaker. *Polymaker™ ASA.* https://shop.polymaker.com/products/polymaker-asa


