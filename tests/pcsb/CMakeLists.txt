cmake_minimum_required(VERSION 3.13)
set(CMAKE_C_STANDARD 11)

project(pcsb
    VERSION 1.0.0
    DESCRIPTION "PicoCalc STM32 southbridge I2C driver"
)

add_library(${PROJECT_NAME} INTERFACE)

target_sources(${PROJECT_NAME} INTERFACE
    pcsb.c
    kbd.c
    rtc.c
)

target_link_libraries(${PROJECT_NAME} INTERFACE 
    pico_stdlib
    hardware_i2c
)

target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_LIST_DIR})