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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define OLED_RES_Pin GPIO_PIN_0
#define OLED_RES_GPIO_Port GPIOB
#define OLED_DC_Pin GPIO_PIN_1
#define OLED_DC_GPIO_Port GPIOB
#define OLED_NSS_Pin GPIO_PIN_10
#define OLED_NSS_GPIO_Port GPIOB
#define KB_C0_Pin GPIO_PIN_12
#define KB_C0_GPIO_Port GPIOB
#define KB_C1_Pin GPIO_PIN_13
#define KB_C1_GPIO_Port GPIOB
#define KB_C2_Pin GPIO_PIN_14
#define KB_C2_GPIO_Port GPIOB
#define KB_C3_Pin GPIO_PIN_15
#define KB_C3_GPIO_Port GPIOB
#define KB_R0_Pin GPIO_PIN_15
#define KB_R0_GPIO_Port GPIOA
#define KB_R1_Pin GPIO_PIN_3
#define KB_R1_GPIO_Port GPIOB
#define KB_R2_Pin GPIO_PIN_4
#define KB_R2_GPIO_Port GPIOB
#define KB_R3_Pin GPIO_PIN_5
#define KB_R3_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
//state表：
//  输入  1
//   +    2
//   -    3
//   x    4
//   /    5
//  输出  6
#define _input   1
#define _output    2
#define _plus     3
#define _sub   4
#define _multi     5
#define _div  6

//*************************************
//model
#define _int   1
#define _float 2



/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
