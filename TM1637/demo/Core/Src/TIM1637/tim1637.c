#include "tim1637.h"
#include "tim1637_params.h"
#include "delay.h"
void    init_cctim1637(CCTIM1637_Handle* handle_wait, CCGPIO*  CLK, CCGPIO*  DIO)
{
    handle_wait->CLK = CLK;
    handle_wait->DIO = DIO;
}

static void inline __fast_set_dio_gpio_in(CCGPIO* DIO){
    DIO->letter_case->CRL &= 0X0FFFFFFF;
    DIO->letter_case->CRL |= (uint32_t)8<<28;
}

static void inline __fast_set_dio_gpio_out(CCGPIO* DIO){
    DIO->letter_case->CRL &= 0X0FFFFFFF;
    DIO->letter_case->CRL |= (uint32_t)3<<28;
}

static void TIM1637_IIC_Start(CCGPIO* CLK, CCGPIO* DIO)
{
    __fast_set_dio_gpio_out(DIO);
    setGPIOOn(CLK);
    setGPIOOn(DIO);
    delay_us(2);
    setGPIOOff(DIO);
}

static void TIM1637_IIC_ACK(CCGPIO* CLK, CCGPIO* DIO)
{
    __fast_set_dio_gpio_in(DIO);
    setGPIOOff(CLK);
    delay_us(5);
    setGPIOOn(CLK);
    delay_us(2);
    setGPIOOff(CLK);
}

static void TIM1637_IIC_Stop(CCGPIO* CLK, CCGPIO* DIO)
{
    __fast_set_dio_gpio_out(DIO);
    setGPIOOff(CLK);
    delay_us(2);
    setGPIOOff(DIO);
    delay_us(2);
    setGPIOOn(CLK);
    delay_us(2);
    setGPIOOn(DIO);
}

static void TIM1637_writeByte(CCGPIO* DIO, CCGPIO* CLK, uint8_t byte)
{
    __fast_set_dio_gpio_out(DIO);
    for(uint8_t i = 0; i < 8; i++){
        setGPIOOff(CLK);
        setGPIOState(DIO, (byte & 0x01 ? ON : OFF));
        delay_us(3);
        byte >>= 1;
        setGPIOOn(CLK);
        delay_us(3);
    }
}

uint8_t set_display_array_at_index(uint8_t alphanum, DisplayArray arr, uint8_t index)
{
    if(index >= SUPPORT_DISP_N){
        return 0;
    }

    uint8_t wanna_write = search_display_one(alphanum);
    if(wanna_write == FAILED_SEARCH){
        return 0;
    }

    arr[index] = wanna_write;
    return 1;
}

void set_accuired_disp_colon(DisplayArray arr, uint8_t req_display)
{
    if(req_display) {
        SET_COLON(arr);
    }else{
        OFF_COLON(arr);
    }
}

void commit_display_auto_upgrade(CCTIM1637_Handle* handle, const DisplayArray arr)
{
    TIM1637_IIC_Start(handle->CLK, handle->DIO);
    TIM1637_writeByte(handle->DIO, handle->CLK, 0x40);
    TIM1637_IIC_ACK(handle->CLK, handle->DIO);
    TIM1637_IIC_Stop(handle->CLK, handle->DIO);

    TIM1637_IIC_Start(handle->CLK, handle->DIO);
    TIM1637_writeByte(handle->DIO, handle->CLK, 0xC0);
    TIM1637_IIC_ACK(handle->CLK, handle->DIO);

    for(uint8_t i = 0; i < SUPPORT_DISP_N; i++){
        TIM1637_writeByte(handle->DIO, handle->CLK, arr[i]);
        TIM1637_IIC_ACK(handle->CLK, handle->DIO);
    }

    TIM1637_IIC_Stop(handle->CLK, handle->DIO);
}

void    set_TIM1637_Brightness(CCTIM1637_Handle* handle, uint8_t level)
{
    TIM1637_IIC_Start(handle->CLK, handle->DIO);
    TIM1637_writeByte(handle->DIO, handle->CLK,  0x88 | level );
    TIM1637_IIC_ACK(handle->CLK, handle->DIO);
    TIM1637_IIC_Stop(handle->CLK, handle->DIO);
}