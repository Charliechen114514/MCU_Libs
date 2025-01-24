#include "OLED/Driver/oled_base_driver.h"

void test_set_pixel(OLED_Handle* handle)
{
    for(uint8_t i = 0; i < 20; i++)
        oled_helper_setpixel(handle, i, 2 * i);
    oled_helper_update(handle);
}