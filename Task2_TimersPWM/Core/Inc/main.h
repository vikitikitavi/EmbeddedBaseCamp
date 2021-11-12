/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Green_LED_Pin GPIO_PIN_12
#define Green_LED_GPIO_Port GPIOD
#define Orange_LED_Pin GPIO_PIN_13
#define Orange_LED_GPIO_Port GPIOD
#define Red_LED_Pin GPIO_PIN_14
#define Red_LED_GPIO_Port GPIOD
#define Blue_LED_Pin GPIO_PIN_15
#define Blue_LED_GPIO_Port GPIOD
#define SWT4_Pin GPIO_PIN_6
#define SWT4_GPIO_Port GPIOC
#define SWT4_EXTI_IRQn EXTI9_5_IRQn
#define SWT5_Pin GPIO_PIN_8
#define SWT5_GPIO_Port GPIOC
#define SWT5_EXTI_IRQn EXTI9_5_IRQn
#define SWT3_Pin GPIO_PIN_9
#define SWT3_GPIO_Port GPIOC
#define SWT3_EXTI_IRQn EXTI9_5_IRQn
#define SWT2_Pin GPIO_PIN_15
#define SWT2_GPIO_Port GPIOA
#define SWT2_EXTI_IRQn EXTI15_10_IRQn
#define SWT1_Pin GPIO_PIN_11
#define SWT1_GPIO_Port GPIOC
#define SWT1_EXTI_IRQn EXTI15_10_IRQn
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
