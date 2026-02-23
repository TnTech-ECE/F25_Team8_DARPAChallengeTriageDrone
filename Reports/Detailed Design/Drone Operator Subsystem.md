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

These values define the hard limits for any payload and mounting solution. [R2]

### 2.2 Weight & CG Requirements

For this subsystem, the following requirements are defined:

1. **[W-1] Payload mass limit**  
   The triage payload (compute, Doppler radar, ADC/analog front-end, mic/speaker module, power conversion, mounting tray, and wiring) **SHALL have total mass ≤ 1.5 kg** to stay within the Aurelia X4 payload capability. [R2]

2. **[W-1a] Payload mass margin target**  
   To avoid “worst-case” overruns, the design **SHOULD maintain a 10–15% payload mass margin** below the 1.5 kg limit (**target payload ≤ 1.35 kg**, stretch goal ≤ 1.275 kg).

3. **[W-2] MTOW compliance**  
   The combined mass of **Aurelia X4 + standard battery + triage payload** **SHALL NOT exceed 5.212 kg**. [R2]

4. **[W-3] Vitals sensor mass**  
   The vitals sensor assembly (Doppler radar, analog front-end, ADC, mounting) **SHOULD remain ≤ 0.25 kg**.

5. **[W-4] Lateral/longitudinal CG**  
   With payload installed, the aircraft **SHALL maintain its CG within 5% of motor-to-motor span** in X and Y. Practically, the design targets **CG shifts of only a few millimeters**.

6. **[W-5] Vertical CG**  
   The combined CG **SHALL lie at or slightly below the rotor plane** (measured at motor centers), per stability requirement.

7. **[W-6] Structural compatibility**  
   The payload mounting **SHALL use only manufacturer-provided mounting locations** and **SHALL NOT** drill into structural arms or modify the Aurelia frame.

8. **[W-7] Ground clearance**  
   The 3D-printed belly pack **SHALL NOT reduce ground clearance** below safe landing/takeoff limits; it must remain above the lowest landing gear members.

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

- A **3D-printed base tray** that mounts to the **two payload rails** under the battery bay.
- Integrally printed **stiffening ribs** and mounting bosses for:
  - Jetson compute unit (top surface of tray)
  - Power conversion + NP-F plate (adjacent to compute)
  - Doppler radar module (underside, facing downward)
  - Speaker and microphone ports (underside, facing forward/downward)
- A removable **printed cover** or partial shroud to protect wiring while leaving the compute heatsink exposed.

**Preliminary geometry envelope (from Aurelia X4 technical drawing):** [R1]

- Payload rail diameter: **Ø12 mm**.  
- Approx. rail spacing / payload bay width: **132 mm** (plan view).  
- Approx. available mounting span under bay: **~214 mm** (front view).  

These dimensions define the initial tray footprint used for CG estimating and placement verification. Final as-built geometry will be confirmed in CAD during integration.

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

This detailed design stage uses a **measured / vendor-spec-based** mass budget to ensure the payload stays comfortably below the 1.5 kg platform limit and preserves a **10–15% margin** (requirement [W-1a]).

### 6.1 Component-Level Budget (Updated)

| Subsystem / Component                 | Example Part(s) / Notes                                                                 | Budgeted Mass (g) |
|--------------------------------------|------------------------------------------------------------------------------------------|-------------------|
| Compute unit                          | **NVIDIA Jetson Nano** (budget includes heatsink/case + mounting hardware)              | 280               |
| Doppler radar + analog front-end     | 24 GHz radar module + analog front-end + ADC + mounting (small PCB stack)              | 80                |
| Microphone board                      | SparkFun **BOB-19389** (board-level)                                                    | 1                 |
| Speaker                               | SparkFun **COM-18343** Mini USB Stereo Speaker                                          | 195               |
| Power conversion + battery plate      | NP-F plate + 1–2 DC-DC buck modules + wiring pigtails                                   | 120               |
| 3D-printed belly pack (tray + cover)  | PETG tray, ribs, inserts; print optimized for weight                                    | 170               |
| Wiring, strain relief, fasteners      | Harnessing, USB/power cables, zip ties, ferrites, screws                                | 60                |
| **Estimated payload subtotal**        |                                                                                          | **~906 g**        |
| **Payload margin vs 1.5 kg**          | 1500 g − 906 g = **594 g margin** (**~39.6%**)                                          | —                 |

