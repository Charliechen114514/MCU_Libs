#include "Graphic/widgets/components/CCGraphic_Frame/CCGraphic_Frame.h"
#include "Graphic/widgets/common/CCGraphic_WidgetBase.h"
#include "Graphic/CCGraphic_device_adapter.h"
static void __pvt_update(CCGraphic_Frame* frame)
{
    frame->handler->operations.update_device_function(frame->handler);
}

static void __pvt_hide(CCGraphic_Frame* frame)
{
    // clear left
    frame->handler->operations.clearArea_function(
        frame->handler, frame->rect.top_left.x, frame->rect.top_left.y,
        frame->line_width + 1, frame->rect.bottom_right.y - frame->rect.top_left.y
    );
    // clear top
    frame->handler->operations.clearArea_function(
        frame->handler, frame->rect.top_left.x, frame->rect.top_left.y,
        frame->rect.bottom_right.x - frame->rect.top_left.x, frame->line_width + 1
    ); 
    // clear right
    frame->handler->operations.clearArea_function(
        frame->handler, frame->rect.bottom_right.x - frame->line_width, frame->rect.top_left.y,
        frame->line_width, frame->rect.bottom_right.y - frame->rect.top_left.y + 1 
    );  
    // clear bottom
    frame->handler->operations.clearArea_function(
        frame->handler, frame->rect.top_left.x, frame->rect.bottom_right.y - frame->line_width,
        frame->rect.bottom_right.x - frame->rect.top_left.x + 1, frame->line_width 
    );     
    __pvt_update(frame);
}

static void __pvt_show(CCGraphic_Frame* frame)
{
    // clear left
    CCGraphic_Rectangle tmp;
    tmp = frame->rect;

    for(SizeBaseType i = 0; i < frame->line_width; i++)
    {
        tmp.top_left.x +=1;
        tmp.top_left.y +=1;
        tmp.bottom_right.x -=1;
        tmp.bottom_right.y -=1;
        CCGraphic_draw_rectangle(frame->handler, &tmp);
    }
    __pvt_update(frame);
}

void CCGraphic_createDeviceFrame(
    CCGraphic_Frame* frame, CCDeviceHandler* handler, SizeBaseType line_width, 
    SizeBaseType margin_width, SizeBaseType margin_height)
{
    frame->handler = handler;
    CCGraphic_Size  size = CCGraphicWidget_MaxAcceptable_Size(handler);

    if (margin_width + line_width > size.width / 2 || 
        margin_height + line_width> size.height / 2)
    {
        return;
    }
    
    frame->line_width = line_width;

    frame->rect.top_left.x = margin_width;
    frame->rect.top_left.y = margin_height;

    frame->rect.bottom_right.x = size.width     - margin_width;
    frame->rect.bottom_right.y = size.height    -  margin_height;
    frame->operation.operation.update = (Update)__pvt_update;
    frame->operation.operation.show = (Show)__pvt_show;
    frame->operation.operation.hide = (Hide)__pvt_hide;
}

