/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "trackball.h"
#include "keyboard.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim4;

/* USER CODE BEGIN PV */
extern USBD_HandleTypeDef hUsbDeviceFS;

uint8_t Col_Number = 0;
	//This variable stores the number of the scanned column of the current button being scanned. 
	
uint8_t Row_Number = 0;
	//This variable stores the number of the scanned row	 of the current button being scanned.
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM4_Init(void);
/* USER CODE BEGIN PFP */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
		Send_Keyboard_USB_Data();
		//without sending this zero packet, there is some kind of garbage on the bus at the beginning 
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USB_DEVICE_Init();
  MX_TIM2_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_Encoder_Start_IT(&htim4, TIM_CHANNEL_1);
	HAL_TIM_Encoder_Start_IT(&htim2, TIM_CHANNEL_1);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
	/*****************************************************/	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1){	
	Clearing_Flags();
	//Checking wich buttons was pressed in previous	iteration 
	Col_1_ON;
		Col_Number = 1;
			Row_Number = 1;
				if (Row_1_Read){//START BUTTON OLD
					Polling_Old_Modifier_Buttons();
				}
			Row_Number = 2;
				if (Row_2_Read){//A BUTTON OLD
					Polling_Old_Usual_Buttons();
				}
			Row_Number = 3;
				if (Row_3_Read){//B BUTTON OLD
					Polling_Old_Usual_Buttons();
				}
			Row_Number = 4;
				if (Row_4_Read){//* BUTTON OLD
					Polling_Old_Usual_Buttons();
				}
	Col_1_OFF;
/////////////////////////////////////////////////////////////////////////////
	Col_2_ON;
		Col_Number = 2;
			Row_Number = 1;
				if (Row_1_Read){//6 BUTTON OLD
					Polling_Old_Usual_Buttons();
				}
			Row_Number = 2;
				if (Row_2_Read){//1 BUTTON OLD
					Polling_Old_Modifier_Buttons();
				}
			Row_Number = 3;
				if (Row_3_Read){//2 BUTTON OLD
					Polling_Old_Usual_Buttons();
				}
			Row_Number = 4;
				if (Row_4_Read){//7 BUTTON OLD
					Polling_Old_Usual_Buttons();
				}
	Col_2_OFF;
/////////////////////////////////////////////////////////////////////////////
	Col_3_ON;
		Col_Number = 3;
			Row_Number = 1;
				if (Row_1_Read){//8 BUTTON OLD
					Polling_Old_Usual_Buttons();
				}
			Row_Number = 2;
				if (Row_2_Read){//3 BUTTON OLD
					Polling_Old_Usual_Buttons();
				}
			Row_Number = 3;
				if (Row_3_Read){//4 BUTTON OLD
					Polling_Old_Modifier_Buttons();
				}
			Row_Number = 4;
				if (Row_4_Read){//9 BUTTON OLD
					Polling_Old_Usual_Buttons();
				}
	Col_3_OFF;
/////////////////////////////////////////////////////////////////////////////
	Col_4_ON;
		Col_Number = 4;
			Row_Number = 1;
				if (Row_1_Read){//0 BUTTON OLD
					Polling_Old_Usual_Buttons();
				}
			Row_Number = 2;
				if (Row_2_Read){//5 BUTTON OLD
					Polling_Old_Usual_Buttons();
				}
			Row_Number = 3;
				if (Row_3_Read){//C BUTTON OLD
					Polling_Old_Usual_Buttons();
				}
				Row_Number = 4;
				if (Row_4_Read){//ENTER BUTTON OLD
					Polling_Old_Modifier_Buttons();
				}
	Col_4_OFF;
	//HAL_Delay(1);
/////////////////////////////////////////////////////////////////////////
/**********************************************************************************/
//Polling buttons wich pressed in this iteration and was not pressed in previous iteration
	Col_1_ON;
			Col_Number = 1;
			Row_Number = 1;
				if (Row_1_Read){//START BUTTON NEW 
					Polling_New_Modifier_Buttons();
				}
			Row_Number = 2;
				if (Row_2_Read){//A BUTTON NEW
					Polling_New_Usual_Buttons();
				}
			Row_Number = 3;
				if (Row_3_Read){//B BUTTON NEW
					Polling_New_Usual_Buttons();
				}
			Row_Number =4;
				if (Row_4_Read){//* BUTTON NEW
					Polling_New_Usual_Buttons();
				}
		/////////////////////////////////////////////////////////////
		Col_1_OFF;
		Col_2_ON;
			Col_Number = 2; 
			Row_Number = 1;
				if (Row_1_Read){//6 BUTTON NEW
					Polling_New_Usual_Buttons();
				}
			Row_Number = 2;
				if (Row_2_Read){//1 BUTTON NEW
					Polling_New_Modifier_Buttons();
				}
			Row_Number = 3;
				if (Row_3_Read){//2 BUTTON NEW		
					Polling_New_Usual_Buttons();
				}
			Row_Number = 4;
				if (Row_4_Read){//7 BUTTON NEW
					Polling_New_Usual_Buttons();
				}
		Col_2_OFF;
		///////////////////////////////////////////////
		Col_3_ON;
			Col_Number = 3;
			Row_Number = 1;
				if (Row_1_Read){//8 BUTTON NEW
					Polling_New_Usual_Buttons();
				}
			Row_Number = 2;
				if (Row_2_Read){//3 BUTTON NEW
					Polling_New_Usual_Buttons();
				}
			Row_Number = 3;
				if (Row_3_Read){//4 BUTTON NEW
					Polling_New_Modifier_Buttons();
			}	
				HAL_Delay(1);
			Row_Number = 4;
				if (Row_4_Read){//9 BUTTON NEW
					Polling_New_Usual_Buttons();
				}
		Col_3_OFF;
		/////////////////////////////////////////////////////
		Col_4_ON;
			Col_Number = 4;
			Row_Number = 1;
				if (Row_1_Read){//0 BUTTON NEW
					Polling_New_Usual_Buttons();
				}
			Row_Number = 2;
				if (Row_2_Read){//5 BUTTON NEW
					Polling_New_Usual_Buttons();
				}
			Row_Number = 3;
				if (Row_3_Read){//C BUTTON NEW 
					Polling_New_Usual_Buttons();
				}
			Row_Number = 4;
				if (Row_4_Read){//ENTER BUTTON NEW
					Polling_New_Modifier_Buttons();
				}
			Col_4_OFF;
////////////////////////////////////////////////////////////////////////
		Keyboard_Send_Data_Handle();
		Get_Mouse_Direction();
		if (!Read_Left_Mouse_Buton){
			Set_Click(1);
			Led_ON;
		}
		else {
			Set_Click(0);
			Led_OFF;
		}
		Send_Mouse_USB_Data();
				/***************************************************/
		
		
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */
	
  /* USER CODE END TIM2_Init 0 */

  TIM_Encoder_InitTypeDef sConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 255;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  sConfig.EncoderMode = TIM_ENCODERMODE_TI1;
  sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC1Filter = 15;
  sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC2Filter = 15;
  if (HAL_TIM_Encoder_Init(&htim2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_Encoder_InitTypeDef sConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 0;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 255;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  sConfig.EncoderMode = TIM_ENCODERMODE_TI1;
  sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC1Filter = 15;
  sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC2Filter = 15;
  if (HAL_TIM_Encoder_Init(&htim4, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, COL3_PIN7_Pin|COL4_PIN8_Pin|Nucleo_Led_Pin|COL2_PIN6_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(COL1_PIN4_GPIO_Port, COL1_PIN4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : Nucleo_Button_Pin */
  GPIO_InitStruct.Pin = Nucleo_Button_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Nucleo_Button_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : COL3_PIN7_Pin COL4_PIN8_Pin Nucleo_Led_Pin COL2_PIN6_Pin */
  GPIO_InitStruct.Pin = COL3_PIN7_Pin|COL4_PIN8_Pin|Nucleo_Led_Pin|COL2_PIN6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : ROW2_PIN2_Pin ROW4_PIN5_Pin ROW3_PIN3_Pin */
  GPIO_InitStruct.Pin = ROW2_PIN2_Pin|ROW4_PIN5_Pin|ROW3_PIN3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : ROW1_PIN1_Pin */
  GPIO_InitStruct.Pin = ROW1_PIN1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(ROW1_PIN1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : COL1_PIN4_Pin */
  GPIO_InitStruct.Pin = COL1_PIN4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(COL1_PIN4_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
