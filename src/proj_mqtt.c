
#include "../inc/proj_mqtt.h"
#//include "lwip/apps/mqtt.h"
#include <string.h>

void mqtt_connect(mqtt_client_t *client) {
    struct mqtt_connect_client_info_t ci;
    err_t err;

    memset(&ci, 0, sizeof(ci));
    ci.client_id = "pico";
    ci.keep_alive = 100;
        
    ip_addr_t mqtt_broker;
    IP4_ADDR(&mqtt_broker, 192, 168, 1, 163);

    err = mqtt_client_connect(client, &mqtt_broker, MQTT_PORT, mqtt_connect_cb, 0, &ci);

    if (err != ERR_OK) {
        printf("mqtt_connect error %d\n", err);
    }
}

void mqtt_connect_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status) {
    err_t err;
    if (status == MQTT_CONNECT_ACCEPTED) {
        printf("mqqt_connect_cb: success\n");

        mqtt_set_inpub_callback(client, mqtt_incoming_publish_cb, mqtt_incoming_data_cb, arg);

        err = mqtt_subscribe(client, "controller/led", 1, mqtt_sub_request_cb, arg);

        if (err != ERR_OK) {
            printf("mqtt_connect_cb: subscribe returns %d\n", err);
        }
    }
    else {
        printf("mqtt_connect_cb: disconnected %d\n", status);

        mqtt_connect(client);
    }
}


//
void mqtt_sub_request_cb(void *arg, err_t result) {
    printf("Subscribe result: %d\n", result);
}

void mqtt_incoming_publish_cb(void *arg, const char *topic, u32_t tot_len) {
    printf("Incoming publish at topic %s with total length %u\n", topic, (unsigned int)tot_len);

    //TODO: modify
    if (strcmp(topic, "controller/led") == 0) {
        inpub_id = 1;
    }
    else {
        inpub_id = 0;
    }
    printf("Set inpub_id %d\n", inpub_id);
}

void mqtt_incoming_data_cb(void *arg, const u8_t *data, u16_t len, u8_t flags) {
    printf("Incoming publish payload with length %d, flags %u\n", len, (unsigned int)flags);

    //TODO: modify
    char buf[50] = {0};
    printf("Payload: ");
    for (int i=0;i<len;i++) {
        printf("%c",data[i]);
	buf[i] = data[i];
    }
    printf("\n");

    char* ret;
    /*char val[10];
    char key[10];
	
    char buf[50] = {0};
    ret = strstr(buf, "message");
    if (ret != NULL) {
        sscanf(ret, "%7s%*s", key);
        printf("Payload key: %s\n", key);
    }
    else {
        printf("Payload has invalid key\n");
    }

    ret = strstr(buf, "Done");
    if (ret != NULL) {
        sscanf(ret, "%4s%*s", val);
        printf("Payload value: %s\n", val);
    }
    else {
        printf("Payload has invalid value\n");
    }

    if (strcmp(val, "Done") == 0) {
       mqtt_led_done = 1;
        printf("led_done set to 1\n");
    }*/
    
    ret = strstr(buf, "Done");
    if (ret != NULL) {
	mqtt_led_done = 1;
	printf("mqtt led done set");
    }

    /*if(flags & MQTT_DATA_FLAG_LAST) {
        if (inpub_id == 1) {
            if(data[len-1] == 0) {
                printf("mqtt_incoming_data_cb: %s\n", (const char *)data);
            }
        }
    } else {
        // Handle fragmented payload, store in buffer, write to file or whatever 
    }*/
}

void mqtt_pub_request_cb(void *arg, err_t result) {
    if(result != ERR_OK) {
        printf("\nPublish result: %d\n", result);
    }
}
