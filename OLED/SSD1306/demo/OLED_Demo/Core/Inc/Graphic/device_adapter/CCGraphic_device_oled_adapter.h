#ifndef CCGraphic_device_oled_adapter_H
#define CCGraphic_device_oled_adapter_H
#include "CCGraphic_device_adapter.h"
#include "OLED/Driver/oled_config.h"

/* functions are provided for oled device */
typedef struct {
    /* typed configs */
    void*               related_configs;
}CCGraphic_OLED_Config;

void init_device_oled(
    CCDeviceHandler* blank, CCGraphic_OLED_Config* onProvideConfigs);

void update_device_oled(CCDeviceHandler* handler);
void clear_device_oled(CCDeviceHandler* handler);
void setpixel_device_oled(CCDeviceHandler* handler, uint8_t x, uint8_t y);

#endif