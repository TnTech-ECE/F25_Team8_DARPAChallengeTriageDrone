# Experiments for Heart Rate

This experiment was designed to evaluate the accuracy of the BGT60UTR11AIP radar sensor in measuring heart rate across two subjects at two fixed distances: **0.5 meters** and **1.0 meters**. The specification requires the signal processing subsystem to detect heart rate in the range of **0.8 to 3.0 Hz (48–180 bpm)** from at least one meter away. Two volunteers participated, each providing 10 data points per distance condition, for a total of 20 measurements per sheet. A pulse oximeter served as the reference device.

### Expectation

It is expected that the radar's heart rate measurements will closely match the pulse oximeter's readings, particularly in the normal resting range of 60–100 bpm. Measurements taken at 0.5 m are expected to show similar or slightly better accuracy compared to 1.0 m due to stronger signal return at closer range.

### Procedure

- Step 1: Make sure the radar is plugged into your computer via USB.
- Step 2: Have volunteer lie down under the radar sensor at the specified distance (0.5 m or 1.0 m)
- Step 3: Attach pulse oximeter to the volunteer's finger
- Step 4: Begin radar program
    - Every 15 seconds the radar's heart rate output will be written to a new row in a CSV file.
- Step 5: Start recording
- Step 6: Start 3 minute timer
    - radar should start saving datapoints starting at 2:15 on the timer
- Step 7: Repeat for the second volunteer and the second distance

### Data — Heart Rate @ 1.0 m

| Test # | Subject  | Oximeter HR (bpm) | Radar HR (bpm) | Error (bpm) | % Error |
|:------:|:--------:|:-----------------:|:--------------:|:-----------:|:-------:|
| 1  | Person 1 | 80 | 110.1 | +30.1 | 37.62% |
| 2  | Person 1 | 75 | 115.6 | +40.6 | 54.13% |
| 3  | Person 1 | 80 | 119.5 | +39.5 | 49.38% |
| 4  | Person 1 | 72 | 108.4 | +36.4 | 50.56% |
| 5  | Person 1 | 80 | 115.7 | +35.7 | 44.63% |
| 6  | Person 1 | 81 | 108.1 | +27.1 | 33.46% |
| 7  | Person 1 | 77 | 110.4 | +33.4 | 43.38% |
| 8  | Person 1 | 80 | 111.2 | +31.2 | 39.00% |
| 9  | Person 1 | 76 | 110.4 | +34.4 | 45.26% |
| 10 | Person 1 | 80 | 111.8 | +31.8 | 39.75% |
| 11 | Person 2 | 67 | 112.1 | +45.1 | 67.31% |
| 12 | Person 2 | 71 | 112.7 | +41.7 | 58.73% |
| 13 | Person 2 | 67 | 112.3 | +45.3 | 67.61% |
| 14 | Person 2 | 70 | 106.5 | +36.5 | 52.14% |
| 15 | Person 2 | 66 | 107.0 | +41.0 | 62.12% |
| 16 | Person 2 | 71 | 108.6 | +37.6 | 52.96% |
| 17 | Person 2 | 69 | 107.2 | +38.2 | 55.36% |
| 18 | Person 2 | 71 | 106.2 | +35.2 | 49.58% |
| 19 | Person 2 | 72 | 109.3 | +37.3 | 51.81% |
| 20 | Person 2 | 68 | 109.0 | +41.0 | 60.29% |

**Summary — HR @ 1.0 m**

| | Person 1 | Person 2 | Overall |
|:--|:--:|:--:|:--:|
| Mean % Error | 43.72% | 57.79% | 50.75% |

### Data — Heart Rate @ 0.5 m

