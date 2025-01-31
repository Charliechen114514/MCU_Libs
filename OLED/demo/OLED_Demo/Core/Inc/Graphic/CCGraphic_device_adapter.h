#ifndef CCGraphic_device_adapter_H
#define CCGraphic_device_adapter_H

#include "Graphic/CCGraphic_common.h"

typedef enum{
    OLED_Type
}CCDeviceType;

typedef void*   CCDeviceRawHandle;
typedef void*   CCDeviceRawHandleConfig;

typedef void(*Initer)(
    CCDeviceHandler* handler, 
    CCDeviceRawHandleConfig config);

typedef void(*ClearDevice)(
    CCDeviceHandler* handler);

typedef void(*UpdateDevice)(
    CCDeviceHandler* handler);

typedef void(*ReverseDevice)(
    CCDeviceHandler* handler);

typedef void(*SetPixel)(
    CCDeviceHandler* handler, uint16_t x, uint16_t y);

typedef void(*DrawArea)(
    CCDeviceHandler* handler, 
    uint16_t x, uint16_t y, 
    uint16_t width, uint16_t height, uint8_t* sources
);

typedef void(*AreaOperation)(
    CCDeviceHandler* handler, 
    uint16_t x, uint16_t y, 
    uint16_t width, uint16_t height
);

typedef enum{
    CommonProperty_WIDTH,
    CommonProperty_HEIGHT,
    CommonProperty_SUPPORT_RGB
}CommonProperty;

typedef void(*FetchProperty)(CCDeviceHandler*, void*, CommonProperty p);

typedef struct __DeviceOperations 
{
    Initer          init_function;
    ClearDevice     clear_device_function;
    UpdateDevice    update_device_function;
    SetPixel        set_pixel_device_function;
    ReverseDevice   reverse_device_function;
    DrawArea        draw_area_device_function;
    AreaOperation   clearArea_function;
    AreaOperation   updateArea_function;
    AreaOperation   reverseArea_function;
    FetchProperty   property_function;
}CCDeviceOperations;

typedef struct __DeviceProperty
{
    /* device type */
    CCDeviceType            device_type;
    /* device raw data handle */
    CCDeviceRawHandle       handle;
    /* device functions */
    CCDeviceOperations      operations;
}CCDeviceHandler;

/* calling this is not encouraged! */
void __register_paintdevice(
    CCDeviceHandler* blank_handler, 
    CCDeviceRawHandle raw_handle, 
    CCDeviceRawHandleConfig config, 
    CCDeviceType type);

#define register_oled_paintdevice(handler, raw, config) \
    __register_paintdevice(handler, raw, config, OLED_Type)

/* device delay */
void __device_delay(uint16_t    sec);
void __device_delayclock_enabled();
void __device_usdelay(uint16_t  usec);

#endif


