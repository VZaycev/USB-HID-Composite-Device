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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim2;
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
#define Nucleo_Button_Pin GPIO_PIN_13
#define Nucleo_Button_GPIO_Port GPIOC
#define COL3_PIN7_Pin GPIO_PIN_2
#define COL3_PIN7_GPIO_Port GPIOA
#define COL4_PIN8_Pin GPIO_PIN_3
#define COL4_PIN8_GPIO_Port GPIOA
#define Nucleo_Led_Pin GPIO_PIN_5
#define Nucleo_Led_GPIO_Port GPIOA
#define ROW2_PIN2_Pin GPIO_PIN_10
#define ROW2_PIN2_GPIO_Port GPIOB
#define ROW1_PIN1_Pin GPIO_PIN_8
#define ROW1_PIN1_GPIO_Port GPIOA
#define COL2_PIN6_Pin GPIO_PIN_10
#define COL2_PIN6_GPIO_Port GPIOA
#define ROW4_PIN5_Pin GPIO_PIN_3
#define ROW4_PIN5_GPIO_Port GPIOB
#define ROW3_PIN3_Pin GPIO_PIN_4
#define ROW3_PIN3_GPIO_Port GPIOB
#define COL1_PIN4_Pin GPIO_PIN_5
#define COL1_PIN4_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
//Rows
#define Row_1_Read HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) 
#define Row_2_Read HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10)
#define Row_3_Read HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4)
#define Row_4_Read HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3)
//Columns
#define Col_1_ON HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET)
#define Col_1_OFF HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET)
#define Col_2_ON HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET)
#define Col_2_OFF HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET)
#define Col_3_ON HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET)
#define Col_3_OFF HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET)
#define Col_4_ON HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET)
#define Col_4_OFF HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET)
//Led
#define Led_ON HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET)
#define Led_OFF HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET)
//Mouse
#define Read_Left_Mouse_Buton HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