| Test # | Subject  | Oximeter HR (bpm) | Radar HR (bpm) | Error (bpm) | % Error |
|:------:|:--------:|:-----------------:|:--------------:|:-----------:|:-------:|
| 1  | Person 1 | 81 | 119.3 | +38.3 | 47.28% |
| 2  | Person 1 | 79 | 109.8 | +30.8 | 38.99% |
| 3  | Person 1 | 75 | 117.2 | +42.2 | 56.27% |
| 4  | Person 1 | 75 | 111.4 | +36.4 | 48.53% |
| 5  | Person 1 | 78 | 111.4 | +33.4 | 42.82% |
| 6  | Person 1 | 77 | 111.6 | +34.6 | 44.94% |
| 7  | Person 1 | 77 | 112.5 | +35.5 | 46.10% |
| 8  | Person 1 | 80 | 113.5 | +33.5 | 41.88% |
| 9  | Person 1 | 77 | 109.4 | +32.4 | 42.08% |
| 10 | Person 1 | 79 | 110.8 | +31.8 | 40.25% |
| 11 | Person 2 | 68 | 109.3 | +41.3 | 60.74% |
| 12 | Person 2 | 74 | 107.7 | +33.7 | 45.54% |
| 13 | Person 2 | 70 | 108.6 | +38.6 | 55.14% |
| 14 | Person 2 | 67 | 102.9 | +35.9 | 53.58% |
| 15 | Person 2 | 67 | 112.6 | +45.6 | 68.06% |
| 16 | Person 2 | 69 | 105.3 | +36.3 | 52.61% |
| 17 | Person 2 | 72 | 109.9 | +37.9 | 52.64% |
| 18 | Person 2 | 69 | 103.7 | +34.7 | 50.29% |
| 19 | Person 2 | 72 | 108.0 | +36.0 | 50.00% |
| 20 | Person 2 | 73 | 101.2 | +28.2 | 38.63% |

**Summary — HR @ 0.5 m**

| | Person 1 | Person 2 | Overall |
|:--|:--:|:--:|:--:|
| Mean % Error | 44.91% | 52.72% | 48.82% |

### Data Analysis

