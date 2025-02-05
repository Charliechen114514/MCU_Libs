#include "OLED/Driver/oled_base_driver.h"

void test_set_pixel(OLED_Handle* handle)
{
    for(uint8_t i = 0; i < 20; i++)
        oled_helper_setpixel(handle,2 * i, i);
    oled_helper_update(handle);
}

void test_set_pixel_line(
    OLED_Handle* handle, uint8_t xoffset, uint8_t y_offset)
{
    for(uint8_t i = 0; i < 20; i++)
        oled_helper_setpixel(handle,xoffset * i, y_offset * i);
    oled_helper_update(handle);
}

void test_clear(OLED_Handle* handle)
{
    oled_helper_clear_frame(handle);
    oled_helper_update(handle);
}