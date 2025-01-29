#ifndef OLED_CONFIG_H
#define OLED_CONFIG_H

#ifdef STM32F1

#include "stm32f1xx_hal.h"

/* command send fucntion */
typedef void(*SendCommand)(void*, uint8_t);
/* data send fucntion */
typedef void(*SendData)(void*, uint8_t*, uint16_t);

/* driver level oled driver's functionalities */
typedef struct __OLED_Operations{
    SendCommand command_sender;
    SendData    data_sender;
}OLED_Operations;

typedef enum {
    OLED_SOFT_IIC_DRIVER_TYPE,
    OLED_HARD_IIC_DRIVER_TYPE,
    OLED_SOFT_SPI_DRIVER_TYPE,
    OLED_HARD_SPI_DRIVER_TYPE
}OLED_Driver_Type;

/* OLED Communication requires this*/
#define DATA_PREFIX     (0x40)
#define CMD_PREFIX      (0x00)

/*  
    to abstract the private handle base 
    this is to isolate the dependencies of
    the real implementations
*/
typedef void* OLED_Handle_Private;
/* hard iic communication requires indications */
typedef struct __OLED_HARD_IIC_Private_Config OLED_HARD_IIC_Private_Config;
/* soft iic communication requires indications */
typedef struct __OLED_SOFT_IIC_Private_Config OLED_SOFT_IIC_Private_Config;
/* hard spi communication requires indications */
typedef struct __OLED_HARD_SPI_Private_Config OLED_HARD_SPI_Private_Config;
/* soft spi communication requires indications */
typedef struct __OLED_SOFT_SPI_Private_Config OLED_SOFT_SPI_Private_Config;

/* final handle */
typedef struct __OLED_Handle_Type OLED_Handle;

#else
#error "Current Chip is not supported"
#endif

/* oled chips selections */

#ifdef SSD1306

#include "configs/ssd1306.h"

#elif SSD1309
#include "configs/ssd1309.h"
#else
#error "Unknown chips, please select in compile time using define!"
#endif

#endif