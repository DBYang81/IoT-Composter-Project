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
#include "inc/proj_mqtt.h"
#include "lwipopts.h"

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
    char payload_buf[100];
    const char* meg[3] = {"{\"message\":\"Put more wastes!\"}",
	    "{\"message\":\"Humidity too HIGH!\"}",
	    "{\"message\":\"Temperature too HIGH!\"}"
    };

    while (1){
        
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);

	distance = getCm();
       // printf("Object is %5.2f cm away. \n", distance);
       

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
        sleep_ms(100);

//check mqtt connection
        if (mqtt_client_is_connected(client) == 0) {
            mqtt_connect(client);
        }
            
        //form mqtt message
        snprintf(payload_buf, 100, "{\"temperature\":\"%.1f\",\"humidity\":\"%.1f\",\"distance\":\"%5.2f\"}", deg, hum, distance);
	
	printf("%s\n", payload_buf);

        //publish message
        err = mqtt_publish(client, "controller/status", payload_buf, strlen(payload_buf), 0, 0, mqtt_pub_request_cb, NULL);

	if(distance > 10.0) {
	        err = mqtt_publish(client, "controller/message", meg[0], strlen(meg[0]), 0, 0, mqtt_pub_request_cb, NULL);

	}else if(hum > 15){
		err = mqtt_publish(client, "controller/message", meg[1], strlen(meg[1]), 0, 0, mqtt_pub_request_cb, NULL);
	}else if(deg > 30){
		err = mqtt_publish(client, "controller/message", meg[2], strlen(meg[2]), 0, 0, mqtt_pub_request_cb, NULL);
	}
	if(err != ERR_OK) {
            printf("Publish err: %d\n", err);
        }

    }  
  
    return 0;
}

