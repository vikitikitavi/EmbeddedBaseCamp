/*
 * ledManager.h
 *
 *  Created on: Nov 2, 2021
 *      Author: tori
 */

#ifndef INC_LEDMANAGER_H_
#define INC_LEDMANAGER_H_

typedef enum {
	NEXT_SCHEME,
	PREVIOUS_SCHEME,

	SPEED_UP,
	SLOW_DOWN,

	ON_OFF,
	MAX_BUTTON
} CONTROL;

void RunLEDsSchema(void);
void LEDControl_Handler(CONTROL c);

#endif /* INC_LEDMANAGER_H_ */
