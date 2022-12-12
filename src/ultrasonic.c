#include "../inc/ultrasonic.h"

uint trigPin =16; 
uint echoPin =17;
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

absolute_time_t measurePulse (uint pin, uint state) {
    while (gpio_get(pin) != state);
    absolute_time_t start = get_absolute_time();

    while (gpio_get(pin) == state);
    absolute_time_t end = get_absolute_time();

    return end - start;
}

float getCm ()
{
    setupUltrasonicPins(trigPin, echoPin);
    bool high =true;

    gpio_put(trigPin, 0);
    sleep_ms(2);
    gpio_put(trigPin, 1);
    sleep_us(10);
    gpio_put(trigPin, 0);

    long pulse_length = measurePulse(echoPin, 0);

    float distance = pulse_length / 58.0;
    
    return distance;
}

