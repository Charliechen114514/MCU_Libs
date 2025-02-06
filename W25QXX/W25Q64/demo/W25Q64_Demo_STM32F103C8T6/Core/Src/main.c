/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2025 STMicroelectronics.
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Graphic/fast_setup/fast_setup.h"
#include "Graphic/sim_app/simple_text.h"

#include "SPI_Common/soft_spi/soft_spi.h"
#include "SPI_Common/hard_spi/hard_spi.h"
#include "WX25Q64/wx25q64.h"
#include <stdio.h>

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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

SOFTSPI_Protocol  spi;
HARDSPI_Protocol  hard_spi;
CommonSPIHandle   spi_handle;
WX25Q64_Handle    wx25q64;

SPI_GPIOPack ss = {GPIOA, GPIO_PIN_4};
SPI_GPIOPack clk = {GPIOA, GPIO_PIN_5};
SPI_GPIOPack mosi = {GPIOA, GPIO_PIN_7};
SPI_GPIOPack miso = {GPIOA, GPIO_PIN_6};
void init_wx25q64()
{
    SPI_Configure config;
    config.delay_time = HAL_MAX_DELAY;
    
    init_softspi_protocol(
      &spi, ss, clk, mosi, miso, config
    );
    register_softspi_spihandle(
      &spi_handle, &spi
    );

    // init_hardspi_protocol(
    //   &hard_spi, &hspi1, ss, config
    // );
    // register_hardspi_spihandle(&spi_handle, &hard_spi);

    WX25Q64_Handle_register_spi_handle(
      &wx25q64, &spi_handle
    );
}


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

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
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
  CCDeviceHandler handler;
  CCGraphicTextEdit edit;

  oled_soft_iic_setup(&handler);
  init_wx25q64();
  char buffers[50];
  // uint32_t device_id = 0;
  // wx25q64.op->WX25Q64_Fetch_Property(&wx25q64, &device_id, ID);
  // uint8_t mid = GET_MID(device_id);
  // uint16_t did = GET_DID(device_id);
  // snprintf(buffers, 20, "Manu   ID: %X", mid);
  // set_simple_text(&edit, &handler, buffers);
  // snprintf(buffers, 20, "Device ID: %X", did);
  // set_newline_text(&edit, &handler, buffers);
  
  uint8_t array[] = "2345";
  uint8_t fetch[5] = {0, 0, 0, 0, 0};
  wx25q64.op->write_data(&wx25q64, 0x000000, array, 4);
  wx25q64.op->read_data(&wx25q64, 0x000000, fetch, 4);
  set_simple_text(&edit, &handler, "Read from raw:");
  snprintf(buffers, 50, 
      "%X,%X,%X,%X", 
      fetch[0], fetch[1], fetch[2], fetch[3]);
  set_newline_text(&edit, &handler, buffers);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
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
