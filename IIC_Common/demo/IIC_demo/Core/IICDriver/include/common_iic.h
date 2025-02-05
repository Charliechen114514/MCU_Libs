#ifndef COMMON_IIC_H
#define COMMON_IIC_H

#ifdef STM32F1
#include "stm32f1xx_hal.h"
#else
#error "Unsupportive Chips"
#endif

typedef void*   IICCommonHandleType;
typedef void(*SendData)(IICCommonHandleType, uint8_t*, uint16_t);
typedef void(*ReceiveData)(IICCommonHandleType, uint8_t*, uint16_t);
typedef void(*OpenIIC)(IICCommonHandleType);
typedef void(*CloseIIC)(IICCommonHandleType);
typedef void(*SendACK)(IICCommonHandleType, uint8_t);
typedef uint8_t(*WaitACK)(IICCommonHandleType);


typedef struct{    
    SendData    data_sender;
    ReceiveData data_receiver;
    OpenIIC     start_iic;
    CloseIIC    end_iic;
    SendACK     ack_sender;
    WaitACK     ack_receiver;
}IIC_Operations;

typedef struct{
    uint32_t    max_delay;
    uint8_t     iic_addr;
}IICCommonConfig;

void __soft_iic_delay_us(uint32_t secs);

#endif