#include "Graphic/base/CCGraphic_Rectangle/CCGraphic_Rectangle.h"
#include "Graphic/base/CCGraphic_Line/CCGraphic_Line.h"

void CCGraphic_init_rectangle(
    CCGraphic_Rectangle* rect, CCGraphic_Point tl, CCGraphic_Point br)
{
    rect->top_left = tl;
    rect->bottom_right = br;
}

void CCGraphic_draw_rectangle(
    CCDeviceHandler* handler, CCGraphic_Rectangle* rect)
{
    CCGraphic_Line l;
    CCGraphic_Point tmp;

    // draw top, set tmp as the top_right
    tmp.x = rect->bottom_right.y;
    tmp.y = rect->top_left.y;
    CCGraphic_init_line(&l, rect->top_left, tmp);
    CCGraphic_draw_line(handler, &l);

    // draw right
    CCGraphic_init_line(&l, tmp, rect->bottom_right);
    CCGraphic_draw_line(handler, &l);    

    // draw left
    tmp.x = rect->top_left.x;
    tmp.y = rect->bottom_right.y;
    CCGraphic_init_line(&l, rect->top_left, tmp);
    CCGraphic_draw_line(handler, &l);      

    // draw bottom
    CCGraphic_init_line(&l,tmp, rect->bottom_right);
    CCGraphic_draw_line(handler, &l);      
}


void CCGraphic_drawfilled_rectangle(
    CCDeviceHandler* handler, CCGraphic_Rectangle* rect)
{
    CCGraphic_Point p;
    for(PointBaseType 
        iterate_x = rect->top_left.x; 
        iterate_x <= rect->bottom_right.x; iterate_x++)
    {
        p.x = iterate_x;
        for(PointBaseType 
            iterate_y = rect->top_left.y; 
            iterate_y <= rect->bottom_right.y; iterate_y++)
        {
            p.y = iterate_y;
            CCGraphic_draw_point(handler, &p);
        }        
    }
}


