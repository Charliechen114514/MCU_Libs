#include "Graphic/widgets/core/CCGraphic_Time.h"

static uint8_t __adjust_to_normal(CCGraphic_Time* t)
{
    t->minutes += t->second / 60;
    t->second %= 60;

    t->hour += t->minutes / 60;
    t->minutes %= 60;

    uint8_t req_add_date = t->hour / 24;
    t->hour %= 24;
    return req_add_date;
}


void CCGrapgic_Time_addTime(
    CCGraphic_Time* addee, CCGraphic_Time* adder)
{
    addee->second += adder->second;
    addee->minutes += adder->minutes;
    addee->hour += adder->hour;
    __adjust_to_normal(addee);
}