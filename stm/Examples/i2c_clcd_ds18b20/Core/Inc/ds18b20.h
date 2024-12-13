/*
 * ds18b20.h
 *
 *  Created on: Nov 26, 2024
 *      Author: IoT Main
 */

#ifndef INC_DS18B20_H_
#define INC_DS18B20_H_

#include "stm32f4xx_hal.h"

#define DS18B20_Pin GPIO_PIN_1
#define DS18B20_GPIO_Port GPIOA

void DS18B20_init();
uint8_t DS18B20_Start (void);
void DS18B20_Write (uint8_t data);
uint8_t DS18B20_Read (void);

#endif /* INC_DS18B20_H_ */
