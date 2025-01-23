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

typedef void(*SetPixel)(
    CCDeviceHandler* handler, uint16_t x, uint16_t y);

typedef struct __DeviceOperations 
{
    Initer          init_function;
    ClearDevice     clear_device_function;
    UpdateDevice    update_device_function;
    SetPixel        set_pixel_device_function;
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



#endif


