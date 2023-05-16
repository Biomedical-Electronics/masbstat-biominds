/*
 * adc.c
 *
 *  Created on: 16 de maig 2023
 *      Author: plade
 */

#include "main.h"

extern ADC_HandleTypeDef hadc1;

uint32_t ADC_get_value_cells() {
	HAL_ADC_Start(&hadc1); // We start the conversion
	HAL_ADC_PollForConversion(&hadc1, 300); // Poll for regular conversion complete. (300 ms)
	return HAL_ADC_GetValue(&hadc1);  // We read the result of the conversion and we save it in potADC
}