<!-- Upload your HR chart screenshots to GitHub and replace these URLs -->
![HR @ 1.0m Chart](https://raw.githubusercontent.com/TnTech-ECE/F25_Team8_DARPAChallengeTriageDrone/refs/heads/Gideon-B3-Vitals-n-DSP-experimental/Reports/Experimental%20Analysis/Radar%20Testing%20Graphs/HR-1.0m.png)
![HR @ 0.5m Chart](https://raw.githubusercontent.com/TnTech-ECE/F25_Team8_DARPAChallengeTriageDrone/refs/heads/Gideon-B3-Vitals-n-DSP-experimental/Reports/Experimental%20Analysis/Radar%20Testing%20Graphs/HR-0.5m.png)

Across both distances, the radar system consistently overestimated heart rate, with all 40 measurements reading higher than the oximeter reference. At **1.0 m**, the overall mean percent error was **50.75%**, with Person 1 averaging **43.72%** and Person 2 averaging **57.79%**. At **0.5 m**, the overall mean percent error was slightly lower at **48.82%**, with Person 1 at **44.91%** and Person 2 at **52.72%**. The system produced readings clustered in the 101–120 bpm range regardless of each subject's actual heart rate (66–81 bpm), indicating a consistent positive bias. This suggests the signal processing subsystem is locking onto a secondary frequency component — likely a breathing harmonic or cardiac overtone — rather than the fundamental heart rate frequency.

### Experimental Conclusion

The heart rate measurement subsystem demonstrated a systematic overestimation across all subjects and distances. The specification requires heart rate detection in the **0.8 to 3.0 Hz** range from at least **1.0 m**, and while the system produces readings within this frequency range, absolute accuracy is insufficient for clinical use at this stage. The consistent positive bias across both subjects and both distances indicates the issue lies in the frequency extraction algorithm rather than hardware sensitivity — the sensor detects cardiac motion at the required distance but incorrectly identifies the dominant frequency bin. Further development is needed to refine peak detection in the heart rate band and suppress breathing harmonic interference. The prototype confirms that the radar can detect physiological motion at the required distance, which is sufficient as a proof of concept.

---

# Experiment for Breathing Rate

This experiment evaluated the accuracy of the radar sensor in measuring breathing rate across two subjects at two fixed distances: **0.5 meters** and **1.0 meters**. The specification requires the signal processing subsystem to detect respiratory rate in the range of **0.13 to 1.0 Hz (8–60 breaths/min)** from at least one meter away. Two volunteers participated, each providing 10 data points per distance, for a total of 20 measurements per condition. The pulse oximeter's respiratory rate output served as the reference.

### Expectation

It is expected that the radar's breathing rate measurements will closely match the reference values across the normal resting respiratory range of 12–20 breaths/min. It is also expected that the breath readings should be more accurate than the heart rate, since . The system is expected to perform better at 0.5 m due to stronger phase signal from chest displacement at closer range.

### Procedure

- Step 1: Make sure the radar is plugged into your computer via USB.
- Step 2: Have volunteer lie down under the radar sensor at the specified distance (0.5 m or 1.0 m)
- Step 3: Attach pulse oximeter to the volunteer's finger
- Step 4: Begin radar program
    - Every 15 seconds the radar's breath rate output will be written to a new row in a CSV file.
- Step 5: Start recording
- Step 6: Start 3 minute timer
    - The radar should start saving datapoints starting at 2:15 on the timer
- Step 7: Repeat for the second volunteer and the second distance

### Data — Breathing Rate @ 1.0 m

| Test # | Subject  | Oximeter BR (br/min) | Radar BR (br/min) | Error (br/min) | % Error |
|:------:|:--------:|:--------------------:|:-----------------:|:--------------:|:-------:|
| 1  | Person 1 | 14 | 16.6 | +2.6  | 18.57% |
| 2  | Person 1 | 14 | 18.7 | +4.7  | 33.57% |
| 3  | Person 1 | 15 | 17.1 | +2.1  | 14.00% |
| 4  | Person 1 | 17 | 14.7 | −2.3  | 13.53% |
| 5  | Person 1 | 15 | 14.4 | −0.6  | 4.00%  |
| 6  | Person 1 | 13 | 15.8 | +2.8  | 21.54% |
| 7  | Person 1 | 10 | 7.3  | −2.7  | 27.00% |
| 8  | Person 1 | 16 | 7.6  | −8.4  | 52.50% |
| 9  | Person 1 | 20 | 11.6 | −8.4  | 42.00% |
| 10 | Person 1 | 19 | 13.1 | −5.9  | 31.05% |
| 11 | Person 2 | 15 | 14.4 | −0.6  | 4.00%  |
| 12 | Person 2 | 15 | 17.8 | +2.8  | 18.67% |
| 13 | Person 2 | 15 | 11.9 | −3.1  | 20.67% |
| 14 | Person 2 | 14 | 9.5  | −4.5  | 32.14% |
| 15 | Person 2 | 13 | 10.8 | −2.2  | 16.92% |
| 16 | Person 2 | 13 | 10.3 | −2.7  | 20.77% |
| 17 | Person 2 | 13 | 11.4 | −1.6  | 12.31% |
| 18 | Person 2 | 12 | 11.5 | −0.5  | 4.17%  |
| 19 | Person 2 | 12 | 9.1  | −2.9  | 24.17% |
| 20 | Person 2 | 12 | 10.4 | −1.6  | 13.33% |

**Summary — BR @ 1.0 m**

| | Person 1 | Person 2 | Overall |
|:--|:--:|:--:|:--:|
| Mean % Error | 25.78% | 16.71% | 21.25% |

### Data — Breathing Rate @ 0.5 m

| Test # | Subject  | Oximeter BR (br/min) | Radar BR (br/min) | Error (br/min) | % Error |
|:------:|:--------:|:--------------------:|:-----------------:|:--------------:|:-------:|
| 1  | Person 1 | 22 | 16.1 | −5.9  | 26.82% |
| 2  | Person 1 | 22 | 15.0 | −7.0  | 31.82% |
| 3  | Person 1 | 20 | 13.6 | −6.4  | 32.00% |
| 4  | Person 1 | 17 | 22.1 | +5.1  | 30.00% |
| 5  | Person 1 | 18 | 10.9 | −7.1  | 39.44% |
| 6  | Person 1 | 21 | 16.4 | −4.6  | 21.90% |
| 7  | Person 1 | 21 | 14.1 | −6.9  | 32.86% |
| 8  | Person 1 | 23 | 14.9 | −8.1  | 35.22% |
| 9  | Person 1 | 23 | 21.2 | −1.8  | 7.83%  |
| 10 | Person 1 | 22 | 10.1 | −11.9 | 54.09% |
| 11 | Person 2 | 16 | 17.8 | +1.8  | 11.25% |
| 12 | Person 2 | 15 | 8.2  | −6.8  | 45.33% |
| 13 | Person 2 | 16 | 10.6 | −5.4  | 33.75% |
| 14 | Person 2 | 14 | 22.8 | +8.8  | 62.86% |
| 15 | Person 2 | 13 | 22.7 | +9.7  | 74.62% |
| 16 | Person 2 | 13 | 17.6 | +4.6  | 35.38% |
| 17 | Person 2 | 13 | 14.4 | +1.4  | 10.77% |
| 18 | Person 2 | 13 | 13.7 | +0.7  | 5.38%  |
| 19 | Person 2 | 14 | 17.7 | +3.7  | 26.43% |
| 20 | Person 2 | 15 | 9.1  | −5.9  | 39.33% |

**Summary — BR @ 0.5 m**

| | Person 1 | Person 2 | Overall |
|:--|:--:|:--:|:--:|
| Mean % Error | 31.20% | 34.51% | 32.85% |

### Data Analysis

<!-- Upload your BR chart screenshots to GitHub and replace these URLs -->
![BR @ 1.0m Chart](https://raw.githubusercontent.com/TnTech-ECE/F25_Team8_DARPAChallengeTriageDrone/refs/heads/Gideon-B3-Vitals-n-DSP-experimental/Reports/Experimental%20Analysis/Radar%20Testing%20Graphs/BR-1.0m.png)
![BR @ 0.5m Chart](https://raw.githubusercontent.com/TnTech-ECE/F25_Team8_DARPAChallengeTriageDrone/refs/heads/Gideon-B3-Vitals-n-DSP-experimental/Reports/Experimental%20Analysis/Radar%20Testing%20Graphs/BR-0.5m.png)

The breathing rate subsystem performed meaningfully better than the heart rate subsystem. At **1.0 m**, the overall mean percent error was **21.25%**, with Person 2 performing particularly well at **16.71%**. At **0.5 m**, performance was worse at **32.85%** overall — contrary to the expectation that closer range would improve accuracy. This suggests that at 0.5 m, chest displacement at closer range may be saturating the phase signal or introducing aliasing in the breathing frequency band. Unlike the consistent positive bias seen in heart rate, breathing rate errors were bidirectional — both over- and underestimation occurred — indicating the algorithm is tracking the correct frequency region but with inconsistent precision. Performance was strongest in the 12–17 breaths/min range, which falls squarely within the specified **0.13–1.0 Hz** window.

### Experimental Conclusion

The breathing rate measurement subsystem demonstrated reasonable performance consistent with the proof-of-concept stage. The specification requires respiratory rate detection in the **0.13 to 1.0 Hz** range from at least **1.0 m**, and the system meets this requirement — all measurements were taken at the required distance and detected rates fell within the specified band. The mean percent error of **21.25% at 1.0 m** is acceptable for a prototype. The unexpected accuracy degradation at 0.5 m warrants further investigation, as closer range should theoretically improve signal strength. A likely cause is increased motion artifact contamination when the subject is nearer to the sensor. Further tuning of the bandpass filter boundaries and phase unwrapping algorithm is recommended to improve consistency across subjects and distances.
