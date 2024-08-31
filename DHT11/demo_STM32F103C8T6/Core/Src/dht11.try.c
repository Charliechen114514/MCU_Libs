//
// Created by diyhome on 2020/3/7.
//

#include "dht11_try.h"
#include "tim.h"

static void DHT11_Mode_IPU(DHT11_Data_TypeDef* DHT11_Data);       //设置端口为输入模式
static void DHT11_Mode_Out_pp(DHT11_Data_TypeDef* DHT11_Data);    //设置端口为输出模式
static uint8_t DHT11_ReadByte(DHT11_Data_TypeDef* DHT11_Data);    //读取一个字节
static void delay_us(uint16_t us);             //us级延时函数

#define DHT11_Data_IN HAL_GPIO_ReadPin(DHT11_Data->_GPIO_PORT,DHT11_Data->GPIO_Pin)

#define DHT11_GPIO_HIGH HAL_GPIO_WritePin(DHT11_Data->_GPIO_PORT,DHT11_Data->GPIO_Pin,SET);
#define DHT11_GPIO_LOW HAL_GPIO_WritePin(DHT11_Data->_GPIO_PORT,DHT11_Data->GPIO_Pin,RESET);

#ifdef NEED_DELAY_US
/**
 * 这个是us级延时,但是最长只支持24为长度的延时
 * @param us 延时时间,单位us
 * 具体参考:https://blog.csdn.net/hxkrrzq/article/details/52808372
 */
static void delay_us(uint16_t us)
{
    uint32_t temp;
    SysTick->LOAD = 10*us;
    SysTick->VAL=0X00;//清空计数器
    SysTick->CTRL=0X01;//使能，减到零是无动作，采用外部时钟源
    do{
        temp=SysTick->CTRL;//读取当前倒计数值
    }while((temp&0x01)&&(!(temp&(1<<16))));//等待时间到达
    SysTick->CTRL=0x00; //关闭计数器
    SysTick->VAL =0X00; //清空计数器
}
#else
static void delay_us(uint16_t us)
{
    uint16_t differ=0xffff-us-5;

    HAL_TIM_Base_Start(&DELAY_TIM);
            __HAL_TIM_SetCounter(&DELAY_TIM,differ);
    while(differ<0xffff-5){
        differ = __HAL_TIM_GetCounter(&DELAY_TIM);
    }
    HAL_TIM_Base_Stop(&DELAY_TIM);
}
#endif

static void DHT11_Mode_IPU(DHT11_Data_TypeDef* DHT11_Data)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = DHT11_Data->GPIO_Pin;
    GPIO_InitStruct.Mode= GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull= GPIO_PULLUP;
    HAL_GPIO_Init(DHT11_Data->_GPIO_PORT,&GPIO_InitStruct);
}

static void DHT11_Mode_Out_pp(DHT11_Data_TypeDef* DHT11_Data)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.Pin = DHT11_Data->GPIO_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(DHT11_Data->_GPIO_PORT,&GPIO_InitStruct);
}

static uint8_t DHT11_ReadByte(DHT11_Data_TypeDef* DHT11_Data)
{
//    DHT11_Mode_IPU(DHT11_Data);   //主读取函数里面写了这个,不要重复
    uint8_t i,temp=0;

    for (i = 0; i < 8; ++i) {
        while(DHT11_Data_IN == GPIO_PIN_RESET);     //等待拉高信号,开始读取
        delay_us(40);                           //等待

//        数据信号电平高低转换位0,1
        if(DHT11_Data_IN==GPIO_PIN_SET){
            while(DHT11_Data_IN==GPIO_PIN_SET);
            temp|=(uint8_t)(0x01<<(7-i));
        } else {
            temp &= (uint8_t) ~(0x01<<(7 - i));
        }
    }
    return temp;
}

/**
 * 读取DHT11的数据
 * @param DHT11_Data DHT11的结构体指针
 * @return 0->成功读取;1->错误
 */
uint8_t DHT11_Read_TempHumi(DHT11_Data_TypeDef* DHT11_Data)
{

//    通知DHT11开始读取数据
    DHT11_Mode_Out_pp(DHT11_Data);
    DHT11_GPIO_LOW
    HAL_Delay(18);
//    delay_us(18);
    DHT11_GPIO_HIGH;
    delay_us(30);

//    设置输入模式防止干扰
    DHT11_Mode_IPU(DHT11_Data);
    if(DHT11_Data_IN==GPIO_PIN_RESET){
//        等待DHT11通知可以开始读取
        while(DHT11_Data_IN==GPIO_PIN_RESET);
        while(DHT11_Data_IN==GPIO_PIN_SET);

        DHT11_Data->humi_high8bit = DHT11_ReadByte(DHT11_Data);
        DHT11_Data->humi_low8bit  = DHT11_ReadByte(DHT11_Data);
        DHT11_Data->temp_high8bit = DHT11_ReadByte(DHT11_Data);
        DHT11_Data->humi_low8bit  = DHT11_ReadByte(DHT11_Data);
        DHT11_Data->check_sum = DHT11_ReadByte(DHT11_Data);

//        读取完成的扫尾工作
        DHT11_Mode_Out_pp(DHT11_Data);
        DHT11_GPIO_HIGH;

//        计算校验和
        uint8_t temp_check = DHT11_Data->humi_high8bit + DHT11_Data->humi_low8bit + DHT11_Data->temp_high8bit + DHT11_Data->temp_low8bit;
        if(temp_check==DHT11_Data->check_sum) return 0;
        else return 1;
    } else return 1;
}