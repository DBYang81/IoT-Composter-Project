#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include "pico/stdlib.h"
#include <stdio.h>
#include "hardware/gpio.h"
#include "hardware/timer.h"
#include "pico/cyw43_arch.h"
#include "hardware/uart.h"
#include <stdbool.h>
#include "pico/time.h"
#include "pico/types.h"





void setupUltrasonicPins(uint trigPin, uint echoPin);
float getCm();
absolute_time_t measurePulse(uint trigPin, uint echoPin);
#endif
