# Makefile for vital_sense.exe - Windows NMake + CMake

.PHONY: clean build run rebuild default

# Clean only the build folder
clean:
	@if exist build rmdir /s /q build
	@echo Build directory cleaned.

# Rebuild from scratch
rebuild: clean build

# Main build target
build:
	@if not exist build mkdir build
	@echo === Configuring with CMake ===
	@cd build && cmake -G "NMake Makefiles" ..
	@echo.
	@echo === Building with nmake ===
	@cd build && nmake /NOLOGO
	@echo.
	@echo === Copying DLLs ===
	@robocopy "libraries" "build" *.dll || echo No DLLs found or copy completed.
	@echo.
	@echo === Build completed successfully! ===
	@echo Final executable: build\vital_sense.exe

# Build and then run the executable
run: build
	@echo.
	@echo === Running vital_sense.exe ===
	@cd build && .\vital_sense.exe

# Default target
default: build