**Margin recovery justification:** The previous “worst-case” estimate assumed a ~600 g compute module and oversized allowances for power hardware and printed structure. Updated values use published weights for the Jetson Nano dev kit (~141 g bare) plus a conservative allowance for casing/heatsink/cabling [R3], published speaker weight (~193 g) [R5], and typical off-the-shelf NP-F plate + buck-converter module weights [R6][R7].

#### Bill of Materials (Procurement Snapshot)

This table mirrors the mass budget items and provides a simple procurement checklist (quantities are **placeholders** and will be finalized during integration).

| Item | Qty | Example part(s) / notes | Mass used in budget (g) |
|---|---:|---|---:|
| Compute unit | 1 | **NVIDIA Jetson Nano** (budget includes heatsink/case + mounting hardware) | 280 |
| Doppler radar + analog front-end | 1 | 24 GHz radar module + analog front-end + ADC + mounting (small PCB stack) | 80 |
| Microphone board | 1 | SparkFun **BOB-19389** (board-level) | 1 |
| Speaker | 1 | SparkFun **COM-18343** Mini USB Stereo Speaker | 195 |
| Power conversion + battery plate | 1 | NP-F plate + 1–2 DC-DC buck modules + wiring pigtails | 120 |
| 3D-printed belly pack (tray + cover) | 1 | PETG tray, ribs, inserts; print optimized for weight | 170 |
| Wiring, strain relief, fasteners | 1 set | Harnessing, USB/power cables, zip ties, ferrites, screws | 60 |

### 6.2 Margin Preservation Plan (If Mass Creeps Up)

If the measured as-built payload approaches the [W-1a] target (≤ 1.35 kg), the design has clear “knobs” to regain margin without redesigning the subsystem:

- **Compute choice:** Jetson Orin Nano dev kit is published at **0.174 kg** (board-level) and can replace a heavier enclosure if needed.  
- **Printed structure optimization:** reduce infill, use ribbed walls, and avoid solid blocks (tray is the easiest mass to trim once fit is verified).  
- **Audio hardware:** speaker can be swapped to a lighter transducer if required (with minor acoustic compromise).  
- **Cabling discipline:** shorten USB/power runs, remove unused connectors, and use lighter gauge where allowable.

---

## 7. Coordinate System and CG Calculations

This section closes the gap noted in review: the coordinate system is defined **and** a preliminary CG estimate is provided using rough CAD-derived geometry.

### 7.1 Coordinate Definition (Body-Fixed Frame)

- **Origin (O):** geometric center of the aircraft at the **rotor plane** (intersection of the diagonals between motor centers).  
- **+X:** forward (toward front arms)  
- **+Y:** right (starboard)  
- **+Z:** up (toward propellers)  

Motor-to-motor span (center-to-center across the frame) from the Aurelia X4 drawing is approximately:

- **L ≈ 0.76453 m** [R1]  

### 7.2 CG Computation Method

For each payload component *i*, define:

- Mass: **mᵢ** (kg)  
- Position vector: **rᵢ = ⟨xᵢ, yᵢ, zᵢ⟩** (m), measured from the origin O

Payload CG is computed by the standard mass-weighted average:

- **r_CG,payload = (Σ mᵢ rᵢ) / (Σ mᵢ)**

Expanded into components:

- **x_CG = Σ(mᵢ xᵢ) / Σ(mᵢ)**  
- **y_CG = Σ(mᵢ yᵢ) / Σ(mᵢ)**  
- **z_CG = Σ(mᵢ zᵢ) / Σ(mᵢ)**  

A first-pass estimate of how much the payload shifts the *vehicle* CG (relative to the stock aircraft CG) is:

- **Δr_CG,vehicle ≈ (m_payload / (m_vehicle + m_payload)) · r_CG,payload**

