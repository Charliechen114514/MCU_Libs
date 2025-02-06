#ifndef CCGraphic_Arc_H
#define CCGraphic_Arc_H
#include "Graphic/base/CCGraphic_Base.h"
#include "Graphic/base/CCGraphic_Point/CCGraphic_Point.h"

typedef struct __CCGraphic_Arc{
    CCGraphic_Point     center;
    PointBaseType       radius;
    int16_t             start_degree;
    int16_t             end_degree;
}CCGraphic_Arc;

void CCGraphic_init_CCGraphic_Arc(
    CCGraphic_Arc*      handle,
    CCGraphic_Point     center,
    PointBaseType       radius,
    int16_t             start_degree,
    int16_t             end_degree  
);

void CCGraphic_draw_arc(
    CCDeviceHandler* handler,
    CCGraphic_Arc* handle
);

void CCGraphic_drawfilled_arc(
    CCDeviceHandler* handler,
    CCGraphic_Arc* handle
);

#endif