cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(pico_temp C CXX ASM)
set(CMAKE_C STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()


add_executable(proj
        proj.c
        )

target_link_libraries(proj
        pico_stdlib              # for core functionality
        pico_cyw43_arch_none     # we need Wifi to access the GPIO, but we don't need anything else
        hardware_i2c
        )

# enable usb output, disable uart output
pico_enable_stdio_usb(proj 1)
pico_enable_stdio_uart(proj 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(proj)

target_include_directories(proj PRIVATE ${CMAKE_CURRENT_LIST_DIR} )

# add url via pico_set_program_url
#example_auto_set_url(proj)
