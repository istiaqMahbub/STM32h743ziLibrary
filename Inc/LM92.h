/*
 * LM92.h
 *
 *  Created on: Feb 20, 2019
 *      Author: Mahbub.Istiaq
 */

#ifndef LM92_H_
#define LM92_H_

#include <stdbool.h>
#include "stm32h7xx_it.h"
#include "stm32h7xx.h"
#include "stm32h7xx_hal_conf.h"

#define BASE_I2C_ADDRESS 			0x48
#define TEMPERATURE_REG_PTR			0x00
#define CONFIG_REG_PTR				0x01
#define T_HYST_SET_REG_PTR			0x02
#define T_CRIT_SET_REG_PTR			0x03
#define T_LOW_SET_REG_PTR			0x04
#define T_HIGH_SET_REG_PTR			0x05
#define ID_REG_PTR					0x07

I2C_HandleTypeDef hi2c1;

typedef struct {

	uint8_t i2cAddress;
	bool resultInCelcius;
	uint8_t configBuffer[10];
	uint8_t receiveBuffer[10];
}tempHandle_t;

extern float ReadTemperature(tempHandle_t* tempHandler, uint8_t timeout);
extern unsigned int GetManufactureId(tempHandle_t* tempHandler);
extern unsigned int ReadConfigurationRegister(tempHandle_t* tempHandler);
extern float ReadHysteresis(tempHandle_t* tempHandler);
extern float ReadTHigh(tempHandle_t* tempHandler);
extern float ReadTLow(tempHandle_t* tempHandler);
extern double ReadTCritical(tempHandle_t* tempHandler);
extern void SetHysteresis(tempHandle_t* tempHandler,double t);
extern void SetTHigh(tempHandle_t* tempHandler,double t);
extern void SetTLow(tempHandle_t* tempHandler,double t);
extern void SetTCritical(tempHandle_t* tempHandler,double t);
extern void TemperatureSensorInit(tempHandle_t* tempHandler, uint8_t A1, uint8_t A0);
extern float ReadTemp(uint16_t tmp);

#endif /* LM92_H_ */