This is sufficient at the detailed design stage to confirm that the payload placement is near-center and below the rotor plane. Final values will be re-run using CAD-extracted coordinates once the belly pack model is finalized.

### 7.3 Preliminary CG Estimate (Rough CAD / Layout-Based)

Assumptions used for this first-pass estimate:

- Payload is centered on the rail midspan, with only small fore/aft offsets for ports.
- Z positions are set by the belly-pack stack-up; components live **below the rotor plane**.
- Symmetry is preserved in Y (left/right) to minimize lateral CG shift.

| Component                          | Mass (g) | x (m)  | y (m)  | z (m)   |
|-----------------------------------|---------:|-------:|-------:|--------:|
| Jetson Nano (w/ mounting)         | 280      | 0.000  | 0.000  | -0.10   |
| Doppler radar + AFE + ADC         | 80       | 0.000  | 0.000  | -0.16   |
| Microphone board                  | 1        | 0.020  | 0.000  | -0.14   |
| USB speaker                       | 195      | 0.030  | 0.000  | -0.14   |
| Power conv + NP-F plate           | 120      | 0.000  | 0.000  | -0.11   |
| 3D-printed belly pack structure   | 170      | 0.000  | 0.000  | -0.12   |
| Wiring/strain relief/fasteners    | 60       | 0.000  | 0.000  | -0.12   |

**Computed payload CG (from the table above):**

- **x_CG,payload ≈ +0.0065 m** (**+6.5 mm forward**)  
- **y_CG,payload ≈ 0.0000 m** (**0 mm lateral**)  
- **z_CG,payload ≈ -0.120 m** (**120 mm below rotor plane**)  

**Requirement check:**

- Lateral/longitudinal CG bound [W-4]: **0.05 · L ≈ 0.038 m = 38 mm** → **PASS** (6.5 mm < 38 mm).  
- Vertical CG intent [W-5]: payload CG is **below rotor plane**; when combined with the stock aircraft mass, the net CG shift is expected to remain **at or slightly below** the rotor plane.

### 7.4 How This Will Be Finalized (Without Full 3D Modeling Here)

- Final x/y/z coordinates will be pulled from CAD once the belly pack model is complete.
- Component masses will be updated using **scale measurements** for the as-built payload.
- The spreadsheet method below will be used to recompute CG and verify [W-4]/[W-5].

### 7.5 Spreadsheet Implementation

Create a spreadsheet with columns:  
`Component | Mass (kg) | x (m) | y (m) | z (m) | m·x | m·y | m·z`

Then compute:

- **x_CG = SUM(m·x) / SUM(m)** (and similarly for y, z)  
- Compare **|x_CG|** and **|y_CG|** to **0.05 · L**, where **L ≈ 0.76453 m**

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

### 8.3 Jetson Nano (Signal Processing Subsystem)

- Mounted on the **top side of the belly tray**, centered in X/Y to minimize lateral CG shift.
- Uses a **standoff + insert pattern** (heat-set inserts or metal standoffs) so the board/case is not hard-clamped to the tray.
- **Thermal:** keep airflow around the heatsink/fan unobstructed; printed covers stop short of the heatsink to avoid trapping heat.
- **Mass budget:** Jetson Nano dev kit is published around **141 g** bare; the design budgets **280 g** to include enclosure/heatsink, mounting hardware, and short cables. [R3]

*Contingency option:* If additional margin is needed or a lighter compute solution is selected later, the Jetson Orin Nano dev kit is published at **0.174 kg** (board-level). [R4]

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

### 9.2 Vibration Considerations

This design accounts for vibration primarily as a **mounting reliability** and **sensor-quality** risk (review concern), without going into subsystem-specific audio treatments.

- **Stiff main structure:** the belly tray/rail interface is kept rigid so the payload does not “wag” during maneuvers.  
- **Connector protection:** all cables include **strain relief** on the tray so connectors are not carrying vibration loads.  
- **Fastener security:** use **nylock nuts** or thread-locker on mounting hardware to prevent loosening over time.  
- **Optional board-level compliance (if needed):** if testing shows vibration coupling into the Doppler stack, use **rubber grommets / compliant standoffs** for the radar + ADC mounting points.  

