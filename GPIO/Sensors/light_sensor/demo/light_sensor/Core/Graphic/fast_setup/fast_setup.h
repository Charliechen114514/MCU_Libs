#ifndef FAST_SETUP_H
#define FAST_SETUP_H
#include "Graphic/CCGraphic_common.h"
/*
    convinient setup for global drawing devices
    provided a blank device to init the device
*/

void oled_soft_iic_setup(CCDeviceHandler* device);
void oled_hard_iic_setup(CCDeviceHandler* device);
void oled_soft_spi_setup(CCDeviceHandler* device);
void oled_hard_spi_setup(CCDeviceHandler* device);

#endif