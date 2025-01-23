#include "Graphic/base/CCGraphic_Circle/CCGraphic_Circle.h"
#include "Graphic/CCGraphic_device_adapter.h"
#include "Graphic/common/CCGraphic_Utils.h"

void CCGraphic_init_circle(
    CCGraphic_Circle* circle, CCGraphic_Point c, uint8_t radius)
{
    circle->center = c;
    circle->radius = radius;
}
void CCGraphic_draw_circle(
    CCDeviceHandler* handler, CCGraphic_Circle* circle)
{
	/*参考文档：https://www.cs.montana.edu/courses/spring2009/425/dslectures/Bresenham.pdf*/
	/*参考教程：https://www.bilibili.com/video/BV1VM4y1u7wJ*/
    CCGraphic_Point p;
    int16_t d = 1 - circle->radius;
    int16_t x = 0;
    int16_t y = circle->radius;

#define DRAW_OFFSET_POINT(point, offsetx, offsety) \
    do { \
        point.x = circle->center.x + (offsetx); \
        point.y = circle->center.y + (offsety); \
        CCGraphic_draw_point(handler, &point);}while(0)\

    DRAW_OFFSET_POINT(p, x, y);
    DRAW_OFFSET_POINT(p, -x, -y);
    DRAW_OFFSET_POINT(p, y, x);
    DRAW_OFFSET_POINT(p, -y, -x);

    while(x < y)
    {
        x++;
        if(d < 0){ d += 2 * x + 1;}
        else {y--; d += 2 * (x - y) + 1;}
        DRAW_OFFSET_POINT(p, x, y);
        DRAW_OFFSET_POINT(p, y, x);
        DRAW_OFFSET_POINT(p, -x, -y);
        DRAW_OFFSET_POINT(p, -y, -x);
        DRAW_OFFSET_POINT(p, x, -y);
        DRAW_OFFSET_POINT(p, y, -x);
        DRAW_OFFSET_POINT(p, -x, y);
        DRAW_OFFSET_POINT(p, -y, x);            
    }
}

void CCGraphic_drawfilled_circle(CCDeviceHandler* handler, CCGraphic_Circle* circle)
{
    
}