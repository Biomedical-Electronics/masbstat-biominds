/*
 * PMU.c
 *
 *  Created on: 16 may. 2023
 *      Author: Marc
 */
#include "main.h"

void Start_PMU(void){
	HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET);
	HAL_Delay(500);
}

void Close_PMU(void){
	HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET);
}
