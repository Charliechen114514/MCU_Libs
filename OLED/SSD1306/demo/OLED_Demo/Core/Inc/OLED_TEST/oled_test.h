#pragma once
#include "OLED/Driver/oled_base_driver.h"

/*
    init oled interface like
*/
void user_init_hard_iic_oled_handle(OLED_Handle* handle);
void user_init_soft_iic_oled_handle(OLED_Handle* handle);

void test_set_pixel(OLED_Handle* handle);



