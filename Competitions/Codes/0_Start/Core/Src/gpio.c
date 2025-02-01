/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_8
                          |GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ENABLE_CHANGE_GPIO_Port, ENABLE_CHANGE_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PC13 PC14 PC15 PC8
                           PC9 PC10 PC11 PC12 */
  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_8
                          |GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : ENABLE_CHANGE_Pin */
  GPIO_InitStruct.Pin = ENABLE_CHANGE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(ENABLE_CHANGE_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */
void onEnableLEDGPIO(void)
{
    GPIO_InitTypeDef init = {0};
    __HAL_RCC_GPIOC_CLK_ENABLE(); // enable the clock
    uint32_t all_pins = LED_BASE_Pin(8);
//    all_pins |= LED_BASE_Pin(9);
//    all_pins |= LED_BASE_Pin(10);
//    all_pins |= LED_BASE_Pin(11);
//    all_pins |= LED_BASE_Pin(12);
//    all_pins |= LED_BASE_Pin(13);
//    all_pins |= LED_BASE_Pin(14);
//    all_pins |= LED_BASE_Pin(15);
    init.Pin = all_pins;
    init.Mode = GPIO_MODE_OUTPUT_PP;
    init.Pull = GPIO_NOPULL;
    init.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_WritePin(LED_BASE_GPIO, all_pins, GPIO_PIN_SET);
    HAL_GPIO_Init(ENABLE_CHANGE_GPIO_Port, &init);
}

void onSetEnableLED(GPIO_PinState enabled)
{
    HAL_GPIO_WritePin(ENABLE_CHANGE_GPIO_Port, ENABLE_CHANGE_Pin, enabled);
}

void onLightenUp(uint32_t who)
{
    // As the board requires the low level to light up the led
    HAL_GPIO_WritePin(LED_BASE_GPIO, who, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_RESET);
}

void onLightenOff(uint32_t who)
{
    // As the board requires the low level to light up the led
    HAL_GPIO_WritePin(LED_BASE_GPIO, who, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_RESET);
}



void onLightenUpArray(uint8_t array_like);

/* USER CODE END 2 */
