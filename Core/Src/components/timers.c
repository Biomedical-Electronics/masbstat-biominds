/*
 * timers.c
 *
 *  Created on: 16 may. 2023
 *      Author: Marc
 */

#include "main.h"


static uint32_t Voltage = 0;
static uint32_t Current = 0;



void Start_Timer(){    //because it was the timer we defined previously
	__HAL_TIM_SET_AUTORELOAD(&htim2,10000);
}
