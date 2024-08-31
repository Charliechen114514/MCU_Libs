#include "stm32f1xx_hal.h"

// 最大尝试次数
#define RETRY_MAX_TIME (100)
// 协议数据包长度，DHT11默认为5个byte
#define DHT11_BUFFER_SIZE (5)
// Lazy_Init决定了要不要提前拉起DHT11的工作状态
// 定义为1，直到使用的时候才会初始化，
// init_DHT11_Device不会采取实际行动，函数将会总是成功！
// 反之，使能init_DHT11_Device函数
#define LAZY_INIT 0

// 时钟资源
typedef TIM_HandleTypeDef DHT11_ClockSource;

// 指定的端口
typedef uint16_t GPIO_Pin_Type;
typedef struct __DHT11_Config{
    GPIO_TypeDef* GPIO_Who;
    GPIO_Pin_Type GPIO_Pin;
}DHT11_Config;

// 状态错误码
typedef enum __DHT11_Error{
    DHT11_NO_ERROR,                 // 没错误
    DHT11_NOT_INIT,                 // 没有初始化
    DHT11_ERROR_DEVICE_NOT_FOUND,   // 设备未找到
    DHT11_FAILED_READ_DATA,         // 无法读取数据
    DHT11_FAILED_PASS_CHECK         // 没有通过校验检查
}DHT11_Error;

// DHT11数据结构体
typedef struct __DHT11_DataPack{
    uint8_t int_temperature;
    uint8_t float_temperature;
    uint8_t int_humanity;
    uint8_t float_humanity;
}DHT11_DataPack;

// 接口说明

// 初始化设备，其行为依据LAZY_INIT确定
uint8_t     init_DHT11_Device(DHT11_Config* config);
// 设置DHT11延时函数的时钟资源，该函数务必在使用DHT11之前就有所调用
// 否则，将会使用系统时钟，导致延时不准确！
void        setDHT11_DelayClockSource(DHT11_ClockSource* source);
// 获取数据包，pack推介是空的！
void        getDHT11_DataPack(DHT11_Config* config, DHT11_DataPack* pack);
// 获取当前状态
DHT11_Error error_GetDHT11_Status();