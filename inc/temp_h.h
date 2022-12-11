#include <stdio.h>
#include <math.h>
#include "pico/cyw43_arch.h"
#include "hardware/i2c.h"
#include "pico/stdlib.h"


typedef struct tempHumi{
	float humidity;
	float temp;
}tempHumi;


/*uint8_t status; //var for status
uint8_t arr[4] = {}; //array for storing the 4 bytes data from sensor

const uint8_t sensor_address = 0x27; //default slave address
const uint8_t readStateCmd = 0x01; //reading bit
const uint8_t measureReqCmd = 0x00; //measurement request command
const uint8_t statusCmd = 0x01; //status bit
*/

tempHumi getTempAndHumidityData ();


