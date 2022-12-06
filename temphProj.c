#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/i2c.h"
#include <math.h>


int main(){
    
    stdio_init_all();
    if(cyw43_arch_init()){
        printf("WiFi init failed");
        return -1;
    }
    
    //i2c stuff
    i2c_init(i2c1, 100000); //choose i2c0, 100k speed
    gpio_set_function(14, GPIO_FUNC_I2C); //sda
    gpio_set_function(15, GPIO_FUNC_I2C); //scl
    gpio_pull_up(14); //sda pullup 
    gpio_pull_up(15); //scl pullup 
    
    uint8_t status; //var for status
    uint8_t arr[4] = {}; // array for storing the 4 bytes data from sensor
   

    const uint8_t sensor_address = 0x27; // default salve address
    const uint8_t readStateCmd = 0x01; // reading bit
    const uint8_t measureReqCmd = 0x00; // measurement request command
    const uint8_t statusCmd = 0x01; // status bit

    sleep_ms(5000);

    while(true){
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);

        //send 0x01 measurment request to wake up sensor
        i2c_write_blocking(i2c1, sensor_address, &measureReqCmd, 1, false); 
        sleep_ms(100);

        //read data of 4 bytes from reg, starting humidity then temperature
        i2c_read_blocking(i2c1, sensor_address, arr, 4, false);
        sleep_ms(100);

        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
	
	sleep_ms(300);

//	printf("humidity: %x, %x temp: %x, %x\n", arr[0], arr[1], arr[2], arr[3]);

	unsigned int comb_hum = ((unsigned int) arr[0] << 8) + arr[1]; 
	float humidity = comb_hum / (pow(2, 14) - 2) * 100;
	
	unsigned int comb_temp = ((unsigned int) arr[2] << 8 ) + arr[3]; 
 	float temp = (comb_temp >> 2 )/ (pow(2, 14) - 2) * 165 - 40;

        //print results
        printf("humidity: %.1f %%, temp: %.1f Degree\n", humidity, temp);

    }

    return 0;
}

