cmake_minimum_required(VERSION 3.13)

# include($ENV{PICO_SDK_PATH}/pico_sdk_init.cmake) 
include(${CMAKE_CURRENT_LIST_DIR}/lib/pico-sdk/pico_sdk_init.cmake)

project(MPU6050_Gyro_Test)
pico_sdk_init()

add_executable(gyro_test
    gyro.c
    mpu6050.c
)

target_link_libraries(gyro_test
    pico_stdlib
    hardware_i2c
)

pico_add_extra_outputs(gyro_test)
set(CMAKE_BUILD_TYPE Debug)
