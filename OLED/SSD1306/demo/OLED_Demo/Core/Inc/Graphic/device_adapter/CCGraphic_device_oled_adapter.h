#ifndef CCGraphic_device_oled_adapter_H
#define CCGraphic_device_oled_adapter_H
#include "Graphic/CCGraphic_device_adapter.h"
#include "OLED/Driver/oled_config.h"

/* functions are provided for oled device */
typedef struct {
    OLED_Driver_Type    createType;
    /* typed configs */
    void*               related_configs;
}CCGraphic_OLED_Config;

/*
    firstly, you should submit a config with inited configs 
        using softiic or hardiic, then submit the configs type
*/
void init_device_oled(
    CCDeviceHandler* blank, CCGraphic_OLED_Config* onProvideConfigs);

void update_device_oled(CCDeviceHandler* handler);
void clear_device_oled(CCDeviceHandler* handler);
void setpixel_device_oled(CCDeviceHandler* handler, uint16_t x, uint16_t y);

void clear_area_device_oled(CCDeviceHandler* handler, 
        uint16_t x, uint16_t y, uint16_t width, uint16_t height);

void update_area_device_oled(CCDeviceHandler* handler, 
        uint16_t x, uint16_t y, uint16_t width, uint16_t height);

void reverse_device_oled(CCDeviceHandler* handler);
void reversearea_device_oled(CCDeviceHandler* handler, 
        uint16_t x, uint16_t y, uint16_t width, uint16_t height);

void draw_area_device_oled(
    CCDeviceHandler* handler, 
    uint16_t x, uint16_t y, 
    uint16_t width, uint16_t height, uint8_t* sources
);

void property_fetcher_device_oled(
    CCDeviceHandler* handler, void* getter, CommonProperty p
);

#endif