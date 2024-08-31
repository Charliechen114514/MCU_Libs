#include "stm32f1xx_hal.h"
#define RETRY_MAX_TIME (100)
#define DHT11_BUFFER_SIZE (5)

typedef TIM_HandleTypeDef DHT11_ClockSource;
typedef uint16_t GPIO_Pin_Type;
typedef struct __DHT11_Config{
    GPIO_TypeDef* GPIO_Who;
    GPIO_Pin_Type GPIO_Pin;
}DHT11_Config;

typedef enum __DHT11_Error{
    DHT11_NO_ERROR,
    DHT11_NOT_INIT,
    DHT11_ERROR_DEVICE_NOT_FOUND,
    DHT11_FAILED_READ_DATA,
    DHT11_ERROR_DATA
}DHT11_Error;


typedef enum __DHT11_Mode{
    DHT11_Mode_Write, 
    DHT11_Mode_Read
}DHT11_Mode;

typedef struct __DHT11_DataPack{
    uint8_t temperature;
    uint8_t humanity;
}DHT11_DataPack;

uint8_t     init_DHT11_Device(DHT11_Config* config);
void        setDHT11_DelayClockSource(DHT11_ClockSource* source);
void        getDHT11_DataPack(DHT11_Config* config, DHT11_DataPack* pack);
DHT11_Error error_GetDHT11_Status();