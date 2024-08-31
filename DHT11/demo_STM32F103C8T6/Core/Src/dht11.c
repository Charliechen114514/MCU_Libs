#include "dht11.h"
#include "tim.h"

typedef enum __DHT11_Mode{
    DHT11_Mode_Write, 
    DHT11_Mode_Read
}DHT11_Mode;

// 错误设置
static DHT11_Error global_error = DHT11_NOT_INIT;
// buffer
static uint8_t dataFrame[DHT11_BUFFER_SIZE];
// 使用的时钟
TIM_HandleTypeDef* using_clock = NULL;

// 设计方法：将这个C文件自身看作模块，所有
// static 修饰的函数都是 private 私有函数

// 设置全局错误
static inline void __set_global_error(DHT11_Error error){
    global_error = error;
}

// 使用系统时钟，非常不推介！
static void __DHT11_NO_CLOCK_SET(uint16_t us){
    uint32_t Tdata = us* SystemCoreClock / 8U / 1000000U;
    do{__NOP();}while(Tdata--);
    return ;
}

// 自己搓的HAL_DELAY_US，需要开启一个定时器，定时器资源使用
// setDHT11_DelayClockSource提前设置好
static void __DHT11_MAKE_US_DELAY(uint16_t us){
    if(!using_clock) return __DHT11_NO_CLOCK_SET(us);
    
    uint16_t differ=0xffff-us-5;

    HAL_TIM_Base_Start(using_clock);
            __HAL_TIM_SetCounter(using_clock,differ);
    while(differ<0xffff-5){
        differ = __HAL_TIM_GetCounter(using_clock);
    }
    HAL_TIM_Base_Stop(using_clock);
}

// 设置端口IO模式的_impl函数
static void __DHT11_SetPackInternal(DHT11_Config* config, uint32_t mode)
{
    GPIO_InitTypeDef init;
    init.Mode = mode;
    init.Pin = config->GPIO_Pin;
    
    if(mode == GPIO_MODE_INPUT)
        init.Pull = GPIO_PULLUP; // 输入则上拉
    else
        init.Speed = GPIO_SPEED_FREQ_HIGH; // 输出设置快速输出
    HAL_GPIO_Init(config->GPIO_Who, &init); 
}

// 设置端口IO模式
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

// 这个是查看retry是否成功的，想要使得库更加的严谨，考虑检查返回值！
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
    return retry_times < RETRY_MAX_TIME;
}

// 查看工作状态是否正常
static uint8_t __DHT11_Check_If_DHT11_Work(DHT11_Config* config){
    __setDHT11_PinMode(config, DHT11_Mode_Read);
    uint8_t status = HAL_GPIO_ReadPin(config->GPIO_Who, config->GPIO_Pin) == GPIO_PIN_RESET;
    if(!status){
        __set_global_error(DHT11_FAILED_READ_DATA);
    }
    return status;
}

// 读取一个比特
static inline uint8_t __DHT11_read_one_bit(DHT11_Config* config)
{
    if(!__dht11_pass_retry(config, GPIO_PIN_RESET)){
        __set_global_error(DHT11_FAILED_READ_DATA);
    }
    // 根据时序图，DHT传回高电平信号维持26us~28us表示0，	维持70us表示1
    __DHT11_MAKE_US_DELAY(30);
    uint8_t res = HAL_GPIO_ReadPin(config->GPIO_Who, config->GPIO_Pin);
    // 还是做检查有没有正常传递结束一个比特的检查
    if(!__dht11_pass_retry(config, GPIO_PIN_SET)){
        __set_global_error(DHT11_FAILED_READ_DATA);
    }

    return res;
}

// 读取一个字节，是对__DHT11_read_one_bit的循环封装
static uint8_t __DHT11_read_one_byte(DHT11_Config* config)
{
    uint8_t required_ret_byte = 0;
    for(uint8_t i = 0; i < 8; i++){
        required_ret_byte <<= 1;
        required_ret_byte |= __DHT11_read_one_bit(config);
    }
    return required_ret_byte;
}

// 数据校验
static inline uint8_t __DHT11_Check_Policy(){
    return dataFrame[0]+dataFrame[1]+dataFrame[2]+dataFrame[3]==dataFrame[4];
}

// 只初始化不做检查
static void __DHT11_Only_Init(DHT11_Config* config){
    __setDHT11_PinMode(config, DHT11_Mode_Write);
    HAL_GPIO_WritePin(config->GPIO_Who, config->GPIO_Pin, GPIO_PIN_RESET);
    HAL_Delay(20);
    HAL_GPIO_WritePin(config->GPIO_Who, config->GPIO_Pin, GPIO_PIN_SET);
    __DHT11_MAKE_US_DELAY(30);
    __set_global_error(DHT11_NO_ERROR);
}

uint8_t init_DHT11_Device(DHT11_Config* config)
{
#if LAZY_INIT
    return 1;
#else
    __DHT11_Only_Init(config);
    return __DHT11_Check_If_DHT11_Work(config);
#endif
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
    __DHT11_Only_Init(config);
    if(__DHT11_Check_If_DHT11_Work(config))
    {
        // 接下来，DHT11拉低电平一段时间后拉高电平一段时间
        // 这个失误可以在下几次循环中消除，所以只设错误不反回
        __dht11_pass_retry(config, GPIO_PIN_RESET);
        __dht11_pass_retry(config, GPIO_PIN_SET);
        for(int i = 0; i < 5;i++)
            dataFrame[i] = __DHT11_read_one_byte(config);

        if(__DHT11_Check_Policy()){
            pack->int_humanity = dataFrame[0];
            pack->float_humanity = dataFrame[1];
            pack->int_temperature = dataFrame[2];
            pack->float_temperature = dataFrame[3];
        }else{
            __set_global_error(DHT11_FAILED_PASS_CHECK);
        }
    }

}
