#ifndef __CCGraphic_Time_H
#define __CCGraphic_Time_H

#include "Graphic/CCGraphic_common.h"

typedef struct 
{
    uint8_t second;
    uint8_t minutes;
    uint8_t hour;
}CCGraphic_Time;

typedef struct
{
    uint8_t day;
    uint8_t month;
    uint8_t week;
    uint8_t year; // since 2000
}CCGraphic_Date;

void CCGrapgic_Time_addTime(CCGraphic_Time* addee, CCGraphic_Time* adder);


#endif