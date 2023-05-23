/*
 * timers.c
 *
 *  Created on: 16 may. 2023
 *      Author: Marc
 */

#include "main.h"
#include <stdbool.h>

volatile static bool timeout;  //variable porvada


void Start_Timer(uint32_t period){    //because it was the timer we defined previously
	__HAL_TIM_SET_AUTORELOAD(&htim2,period);
	__HAL_TIM_SET_COUNTER(&htim2,0);
	timeout=false;
	HAL_TIM_Base_Start_IT(&htim2);
}


bool TimeoutEllapsed(void){
	return timeout;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {

	timeout= true;

}

void ClearTimeout(void){
	timeout= false;
}

void Stop_Timer(void){

}
