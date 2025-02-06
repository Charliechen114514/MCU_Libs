#include "Graphic/widgets/common/CCGraphic_Size/CCGraphic_Size.h"
#include "Graphic/CCGraphic_device_adapter.h"

void CCGraphicWidget_initSize(
    CCGraphic_Size* size, 
    SizeBaseType    width,
    SizeBaseType    height)
{
    size->height = height;
    size->width  = width;
}


