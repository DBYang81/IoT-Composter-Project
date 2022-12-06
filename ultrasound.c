#include "pico/stdlib.h"
#include <stdio.h>
#include "hardware/gpio.h"
#include "hardware/timer.h"
#include "pico/cyw43_arch.h"
#include "hardware/uart.h"
#include <stdbool.h>
#include "pico/time.h"
#include "pico/types.h"
uint trigPin =12; 
uint echoPin =13;
//int timeout = 26100;
//static int width = 0;


void setupUltrasonicPins(uint trigPin, uint echoPin)
{
    gpio_init(trigPin);
    gpio_init(echoPin);
    gpio_set_dir(echoPin, GPIO_IN);
    gpio_set_dir(trigPin, GPIO_OUT);

    // gpio_pull_up(echoPin);
}

absolute_time_t pulseIn (uint pin, uint state) {
    while (gpio_get(pin) != state);
    absolute_time_t start = get_absolute_time();

    while (gpio_get(pin) == state);
    absolute_time_t end = get_absolute_time();

    return end - start;
}

double getCm ()
{
    bool high =true;

    gpio_put(trigPin, 0);
    sleep_ms(2);
    gpio_put(trigPin, 1);
    sleep_us(10);
    gpio_put(trigPin, 0);

    long pulse_length = pulseIn(echoPin, 0);

    double distance = pulse_length / 58.0;
    
    return distance;
}


int main()
{
    stdio_init_all();
    setupUltrasonicPins(trigPin, echoPin);

    while (true) { 
        double distance = getCm();
        printf("\nObject is %5.2f cm is away.\n\n", distance); 
        sleep_ms(1000);
    }
}
