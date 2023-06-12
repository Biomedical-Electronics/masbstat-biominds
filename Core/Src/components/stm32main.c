/*
 * stm32main**.c
 *
 *  Created on: Apr 25, 2023
 *      Author: plade
 */


#include <components/ad5280_driver.h>
#include <components/i2c_lib.h>
#include <components/mcp4725_driver.h>
#include <components/stm32main.h>
#include "components/masb_comm_s.h"
#include "components/adc.h"
#include "components/stm32main.h"
#include "components/chronoamperometry.h"
#include "components/cyclic_voltammetry.h"

extern I2C_HandleTypeDef hi2c1;

struct CV_Configuration_S cvConfiguration;
struct CA_Configuration_S caConfiguration;

struct Data_S data;


MCP4725_Handle_T hdac = NULL;


uint32_t Estado;

// Funcio setup que la crida el main.c
void setup(struct Handles_S *handles) {
     MASB_COMM_S_waitForMessage();

     I2C_init(&hi2c1);


     // pmu on
     Start_PMU();


     // Convertidor digital-analógico
     hdac = MCP4725_Init();
     MCP4725_ConfigSlaveAddress(hdac, 0x66); // DIRECCION DEL ESCLAVO
     MCP4725_ConfigVoltageReference(hdac, 4.0f); // TENSION DE REFERENCIA
     MCP4725_ConfigWriteFunction(hdac, I2C_write); // FUNCION DE ESCRITURA (libreria I2C_lib)


     // Potenciomatro digital


     AD5280_Handle_T hpot = NULL;

     hpot = AD5280_Init();

     // Configuramos su direccion I2C de esclavo, su resistencia total (hay
     // diferentes modelos; este tiene 50kohms) e indicamos que funcion queremos que
     // se encargue de la escritura a traves del I2C. Utilizaremos la funcion
     // I2C_Write de la libreria i2c_lib.
     AD5280_ConfigSlaveAddress(hpot, 0x2C);
     AD5280_ConfigNominalResistorValue(hpot, 50e3f);
     AD5280_ConfigWriteFunction(hpot, I2C_write);

     // Fijamos la resistencia de 50 kohms.
     AD5280_SetWBResistance(hpot, 50e3f);

     Estado = IDLE;
}

// Funcio loop que la crida el main.c
void loop(void) {
    if (MASB_COMM_S_dataReceived()) { // Si se ha recibido un mensaje...

 		switch(MASB_COMM_S_command()) { // Miramos que comando hemos recibido

 			case START_CV_MEAS: // Si hemos recibido START_CV_MEAS

                 // Leemos la configuracion que se nos ha enviado en el mensaje y
                 // la guardamos en la variable cvConfiguration
				cvConfiguration = MASB_COMM_S_getCvConfiguration();
				Estado = CV;
				__NOP();
 				break;

 			case START_CA_MEAS: // Si hemos recibido START_CV_MEAS

 				// Leemos la configuracion que se nos ha enviado en el mensaje y
 				// la guardamos en la variable cvConfiguration
 				caConfiguration = MASB_COMM_S_getCaConfiguration();
 				Estado = CA;
 				break;

			case STOP_MEAS: // Si hemos recibido STOP_MEAS
				Estado = IDLE;

 				__NOP(); // Esta instruccion no hace nada y solo sirve para poder anadir un breakpoint
 				break;

 			default: // En el caso que se envia un comando que no exista

 				break;

 		}

       // Una vez procesado los comando, esperamos el siguiente
 		MASB_COMM_S_waitForMessage();

 	}else{

		switch(Estado) { // Miramos que comando hemos recibido

					case CV:
						cyclic_voltammetry(cvConfiguration);
						Estado = IDLE;
						__NOP();
						break;
					case CA:
						chronoamperometry(caConfiguration);
						Estado = IDLE;
						__NOP();
						break;

					default:
						break;


				}
 	}


}
