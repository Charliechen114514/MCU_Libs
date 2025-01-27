#ifndef CCGraphic_Utils_H
#define CCGraphic_Utils_H
#include "Graphic/CCGraphic_common.h"
void swap_uint8(uint8_t* val1, uint8_t* val2);
uint8_t max_uint8(uint8_t val1, uint8_t val2);
uint8_t min_uint8(uint8_t val1, uint8_t val2);

void swap_uint16(uint16_t* val1, uint16_t* val2);
uint16_t max_uint16(uint16_t val1, uint16_t val2);
uint16_t min_uint16(uint16_t val1, uint16_t val2);

void swap_int16(int16_t* val1, int16_t* val2);
int16_t max_int16(int16_t val1, int16_t val2);
int16_t min_int16(int16_t val1, int16_t val2);

int16_t find_int16min(int16_t* vals, int16_t size);
int16_t find_int16max(int16_t* vals, int16_t size);

#endif