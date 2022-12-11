#include "inc/temp_h.h"


/*i2c_init(i2c1, 200000); //choose i2c1, 200k speed
gpio_set_function(14, GPIO_FUNC_I2C); //SDA
gpio_set_funciton(15, GPIO_FUNC_I2C); //SCL
gpio_pull_up(14); //sda pullup
gpio_pull_up(15); //scl pullup
*/

tempHumi getTempAndHumidityData(){
	
	i2c_init(i2c1, 200000); //choose i2c1, 200k speed
	gpio_set_function(14, GPIO_FUNC_I2C); //SDA
	gpio_set_function(15, GPIO_FUNC_I2C); //SCL
	gpio_pull_up(14); //sda pullup
	gpio_pull_up(15); //scl pullup



	uint8_t status; //var for status
	uint8_t arr[4] = {}; //array for storing the 4 bytes data from sensor

	const uint8_t sensor_address = 0x27; //default slave address
	const uint8_t readStateCmd = 0x01; //reading bit
	const uint8_t measureReqCmd = 0x00; //measurement request command
	const uint8_t statusCmd = 0x01; //status bit


	i2c_write_blocking(i2c1, sensor_address, &measureReqCmd, 1, false);
	sleep_ms(100);

	i2c_read_blocking(i2c1, sensor_address, arr, 4, false);
	sleep_ms(100);

	unsigned int comb_hum = ((unsigned int) arr[0] << 8) + arr[1];
	float humidity = comb_hum / (pow(2, 14) - 2) * 100;

	unsigned int comb_temp = ((unsigned int) arr[2] << 8) + arr[3];
	float temp = (comb_temp >> 2) / (pow(2, 14) - 2) * 165 - 40;

	tempHumi tempAndHumidity = {humidity, temp};

	return tempAndHumidity;

}
