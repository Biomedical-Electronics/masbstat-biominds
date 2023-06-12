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
#include "components/formulas.h"
#include "main.h"


extern I2C_HandleTypeDef hi2c1;
extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim2;
extern MCP4725_Handle_T hdac;


int compare_function(double x, double y) {
    return (x - y) < 0.000005;
}

void cyclic_voltammetry(struct CV_Configuration_S cvConfiguration) {

	Start_Rele();

	float Vcell = cvConfiguration.eBegin;

    MCP4725_SetOutputVoltage(hdac, calculateDacOutputVoltage(Vcell));

    double VObj = cvConfiguration.eVertex1;
    double scanRate = cvConfiguration.scanRate;
    double eStep = cvConfiguration.eStep;
    double SamplingPeriod = eStep / (scanRate / 1000);

    uint8_t cycles = cvConfiguration.cycles;

    uint32_t counter_data = 1;
    uint32_t EllapsedTime= 0;
    uint32_t total_cycles = 0;

    Start_Timer(SamplingPeriod);

    while (total_cycles < cycles){
    	while (TimeoutEllapsed()== true){

			ADC_Start();
			uint32_t voltageAdc = ADC_get_Voltage();
			uint32_t currentAdc = ADC_get_Current();
			double current = calculateIcellCurrent(currentAdc);
			double voltage = calculateVrefVoltage(voltageAdc);

			struct Data_S data;
			data.point = counter_data;
			counter_data++;
			data.timeMs = EllapsedTime;
			data.current = current;
			data.voltage = voltage;

			MASB_COMM_S_sendData(data);

			EllapsedTime = EllapsedTime + SamplingPeriod;



			if (compare_function(Vcell, VObj)){

				if(compare_function(VObj, cvConfiguration.eVertex1)){

					VObj = cvConfiguration.eVertex2;

				}else if (compare_function(VObj, cvConfiguration.eVertex2)){

					VObj = cvConfiguration.eBegin;

				}else {

					VObj = cvConfiguration.eVertex1;

					total_cycles++;
				}
			} else {

				if (compare_function(VObj, cvConfiguration.eVertex1)){

					if (Vcell + eStep > VObj){

						Vcell = VObj;

					} else {

						Vcell = Vcell + eStep;
					}
				}

				if (compare_function(VObj,cvConfiguration.eVertex2)){

					if (Vcell - eStep < VObj){

						Vcell = VObj;

					} else {

						Vcell = Vcell - eStep;
					}
				}

				if (compare_function(VObj, cvConfiguration.eBegin)){

					if (Vcell + eStep > VObj){

						Vcell = VObj;

					} else {

						Vcell = Vcell + eStep;
					}
				}
			ClearTimeout();
			}
		    MCP4725_SetOutputVoltage(hdac, calculateDacOutputVoltage(Vcell));
    	}

    }
    Close_Rele();
    ADC_Stop();
    Stop_Timer();

}
