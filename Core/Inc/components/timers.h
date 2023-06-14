/*
 * timers.h
 *
 *  Created on: 23 may. 2023
 *      Author: Marc
 */

#ifndef INC_COMPONENTS_TIMERS_H_
#define INC_COMPONENTS_TIMERS_H_
#include <stdbool.h>

void Start_Timer(uint32_t period);
void Stop_Timer(void);
void ClearTimeout(void);
bool TimeoutEllapsed(void);

#endif /* INC_COMPONENTS_TIMERS_H_ */
