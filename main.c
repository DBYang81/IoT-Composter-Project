#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/i2c.h"
#include "inc/ssd1306.h"
#include "inc/temp_h.h"
#include "inc/ultrasonic.h"
#include "inc/oled.h"


int main(){
    
    stdio_init_all();
    if(cyw43_arch_init()){
        printf("WiFi init failed");
        return -1;
    }

    getI2cInit();
    initOled();

    double distance;
    tpHumi th;
    float deg = 0, hum = 0;
    char* tempDescription = "Temperature: ";
    char* humDescription = "Humidity: ";
    char degBuff[10];
    char humBuff[10];


    while (1){
        
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);

	distance = getCm();
        printf("Object is %5.2f cm away. \n", distance);
       

	th = getTempAndHumidityData();
        deg = th.temp;
        hum = th.humidity;
        printIntoStrDeg(degBuff,deg);
        printIntoStrHum(humBuff,hum);
        oledClean();
        oledDisplay(0,  5, 1, tempDescription);
        oledDisplay(0, 15, 2, degBuff);
        oledDisplay(0, 35, 1, humDescription);
        oledDisplay(0, 45, 2, humBuff);
        oledShow();

        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        sleep_ms(1000);
    }

     
  
    return 0;
}

