cmake_minimum_required(VERSION 3.10)
project(vital_sense C)

set(SDK_PATH "C:/Users/drago/OneDrive/Desktop/ECE-4961/radar_sdk")

include_directories(${SDK_PATH}/sdk/c)

link_directories(${SDK_PATH}/libs/win32_x64)

add_executable(vital_sense vital_sense.c)

target_link_libraries(vital_sense sdk_avian sdk_algo sdk_base)