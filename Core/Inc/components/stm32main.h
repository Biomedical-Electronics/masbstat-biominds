/*
 * stm32main**.h
 *
 *  Created on: Apr 25, 2023
 *      Author: plade
 */

#ifndef INC_COMPONENTS_STM32MAIN_H_
#define INC_COMPONENTS_STM32MAIN_H_

#include "stm32f4xx_hal.h"
#include "components/cyclic_voltammetry.h"
#include "components/mcp4725_driver.h"
#include "components/ad5280_driver.h"

#define CV 0
#define CA 1
#define IDLE 2

 struct Handles_S {
     UART_HandleTypeDef *huart;
     I2C_HandleTypeDef hi2c1;
     ADC_HandleTypeDef hadc1;
     TIM_HandleTypeDef htim2;
     MCP4725_Handle_T hdac;
     // Aqui iriamos anadiendo los diferentes XXX_HandleTypeDef que necesitaramos anadir.
 };

 void setup(struct Handles_S *handles);
 void loop(void);
#endif /* INC_COMPONENTS_STM32MAIN_H_ */
