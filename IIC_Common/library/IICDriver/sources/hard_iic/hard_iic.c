#include "IICDriver/include/hard_iic.h"

static void dummy(CCIIC_HardIICHandle* handle)
{}

static void __pvt_receive_data(CCIIC_HardIICHandle* handle, uint8_t* data, uint16_t data_size)
{
    HAL_I2C_Master_Receive(handle->raw_handle, handle->configs.iic_addr, 
        data, data_size, handle->configs.max_delay);
}

static void __pvt_send_data(CCIIC_HardIICHandle* handle, uint8_t* data, uint16_t data_size)
{
    // you can modify the send here
    HAL_I2C_Master_Transmit(handle->raw_handle, handle->configs.iic_addr, 
        data, data_size, handle->configs.max_delay);
}

static void __pvt_send_ack(CCIIC_HardIICHandle* handle, uint8_t ack_level)
{}

static uint8_t __pvt_receive_ack(CCIIC_HardIICHandle* handle)
{
    return 1;
}

static IIC_Operations operations = {
    (SendData)__pvt_send_data, 
    (ReceiveData)__pvt_receive_data, 
    (OpenIIC)dummy,
    (CloseIIC)dummy,
    (SendACK)__pvt_send_ack,
    (WaitACK)__pvt_receive_ack
};

void init_hard_iic_handle(
    CCIIC_HardIICHandle* handle, I2C_TypeDef* types, IICCommonConfig* configs)
{
    handle->operations = &operations;
    handle->raw_handle = types;
    handle->configs = *configs;
}