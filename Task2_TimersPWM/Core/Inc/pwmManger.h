/*
 * pwmManger.h
 *
 *  Created on: Nov 9, 2021
 *      Author: tori
 */

#ifndef INC_PWMMANGER_H_
#define INC_PWMMANGER_H_

#define DUTY_CYCLE_STEP				5 		// percent from max duty cycle
#define FREQ_STEP					5000 	// 5kHz
#define CHNL_QUANTITY				4
#define CHANNEL_RESET_DUTY_CYCLE	0

#define HSE_CLK_FREQ				(8000000)						// 8MHz
#define TIM_IN_CLCK_FREQ			(HSE_CLK_FREQ/(TIM4->PSC + 1))

#define MAX_TIM_FREQ				(5 * FREQ_STEP)			// 25 KHz
#define MIN_TIM_FREQ				(FREQ_STEP)

#define TIM_PERIOD					(TIM4->ARR & 0xffff)	// tim4 ARR is 16 bit

#define MAX_DUTY_CYCLE_PERCENT		(100)
#define MIN_DUTY_CYCLE_PERCENT		(0)


typedef volatile long unsigned int PWMChannel;

void DecrementFrequency(void);
void IncrementFrequency(void);
void IncrementDutyCycle(void);
void DecrementDutyCycle(void);
void NextOutputChannel(void);

#endif /* INC_PWMMANGER_H_ */
