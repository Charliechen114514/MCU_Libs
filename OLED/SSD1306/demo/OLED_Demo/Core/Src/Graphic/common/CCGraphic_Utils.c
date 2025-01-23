#include "Graphic/common/CCGraphic_Utils.h"

void swap_uint8(uint8_t* val1, uint8_t* val2)
{
    if(*val1 == *val2) return;
    *val1 ^= *val2;
    *val2 ^= *val1;
    *val1 ^= *val2;
}

uint8_t max_uint8(uint8_t val1, uint8_t val2)
{
    return val1 > val2 ? val1 : val2;
}

uint8_t min_uint8(uint8_t val1, uint8_t val2)
{
    return val1 < val2 ? val1 : val2;
}

void swap_uint16(uint16_t* val1, uint16_t* val2)
{
    if(*val1 == *val2) return;
    *val1 ^= *val2;
    *val2 ^= *val1;
    *val1 ^= *val2;
}

uint16_t max_uint16(uint16_t val1, uint16_t val2)
{
    return val1 > val2 ? val1 : val2;
}

uint16_t min_uint16(uint16_t val1, uint16_t val2)
{
    return val1 < val2 ? val1 : val2;
}