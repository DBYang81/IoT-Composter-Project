cmake_minimum_required(VERSION 3.13)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(project C CXX ASM)
set(CMAKE_C STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(temphProj
    temphProj.c
)

target_link_libraries(temphProj
        pico_stdlib
        pico_cyw43_arch_none
        hardware_i2c
        )

pico_enable_stdio_usb(temphProj 1)
pico_enable_stdio_uart(temphProj 0)

pico_add_extra_outputs(temphProj)

target_include_directories(temphProj PRIVATE ${CMAKE_CURRENT_LIST_DIR} )


target_link_libraries(temphProj pico_cyw43_arch_lwip_threadsafe_background pico_stdlib)