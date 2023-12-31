/*
 * cyclic_voltammetry.h
 *
 *  Created on: 8 de juny 2023
 *      Author: plade
 */

#include <stdint.h>
#ifndef INC_COMPONENTS_CYCLIC_VOLTAMMETRY_H_
#define INC_COMPONENTS_CYCLIC_VOLTAMMETRY_H_

struct CV_Configuration_S {
	double eBegin;
	double eVertex1;
	double eVertex2;
	uint8_t cycles;
	double scanRate;
	double eStep;
};

void cyclic_voltammetry(struct CV_Configuration_S cvConfiguration);

#endif /* INC_COMPONENTS_CYCLIC_VOLTAMMETRY_H_ */
