#ifndef HARD_IIC_H
#define HARD_IIC_H

#include "common_iic.h"

typedef struct __CommonHardIIC{
    I2C_TypeDef*        raw_handle;
    IIC_Operations*     operations;
    IICCommonConfig     configs;
}CCIIC_HardIICHandle;

void init_hard_iic_handle(
    CCIIC_HardIICHandle* handle, I2C_TypeDef* types, IICCommonConfig* configs);


#endif