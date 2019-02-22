/*
 * LM92.c
 *
 *  Created on: Feb 20, 2019
 *      Author: Mahbub.Istiaq
 */

#include "LM92.h"



void TemperatureSensorInit(tempHandle_t* tempHandler, uint8_t A1, uint8_t A0) {
	tempHandler->i2cAddress = (BASE_I2C_ADDRESS | A1 <<1 | A0)<<1;
	tempHandler->resultInCelcius = false;
	HAL_Delay(100);
}
float ReadTemperature(tempHandle_t* tempHandler, uint8_t timeout) {
	tempHandler->configBuffer[0] = TEMPERATURE_REG_PTR;
	HAL_I2C_Master_Transmit(&hi2c1, tempHandler->i2cAddress, tempHandler->configBuffer, 1, timeout);
	HAL_Delay(50);
	HAL_I2C_Master_Receive(&hi2c1, tempHandler->i2cAddress, tempHandler->receiveBuffer, 2, timeout);
	uint16_t temp = ((tempHandler->receiveBuffer[0] << 8) + (tempHandler->receiveBuffer[1]));
	return (ReadTemp(temp));
}
float ReadTemp(uint16_t tmp) {
	tmp = tmp >> 3;
	float temperature = (tmp * 0.0625);
	return temperature;
}
unsigned int GetManufactureId(tempHandle_t* tempHandler) {
	tempHandler->configBuffer[0] = ID_REG_PTR;
	HAL_I2C_Master_Transmit(&hi2c1, tempHandler->i2cAddress, tempHandler->configBuffer, 1, 100);
	HAL_Delay(50);
	HAL_I2C_Master_Receive(&hi2c1, tempHandler->i2cAddress, tempHandler->receiveBuffer, 2, 100);
	uint16_t temp = ((tempHandler->receiveBuffer[0] << 8) + (tempHandler->receiveBuffer[1] ));
	return temp;
}
unsigned int ReadConfigurationRegister(tempHandle_t* tempHandler) {
	tempHandler->configBuffer[0] = CONFIG_REG_PTR;
	HAL_I2C_Master_Transmit(&hi2c1, tempHandler->i2cAddress, tempHandler->configBuffer, 1, 100);
	HAL_Delay(50);
	HAL_I2C_Master_Receive(&hi2c1, tempHandler->i2cAddress, tempHandler->receiveBuffer, 1, 100);
	return tempHandler->receiveBuffer[0];
}
float ReadHysteresis(tempHandle_t* tempHandler) {
	tempHandler->configBuffer[0] = T_HYST_SET_REG_PTR;
	HAL_I2C_Master_Transmit(&hi2c1, tempHandler->i2cAddress, tempHandler->configBuffer, 1, 100);
	HAL_Delay(50);
	HAL_I2C_Master_Receive(&hi2c1, tempHandler->i2cAddress, tempHandler->receiveBuffer, 2, 100);
	uint16_t temp = ((tempHandler->receiveBuffer[0] << 8) + (tempHandler->receiveBuffer[1]));
	return(ReadTemp(temp));
}
float ReadTHigh(tempHandle_t* tempHandler) {
	tempHandler->configBuffer[0] = T_HIGH_SET_REG_PTR;
	HAL_I2C_Master_Transmit(&hi2c1, tempHandler->i2cAddress, tempHandler->configBuffer, 1, 100);
	HAL_Delay(50);
	HAL_I2C_Master_Receive(&hi2c1, tempHandler->i2cAddress, tempHandler->receiveBuffer, 2, 100);
	uint16_t temp = ((tempHandler->receiveBuffer[0] << 8) + (tempHandler->receiveBuffer[1]));
	return(ReadTemp(temp));
}
float ReadTlow(tempHandle_t* tempHandler) {
	tempHandler->configBuffer[0] = T_CRIT_SET_REG_PTR;
	HAL_I2C_Master_Transmit(&hi2c1, tempHandler->i2cAddress, tempHandler->configBuffer, 1, 100);
	HAL_Delay(50);
	HAL_I2C_Master_Receive(&hi2c1, tempHandler->i2cAddress, tempHandler->receiveBuffer, 2, 100);
	uint16_t temp = ((tempHandler->receiveBuffer[0] << 8) + (tempHandler->receiveBuffer[1]));
	return(ReadTemp(temp));
}
void SetHysteresis(tempHandle_t* tempHandler,double t) {
	t/= 0.0625;
	unsigned int temp = (int) t<<3;
	uint8_t tempBuffer[2];
	tempBuffer[0] = T_HYST_SET_REG_PTR;
	tempBuffer[1] = temp & 0xFF;
	tempBuffer[2] = (temp >> 8) & 0xFF;
	HAL_I2C_Master_Transmit(&hi2c1, tempHandler->i2cAddress, tempBuffer, 3, 100);
}
void SetTHigh(tempHandle_t* tempHandler,double t) {
	t/= 0.0625;
	unsigned int temp = (int) t<<3;
	uint8_t tempBuffer[2];
	tempBuffer[0] = T_HIGH_SET_REG_PTR;
	tempBuffer[1] = temp & 0xFF;
	tempBuffer[2] = (temp >> 8) & 0xFF;
	HAL_I2C_Master_Transmit(&hi2c1, tempHandler->i2cAddress, tempBuffer, 3, 100);
}
void SetTLow(tempHandle_t* tempHandler,double t) {
	t/= 0.0625;
	unsigned int temp = (int) t<<3;
	uint8_t tempBuffer[2];
	tempBuffer[0] = T_LOW_SET_REG_PTR;
	tempBuffer[1] = temp & 0xFF;
	tempBuffer[2] = (temp >> 8) & 0xFF;
	HAL_I2C_Master_Transmit(&hi2c1, tempHandler->i2cAddress, tempBuffer, 3, 100);
}
void SetTCritical(tempHandle_t* tempHandler,double t) {
	t/= 0.0625;
	unsigned int temp = (int) t<<3;
	uint8_t tempBuffer[2];
	tempBuffer[0] = T_CRIT_SET_REG_PTR;
	tempBuffer[1] = temp & 0xFF;
	tempBuffer[2] = (temp >> 8) & 0xFF;
	HAL_I2C_Master_Transmit(&hi2c1, tempHandler->i2cAddress, tempBuffer, 3, 100);
}
