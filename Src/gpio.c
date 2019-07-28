/**
  ******************************************************************************
  * File Name          : gpio.c
  * Description        : This file provides code for the configuration
  *                      of all used GPIO pins.
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

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, MCU_SPI2_RESET_MCP23S17_Pin|MCU_SPI2_CS_DIDO_MCP23S17_Pin|MCU_AIC_EN_POINT_LED_Pin|MCU_HIOC1_EN_POINT_LED_Pin 
                          |MCU_HIOC2_EN_POINT_LEDE9_Pin|MCU_1_SPI4_DIGCS_ADC_Pin|MCU_1_SPI4_CS_ADC_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, MCU_HIOC2_EN_POINT_LED_Pin|MCU_SPI2_RESET_MCP23S17C14_Pin|MCU_SPI2_CS_AIHIO_MCP23S17_Pin|MCU_DOP_EN_POINT_LED_Pin 
                          |MCU_AIP_EN_POINT_LED_Pin|MCU_AIC_EN_POINT_LEDC7_Pin|MCU_HIOP_EN_POINT_LED_Pin|MCU_HIOC1_EN_POINT_LEDC9_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, HIO_SPI5_CS_ADC_Pin|MCU_TB_EN_POINT_LED_Pin|MCU_1_POINT_LED_D_Pin|MCU_1_POINT_LED_A0_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, MCU_DIC1_EN_POINT_LED_Pin|MCU_DIC2_EN_POINT_LED_Pin|MCU_DIP_EN_POINT_LED_Pin|MCU_1_POINT_LED_DA9_Pin 
                          |MCU_1_POINT_LED_A0A10_Pin|MCU_1_POINT_LED_A1A11_Pin|MCU_1_POINT_LED_A2A12_Pin|SPI3_DAC_AICS_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, MCU_DOC1_EN_POINT_LED_Pin|MCU_DOC2_EN_POINT_LED_Pin|MCU_DOC2_EN_POINT_LEDB10_Pin|MCU_SPI2_CS_AIHIO_MCP23S17B12_Pin 
                          |MCU_DIC1_EN_POINT_LEDB6_Pin|MCU_DIC2_EN_POINT_LEDB7_Pin|MCU_DOC1_EN_POINT_LEDB9_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, MCU_1_POINT_LED_A1_Pin|MCU_1_POINT_LED_A2_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, SPI3_DAC_HIOCS_Pin|SPI3_DAC_RESET_Pin|MCU_MAIN_EN_POINT_LED_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : PEPin PEPin PEPin PEPin 
                           PEPin PEPin PEPin */
  GPIO_InitStruct.Pin = MCU_SPI2_RESET_MCP23S17_Pin|MCU_SPI2_CS_DIDO_MCP23S17_Pin|MCU_AIC_EN_POINT_LED_Pin|MCU_HIOC1_EN_POINT_LED_Pin 
                          |MCU_HIOC2_EN_POINT_LEDE9_Pin|MCU_1_SPI4_DIGCS_ADC_Pin|MCU_1_SPI4_CS_ADC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PCPin PCPin PCPin */
  GPIO_InitStruct.Pin = MCU_HIOC2_EN_POINT_LED_Pin|MCU_SPI2_RESET_MCP23S17C14_Pin|MCU_SPI2_CS_AIHIO_MCP23S17_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PFPin PFPin PFPin PFPin */
  GPIO_InitStruct.Pin = HIO_SPI5_CS_ADC_Pin|MCU_TB_EN_POINT_LED_Pin|MCU_1_POINT_LED_D_Pin|MCU_1_POINT_LED_A0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : PCPin PCPin PCPin PCPin 
                           PCPin */
  GPIO_InitStruct.Pin = MCU_DOP_EN_POINT_LED_Pin|MCU_AIP_EN_POINT_LED_Pin|MCU_AIC_EN_POINT_LEDC7_Pin|MCU_HIOP_EN_POINT_LED_Pin 
                          |MCU_HIOC1_EN_POINT_LEDC9_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PAPin PAPin PAPin PAPin 
                           PAPin PAPin PAPin PAPin */
  GPIO_InitStruct.Pin = MCU_DIC1_EN_POINT_LED_Pin|MCU_DIC2_EN_POINT_LED_Pin|MCU_DIP_EN_POINT_LED_Pin|MCU_1_POINT_LED_DA9_Pin 
                          |MCU_1_POINT_LED_A0A10_Pin|MCU_1_POINT_LED_A1A11_Pin|MCU_1_POINT_LED_A2A12_Pin|SPI3_DAC_AICS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PBPin PBPin PBPin 
                           PBPin PBPin PBPin */
  GPIO_InitStruct.Pin = MCU_DOC1_EN_POINT_LED_Pin|MCU_DOC2_EN_POINT_LED_Pin|MCU_DOC2_EN_POINT_LEDB10_Pin|MCU_SPI2_CS_AIHIO_MCP23S17B12_Pin 
                          |MCU_DIC1_EN_POINT_LEDB6_Pin|MCU_DIC2_EN_POINT_LEDB7_Pin|MCU_DOC1_EN_POINT_LEDB9_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PGPin PGPin */
  GPIO_InitStruct.Pin = MCU_1_POINT_LED_A1_Pin|MCU_1_POINT_LED_A2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : PDPin PDPin PDPin PDPin 
                           PDPin PDPin */
  GPIO_InitStruct.Pin = MCU_MODE_SWITCH_Pin|MCU_TEST_START_Pin|MCU_MAIN_DITEST_Pin|MCU_MAIN_DOTEST_Pin 
                          |MCU_MAIN_AITEST_Pin|MCU_MAIN_HIOTEST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PDPin PDPin PDPin */
  GPIO_InitStruct.Pin = SPI3_DAC_HIOCS_Pin|SPI3_DAC_RESET_Pin|MCU_MAIN_EN_POINT_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
