// this should be enough, but some compilers disagree the issue
#pragma once 

#ifndef OLED_BASE_DRIVER_H
#define OLED_BASE_DRIVER_H

#ifndef uint8_t
    typedef unsigned char uint8_t;
#endif

#include "oled_driver_config.h"

struct _OLED_Handle;
typedef void* OLED_PrivateData;

typedef enum {
    OLED_SOFTIIC_PACK,
    OLED_HARDIIC_PACK
}OLEDCommunicationType;

typedef struct _OLED_Handle
{
    OLEDCommunicationType type;
    // private operations data is here
    OLED_PrivateData private_data;
}OLED_Handle;

/*
    init_oled_handle_softiic:
    1. handle:  handle should be blank
    2. pvts:    softiic comm's requires
*/
void init_oled_handle_softiic(
    OLED_Handle* handle, 
    OLED_Handle_SoftIIC_Handle_Private* pvts
);

/*
    init_oled_handle_hardiic:
    1. handle:  handle should be blank
    2. pvts:    hardiic comm's requires
*/
void init_oled_handle_hardiic(
    OLED_Handle* handle, 
    OLED_Handle_HardIIC_Private* pvts
);

void oled_set_pixel(
    OLED_Handle* handle, 
    uint8_t x, uint8_t y);

void oled_update(OLED_Handle* handle);
#undef uint8_t // clean the def of uint8_t
#endif