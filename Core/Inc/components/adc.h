/*
 * adc.h
 *
 *  Created on: 16 de maig 2023
 *      Author: plade
 */

#ifndef INC_COMPONENTS_ADC_H_
#define INC_COMPONENTS_ADC_H_

ADC_Start();

uint32_t ADC_get_Voltage();

uint32_t ADC_get_Current();

ADC_Stop();

#endif /* INC_COMPONENTS_ADC_H_ */
