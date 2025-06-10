# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 1.5.1)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(Sintetizador_de_Audio C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(Sintetizador_de_Audio app/Sintetizador_de_Audio_definitivo.c )

add_library(driver STATIC
    driver/microphone.c
    driver/neopixel.c
    driver/ssd1306.c
    driver/ssd1306.c
    driver/buzzer.c
    driver/button.c
    driver/led.c
)

add_library(hal STATIC
        hal/write_display.c
        hal/signal_tratament.c
        hal/show_display.c
)


pico_set_program_name(Sintetizador_de_Audio "Sintetizador_de_Audio")
pico_set_program_version(Sintetizador_de_Audio "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(Sintetizador_de_Audio 0)
pico_enable_stdio_usb(Sintetizador_de_Audio 1)

# Add the standard library to the build
target_link_libraries(Sintetizador_de_Audio
        pico_stdlib
        hal 
        driver)

target_link_libraries(driver 
        pico_stdlib
        hardware_dma
        hardware_timer
        hardware_adc
        hardware_pio
        hardware_clocks
        hardware_i2c
        hardware_pwm
        )

target_link_libraries(hal 
        pico_stdlib
        hardware_i2c
        driver
        )

pico_generate_pio_header(driver
    ${CMAKE_CURRENT_LIST_DIR}/driver/ws2818b.pio
)

# Add the standard include files to the build
target_include_directories(Sintetizador_de_Audio PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/include
)

target_include_directories(driver PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/include
)

target_include_directories(hal PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/include
)

# Add any user requested libraries
target_link_libraries(Sintetizador_de_Audio 
        
        )

pico_add_extra_outputs(Sintetizador_de_Audio)

