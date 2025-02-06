#ifndef __CCGraphic_Point_H
#define __CCGraphic_Point_H
#include "Graphic/base/CCGraphic_Base.h"
/*
    x:  The x-coordinate of the point
    y:  The y-coordinate of the point
    operations: 
        An instance of CCGraphic_BaseOperations that 
        stores operations or behaviors related to the point, 
        likely used for drawing or other graphical manipulations.
*/
typedef struct __CCGraphic_Point{
    PointBaseType                     x;
    PointBaseType                     y;
}CCGraphic_Point;

void CCGraphic_init_point(CCGraphic_Point* point, 
        PointBaseType x, PointBaseType y);
void CCGraphic_draw_point(CCDeviceHandler* handler, CCGraphic_Point* point);

#endif