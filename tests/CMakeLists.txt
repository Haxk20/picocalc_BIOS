cmake_minimum_required(VERSION 3.12)

set(ENV{PICO_PLATFORM} "rp2350")

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)
#include(pico_extras_import_optional.cmake)

project(picocalc_BIOS_jcs_picotester C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "2.1.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 2.1.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

if (NOT DEFINED PICO_STDIO_USB_CONNECT_WAIT_TIMEOUT_MS)
    set(PICO_STDIO_USB_CONNECT_WAIT_TIMEOUT_MS 3000)
endif()

# Initialize the SDK
pico_sdk_init()

add_compile_options(
	-Wall
	-Wextra
	-Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
	-Wno-unused-function # we have some for the docs that aren't called
)
		
if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wno-maybe-uninitialized)
endif()

include_directories(
	${CMAKE_CURRENT_LIST_DIR}
)

add_subdirectory(pcsb)
add_subdirectory(lcdspi)
add_subdirectory(rp2040-psram)

add_executable(${PROJECT_NAME}
	main.c
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    PSRAM_MUTEX=1
    #PSRAM_SPINLOCK=0
    PSRAM_ASYNC=0
    PSRAM_PIN_CS=20
    PSRAM_PIN_SCK=21
    PSRAM_PIN_MOSI=2
    PSRAM_PIN_MISO=3
)

# pull in common dependencies
target_link_libraries(${PROJECT_NAME} 
	pico_stdlib
	hardware_irq
	hardware_i2c
	hardware_spi
	hardware_dma
	hardware_exception
	hardware_pio
	pcsb
	lcdspi
	rp2040-psram
)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(${PROJECT_NAME})

# some hardware configurations
pico_enable_stdio_usb(${PROJECT_NAME} 0)
pico_enable_stdio_uart(${PROJECT_NAME} 0)