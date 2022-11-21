#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/i2c.h"

int main(){
    
    stdio_init_all();
    if(cyw43_arch_init()){
        printf("WiFi init failed");
        return -1;
    }
    
    //i2c stuff
    i2c_init(i2c1, 100000); //choose i2c0, 50k speed
    gpio_set_function(14, GPIO_FUNC_I2C); //sda
    gpio_set_function(15, GPIO_FUNC_I2C); //scl
    gpio_pull_up(14); //sda
    gpio_pull_up(15); //scl
    
    //uint8_t temp; //variable for temperature
    uint8_t status; //var for status
    //uint16_t humid; //var for humidity
    uint8_t arr[4] = {};
    
    const uint8_t sensor_address = 0x27; // default salve address
    const uint8_t readStateCmd = 0x01; // reading bit
    const uint8_t measureReqCmd = 0x00; // measurement request command
    const uint8_t statusCmd = 0x01; // status bit

    sleep_ms(5000);

    while(true){
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        printf("Hello user\n");
        //Measrument request 
        //send command 0x00, wait and read the data status
        i2c_write_blocking(i2c1, sensor_address, &measureReqCmd, 1, false); 
       // sleep_ms(100);
        //i2c_read_blocking(i2c_default, sensor_address, &ico_ dico_ dstatus, 1, false);
        //sleep_ms(100);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        //sleep_ms(100);

        //read humidity reg
        //if(status == statusCmd){ // data is ready
        //printf("step 1\n");
            //i2c_write_blocking(i2c_default, sensor_address, &readStateCmd, 1, true);
            
        i2c_read_blocking(i2c1, sensor_address, arr, 4, false);

        printf("step 2\n");
        sleep_ms(100);
            //i2c_read_blocking(i2c_default, sensor_address, &temp, 2, false);
            //sleep_ms(100);
        //}
        printf("sadha %d\n", arr[0]);
        sleep_ms(600);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);

        //print results
        printf("humidity: %d, %d temp: %d, %d\n", arr[0], arr[1], arr[2], arr[3]);
    }
    return 0;
}

