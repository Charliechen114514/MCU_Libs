#ifndef SOFT_IIC_H
#define SOFT_IIC_H

#define ENABLE_SCL_CLK      __HAL_RCC_GPIOA_CLK_ENABLE()
#define ENABLE_SDA_CLK      __HAL_RCC_GPIOA_CLK_ENABLE()

#include "common_iic.h"

typedef struct {
    GPIO_TypeDef*   port;
    uint16_t        pin;
}SoftIICGPIOPackageType;

typedef struct __CommonSoftIIC{
    SoftIICGPIOPackageType  scl;
    SoftIICGPIOPackageType  sda;
    IIC_Operations*     operations;
    IICCommonConfig     configs;
}CCIIC_SoftIICHandle;

void init_soft_iic_handle(
    CCIIC_SoftIICHandle*        handle,
    SoftIICGPIOPackageType*     scl,
    SoftIICGPIOPackageType*     sda,
    IICCommonConfig*            configs
);


#endif