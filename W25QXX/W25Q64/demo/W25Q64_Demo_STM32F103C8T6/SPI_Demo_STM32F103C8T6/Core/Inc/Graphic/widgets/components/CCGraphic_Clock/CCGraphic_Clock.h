#ifndef __CCGRAPHIC_CLOCK_H
#define __CCGRAPHIC_CLOCK_H
#include "Graphic/widgets/common/CCGraphic_WidgetBase.h"
#include "Graphic/base/CCGraphic_Circle/CCGraphic_Circle.h"
#include "Graphic/widgets/core/CCGraphic_Time.h"

typedef struct __CCGrapghic_Clock CCGrapghic_Clock;


typedef struct {
    CCGraphicWidgetCommonOperation  operations;
    /* update time */
    void (*updateTime)(CCGrapghic_Clock*, CCGraphic_Time*);
}CCGrapghic_Clock_Operations;

typedef struct __CCGrapghic_Clock{
    CCGraphic_Circle    handling_circle;    // handling circle
    uint16_t            major_tickel_length;      // tickal length 
    uint16_t            minor_tickel_length;      // tickal length 
    CCGraphic_Time      current_time;
    CCDeviceHandler*    borrowed_device;
    CCGrapghic_Clock_Operations op;
}CCGrapghic_Clock;

void initCCGraphic_Clock(
    CCGrapghic_Clock* clk, CCDeviceHandler* device, CCGraphic_Circle* circle);

#endif

