#include "Test/GraphicTest/graphic_test.h"
#include "Graphic/fast_setup/fast_setup.h"


#ifdef USE_SOFTIIC_PROTOCOL
void on_test_init_softiic_oled(CCDeviceHandler* device)
{
    oled_soft_iic_setup(device);
}
#endif

#ifdef USE_HARDIIC_PROTOCOL
void on_test_init_hardiic_oled(CCDeviceHandler* device)
{
    oled_hard_iic_setup(device);
}
#endif

#ifdef USE_SOFTSPI_PROTOCOL
void on_test_init_softspi_oled(CCDeviceHandler* device)
{
    oled_soft_spi_setup(device);
}
#endif

#ifdef USE_HARDSPI_PROTOCOL
void on_test_init_hardspi_oled(CCDeviceHandler* device)
{
    oled_hard_spi_setup(device);
}
#endif