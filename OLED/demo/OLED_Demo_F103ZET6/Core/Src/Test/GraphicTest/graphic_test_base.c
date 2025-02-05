#include "Test/GraphicTest/graphic_test.h"
#include "Graphic/base/CCGraphic_Point/CCGraphic_Point.h"
#include "Graphic/base/CCGraphic_Line/CCGraphic_Line.h"
#include "Graphic/base/CCGraphic_Circle/CCGraphic_Circle.h"
#include "Graphic/base/CCGraphic_Rectangle/CCGraphic_Rectangle.h"
#include "Graphic/base/CCGraphic_Triangle/CCGraphic_Triangle.h"
#include "Graphic/base/CCGraphic_Ellipse/CCGraphic_Ellipse.h"
#include "Graphic/base/CCGraphic_Arc/CCGraphic_Arc.h"

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
    CCGraphic_init_circle(&c, p, 10);
    CCGraphic_drawfilled_circle(handle, &c);

    p.x = 10;
    p.y = 32;
    CCGraphic_init_circle(&c, p, 5);
    CCGraphic_draw_circle(handle, &c);
    handle->operations.update_device_function(handle);
}

void on_test_draw_rectangle(CCDeviceHandler* handle)
{
    CCGraphic_Rectangle rect;
    CCGraphic_Point     tl;
    CCGraphic_Point     br;

    tl.x = 5;
    tl.y = 5;

    br.x = 20;
    br.y = 20;

    CCGraphic_init_rectangle(&rect, tl, br);
    CCGraphic_draw_rectangle(handle, &rect);

    tl.x = 21;
    tl.y = 21;

    br.x = 50;
    br.y = 50;    
    CCGraphic_init_rectangle(&rect, tl, br);
    CCGraphic_drawfilled_rectangle(handle, &rect);
    handle->operations.update_device_function(handle);
}

void on_test_draw_triangle(CCDeviceHandler* handle)
{
    CCGraphic_Triangle  triangle;
    CCGraphic_Point     p1;
    CCGraphic_Point     p2;
    CCGraphic_Point     p3;

    p1.x = 10;
    p1.y = 10;

    p2.x = 15;
    p2.y = 5;

    p3.x = 80;
    p3.y = 40;

    CCGraphic_init_triangle(&triangle, p1, p3, p2);
    CCGraphic_drawfilled_triangle(handle, &triangle);
    handle->operations.update_device_function(handle);
}

void on_test_draw_ellipse(CCDeviceHandler* handle)
{
    CCGraphic_Ellipse ellipse;
    CCGraphic_Point p;
    p.x = 20;
    p.y = 32;

    CCGraphic_init_ellipse(&ellipse, p, 10, 30);
    CCGraphic_draw_ellipse(handle, &ellipse);

    p.x = 80;
    p.y = 32;
    CCGraphic_init_ellipse(&ellipse, p, 40, 30);
    CCGraphic_drawfilled_ellipse(handle, &ellipse);
    handle->operations.update_device_function(handle);
}

void on_test_draw_arc(CCDeviceHandler* handle)
{
    CCGraphic_Arc arc;
    CCGraphic_Point p;
    p.x = 64;
    p.y = 32;
    CCGraphic_init_CCGraphic_Arc(&arc, p, 40, -20, 40);
    CCGraphic_draw_arc(handle, &arc);
    handle->operations.update_device_function(handle);
}

