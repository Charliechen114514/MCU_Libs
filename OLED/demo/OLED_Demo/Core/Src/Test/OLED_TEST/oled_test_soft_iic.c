#include "Test/OLED_TEST/oled_test.h"
#include "OLED/Driver/soft_iic/soft_iic.h"
/* configs should be in persist way */
OLED_SOFT_IIC_Private_Config config;
OLED_GPIOPack sda;
OLED_GPIOPack scl;

void user_init_soft_iic_oled_handle(OLED_Handle* handle)
{
    sda.pin     = PIN_SDA;
    sda.port    = PORT_SDA;
    scl.pin     = PIN_SCL;
    scl.port    = PORT_SCL;
    oled_bind_softiic_handle(
        &config, &sda, &scl, 
        0x78, HAL_MAX_DELAY
    );
    oled_init_softiic_handle(handle, &config);
}