#ifndef PROJ_MQTT_H
#define PROJ_MQTT_H

//#include "lwipopts.h"
#include "lwip/apps/mqtt.h"

static const char wifi_ssid[] = "SmartIotMQTT";
static const char wifi_pass[] = "SmartIot";

static int inpub_id;

void mqtt_connect(mqtt_client_t *client);
void mqtt_connect_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status);
void mqtt_sub_request_cb(void *arg, err_t result);
void mqtt_incoming_publish_cb(void *arg, const char *topic, u32_t tot_len);
void mqtt_incoming_data_cb(void *arg, const u8_t *data, u16_t len, u8_t flags);
void mqtt_pub_request_cb(void *arg, err_t result);

#endif
