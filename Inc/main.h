/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define KEY_Pin GPIO_PIN_13
#define KEY_GPIO_Port GPIOC
#define SPI5_NSS_Pin GPIO_PIN_6
#define SPI5_NSS_GPIO_Port GPIOF
#define KEY1_Pin GPIO_PIN_0
#define KEY1_GPIO_Port GPIOA
#define I2C_SCL_Pin GPIO_PIN_4
#define I2C_SCL_GPIO_Port GPIOH
#define I2C_SDA_Pin GPIO_PIN_5
#define I2C_SDA_GPIO_Port GPIOH
#define LED_R_Pin GPIO_PIN_10
#define LED_R_GPIO_Port GPIOH
#define LED_G_Pin GPIO_PIN_11
#define LED_G_GPIO_Port GPIOH
#define LED_B_Pin GPIO_PIN_12
#define LED_B_GPIO_Port GPIOH
#define CTP_RSTN_Pin GPIO_PIN_12
#define CTP_RSTN_GPIO_Port GPIOD
#define CTP_INT_Pin GPIO_PIN_13
#define CTP_INT_GPIO_Port GPIOD
#define DISP_Pin GPIO_PIN_4
#define DISP_GPIO_Port GPIOD
#define LCD_BL_Pin GPIO_PIN_7
#define LCD_BL_GPIO_Port GPIOD
#define WIFI_DISABLE_Pin GPIO_PIN_9
#define WIFI_DISABLE_GPIO_Port GPIOG
void   MX_SPI5_Init(void);
/* USER CODE BEGIN Private defines */
#define UBP_KEY  1
#define UBP_LIGHT_OFF 2
#define UBP_LIGHT_ON  3
#define UBP_REFRESH  4
#define UBP_START  5
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
