#pragma once
/*
    For Tim1637, Though it is using IIC, but the Sequence Diagram
    Datasheet provided is not a typical IIC, we have to simulate
    The requiring initializations
*/
#include "gpio_driver.h"
#include "tim1637_params.h"


typedef struct {
    /* CLK(SCK) */
    CCGPIO*  CLK;
    CCGPIO*  DIO;
}CCTIM1637_Handle;

/*
    Upload three blank value:)
    handle_wait is a blank value for handle waiting for displaying
    CLK is the GPIO which shell be later used for
    DIO is the GPIO which send data
*/
void    init_cctim1637(CCTIM1637_Handle* handle_wait, CCGPIO*  CLK, CCGPIO*  DIO);
uint8_t set_display_array_at_index(uint8_t alphanum, DisplayArray arr, uint8_t index);
void    set_accuired_disp_colon(DisplayArray arr, uint8_t req_display);
void    commit_display_auto_upgrade(CCTIM1637_Handle* handle, const DisplayArray arr);
void    set_TIM1637_Brightness(CCTIM1637_Handle* handle, uint8_t level);



