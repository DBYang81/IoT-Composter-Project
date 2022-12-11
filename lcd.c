#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include "ssd1306.h"
#include "pico/cyw43_arch.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>



int main() {
	
  	i2c_init(i2c0, 100000); //Select i2c0, 100k speed
  	gpio_set_function(0, GPIO_FUNC_I2C); // sda for oled
  	gpio_set_function(1, GPIO_FUNC_I2C); // scl for oled
  	gpio_pull_up(0); //sda pullup
  	gpio_pull_up(1); //scl pullup
  
  // initialise the oled ssd1306
  	ssd1306_t disp;
  	disp.external_vcc = false;
  	ssd1306_init(&disp, 128, 64, 0x3C, i2c0);
  	ssd1306_contrast(&disp, 0x1F);
  	ssd1306_clear(&disp);


	char *str = "Temperature:";
	char *deg = "28.5 C";
	char *str2 = "Humidity:";
	char *hum = "23.2 %";



	while(true){

		ssd1306_clear(&disp);
    	
		ssd1306_draw_string(&disp, 0, 5, 1, str);
		ssd1306_draw_string(&disp, 0, 15, 2, deg);
		
		ssd1306_draw_string(&disp, 0, 35, 1, str2);
		ssd1306_draw_string(&disp, 0, 45, 2, hum);
	
		ssd1306_show(&disp);
		sleep_ms(50);
	}
  	return 0;
}
