#ifndef SPI_COMMON_H
#define SPI_COMMON_H

#ifdef STM32F1
#include "stm32f1xx_hal.h"
#else
#error "Unsupportive chips"
#endif

typedef struct __CommonSPIHandle CommonSPIHandle;
typedef void* Common_SPI_Protocol_Handle;
typedef struct __SoftSPI_Protocol SOFTSPI_Protocol;
typedef struct __HARD_SPI_COMMON HARDSPI_Protocol;
typedef void(*Start)(CommonSPIHandle*);
typedef void(*End)(CommonSPIHandle*);
typedef void(*SendByte)(CommonSPIHandle*, const uint8_t);
typedef uint8_t(*ReceiveByte)(CommonSPIHandle*);
typedef uint8_t(*SwapByte)(CommonSPIHandle*, uint8_t);
typedef void(*SendBytes)(CommonSPIHandle*, const uint8_t*, uint32_t size);
typedef void(*ReceiveBytes)(CommonSPIHandle*, uint8_t*, uint32_t size);

typedef struct {
    GPIO_TypeDef*       port;    
    uint16_t            pin;
}SPI_GPIOPack;

typedef struct {
    Start       start;
    End         end;
    SendByte    sendByte;
    ReceiveByte receiveByte;
    SwapByte    SwapByte;
    SendBytes   sendBytes;
    ReceiveBytes receiveBytes;
}SPI_CommonOperations;

typedef enum{
    SOFT_SPI_PROTOCOL,
    HARD_SPI_PROTOCOL
}SPI_ProtocalType;

typedef struct {
    uint32_t    delay_time;
}SPI_Configure;

typedef struct __CommonSPIHandle{
    SPI_CommonOperations*       op;
    Common_SPI_Protocol_Handle  handle;
    SPI_ProtocalType            type;
}CommonSPIHandle;

void register_softspi_spihandle(
    CommonSPIHandle* handle, 
    SOFTSPI_Protocol* protocol_internal);

void register_hardspi_spihandle(
    CommonSPIHandle* handle,
    HARDSPI_Protocol* protocol_internal);

#endif