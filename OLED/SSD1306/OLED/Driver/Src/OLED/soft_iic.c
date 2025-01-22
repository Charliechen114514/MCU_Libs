#include "soft_iic.h"
#include "../oled_base_driver.h"
static void __pvt_softiic_sendsda(
    OLED_Handle_SoftIIC_Handle_Private* send, 
    const uint8_t data)
{
    HAL_GPIO_WritePin(send->sda_port, send->sda_pin, 
    (GPIO_PinState)data);
}

static void __pvt_softiic_sendscl(
    OLED_Handle_SoftIIC_Handle_Private* send, const uint8_t data)
{
    HAL_GPIO_WritePin(send->scl_port, send->scl_pin, 
    (GPIO_PinState)data);
}

static void __pvt_sendBytes(
    OLED_Handle_SoftIIC_Handle_Private* handle, 
    const int8_t bytes
    )
{
    for(uint8_t i = 0; i < 8; i++)
    {
        // let !! set the all as 1 which bit is 0
        __pvt_softiic_sendsda(handle, !!(bytes & (0x80 >> i)));
        __pvt_softiic_sendscl(handle, 1);
        __pvt_softiic_sendscl(handle, 0);
    }
    __pvt_softiic_sendscl(handle, 1);
    __pvt_softiic_sendscl(handle, 0);
}


static void __pvt_start_soft_iic(OLED_Handle_SoftIIC_Handle_Private* handle)
{
    __pvt_softiic_sendsda(handle, 1);
    __pvt_softiic_sendscl(handle, 1);
    __pvt_softiic_sendsda(handle, 0);
    __pvt_softiic_sendscl(handle, 0);
}

static void __pvt_stop_soft_iic(OLED_Handle_SoftIIC_Handle_Private* handle)
{
    __pvt_softiic_sendsda(handle, 0);
    __pvt_softiic_sendscl(handle, 1);
    __pvt_softiic_sendsda(handle, 1);
}

static void __pvt_sendData(
    OLED_Handle_SoftIIC_Handle_Private* handle, 
    const uint8_t* data, const uint8_t size)
{
    __pvt_start_soft_iic(handle);
    __pvt_sendBytes(handle, handle->device_address);
    __pvt_sendBytes(handle, DATA_PREFIX);
    for(uint8_t i = 0; i < size; i++)
    {
        __pvt_sendBytes(handle, data[i]);
    }
    __pvt_stop_soft_iic(handle);
}

static void __pvt_sendCommand(
    OLED_Handle_SoftIIC_Handle_Private* handle, 
    const uint8_t command)
{
    __pvt_start_soft_iic(handle);
    __pvt_sendBytes(handle, handle->device_address);
    __pvt_sendBytes(handle, CMD_PREFIX);
    __pvt_sendBytes(handle, command);
    __pvt_stop_soft_iic(handle);
}

void OLED_Handle_SoftIIC_Private_bindHandle(
    OLED_Handle_SoftIIC_Handle_Private* blank_handle,
    uint16_t        device_address,
    GPIO_TypeDef*   sda_port,
    uint16_t        sda_pin,
    GPIO_TypeDef*   sck_port,
    uint16_t        sck_pin
)
{
    blank_handle->scl_pin = sck_pin;
    blank_handle->scl_port = sck_port;
    blank_handle->sda_pin = sda_pin;
    blank_handle->sda_port = sda_port;
    blank_handle->device_address = device_address;
    blank_handle->sendData = __pvt_sendData;
    blank_handle->sendCommand = __pvt_sendCommand;
}