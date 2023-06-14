/*
 * rele.c
 *
 *  Created on: May 16, 2023
 *      Author: plade
 */

#include "main.h"

void Start_Rele(void){
	HAL_GPIO_WritePin(RELAY_GPIO_Port, RELAY_Pin, GPIO_PIN_SET);
}

void Close_Rele(void){
	HAL_GPIO_WritePin(RELAY_GPIO_Port, RELAY_Pin, GPIO_PIN_RESET);
}

