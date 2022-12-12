#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/i2c.h"
#include "inc/ssd1306.h"
#include "inc/temp_h.h"



//i2c stuff
    i2c_init(i2c0, 200000); //choose i2c0, 200k speed
    gpio_set_function(0, GPIO_FUNC_I2C); //sda
    gpio_set_function(1, GPIO_FUNC_I2C); //scl
    gpio_pull_up(0); //sda
    gpio_pull_up(1); //scl
 

//initialize oled 
    ssd1306_t disp;
    disp.external_vcc = false;
    ssd1306_init(&disp, 128, 64, 0x3C, i2c0);
    ssd1306_contrast(&disp, 0x1F);
    ssd1306_clear(&disp);

void printIntoStrDeg(char* str, double deg);

void printIntoStrHum(char* str, double hum);

void oledClean();

void oledDisplay(int x, int y, int font, char* str);

void oledShow();
