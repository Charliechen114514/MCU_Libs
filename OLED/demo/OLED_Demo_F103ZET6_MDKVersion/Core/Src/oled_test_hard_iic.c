#ifdef USE_HARDIIC_PROTOCOL

#include "OLED/Driver/hard_iic/hard_iic.h"
#include "Test/OLED_TEST/oled_test.h"
#include "i2c.h"
/* configs should be in persist way */
OLED_HARD_IIC_Private_Config config;

void user_init_hard_iic_oled_handle(OLED_Handle* handle)
{
    bind_hardiic_handle(&config, &hi2c1, 0x78, HAL_MAX_DELAY);
    oled_init_hardiic_handle(handle, &config);
}

#endif