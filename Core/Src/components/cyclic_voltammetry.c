/*
 * cyclic_voltammetry.c
 *
 *  Created on: 8 de juny 2023
 *      Author: plade
 */

#include "components/cyclic_voltammetry.h"
#include <components/mcp4725_driver.h>
#include "components/chronoamperometry.h"
#include "components/stm32main.h"
#include "components/timers.h"
#include "components/i2c_lib.h"
#include "components/adc.h"
#include "components/masb_comm_s.h"
#include "components/PMU.h"
#include "components/rele.h"
#include "components/stm32main.h"
#include "components/formulas.h"

extern I2C_HandleTypeDef hi2c1;
extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim2;
extern MCP4725_Handle_T hdac;


int compare_function(double x, double y){
	return (x - y) < 0.000005;
}

void cyclic_voltammetry(struct CV_Configuration_S cvConfiguration){

	MCP4725_SetOutputVoltage(hdac,  calculateDacOutputVoltage(cvConfiguration.eBegin));
	double VObjective = cvConfiguration.eVertex1;
	Start_Rele();

	uint8_t cycles = cvConfiguration.cycles;
	double scanRate = cvConfiguration.scanRate;
	double eStep = cvConfiguration.eStep;
	double SamplingPeriod = eStep / (scanRate / 1000);

	Start_Timer(SamplingPeriod);

	uint8_t numbercycles = 0;

	eStep=cvConfiguration.eStep;

	uint32_t EllapsedTime = 0;
	uint32_t counter_data = 1;


	while (EllapsedTime < SamplingPeriod){

			if (TimeoutEllapsed()){
				EllapsedTime = EllapsedTime + SamplingPeriod;

				ADC_Start();
				uint32_t voltageAdc = ADC_get_Voltage();
				uint32_t currentAdc = ADC_get_Current();

				double current = calculateIcellCurrent(currentAdc);
				double voltage = calculateVrefVoltage(voltageAdc);
				ADC_Stop();

				struct Data_S data;

				data.point = counter_data;
				counter_data = counter_data +1;
				data.timeMs = EllapsedTime;
				data.current = current;
				data.voltage = voltage;

				MASB_COMM_S_sendData(data);

				ClearTimeout();

					if (compare_function(VObjective, cvConfiguration.eVertex1)) {

						VObjective = cvConfiguration.eVertex2;

					} else if (compare_function(VObjective, cvConfiguration.eVertex2)) {

						VObjective = cvConfiguration.eBegin;

					} else {
						VObjective = cvConfiguration.eVertex1;


					}
					} else {
						if (compare_function(VObjective, cvConfiguration.eVertex1)) {

							if (cvConfiguration.eBegin + eStep > VObjective) {

								cvConfiguration.eBegin = VObjective;

							} else {

								cvConfiguration.eBegin = cvConfiguration.eBegin + eStep;
							}
						}
						if (compare_function(VObjective, cvConfiguration.eVertex2)) {

							if (cvConfiguration.eBegin - eStep < VObjective) {

								cvConfiguration.eBegin = VObjective;

							} else {

								cvConfiguration.eBegin = cvConfiguration.eBegin - eStep;
							}
						}
						if (compare_function(VObjective, cvConfiguration.eBegin)) {

							if (cvConfiguration.eBegin + eStep > VObjective) {

								cvConfiguration.eBegin = VObjective;

							} else {

								cvConfiguration.eBegin = cvConfiguration.eBegin + eStep;

							}
						}
					}

				MCP4725_SetOutputVoltage(hdac, calculateDacOutputVoltage(cvConfiguration.eBegin));

			}

			Close_Rele();

			Stop_Timer();

}
