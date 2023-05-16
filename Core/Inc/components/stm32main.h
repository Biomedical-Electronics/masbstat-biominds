/*
 * stm32main**.h
 *
 *  Created on: Apr 25, 2023
 *      Author: plade
 */

#ifndef INC_COMPONENTS_STM32MAIN_H_
#define INC_COMPONENTS_STM32MAIN_H_

 #include "stm32f4xx_hal.h"

 struct Handles_S {
     UART_HandleTypeDef *huart;
     // Aqui iriamos anadiendo los diferentes XXX_HandleTypeDef que necesitaramos anadir.
 };

 void setup(struct Handles_S *handles);
 void loop(void);
#endif /* INC_COMPONENTS_STM32MAIN_H_ */
