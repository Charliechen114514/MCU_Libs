#ifndef CCGraphic_Size_H
#define CCGraphic_Size_H
#include "Graphic/CCGraphic_common.h"

typedef struct __CCGraphic_Size{
    SizeBaseType    width;
    SizeBaseType    height;
}CCGraphic_Size;

void CCGraphicWidget_initSize(
    CCGraphic_Size* size, 
    SizeBaseType    width,
    SizeBaseType    height);

#endif