cmake_minimum_required(VERSION 3.13)

include($ENV{PICO_SDK_PATH}external/pico_sdk_import.cmake)

project(display C CXX ASM)
set(CMAKE_C STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(lcd
    lcd.c
    ssd1306.c
    ssd1306.h
)

target_link_libraries(lcd
	pico_stdlib
	pico_cyw43_arch_none
	hardware_i2c
	)

pico_enable_stdio_usb(lcd 1)
pico_enable_stdio_uart(lcd 0)

pico_add_extra_outputs(lcd)

target_include_directories(lcd PRIVATE ${CMAKE_CURRENT_LIST_DIR} )


target_link_libraries(lcd pico_cyw43_arch_lwip_threadsafe_background pico_stdlib hardware_i2c)