Detailed microphone-specific mitigation (ports,### 9.4 Safety and Operational Controls

- **Retention and drop safety:** All payload items are mounted with mechanical fasteners (washers + nyloc nuts or threadlocker). Where practical, include a **secondary retention** (short lanyard/zip-tie anchor) so no component can fall free into the rotors if a fastener loosens.
- **Prop/ground clearance:** The belly pack envelope must stay **inside the landing gear footprint** with no protrusions into the rotor disk. Confirm ground clearance and cable routing with the aircraft on level ground before flight.
- **Edge and snag control:** Printed corners and rib junctions are filleted (no sharp edges). Any openings used for cables should be chamfered and use grommets/printed strain-relief features to prevent abrasion.
- **Serviceability and safe handling:** The payload should be removable with common hand tools and without disturbing critical airframe electronics. During bench work, remove props or ensure motors are disabled.
- **Pre-flight checks:** Verify fastener tightness, cable tie integrity, connector seating, and that the measured payload mass remains within the limit. Perform a quick visual clearance check (no loose wiring, nothing contacting landing gear).

 wind/prop-wash handling, acoustic treatments) is owned by the microphone/speaker subsystem; this document only ensures the mounting locations and mass placement are compatible.

### 9.3 EMI and Cable Routing Considerations

EMI is treated here at the **layout level** (what we control in placement/mounting). Detailed filtering, grounding, and power integrity design is owned by the power/circuitry subsystem.

- **Separation:** keep DC-DC converters and high-current power runs physically separated from the radar analog front-end and microphone wiring.  
- **Short runs:** mount power conversion close to the Jetson and main power entry so heavy copper runs stay short.  
- **Routing discipline:** route power and signal harnesses on different sides of the tray where possible and secure them so they cannot drift.  
- **If interference is observed in testing:** add **ferrite clamps** and/or lightweight shielding as a last step (small mass increase vs improved robustness).

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

## 11. Summary

The Weight Distribution and Sensor Placement subsystem consolidates all triage hardware into a 3D-printed belly pack mounted under the Aurelia X4 Standard drone. By carefully locating heavy components near the frame center, aligning the Doppler and acoustic sensors with the victim region, and respecting the 1.5 kg payload and 5.212 kg MTOW limits, the design preserves flight performance while enabling the vital sensing and cognitive test capabilities required by the DARPA Triage Drone project.

This detailed design defines:

- Quantitative mass and CG requirements.  
- A mechanical architecture (3D-printed tray) compatible with the Aurelia X4.  
- Placement strategies for Jetson, Doppler radar, microphone, speaker, and power hardware.  
- A repeatable process to compute and verify center of gravity.  
- Bench and flight tests to validate that the modified aircraft remains safe and controllable.

Once the physical components are available and the 3D-printed tray is finalized, the team will verify that actual measured masses and CG align with this design and update the project documentation accordingly.

## 12. References

[1] “DARPA Triage Challenge,” DARPA. Available: https://triagechallenge.darpa.mil/

[2] Aurelia Technologies Inc., “Aurelia X4 Standard – Technical Drawing (2025).” Available: https://cdn.shopify.com/s/files/1/0253/9057/9791/files/X4_Standard_Technical_Drawing_-_2025_No_Bg.jpg

[3] Aurelia Technologies Inc., “Aurelia X4 Standard – Product Page / Specs.” Available: https://uavsystemsinternational.com/products/aurelia-x4-standard

[4] NVIDIA, “Jetson Nano – NVIDIA Developer.” Available: https://developer.nvidia.com/embedded/jetson-nano

[5] RS Components, “NVIDIA Jetson Nano Developer Kit (Documentation / datasheet).” Available: https://docs.rs-online.com/8468/A700000006933720.pdf

[6] Federal Aviation Administration, “14 CFR Part 107: Small Unmanned Aircraft Systems.” Available: https://www.faa.gov/uas/commercial_operators/part_107

[7] Texas Instruments, “IWR6843AOP mmWave Sensor Datasheet.” Available: https://www.ti.com/product/IWR6843AOP
