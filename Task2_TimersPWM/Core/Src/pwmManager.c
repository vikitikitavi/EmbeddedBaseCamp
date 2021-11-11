/*
 * pwmManager.c
 *
 *  Created on: Nov 9, 2021
 *      Author: tori
 */

#include "main.h"
#include "pwmManger.h"


PWMChannel * chnls[CHNL_QUANTITY] = {
		&(TIM4->CCR1),		// Green LED 	PD12
		&(TIM4->CCR2),		// Orange LED 	PD13
		&(TIM4->CCR3),		// Red LED		PD14
		&(TIM4->CCR4)		// Blue LED		PD15
};


PWMChannel **g_current_chnl = NULL;
uint32_t g_duty_percent	= 50;

static void setDutyCycle(PWMChannel *chnl, uint32_t percent);

static void setDutyCycle(PWMChannel *chnl, uint32_t percent)
{
	*chnl = (PWMChannel) (((uint32_t) TIM_PERIOD) * percent / 100 );
}

void DecrementFrequency(void)
{
	uint16_t period;

	if (g_current_chnl == NULL)
		return ;

	period  = TIM_PERIOD;
	// overflow check
	if (TIM_IN_CLCK_FREQ / period > MIN_TIM_FREQ + FREQ_STEP )
		period = (TIM_IN_CLCK_FREQ * period) /
			(TIM_IN_CLCK_FREQ - FREQ_STEP * period);
	else
		period = TIM_IN_CLCK_FREQ / MIN_TIM_FREQ;

	TIM4->ARR = period;

	// update duty value according to new timer period
	setDutyCycle(*g_current_chnl, g_duty_percent);
}

void IncrementFrequency(void)
{
	uint16_t period;

	if (g_current_chnl == NULL)
		return ;

	period  = TIM_PERIOD;
	// underflow check
	if (TIM_IN_CLCK_FREQ / period < MAX_TIM_FREQ - FREQ_STEP )
		period = (TIM_IN_CLCK_FREQ * period) /
			(TIM_IN_CLCK_FREQ + FREQ_STEP * period);
	else
		period = TIM_IN_CLCK_FREQ / MAX_TIM_FREQ;

	TIM4->ARR = period;

	// update duty value according to new timer period
	setDutyCycle(*g_current_chnl, g_duty_percent);
}

void IncrementDutyCycle(void)
{
	if (g_current_chnl == NULL)
		return ;

	if (g_duty_percent < MAX_DUTY_CYCLE_PERCENT - DUTY_CYCLE_STEP)
		g_duty_percent += DUTY_CYCLE_STEP;
	else
		g_duty_percent = MAX_DUTY_CYCLE_PERCENT;

	setDutyCycle(*g_current_chnl, g_duty_percent);
}

void DecrementDutyCycle(void)
{
	if (g_current_chnl == NULL)
		return ;

	if (g_duty_percent > MIN_DUTY_CYCLE_PERCENT + DUTY_CYCLE_STEP)
		g_duty_percent -= DUTY_CYCLE_STEP;
	else
		g_duty_percent = MIN_DUTY_CYCLE_PERCENT;

	setDutyCycle(*g_current_chnl, g_duty_percent);
}

void NextOutputChannel(void)
{

	if (g_current_chnl == NULL)
	{
		g_current_chnl = &chnls[0];
		setDutyCycle(*g_current_chnl, g_duty_percent);
	}
	else if (g_current_chnl == &chnls[CHNL_QUANTITY - 1]) 	// last channel in a cycle
	{
		setDutyCycle(*g_current_chnl, CHANNEL_RESET_DUTY_CYCLE);
		g_current_chnl = NULL;
	}
	else
	{
		setDutyCycle(*g_current_chnl, CHANNEL_RESET_DUTY_CYCLE);
		g_current_chnl++;
		setDutyCycle(*g_current_chnl, g_duty_percent);
	}
}
