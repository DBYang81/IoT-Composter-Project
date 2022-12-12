
#include "../inc/oled.h"


//i2c stuff
void getI2cInit(){    
    i2c_init(i2c0, 200000); //choose i2c0, 200k speed
    gpio_set_function(0, GPIO_FUNC_I2C); //sda
    gpio_set_function(1, GPIO_FUNC_I2C); //scl
    gpio_pull_up(0); //sda
    gpio_pull_up(1); //scl
}

ssd1306_t disp;

void initOled(){

    disp.external_vcc = false;
    ssd1306_init(&disp, 128, 64, 0x3C, i2c0);
    ssd1306_contrast(&disp, 0x1F);
    ssd1306_clear(&disp);
}



void oledClean(){

     ssd1306_clear(&disp);
}
	
void printIntoStrDeg(char* buff, float deg){
	snprintf(buff, 10, "%.1f C", deg);

}

void printIntoStrHum(char* buffer, float hum){
	snprintf(buffer, 10, "%.1f %%", hum);
}

void oledDisplay(int x, int y, int font, char* s){
	
	ssd1306_draw_string(&disp, x, y, font, s);
}

void oledShow(){
	ssd1306_show(&disp);
}


