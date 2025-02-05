#include "eeprom.h"
#include "i2c.h"
#define EEPROM_WRITE_DEV_ADDR   (0xA0)
#define EEPROM_READ_DEV_ADDR    (0xA1)


void eeprom_write(uint8_t dev_addr, uint8_t data)
{
    I2CStart();
    
    I2CSendByte(EEPROM_WRITE_DEV_ADDR);
    I2CWaitAck();
    
    I2CSendByte(dev_addr);
    I2CWaitAck();
    
    I2CSendByte(data);
    I2CWaitAck();
    
    I2CStop();
}

uint8_t eeprom_read(uint8_t dev_addr)
{
    I2CStart();
    
    I2CSendByte(EEPROM_WRITE_DEV_ADDR);
    I2CWaitAck();
    
    I2CSendByte(dev_addr);
    I2CWaitAck();
    
    I2CSendByte(EEPROM_READ_DEV_ADDR);
    I2CWaitAck();
    
    uint8_t result = I2CReceiveByte();
    
    I2CSendNotAck();
    I2CStop();
    
    return result;
}