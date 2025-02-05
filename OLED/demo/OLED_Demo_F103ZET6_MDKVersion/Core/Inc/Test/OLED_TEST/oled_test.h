#pragma once
#include "OLED/Driver/oled_base_driver.h"

/*
    init oled interface like
*/
#ifdef USE_HARDIIC_PROTOCOL
void user_init_hard_iic_oled_handle(OLED_Handle* handle);
#endif

#ifdef USE_SOFTIIC_PROTOCOL
void user_init_soft_iic_oled_handle(OLED_Handle* handle);
#endif

#ifdef USE_HARDSPI_PROTOCOL
void user_init_hard_spi_oled_handle(OLED_Handle* handle);
#endif

#ifdef USE_SOFTSPI_PROTOCOL
void user_init_soft_spi_oled_handle(OLED_Handle* handle);
#endif

void test_set_pixel(OLED_Handle* handle);
void test_set_pixel_line(
    OLED_Handle* handle, uint8_t xoffset, uint8_t y_offset);

void test_clear(OLED_Handle* handle);