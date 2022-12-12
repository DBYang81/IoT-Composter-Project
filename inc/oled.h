#ifndef OLED_H
#define OLED_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/i2c.h"
#include "inc/ssd1306.h"
#include "inc/temp_h.h"



//i2c stuff
void getI2cInit();

void initOled();

void printIntoStrDeg(char* buff, float deg);

void printIntoStrHum(char* buffer, float hum);

void oledClean();

void oledDisplay(int x, int y, int font, char* s);

void oledShow();




#endif
