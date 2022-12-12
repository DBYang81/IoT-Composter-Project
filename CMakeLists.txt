cmake_minimum_required(VERSION 3.13)

include($ENV{PICO_SDK_PATH}external/pico_sdk_import.cmake)

project(Decompost_project C CXX ASM)

set(CMAKE_C STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()


add_executable(proj
        main.c
	./src/temp_h.c
	./inc/temp_h.h
	./src/ssd1306.c
	./inc/ssd1306.h
	./inc/font.h
	./src/proj_mqtt.c
	./inc/proj_mqtt.h
)


# enable usb output, disable uart output
pico_enable_stdio_usb(proj 1)
pico_enable_stdio_uart(proj 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(proj)

target_include_directories(proj PRIVATE ${CMAKE_CURRENT_LIST_DIR} )

target_link_libraries(proj pico_cyw43_arch_lwip_threadsafe_background pico_cyw43_arch_none pico_stdlib hardware_i2c)
