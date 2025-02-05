
#include "Graphic/widgets/common/CCGraphic_WidgetBase.h"
#include "Graphic/CCGraphic_device_adapter.h"

CCGraphic_Size  CCGraphicWidget_MaxAcceptable_Size(
    CCDeviceHandler* device_handle
)
{
    CCGraphic_Size size;
    int16_t device_width = 0;
    device_handle->operations.property_function(
        device_handle, &device_width, CommonProperty_WIDTH
    );
    int16_t device_height = 0;
    device_handle->operations.property_function(
        device_handle, &device_height, CommonProperty_HEIGHT
    );
    size.height = device_height;
    size.width = device_width;
    return size;
}