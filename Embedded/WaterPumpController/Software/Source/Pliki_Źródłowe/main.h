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
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32l4xx_hal.h"

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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define NEXT_Pin GPIO_PIN_1
#define NEXT_GPIO_Port GPIOA
#define NEXT_EXTI_IRQn EXTI1_IRQn
#define BEFORE_Pin GPIO_PIN_3
#define BEFORE_GPIO_Port GPIOA
#define BEFORE_EXTI_IRQn EXTI3_IRQn
#define INC_Pin GPIO_PIN_4
#define INC_GPIO_Port GPIOA
#define INC_EXTI_IRQn EXTI4_IRQn
#define DEC_Pin GPIO_PIN_5
#define DEC_GPIO_Port GPIOA
#define DEC_EXTI_IRQn EXTI9_5_IRQn
#define SEL_Pin GPIO_PIN_6
#define SEL_GPIO_Port GPIOA
#define SEL_EXTI_IRQn EXTI9_5_IRQn
#define DS18B20_Pin GPIO_PIN_0
#define DS18B20_GPIO_Port GPIOB
#define LED_Pin GPIO_PIN_3
#define LED_GPIO_Port GPIOB
#define RELAY_Pin GPIO_PIN_4
#define RELAY_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

#define DELAY_US_TIMER	htim1

void Delay_us(uint16_t us);
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
