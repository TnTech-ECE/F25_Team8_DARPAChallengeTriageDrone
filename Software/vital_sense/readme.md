# Vital Sense Radar - Heart & Breathing Rate Monitor

This project uses an Infineon Avian 60 GHz radar sensor to detect heart rate and breathing rate in real-time.

## Requirements

- Note: Idk why im making this because its gonna take so much to run this prototype, it is not worth it bro. If you do want to run this yourself you'll need to update the inclusion path to the radar sdk in the cmake text file.

### Hardware
- Infineon Avian / XENSIV 60 GHz radar board (BGT60UTR11AIP)
- Connected via USB

### Software
- Windows 10 / 11 (64-bit)
- **Visual Studio** (any edition) with **C++ desktop development** workload installed
- **CMake** (latest version recommended)
- The Infineon Radar SDK (with headers and libraries)

### Project Structure
```
F25_Team8_Vital_Sense_Subsystem_proto/
├── radar_sdk/                 ← Contains necessary headers and libraries 
└── vital_sense/
    ├── vital_sense.c          ← Main source file
    ├── CMakeLists.txt         ← CMake configuration
    ├── libraries/             ← Contains required .dll files
    ├── Makefile               ← Simple build commands
    └── README.md
```

## How to Build and Run

### Option 1: Using the Makefile (Recommended)

1. Open **x64 Native Tools Command Prompt for VS**
2. Navigate to your project folder:
   ```cmd
   cd path\to\your\project
   ```

3. **Clean previous build** (recommended first time):
   ```cmd
   nmake clean
   ```

4. **Build the project**:
   ```cmd
   nmake build
   ```

5. **Run the program**:
   ```cmd
   nmake run
   ```

### Useful Commands

| Command              | Description                              |
|----------------------|------------------------------------------|
| `nmake build`        | Configure + build the executable         |
| `nmake run`          | Build then run `vital_sense.exe`         |
| `nmake clean`        | Delete the build folder                  |
| `nmake rebuild`      | Clean + rebuild from scratch             |
| `nmake`              | Don't use, it will just run everything   |

### Option 2: Manual Build

If you prefer to run the commands yourself:

```cmd
mkdir build
cd build
cmake -G "NMake Makefiles" ..
nmake
robocopy "..\libraries" "." *.dll ← provided that you are in the build directory still
vital_sense.exe
```

## After Building

The final executable will be located at:

```
build\vital_sense.exe
```

All required DLLs are automatically copied into the `build` folder.

## Important Notes

- **Warm-up time**: Let the radar run for at least **10 minutes** after starting before trusting the readings, especially in a cool room. The sensor needs time to reach stable operating temperature.
- **Position**: Best results are obtained when the person is **0.3 – 0.45 meters** away from the radar, facing the sensor directly (chest area).
- **First run**: You may see unstable or zero readings during the first 10–15 minutes while the radar warms up.
- The program will show range bin, magnitude, and estimated breathing + heart rate in the console.

## Troubleshooting

- If `nmake` fails during CMake step → Make sure Visual Studio C++ tools and CMake are installed.
- If DLLs are missing then, the `libraries` folder must be present with the required Avian SDK DLLs.
- If the program crashes on start → Check that the radar is properly connected and recognized by Windows.
