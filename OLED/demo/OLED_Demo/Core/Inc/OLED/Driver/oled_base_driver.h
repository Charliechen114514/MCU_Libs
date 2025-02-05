#ifndef OLED_BASE_DRIVER_H
#define OLED_BASE_DRIVER_H

#include "oled_config.h"

typedef struct __OLED_Handle_Type{
    /* driver types announced the way we explain the handle */
    OLED_Driver_Type        stored_handle_type;
    /* handle data types here */
    OLED_Handle_Private     private_handle;
}OLED_Handle;

/*
    oled_init_hardiic_handle registers the hardiic commnications
handle: 
    Pointer to an OLED_Handle structure that represents the handle 
    for the OLED display, used for managing 
    and controlling the OLED device.
    programmers should pass a blank one!

config: 
    Pointer to an OLED_HARD_IIC_Private_Config structure 
    that contains the configuration settings 
    for initializing the hardware interface, 
    typically related to the I2C communication 
    parameters for the OLED display.
*/

void oled_init_hardiic_handle(
    OLED_Handle* handle, 
    OLED_HARD_IIC_Private_Config* config);

void oled_init_softiic_handle(
    OLED_Handle* handle,
    OLED_SOFT_IIC_Private_Config* config
);

void oled_init_softspi_handle(
    OLED_Handle* handle,
    OLED_SOFT_SPI_Private_Config* config
);

void oled_init_hardspi_handle(
    OLED_Handle* handle,
    OLED_HARD_SPI_Private_Config* config
);

void oled_helper_clear_frame(OLED_Handle* handle);

void oled_helper_update(OLED_Handle* handle);

void oled_helper_setpixel(OLED_Handle* handle, uint16_t x, uint16_t y);

void oled_helper_clear_area(OLED_Handle* handle, 
        uint16_t x, uint16_t y, uint16_t width, uint16_t height);

void oled_helper_update_area(OLED_Handle* handle, 
        uint16_t x, uint16_t y, uint16_t width, uint16_t height);

void oled_helper_reverse(OLED_Handle* handle);

void oled_helper_reversearea(OLED_Handle* handle, 
        uint16_t x, uint16_t y, uint16_t width, uint16_t height);

void oled_helper_draw_area(OLED_Handle* handle, 
        uint16_t x, uint16_t y, uint16_t width, 
        uint16_t height, uint8_t* sources);

uint8_t     oled_support_rgb(OLED_Handle* handle);
uint16_t    oled_width(OLED_Handle* handle);
uint16_t    oled_height(OLED_Handle* handle);

// open close_device
void        open_oled(OLED_Handle* handle);
void        close_oled(OLED_Handle* handle);

// property setter
void        set_property_oled(OLED_Handle* handle, void* data, char* property);

#endif