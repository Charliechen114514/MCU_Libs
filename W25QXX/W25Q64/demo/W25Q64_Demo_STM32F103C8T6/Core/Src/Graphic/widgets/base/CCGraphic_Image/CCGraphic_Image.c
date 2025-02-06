#include "Graphic/widgets/base/CCGraphic_Image/CCGraphic_Image.h"
#include "Graphic/CCGraphic_device_adapter.h"
void CCGraphicWidget_init_image(
    CCGraphic_Image*    image,
    CCGraphic_Point     tl_point,
    CCGraphic_Size      image_size,
    uint8_t*      sources_register
)
{
    image->image_size = image_size;
    image->point = tl_point;
    image->sources_register = sources_register;
}

void CCGraphicWidget_draw_image(
    CCDeviceHandler*    handler,
    CCGraphic_Image*    image
)
{
    if(!image->sources_register) return;
    handler->operations.draw_area_device_function(
        handler, image->point.x, image->point.y,
        image->image_size.width, image->image_size.height, image->sources_register
    );
}