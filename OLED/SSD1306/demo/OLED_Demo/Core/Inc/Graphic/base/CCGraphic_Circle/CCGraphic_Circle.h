#ifndef __CCGraphic_Circle_H
#define __CCGraphic_Circle_H
#include "Graphic/base/CCGraphic_Base.h"
#include "Graphic/base/CCGraphic_Point/CCGraphic_Point.h"

typedef struct __CCGraphic_Circle
{
    CCGraphic_Point         center;
    uint16_t                radius;
}CCGraphic_Circle;

void CCGraphic_init_circle(CCGraphic_Circle* circle, CCGraphic_Point c, uint8_t radius);
void CCGraphic_draw_circle(CCDeviceHandler* handler, CCGraphic_Circle* circle);
void CCGraphic_drawfilled_circle(CCDeviceHandler* handler, CCGraphic_Circle* circle);
#endif