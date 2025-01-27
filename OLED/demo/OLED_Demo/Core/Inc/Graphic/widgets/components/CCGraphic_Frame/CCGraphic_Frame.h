#ifndef CCGraphic_Frame_H
#define CCGraphic_Frame_H
#include "Graphic/widgets/common/CCGraphic_WidgetBase.h"
#include "Graphic/base/CCGraphic_Rectangle/CCGraphic_Rectangle.h"

typedef struct {
    CCGraphicWidgetCommonOperation  operation;
}CCGraphic_Frame_SupportiveOperation;


typedef struct __CCGraphic_Frame
{
    CCGraphic_Rectangle rect;
    CCDeviceHandler*    handler;
    SizeBaseType        line_width;
    CCGraphic_Frame_SupportiveOperation operation;
}CCGraphic_Frame;

void CCGraphic_createDeviceFrame(
    CCGraphic_Frame* frame, CCDeviceHandler* handler,
    SizeBaseType    line_width, 
    SizeBaseType margin_width, SizeBaseType margin_height);



#endif

