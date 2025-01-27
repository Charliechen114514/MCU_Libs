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


void swap_int16(int16_t* val1, int16_t* val2)
{
    if(*val1 == *val2) return;
    *val1 ^= *val2;
    *val2 ^= *val1;
    *val1 ^= *val2;
}

int16_t max_int16(int16_t val1, int16_t val2)
{
    return val1 > val2 ? val1 : val2;
}


int16_t find_int16min(int16_t* vals, int16_t size)
{
    int16_t result = vals[0];
    for(int16_t i = 0; i < size; i++)
    {
        if(vals[i] < result) result = vals[i];
    }
    return result;
}

int16_t find_int16max(int16_t* vals, int16_t size)
{
    int16_t result = vals[0];
    for(int16_t i = 0; i < size; i++)
    {
        if(vals[i] > result) result = vals[i];
    }
    return result;
}
