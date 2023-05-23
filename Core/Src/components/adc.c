/*
 * adc.c
 *
 *  Created on: 16 de maig 2023
 *      Author: plade
 */

#include "main.h"

extern ADC_HandleTypeDef hadc1;

void ADC_Start(void) {

HAL_ADC_Start();

}

uint32_t ADC_get_Voltage(void) {
    HAL_ADC_PollForConversion();
    return HAL_ADC_GetValue();
}

uint32_t ADC_get_Current(void) {
    HAL_ADC_PollForConversion();
    return HAL_ADC_GetValue();
}

void ADC_Stop(void) {
    HAL_ADC_Stop();
}

