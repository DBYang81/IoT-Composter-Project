#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/i2c.h"
#include "inc/ssd1306.h"
#include "inc/temp_h.h"

#include "lwipopts.h"
#include "proj_mqtt.h"

int main(){
    
    stdio_init_all();
    if(cyw43_arch_init()){
        printf("WiFi init failed");
        return -1;
    }
    
    //connect to wifi
    cyw43_arch_enable_sta_mode();
    printf("Connecting to WiFi...\n");
    if (cyw43_arch_wifi_connect_timeout_ms(wifi_ssid, wifi_pass, CYW43_AUTH_WPA2_AES_PSK, 30000)) {
        printf("Failed to connect\n");
        return 1;
    }
    else {
        printf("Connected\n");
    }
    
    //create mqtt client
    mqtt_client_t *client = mqtt_client_new();
    if (client != NULL) {
      mqtt_connect(client);
    }
    else {
      printf("mqtt client init failed\n");
      return -1;
    }
	
    //vars for mqtt
    err_t err;
    char payload_buf[30];
	
    //i2c stuff
    i2c_init(i2c0, 200000); //choose i2c0, 200k speed
    gpio_set_function(0, GPIO_FUNC_I2C); //sda
    gpio_set_function(1, GPIO_FUNC_I2C); //scl
    gpio_pull_up(0); //sda
    gpio_pull_up(1); //scl
    
    sleep_ms(100);

    ssd1306_t disp;
    disp.external_vcc = false;
    ssd1306_init(&disp, 128, 64, 0x3C, i2c0);
    ssd1306_contrast(&disp, 0x1F);
    ssd1306_clear(&disp);
	
    float deg = 0, hum = 0;
    char *descrpForTemp = "Teperature:";
    char *descrpForHum = "Humidity:";
	
    char degBuf[10];
    char humBuf[10];

    while(true){
	
	ssd1306_clear(&disp);

        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        
	tempHumi ret = getTempAndHumidityData();
	
	hum = ret.humidity;
	deg = ret.temp;

	snprintf(degBuf, 10, "%.1f C", deg);
	snprintf(humBuf, 10, "%.1f %%", hum);

	ssd1306_draw_string(&disp, 0, 5, 1, descrpForTemp);
	ssd1306_draw_string(&disp, 0, 15, 2, degBuf);

	ssd1306_draw_string(&disp, 0, 35, 1, descrpForHum);
	ssd1306_draw_string(&disp, 0, 45, 2, humBuf);

	ssd1306_show(&disp);

        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);

        sleep_ms(300);
	    
	//check mqtt connection
	if (mqtt_client_is_connected() == 0) {
            mqtt_connect(client);
        }
	    
        //form mqtt message
        snprintf(payload_buf, 30, "{\"temp\":\"%.1f\",\"hum\":\"%.1f\"}", deg, hum);

	//publish message
        err = mqtt_publish(client, "controller/status", payload_buf, strlen(payload_buf), 0, 0, mqtt_pub_request_cb, NULL);
        if(err != ERR_OK) {
            printf("Publish err: %d\n", err);
        }
    }
    return 0;
}

