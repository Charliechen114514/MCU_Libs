#include "Graphic/device_adapter/CCGraphic_device_oled_adapter.h"
#include "Graphic/CCGraphic_device_adapter.h"


void __register_paintdevice(
    CCDeviceHandler* blank_handler, 
    CCDeviceRawHandle raw_handle, 
    CCDeviceRawHandleConfig config, 
    CCDeviceType type)
{
    blank_handler->handle = raw_handle;
    blank_handler->device_type = type;
    switch(type)
    {
        case OLED_Type:
        {
            blank_handler->operations.init_function = 
                (Initer)init_device_oled;
            blank_handler->operations.clear_device_function =
                clear_device_oled;
            blank_handler->operations.set_pixel_device_function = 
                setpixel_device_oled;
            blank_handler->operations.update_device_function = 
                update_device_oled;
            blank_handler->operations.clearArea_function =
                clear_area_device_oled;
            blank_handler->operations.reverse_device_function =
                reverse_device_oled;
            blank_handler->operations.reverseArea_function = 
                reversearea_device_oled;
            blank_handler->operations.updateArea_function = 
                update_area_device_oled;
            blank_handler->operations.draw_area_device_function =
                draw_area_device_oled;
            blank_handler->operations.property_function = 
                property_fetcher_device_oled;
        }
        break;
    }
    blank_handler->operations.init_function(blank_handler, config);
}