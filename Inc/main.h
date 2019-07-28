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
#define MCU_SPI2_RESET_MCP23S17_Pin GPIO_PIN_2
#define MCU_SPI2_RESET_MCP23S17_GPIO_Port GPIOE
#define MCU_SPI2_CS_DIDO_MCP23S17_Pin GPIO_PIN_3
#define MCU_SPI2_CS_DIDO_MCP23S17_GPIO_Port GPIOE
#define MCU_HIOC2_EN_POINT_LED_Pin GPIO_PIN_13
#define MCU_HIOC2_EN_POINT_LED_GPIO_Port GPIOC
#define MCU_SPI2_RESET_MCP23S17C14_Pin GPIO_PIN_14
#define MCU_SPI2_RESET_MCP23S17C14_GPIO_Port GPIOC
#define MCU_SPI2_CS_AIHIO_MCP23S17_Pin GPIO_PIN_15
#define MCU_SPI2_CS_AIHIO_MCP23S17_GPIO_Port GPIOC
#define HIO_SPI5_CS_ADC_Pin GPIO_PIN_6
#define HIO_SPI5_CS_ADC_GPIO_Port GPIOF
#define HIO_SPI5_SCK_CONVERTER_Pin GPIO_PIN_7
#define HIO_SPI5_SCK_CONVERTER_GPIO_Port GPIOF
#define HIO_SPI5_SOMI_CONVERTER_Pin GPIO_PIN_8
#define HIO_SPI5_SOMI_CONVERTER_GPIO_Port GPIOF
#define HIO_SPI5_SIMO_CONVERTER_Pin GPIO_PIN_9
#define HIO_SPI5_SIMO_CONVERTER_GPIO_Port GPIOF
#define MCU_DOP_EN_POINT_LED_Pin GPIO_PIN_0
#define MCU_DOP_EN_POINT_LED_GPIO_Port GPIOC
#define MCU_DIC1_EN_POINT_LED_Pin GPIO_PIN_4
#define MCU_DIC1_EN_POINT_LED_GPIO_Port GPIOA
#define MCU_DIC2_EN_POINT_LED_Pin GPIO_PIN_5
#define MCU_DIC2_EN_POINT_LED_GPIO_Port GPIOA
#define MCU_DOC1_EN_POINT_LED_Pin GPIO_PIN_0
#define MCU_DOC1_EN_POINT_LED_GPIO_Port GPIOB
#define MCU_DOC2_EN_POINT_LED_Pin GPIO_PIN_1
#define MCU_DOC2_EN_POINT_LED_GPIO_Port GPIOB
#define MCU_TB_EN_POINT_LED_Pin GPIO_PIN_11
#define MCU_TB_EN_POINT_LED_GPIO_Port GPIOF
#define MCU_1_POINT_LED_D_Pin GPIO_PIN_14
#define MCU_1_POINT_LED_D_GPIO_Port GPIOF
#define MCU_1_POINT_LED_A0_Pin GPIO_PIN_15
#define MCU_1_POINT_LED_A0_GPIO_Port GPIOF
#define MCU_1_POINT_LED_A1_Pin GPIO_PIN_0
#define MCU_1_POINT_LED_A1_GPIO_Port GPIOG
#define MCU_1_POINT_LED_A2_Pin GPIO_PIN_1
#define MCU_1_POINT_LED_A2_GPIO_Port GPIOG
#define MCU_AIC_EN_POINT_LED_Pin GPIO_PIN_7
#define MCU_AIC_EN_POINT_LED_GPIO_Port GPIOE
#define MCU_HIOC1_EN_POINT_LED_Pin GPIO_PIN_8
#define MCU_HIOC1_EN_POINT_LED_GPIO_Port GPIOE
#define MCU_HIOC2_EN_POINT_LEDE9_Pin GPIO_PIN_9
#define MCU_HIOC2_EN_POINT_LEDE9_GPIO_Port GPIOE
#define MCU_1_SPI4_DIGCS_ADC_Pin GPIO_PIN_10
#define MCU_1_SPI4_DIGCS_ADC_GPIO_Port GPIOE
#define MCU_1_SPI4_CS_ADC_Pin GPIO_PIN_11
#define MCU_1_SPI4_CS_ADC_GPIO_Port GPIOE
#define MCU_1_SPI4_SCK_ADC_Pin GPIO_PIN_12
#define MCU_1_SPI4_SCK_ADC_GPIO_Port GPIOE
#define MCU_1_SPI4_SOMI_ADC_Pin GPIO_PIN_13
#define MCU_1_SPI4_SOMI_ADC_GPIO_Port GPIOE
#define MCU_1_SPI4_SIMO_ADC_Pin GPIO_PIN_14
#define MCU_1_SPI4_SIMO_ADC_GPIO_Port GPIOE
#define MCU_DOC2_EN_POINT_LEDB10_Pin GPIO_PIN_10
#define MCU_DOC2_EN_POINT_LEDB10_GPIO_Port GPIOB
#define MCU_SPI2_CS_AIHIO_MCP23S17B12_Pin GPIO_PIN_12
#define MCU_SPI2_CS_AIHIO_MCP23S17B12_GPIO_Port GPIOB
#define MCU_SPI2_SCK_MCP23S17_Pin GPIO_PIN_13
#define MCU_SPI2_SCK_MCP23S17_GPIO_Port GPIOB
#define MCU_SPI2_SO_MCP23S17_Pin GPIO_PIN_14
#define MCU_SPI2_SO_MCP23S17_GPIO_Port GPIOB
#define MCU_SPI2_SI_MCP23S17_Pin GPIO_PIN_15
#define MCU_SPI2_SI_MCP23S17_GPIO_Port GPIOB
#define MCU_MODE_SWITCH_Pin GPIO_PIN_8
#define MCU_MODE_SWITCH_GPIO_Port GPIOD
#define MCU_TEST_START_Pin GPIO_PIN_9
#define MCU_TEST_START_GPIO_Port GPIOD
#define MCU_MAIN_DITEST_Pin GPIO_PIN_11
#define MCU_MAIN_DITEST_GPIO_Port GPIOD
#define MCU_MAIN_DOTEST_Pin GPIO_PIN_12
#define MCU_MAIN_DOTEST_GPIO_Port GPIOD
#define MCU_MAIN_AITEST_Pin GPIO_PIN_13
#define MCU_MAIN_AITEST_GPIO_Port GPIOD
#define MCU_MAIN_HIOTEST_Pin GPIO_PIN_14
#define MCU_MAIN_HIOTEST_GPIO_Port GPIOD
#define MCU_AIP_EN_POINT_LED_Pin GPIO_PIN_6
#define MCU_AIP_EN_POINT_LED_GPIO_Port GPIOC
#define MCU_AIC_EN_POINT_LEDC7_Pin GPIO_PIN_7
#define MCU_AIC_EN_POINT_LEDC7_GPIO_Port GPIOC
#define MCU_HIOP_EN_POINT_LED_Pin GPIO_PIN_8
#define MCU_HIOP_EN_POINT_LED_GPIO_Port GPIOC
#define MCU_HIOC1_EN_POINT_LEDC9_Pin GPIO_PIN_9
#define MCU_HIOC1_EN_POINT_LEDC9_GPIO_Port GPIOC
#define MCU_DIP_EN_POINT_LED_Pin GPIO_PIN_8
#define MCU_DIP_EN_POINT_LED_GPIO_Port GPIOA
#define MCU_1_POINT_LED_DA9_Pin GPIO_PIN_9
#define MCU_1_POINT_LED_DA9_GPIO_Port GPIOA
#define MCU_1_POINT_LED_A0A10_Pin GPIO_PIN_10
#define MCU_1_POINT_LED_A0A10_GPIO_Port GPIOA
#define MCU_1_POINT_LED_A1A11_Pin GPIO_PIN_11
#define MCU_1_POINT_LED_A1A11_GPIO_Port GPIOA
#define MCU_1_POINT_LED_A2A12_Pin GPIO_PIN_12
#define MCU_1_POINT_LED_A2A12_GPIO_Port GPIOA
#define SPI3_DAC_AICS_Pin GPIO_PIN_15
#define SPI3_DAC_AICS_GPIO_Port GPIOA
#define SPI3_DAC_SCK_Pin GPIO_PIN_10
#define SPI3_DAC_SCK_GPIO_Port GPIOC
#define SPI3_DAC_SOMI_Pin GPIO_PIN_11
#define SPI3_DAC_SOMI_GPIO_Port GPIOC
#define SPI3_DAC_HIOCS_Pin GPIO_PIN_0
#define SPI3_DAC_HIOCS_GPIO_Port GPIOD
#define SPI3_DAC_RESET_Pin GPIO_PIN_1
#define SPI3_DAC_RESET_GPIO_Port GPIOD
#define MCU_MAIN_EN_POINT_LED_Pin GPIO_PIN_3
#define MCU_MAIN_EN_POINT_LED_GPIO_Port GPIOD
#define SPI3_DAC_SIMO_Pin GPIO_PIN_5
#define SPI3_DAC_SIMO_GPIO_Port GPIOB
#define MCU_DIC1_EN_POINT_LEDB6_Pin GPIO_PIN_6
#define MCU_DIC1_EN_POINT_LEDB6_GPIO_Port GPIOB
#define MCU_DIC2_EN_POINT_LEDB7_Pin GPIO_PIN_7
#define MCU_DIC2_EN_POINT_LEDB7_GPIO_Port GPIOB
#define MCU_DOC1_EN_POINT_LEDB9_Pin GPIO_PIN_9
#define MCU_DOC1_EN_POINT_LEDB9_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
