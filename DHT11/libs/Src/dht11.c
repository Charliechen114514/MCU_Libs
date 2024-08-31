#include "dht11.h"
#include "tim.h"

static DHT11_Error global_error = DHT11_NOT_INIT;
static uint8_t dataFrame[DHT11_BUFFER_SIZE];
TIM_HandleTypeDef* using_clock;

static inline void __set_global_error(DHT11_Error error){
    global_error = error;
}



static void __DHT11_MAKE_US_DELAY(uint16_t us){
    uint16_t differ = 0xffff-us-5;				
	__HAL_TIM_SET_COUNTER(using_clock,differ);	//设定TIM1计数器起始值
	HAL_TIM_Base_Start(using_clock);		//启动定时器	
	
	while(differ < 0xffff-5){	//判断
		differ = __HAL_TIM_GET_COUNTER(using_clock);		//查询计数器的计数值
	}
	HAL_TIM_Base_Stop(using_clock);
}

static void __DHT11_SetPackInternal(DHT11_Config* config, uint32_t mode)
{
    GPIO_InitTypeDef init;
    init.Mode = mode;
    init.Pin = config->GPIO_Pin;
    init.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(config->GPIO_Who, &init); 
}

static void __setDHT11_PinMode(DHT11_Config* config, DHT11_Mode mode)
{
    switch (mode)
    {
    case DHT11_Mode_Read:
        __DHT11_SetPackInternal(config, GPIO_MODE_INPUT);
        break;
    case DHT11_Mode_Write:
        __DHT11_SetPackInternal(config, GPIO_MODE_OUTPUT_PP);
        break;
    default:
        break;
    }
}

static uint8_t __dht11_pass_retry(DHT11_Config* config, uint8_t required_check_bits)
{
    uint8_t retry_times = 0;
    __setDHT11_PinMode(config, DHT11_Mode_Read);
    while(  HAL_GPIO_ReadPin(config->GPIO_Who, config->GPIO_Pin) 
                == required_check_bits && 
            retry_times <= RETRY_MAX_TIME)
    {
        __DHT11_MAKE_US_DELAY(1);
        retry_times++;
    }
    return retry_times <= RETRY_MAX_TIME;
}

static uint8_t __DHT11_Check_If_DHT11_Work(DHT11_Config* config){
    if(!__dht11_pass_retry(config, GPIO_PIN_SET)){
        __set_global_error(DHT11_ERROR_DEVICE_NOT_FOUND);
        return 0;
    }

    if(!__dht11_pass_retry(config, GPIO_PIN_RESET)){
        __set_global_error(DHT11_ERROR_DEVICE_NOT_FOUND);
        return 0;
    }
    return 1;
}





// 0 or 1
static inline uint8_t __DHT11_read_one_bit(DHT11_Config* config)
{
    if(!__dht11_pass_retry(config, GPIO_PIN_SET)){
        __set_global_error(DHT11_FAILED_READ_DATA);
    }
    if(!__dht11_pass_retry(config, GPIO_PIN_RESET)){
        __set_global_error(DHT11_FAILED_READ_DATA);
    }
    __DHT11_MAKE_US_DELAY(40);
    return HAL_GPIO_ReadPin(config->GPIO_Who, config->GPIO_Pin);
}

static uint8_t __DHT11_read_one_byte(DHT11_Config* config)
{
    uint8_t required_ret_byte = 0;
    for(uint8_t i = 0; i < 8; i++){
        required_ret_byte <<= 1;
        required_ret_byte |= __DHT11_read_one_bit(config);
    }
    return required_ret_byte;
}

static uint8_t __DHT11_Check_Policy(){
    return dataFrame[0]+dataFrame[1]+dataFrame[2]+dataFrame[3]==dataFrame[4];
}

uint8_t init_DHT11_Device(DHT11_Config* config)
{
    __setDHT11_PinMode(config, DHT11_Mode_Write);
    HAL_GPIO_WritePin(config->GPIO_Who, config->GPIO_Pin, GPIO_PIN_RESET);
    __DHT11_MAKE_US_DELAY(20);
    __setDHT11_PinMode(config, DHT11_Mode_Read);
    HAL_GPIO_WritePin(config->GPIO_Who, config->GPIO_Pin, GPIO_PIN_SET);
    __DHT11_MAKE_US_DELAY(30);
    __set_global_error(DHT11_NO_ERROR);
    return __DHT11_Check_If_DHT11_Work(config);
}



void setDHT11_DelayClockSource(DHT11_ClockSource* source)
{
    using_clock = source;
}

DHT11_Error error_GetDHT11_Status()
{
    return global_error;
}

void getDHT11_DataPack(DHT11_Config* config, DHT11_DataPack* pack)
{
    init_DHT11_Device(config);
    if(__DHT11_Check_If_DHT11_Work(config)){
        for(uint8_t i = 0; i < DHT11_BUFFER_SIZE; i++){
            dataFrame[i] = __DHT11_read_one_byte(config);
        }
        if(__DHT11_Check_Policy()){
            pack->temperature = dataFrame[0];
            pack->humanity = dataFrame[2];
        }else{
            __set_global_error(DHT11_ERROR_DATA);
        }
    }
}
