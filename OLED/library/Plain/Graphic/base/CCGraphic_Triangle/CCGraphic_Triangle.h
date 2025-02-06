#ifndef CCGraphic_Triangle_H
#define CCGraphic_Triangle_H

#include "Graphic/base/CCGraphic_Base.h"
#include "Graphic/base/CCGraphic_Point/CCGraphic_Point.h"

typedef struct __CCGraphic_Triangle
{
    CCGraphic_Point     p1;
    CCGraphic_Point     p2;
    CCGraphic_Point     p3;
}CCGraphic_Triangle;


void CCGraphic_init_triangle(
    CCGraphic_Triangle* triangle, 
    CCGraphic_Point     p1,
    CCGraphic_Point     p2,
    CCGraphic_Point     p3
);

void CCGraphic_draw_triangle(
    CCDeviceHandler*    handle,
    CCGraphic_Triangle* triangle
);

void CCGraphic_drawfilled_triangle(
    CCDeviceHandler*    handle,
    CCGraphic_Triangle* triangle
);

#endif