#ifndef CCGraphic_Rectangle_H
#define CCGraphic_Rectangle_H

#include "Graphic/base/CCGraphic_Base.h"
#include "Graphic/base/CCGraphic_Point/CCGraphic_Point.h"

typedef struct __CCGraphic_Rectangle{
    CCGraphic_Point         top_left;
    CCGraphic_Point         bottom_right;
}CCGraphic_Rectangle;

void CCGraphic_init_rectangle(
    CCGraphic_Rectangle* rect, CCGraphic_Point tl, CCGraphic_Point br);

void CCGraphic_draw_rectangle(
    CCDeviceHandler* handler, CCGraphic_Rectangle* rect);

void CCGraphic_drawfilled_rectangle(
    CCDeviceHandler* handler, CCGraphic_Rectangle* rect);



#endif