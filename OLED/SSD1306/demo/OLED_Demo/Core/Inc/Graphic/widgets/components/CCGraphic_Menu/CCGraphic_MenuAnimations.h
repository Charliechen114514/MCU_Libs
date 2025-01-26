#ifndef CCGraphic_MenuAnimations_H
#define CCGraphic_MenuAnimations_H
#include "Graphic/base/CCGraphic_Point/CCGraphic_Point.h"
#include "Graphic/widgets/common/CCGraphic_Size/CCGraphic_Size.h"

typedef struct __CCGraphic_MenuAnimations CCGraphic_MenuAnimations; 
typedef void    (*DoByStep)(CCGraphic_MenuAnimations*);
typedef struct{
    DoByStep        doByStep;
}CCGraphic_MenuAnimationsOperations;

/*
    this struct shouldn't be registered by programmers
    it shoule be registered by program, so no interface is
    publiced!
*/
typedef struct __CCGraphic_MenuAnimations{
    /* animating rectangle */
    CCDeviceHandler*                    handler;
    CCGraphic_Point                     tl_point;
    CCGraphic_Size                      animationOffsetSize;
    int16_t                             x_step;
    int16_t                             y_step;
    CCGraphic_MenuAnimationsOperations  op;
    uint8_t                             is_doing;
}CCGraphic_MenuAnimations;

#endif