//
// Created by diyhome on 2020/3/7.
//

#ifndef DHT11_DRIVE_DHT11_H
#define DHT11_DRIVE_DHT11_H

//#define NEED_DELAY_US       //定义这个表面使用文件自带的us级延时函数,注释掉的话得定义一个void delay_us(uint8_t us);函数
#ifndef NEED_DELAY_US
#define DELAY_TIM htim1
#endif

#include "main.h"

typedef struct
{
    uint8_t humi_high8bit;  //湿度高八位
    uint8_t humi_low8bit;   //湿度低八位
    uint8_t temp_high8bit;  //温度高八位
    uint8_t temp_low8bit;   //温度低八位
    uint8_t check_sum;      //校验和

    GPIO_TypeDef* _GPIO_PORT;//GPIO的组别
    uint16_t GPIO_Pin;      //GPIO引脚号
} DHT11_Data_TypeDef;

/**
 *  DHT11的读取函数
 * @param DHT11_Data :DHT11定义的结构体
 * @return 校验值的正确与否
 */
uint8_t DHT11_Read_TempHumi(DHT11_Data_TypeDef* DHT11_Data);
#endif //DHT11_DRIVE_DHT11_H
