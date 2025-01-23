#include "Graphic/base/CCGraphic_Line/CCGraphic_Line.h"
#include "Graphic/CCGraphic_device_adapter.h"
#include "Graphic/common/CCGraphic_Utils.h"


/*
    draw the lines that matches the equal x
*/
static void __on_handle_vertical_line(
    CCDeviceHandler* handler,
    CCGraphic_Line* line
)
{
    PointBaseType max_y = max_uint16(line->p_left.y, line->p_right.y);
    PointBaseType min_y = min_uint16(line->p_left.y, line->p_right.y);
    CCGraphic_Point p;
    p.x = line->p_left.x;
    for(PointBaseType i = min_y; i <= max_y; i++)
    {
        p.y = i;
        CCGraphic_draw_point(handler, &p);
    }
}

static void __on_handle_horizental_line(
    CCDeviceHandler* handler,
    CCGraphic_Line* line
)
{
    PointBaseType max_x = max_uint16(line->p_left.x, line->p_right.x);
    PointBaseType min_x = min_uint16(line->p_left.x, line->p_right.x);
    CCGraphic_Point p;
    p.y = line->p_left.y;
    for(PointBaseType i = min_x; i <= max_x; i++)
    {
        p.x = i;
        CCGraphic_draw_point(handler, &p);
    }
}

void CCGraphic_draw_line(CCDeviceHandler* handler, CCGraphic_Line* line)
{
    // test if the vertical
    if(line->p_left.x == line->p_right.x) 
        return __on_handle_vertical_line(handler, line);   
    if(line->p_left.y == line->p_right.y)
        return __on_handle_horizental_line(handler, line);
    
	/*https://www.cs.montana.edu/courses/spring2009/425/dslectures/Bresenham.pdf*/
	/*https://www.bilibili.com/video/BV1364y1d7Lo*/
    /* follows are the implementations */

    uint8_t y_map_flag  = 0;
    uint8_t xy_map_flag = 0;

    CCGraphic_Line l = *line;

    if(line->p_left.x > line->p_right.x)
    {
        swap_uint16(&(l.p_left.x), &(l.p_right.x));
        swap_uint16(&(l.p_left.y), &(l.p_right.y));
    }

    if(line->p_left.y > line->p_right.y)
    {
        l.p_left.y = -l.p_left.y;
        l.p_right.y = -l.p_right.y;

        y_map_flag = 1;
    }

    if( l.p_right.y - l.p_left.y > 
        l.p_right.x - l.p_left.x)
    {
        swap_uint16(&(l.p_left.x), &(l.p_left.y));
        swap_uint16(&(l.p_right.x), &(l.p_right.y));
        xy_map_flag = 1;
    }

    const int16_t dx = l.p_right.x - l.p_left.x;
    const int16_t dy = l.p_right.y - l.p_left.y;
    const int16_t incrE = 2 * dy;
	const int16_t incrNE = 2 * (dy - dx);
	int16_t d = 2 * dy - dx;
	int16_t x = l.p_left.x;
	int16_t y = l.p_left.y;
    CCGraphic_Point p;

    if(y_map_flag && xy_map_flag){
        p.x = y;
        p.y = -x;    
    }
    else if(y_map_flag){
        p.x = x;
        p.y = -y;
    }
    else if(xy_map_flag){
        p.x = y;
        p.y = x;        
    }else{
        p.x = x;
        p.y = y;
    }

    CCGraphic_draw_point(handler, &p);

    while(x < l.p_right.x)
    {
        x++;
        if(d < 0) {
            d+= incrE;
        }
        else {
            y++; 
            d+=incrNE;
        }

        if(y_map_flag && xy_map_flag){
            p.x = y;
            p.y = -x;    
        }
        else if(y_map_flag){
            p.x = x;
            p.y = -y;
        }
        else if(xy_map_flag){
            p.x = y;
            p.y = x;        
        }else{
            p.x = x;
            p.y = y;
        }

        CCGraphic_draw_point(handler, &p);
    }
}

void CCGraphic_init_line(   CCGraphic_Line* line, 
                            CCGraphic_Point pl, 
                            CCGraphic_Point pr)
{
    line->p_left = pl;
    line->p_right = pr;
}
