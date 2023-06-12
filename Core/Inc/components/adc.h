/*
 * adc.h
 *
 *  Created on: 16 de maig 2023
 *      Author: plade
 */

#ifndef INC_COMPONENTS_ADC_H_
#define INC_COMPONENTS_ADC_H_

void ADC_Start(void);

uint32_t ADC_get_Voltage();

uint32_t ADC_get_Current();

void ADC_Stop(void);

#endif /* INC_COMPONENTS_ADC_H_ */
