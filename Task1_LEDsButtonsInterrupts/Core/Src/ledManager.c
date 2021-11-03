/*
 * ledManager.c
 *
 *  Created on: Nov 2, 2021
 *      Author: tori
 */

#include "main.h"
#include "ledManager.h"


#define LED_SCHEMAS_INDEX_MAX				2
#define LED_TRANSITION_STATE_DELAY_MIN		200
#define LED_TRANSITION_STATE_DELAY_MAX		2000
#define LED_TRANSITION_STATE_SPEED_DELTA	300

typedef void (*LED_SCHEMA)(void);
enum {FALSE, TRUE};

static uint32_t 	g_LED_speed				= 	LED_TRANSITION_STATE_DELAY_MIN;
static uint32_t		g_current_schema_index 	= 	0;
static uint32_t 	g_schema_changed 		= 	FALSE;
static uint32_t 	g_on 					= 	TRUE;

static void PairedBlinkMux(void);
static void AllOnOff(void);
static void SequantialToggling(void);
static void ResetAll(void);

static void IncrementSchemaIndex(void);
static void DecrementSchemaIndex(void);
static void SpeedUp(void);
static void SlowDown(void);

static const LED_SCHEMA g_schemas[] = {
		SequantialToggling,
		AllOnOff,
		PairedBlinkMux
};

static void PairedBlinkMux(void)
{
	HAL_GPIO_WritePin(GPIOD, Orange_LED_Pin|Blue_LED_Pin, RESET);
	HAL_GPIO_WritePin(GPIOD, Green_LED_Pin|Red_LED_Pin, SET);
	HAL_Delay(g_LED_speed);

	HAL_GPIO_WritePin(GPIOD, Green_LED_Pin|Red_LED_Pin, RESET);
	HAL_GPIO_WritePin(GPIOD, Orange_LED_Pin|Blue_LED_Pin, SET);
	HAL_Delay(g_LED_speed);

}

static void AllOnOff(void)
{
	HAL_GPIO_WritePin(GPIOD, Green_LED_Pin|Orange_LED_Pin|Blue_LED_Pin|Red_LED_Pin, SET);
	HAL_Delay(g_LED_speed);

	ResetAll();
	HAL_Delay(g_LED_speed);
}

static void SequantialToggling(void)
{
	HAL_GPIO_TogglePin(GPIOD, Green_LED_Pin);
	HAL_Delay(g_LED_speed);

	HAL_GPIO_TogglePin(GPIOD, Orange_LED_Pin);
	HAL_Delay(g_LED_speed);

	HAL_GPIO_TogglePin(GPIOD, Red_LED_Pin);
	HAL_Delay(g_LED_speed);

	HAL_GPIO_TogglePin(GPIOD, Blue_LED_Pin);
	HAL_Delay(g_LED_speed);
}

static void ResetAll(void)
{
	HAL_GPIO_WritePin(GPIOD, Green_LED_Pin|Orange_LED_Pin|Blue_LED_Pin|Red_LED_Pin, RESET);
}

static void IncrementSchemaIndex(void)
{
	if (g_current_schema_index != LED_SCHEMAS_INDEX_MAX)
	{
		g_current_schema_index++;
	}
	else
	{
		g_current_schema_index = 0;
	}
	g_schema_changed = TRUE;
}

static void DecrementSchemaIndex(void)
{
	if (g_current_schema_index != 0)
	{
		g_current_schema_index--;
	}
	else
	{
		g_current_schema_index = LED_SCHEMAS_INDEX_MAX;
	}
	g_schema_changed = TRUE;
}

static void SpeedUp(void) {
	if (g_LED_speed
			<= (LED_TRANSITION_STATE_DELAY_MAX - LED_TRANSITION_STATE_SPEED_DELTA))
	{
		g_LED_speed += LED_TRANSITION_STATE_SPEED_DELTA;
	}
}

static void SlowDown(void) {
	if (g_LED_speed
			>= (LED_TRANSITION_STATE_DELAY_MIN + LED_TRANSITION_STATE_SPEED_DELTA))
	{
		g_LED_speed -= LED_TRANSITION_STATE_SPEED_DELTA;
	}
}

void LEDControl_Handler(CONTROL cntrl)
{
	switch (cntrl)
	{
		case ON_OFF:
			g_on = !g_on;
			break;
		case NEXT_SCHEME:
			if (g_on && !g_schema_changed)
				IncrementSchemaIndex();
			break;
		case PREVIOUS_SCHEME:
			if (g_on && !g_schema_changed)
				DecrementSchemaIndex();
			break;
		case SPEED_UP:
			if (g_on)
				SpeedUp();
			break;
		case SLOW_DOWN:
			if (g_on)
				SlowDown();
			break;
		default:
			break;
	}
}

void RunLEDsSchema(void)
{
	LED_SCHEMA run_schema;

	if (g_on)
	{
		if (g_schema_changed)
		{
			ResetAll();
			g_schema_changed = FALSE;
		}
		run_schema = g_schemas[g_current_schema_index];
	}
	else
	{
		run_schema = ResetAll;
	}

	run_schema();
}
