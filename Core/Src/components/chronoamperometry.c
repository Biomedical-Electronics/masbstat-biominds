/*
 * chronoamperometry.c
 *
 *  Created on: 30 may. 2023
 *      Author: Isabel
 */

#include "components/chronoamperometry.h"
#include "components/stm32main.h"
#include "components/timers.h"
#include "i2c_lib.h"
#include "adc.h"
#include "masb_comm_s.c"
#include "PMU.h"
#include "rele.h"
#include "stm32main.h"
#include "formulas.h"



void chronoamperometry(struct CA_Configuration_S caConfiguration){

	caConfiguration.measurementTime
	caConfiguration.eDC

	MCP4725_SetOutputVoltage(hdac,  calculateDacOutputVoltage(caConfiguration.eDC));// To fix the voltage from all the voltage values it could get
	// Tensio edc --> calculem tensio equivalent --> li passem a la funcio calculateDa

	Close_Rele();
	Start_Timer(caConfiguration.samplingPeriodMs);
	uint32_t EllaspedTime = 0;
	counter_data = 1;

	while (EllapsedTime < caConfiguration.measurementTime*1000){


		if (TimeoutEllapsed()){
			EllaspedTime = EllaspedTime + samplingPeriodMS;
			ADC_Start();
			uint32_t voltageAdc = ADC_getVoltage();
			uint32 currentAdc = ADC_getCurrent();
			double current = calculateIcellCurrent(currentAdc);
			double voltage = calculateVrefVoltage(voltageAdc);
			ADC_stop();

			struct Data_S data;

			data.point = counter_data;
			counter_data = counter_data +1;
			data.timeMs = EllaspedTime;
			data.current = current;
			data.voltage = voltage;

			MASB_COM_S_sendData(data);


			Clear_Timeout();


		}

	}
	Start_Rele();
	Stop_Timer();
}


