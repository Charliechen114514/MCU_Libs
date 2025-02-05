#ifndef EEPROM_H
#define EEPROM_H
#include "main.h"

void eeprom_write(uint8_t dev_addr, uint8_t data);
uint8_t eeprom_read(uint8_t dev_addr);

#endif
