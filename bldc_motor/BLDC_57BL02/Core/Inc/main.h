/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32h7xx_hal.h"

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
#define SPI4_CS_Pin GPIO_PIN_3
#define SPI4_CS_GPIO_Port GPIOE
#define DRV_01_Pin GPIO_PIN_1
#define DRV_01_GPIO_Port GPIOC
#define ENCODER_A_Pin GPIO_PIN_0
#define ENCODER_A_GPIO_Port GPIOA
#define ENCODER_B_Pin GPIO_PIN_1
#define ENCODER_B_GPIO_Port GPIOA
#define ENCODER_I_Pin GPIO_PIN_2
#define ENCODER_I_GPIO_Port GPIOA
#define DRV_02_Pin GPIO_PIN_3
#define DRV_02_GPIO_Port GPIOA
#define DRV_03_Pin GPIO_PIN_7
#define DRV_03_GPIO_Port GPIOA
#define SO1_Pin GPIO_PIN_5
#define SO1_GPIO_Port GPIOC
#define SO2_Pin GPIO_PIN_0
#define SO2_GPIO_Port GPIOB
#define DRV_EN_GATE_Pin GPIO_PIN_14
#define DRV_EN_GATE_GPIO_Port GPIOE
#define DRV_DC_CAL_Pin GPIO_PIN_15
#define DRV_DC_CAL_GPIO_Port GPIOE
#define DRV_OC_ADJ_Pin GPIO_PIN_10
#define DRV_OC_ADJ_GPIO_Port GPIOB
#define DRV_GAIN_Pin GPIO_PIN_11
#define DRV_GAIN_GPIO_Port GPIOB
#define DRV_M_OC_Pin GPIO_PIN_12
#define DRV_M_OC_GPIO_Port GPIOB
#define DRV_M_PWM_Pin GPIO_PIN_13
#define DRV_M_PWM_GPIO_Port GPIOB
#define DRV_nFAULT_Pin GPIO_PIN_14
#define DRV_nFAULT_GPIO_Port GPIOB
#define DRV_nOCTW_Pin GPIO_PIN_15
#define DRV_nOCTW_GPIO_Port GPIOB
#define HALL_A_Pin GPIO_PIN_6
#define HALL_A_GPIO_Port GPIOC
#define HALL_B_Pin GPIO_PIN_7
#define HALL_B_GPIO_Port GPIOC
#define HALL_C_Pin GPIO_PIN_8
#define HALL_C_GPIO_Port GPIOC
#define W5500_RST_Pin GPIO_PIN_8
#define W5500_RST_GPIO_Port GPIOA
#define W5500_INT_Pin GPIO_PIN_15
#define W5500_INT_GPIO_Port GPIOA
#define SPI3_CS_Pin GPIO_PIN_0
#define SPI3_CS_GPIO_Port GPIOD
#define SPI1_CS_Pin GPIO_PIN_5
#define SPI1_CS_GPIO_Port GPIOB
#define DRV_PWRGD_Pin GPIO_PIN_0
#define DRV_PWRGD_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
