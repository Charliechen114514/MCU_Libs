#include "hard_iic.h"
#include "../oled_base_driver.h"


static void __pvt_send_data(
    struct __OLED_Handle_HardIIC_Private* pvt_handle, 
    uint8_t* buffer,
    const uint16_t  size
    )
{
    HAL_I2C_Mem_Write(
        pvt_handle->handle, pvt_handle->device_address,
        DATA_PREFIX, 
        I2C_MEMADD_SIZE_8BIT, buffer, size, pvt_handle->accepted_time_out
    );
}

static void __pvt_send_command(
    struct __OLED_Handle_HardIIC_Private* pvt_handle,
    uint8_t cmd)
{

    HAL_I2C_Mem_Write(
        pvt_handle->handle, pvt_handle->device_address,
        CMD_PREFIX, 
        I2C_MEMADD_SIZE_8BIT, &cmd, 2, pvt_handle->accepted_time_out
    );
}


void OLED_Handle_HardIIC_Private_bindHandle(
    OLED_Handle_HardIIC_Private* blank_handle, 
    uint16_t device_address,
    I2C_HandleTypeDef* raw, uint32_t accept_time_out)
{
    blank_handle->accepted_time_out = accept_time_out;
    blank_handle->handle = raw;
    blank_handle->device_address = device_address;
    blank_handle->sendData = __pvt_send_data;
    blank_handle->sendCommand = __pvt_send_command;
}