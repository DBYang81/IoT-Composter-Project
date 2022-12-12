cmake_minimum_required(VERSION 3.13)

include (pico_sdk_import.cmake)

project(Decompost_project C CXX ASM)

set(CMAKE_C STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(PICO_BOARD pico_w)
pico_sdk_init()

add_executable(proj
    	main.c
	./src/temp_h.c
	./inc/temp_h.h
	./src/ssd1306.c
	./inc/ssd1306.h
	./inc/font.h
	./inc/oled.h
	./src/oled.c
	./inc/ultrasonic.h
	./src/ultrasonic.c
	./inc/proj_mqtt.h
	./src/proj_mqtt.c
)

target_sources(proj PRIVATE 
	${PICO_SDK_PATH}/lib/lwip/src/apps/mqtt/mqtt.c)

# enable usb output, disable uart output
pico_enable_stdio_usb(proj 1)
pico_enable_stdio_uart(proj 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(proj)

target_include_directories(proj PRIVATE ${CMAKE_CURRENT_LIST_DIR} ${PROJECT_SOURCE_DIR})

target_link_libraries(proj pico_cyw43_arch_lwip_threadsafe_background pico_stdlib hardware_i2c hardware_timer hardware_uart)
