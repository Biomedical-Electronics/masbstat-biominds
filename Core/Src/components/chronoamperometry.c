/*
 * chronoamperometry.c
 *
 *  Created on: 30 may. 2023
 *      Author: Isabel
 */

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

void chronoamperometry(struct CA_Configuration_S caConfiguration){


	MCP4725_SetOutputVoltage(hdac,  calculateDacOutputVoltage(caConfiguration.eDC));// To fix the voltage from all the voltage values it could get
	// Tensio edc --> calculem tensio equivalent --> li passem a la funcio calculateDa

	Start_Rele();
	Start_Timer(caConfiguration.samplingPeriodMs);
	uint32_t EllapsedTime = 0;
	uint32_t counter_data = 1;

	while (EllapsedTime < caConfiguration.measurementTime*1000){


		if (TimeoutEllapsed()){
			EllapsedTime = EllapsedTime + caConfiguration.samplingPeriodMs;
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


		}

	}
	Close_Rele();
	Stop_Timer();
}


