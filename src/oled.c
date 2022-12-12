
#include "oled.h"


void oledClean(){

     ssd1306_clear(&disp);
}
	
void printIntoStrDeg(char* str, double deg){
	snprintf(str, 10, "%.1f C", deg);

}

void printIntoStrHum(char* str, double hum){
	snprintf(str, 10, "%.1f %%", hum);
}

void oledDisplay(int x, int y, int font, char*str){
	
	ssd1306_draw_string(&disp, x, y, font, str);
}

void oledShow(){
	ssd1306_show(&disp);
}


