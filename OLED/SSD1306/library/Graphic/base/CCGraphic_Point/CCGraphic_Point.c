#include "Graphic/base/CCGraphic_Point/CCGraphic_Point.h"
#include "Graphic/CCGraphic_device_adapter.h"

void CCGraphic_draw_point(
    CCDeviceHandler* handler, CCGraphic_Point* point)
{
    handler->operations.set_pixel_device_function(
        handler, point->x, point->y);
}

void CCGraphic_init_point(CCGraphic_Point* point, 
    PointBaseType x, PointBaseType y)
{
    point->x = x;
    point->y = y;
}
