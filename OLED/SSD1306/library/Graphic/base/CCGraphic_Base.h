#ifndef CCGraphic_Base_H
#define CCGraphic_Base_H
#include "Graphic/CCGraphic_common.h"

/*
    This is a function pointer type definition. 
    It represents a function that takes the following parameters:

    CCDeviceHandler* handler: 
        A pointer to a CCDeviceHandler structure 
        
    CCGraphicItem item: 
        A CCGraphicItem  that represents the graphical item to be drawn.
*/
typedef void(*Draw_self)(CCDeviceHandler* handler, CCGraphicItem item);
typedef struct {
    Draw_self   draw_self;
}CCGraphic_BaseOperations;

#endif