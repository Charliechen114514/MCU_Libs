#include "GraphicTest/graphic_test.h"
#include "Graphic/base/CCGraphic_Point/CCGraphic_Point.h"
#include "Graphic/base/CCGraphic_Line/CCGraphic_Line.h"
#include "Graphic/base/CCGraphic_Circle/CCGraphic_Circle.h"
void on_test_draw_points(CCDeviceHandler* handle)
{
    CCGraphic_Point point;
    CCGraphic_init_point(&point, 0, 0);
    for(uint8_t i = 0; i < 20; i++)
    {
        point.x = i;
        point.y = i * 2;
        CCGraphic_draw_point(handle, &point);
    }
    handle->operations.update_device_function(handle);
}

void on_test_draw_line(CCDeviceHandler* handle)
{
    CCGraphic_Line  l;
    CCGraphic_Point pleft;
    CCGraphic_Point pright;
    // try vertical
    pleft.x     = 5;
    pleft.y     = 0;
    pright.x    = pleft.x;
    pright.y    = 63;

    CCGraphic_init_line(&l, pleft, pright);
    CCGraphic_draw_line(handle, &l);

    // try horizontal
    pleft.x     = 0;
    pleft.y     = 5;
    pright.x    = 120;
    pright.y    = pleft.y;

    CCGraphic_init_line(&l, pleft, pright);
    CCGraphic_draw_line(handle, &l);

    // try different
    pleft.x     = 0;
    pleft.y     = 10;
    pright.x    = 105;
    pright.y    = 63;

    CCGraphic_init_line(&l, pleft, pright);
    CCGraphic_draw_line(handle, &l);
    handle->operations.update_device_function(handle);
}

void on_test_draw_circle(CCDeviceHandler* handle)
{
    CCGraphic_Circle c;
    CCGraphic_Point p;
    p.x = 64;
    p.y = 32;
    CCGraphic_init_circle(&c, p, 20);
    CCGraphic_draw_circle(handle, &c);
    handle->operations.update_device_function(handle);
}