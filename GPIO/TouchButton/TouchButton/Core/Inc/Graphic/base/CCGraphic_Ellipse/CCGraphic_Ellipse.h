#ifndef CCGraphic_Ellipse_H
#define CCGraphic_Ellipse_H
#include "Graphic/base/CCGraphic_Base.h"
#include "Graphic/base/CCGraphic_Point/CCGraphic_Point.h"

typedef struct __CCGraphic_Ellipse{
    CCGraphic_Point                 center;
    PointBaseType                   X_Radius;
    PointBaseType                   Y_Radius;  
}CCGraphic_Ellipse;

void CCGraphic_init_ellipse(
    CCGraphic_Ellipse*          handle, 
    CCGraphic_Point             center,
    PointBaseType               X_Radius,
    PointBaseType               Y_Radius 
);

void CCGraphic_draw_ellipse(
    CCDeviceHandler* handler,
    CCGraphic_Ellipse* ellipse
);

void CCGraphic_drawfilled_ellipse(
    CCDeviceHandler* handler,
    CCGraphic_Ellipse* ellipse
);


#endif