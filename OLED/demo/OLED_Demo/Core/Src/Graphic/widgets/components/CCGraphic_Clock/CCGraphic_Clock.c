#include "Graphic/widgets/components/CCGraphic_Clock/CCGraphic_Clock.h"
#include "Graphic/widgets/components/CCGraphic_Clock/CCGraphic_Clock_Settings.h"
#include "Graphic/widgets/base/CCGraphic_TextItem/CCGraphic_TextItem.h"
#include "Graphic/CCGraphic_device_adapter.h"
#include <string.h>
#include <math.h>
static char* MAJOR_SHOW[4] = {"12", "3", "6", "9"};
static CCGraphic_AsciiTextItem text_items[4];

static void __pvt_draw_tickal(
    CCDeviceHandler* h, CCGraphic_Point center, int angle, PointBaseType radius, PointBaseType length)
{
    const double K = angle * (3.1415926535L) / 180;
    const double xK = cos(K);
    const double yK = sin(K);
    CCGraphic_Point p;
    for(PointBaseType i = radius - length;i < radius; i++)
    {
        p.x = center.x + xK * i;
        p.y = center.y + yK * i;
        CCGraphic_draw_point(h, &p);
    }    
}


static void __draw_angle_line(CCDeviceHandler* h, CCGraphic_Point center, int angle, PointBaseType length)
{
    const double K = angle * (3.1415926535L) / 180;
    const double xK = cos(K);
    const double yK = sin(K);
    CCGraphic_Point p;
    for(PointBaseType i = 0;i < length; i++)
    {
        p.x = center.x + xK * i;
        p.y = center.y + yK * i;
        CCGraphic_draw_point(h, &p);
    }
}


static void __pvt_clean(CCGrapghic_Clock* clk){
    CCGraphic_Circle circle = clk->handling_circle;
    clk->borrowed_device->operations.clearArea_function(
        clk->borrowed_device, 
        circle.center.x - circle.radius,
        circle.center.y - circle.radius,
        2*circle.radius,
        2*circle.radius
    );
}

static void __pvt_draw(CCGrapghic_Clock* clk)
{
    // draw main
    CCGraphic_draw_circle(clk->borrowed_device, &clk->handling_circle);

    // draw text
    for(uint8_t i = 0; i < 4; i++)
    {
        CCGraphicWidget_drawAsciiTextItem(
            clk->borrowed_device, &text_items[i]);
        
    }

    // draw centors
    CCGraphic_Circle circle;
    circle.center = clk->handling_circle.center;
    circle.radius = CLOCK_CENTER_CIRCLE_R;
    CCGraphic_drawfilled_circle(clk->borrowed_device, &circle);
    const uint16_t sec_len = clk->handling_circle.radius - 2;
    const uint16_t min_len = sec_len * 0.9;
    const uint16_t hour_len = sec_len * 0.6;
    // draw tickel
    __draw_angle_line(clk->borrowed_device, circle.center, clk->current_time.second * 6 - 90, sec_len);
    __draw_angle_line(clk->borrowed_device, circle.center, clk->current_time.minutes * 6 - 90, min_len);
    __draw_angle_line(clk->borrowed_device, circle.center, clk->current_time.hour * 30 - 90, hour_len);

    // draw_tickels
    for(uint16_t i = 0; i < 12; i++){
        if(i % 3 == 0) continue;
        __pvt_draw_tickal(clk->borrowed_device, circle.center, 30 * i, clk->handling_circle.radius, 3);
    }

}

static void __pvt_update(CCGrapghic_Clock* clk){
    CCGraphic_Circle circle = clk->handling_circle;
    clk->borrowed_device->operations.updateArea_function(
        clk->borrowed_device, 
        circle.center.x - circle.radius,
        circle.center.y - circle.radius,
        2*circle.radius,
        2*circle.radius
    );    
}

static void __on_reinit_text_items_locations(CCGrapghic_Clock* clk)
{
    CCGraphic_Point center = clk->handling_circle.center;
    CCGraphic_Size  font_size = __fetch_font_size(CLOCK_TEXT_SIZE);
    PointBaseType   radius = clk->handling_circle.radius; 
    const uint8_t   equal_for_font_offset_w = font_size.width / 2;
    const uint8_t   equal_for_font_offset_h = font_size.height / 2;

    const CCGraphic_Point tl_points[4] = {
        {   center.x - equal_for_font_offset_w * strlen(MAJOR_SHOW[0]), 
            center.y - radius + equal_for_font_offset_h},
        {   center.x + radius - 2.2 * equal_for_font_offset_w,
            center.y - equal_for_font_offset_h},
        {   center.x - equal_for_font_offset_w,
            center.y + radius - 2.2 * equal_for_font_offset_h},
        {   center.x - radius + equal_for_font_offset_w,
            center.y - equal_for_font_offset_h}
    };

    // top one
    for(uint8_t i = 0; i < 4; i++){
        CCGraphicWidget_init_AsciiTextItem(&text_items[i],
        tl_points[i], font_size, CLOCK_TEXT_SIZE);
        if(i == 0) text_items->TexthandleSize.width = 4 * font_size.width;
        else text_items->TexthandleSize.width = 2 * font_size.width;
        CCGraphicWidget_AsciiTextItem_setAsciiText(&text_items[i], MAJOR_SHOW[i]);
        text_items[i].req_update = 0;
    }
}

static void __update_time(CCGrapghic_Clock* clk, CCGraphic_Time* time)
{
    clk->current_time = *time;
    __pvt_clean(clk);
    __pvt_draw(clk);
    __pvt_update(clk);
}

void initCCGraphic_Clock(
    CCGrapghic_Clock* clk,CCDeviceHandler* device,  CCGraphic_Circle* circle)
{
    clk->handling_circle = *circle;
    clk->borrowed_device = device;
    clk->major_tickel_length    = CLOCK_MAJOR_TICKEL_LENGTH;
    clk->minor_tickel_length    = CLOCK_MINOR_TICKEL_LENGTH;
    clk->current_time.hour = 0;
    clk->current_time.minutes = 0;
    clk->current_time.hour = 0;
    clk->op.operations.show = (Show)__pvt_draw;
    clk->op.operations.hide = (Hide)__pvt_clean;
    clk->op.operations.update = (Update)__pvt_update;
    clk->op.updateTime = __update_time;
    __on_reinit_text_items_locations(clk);
}


