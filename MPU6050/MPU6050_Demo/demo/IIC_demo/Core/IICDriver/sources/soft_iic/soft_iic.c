#include "stm32f1xx_hal.h"
#include "IICDriver/include/soft_iic.h"

#define set_scl_pin(handle, value) do{\
    HAL_GPIO_WritePin(handle->scl.port, handle->scl.pin, !!(value));\
    __soft_iic_delay_us(10);\
}while(0)

#define set_sda_pin(handle, value) do{\
    HAL_GPIO_WritePin(handle->sda.port, handle->sda.pin, !!(value));\
    __soft_iic_delay_us(10);\
}while(0)

#define from_sda(handle) HAL_GPIO_ReadPin(handle->sda.port, handle->sda.pin)


static void __pvt_config_given_port(CCIIC_SoftIICHandle* handle)
{
    ENABLE_SCL_CLK;
    ENABLE_SDA_CLK;

    GPIO_InitTypeDef initer = {0};
    initer.Pin = handle->scl.pin | handle->sda.pin;
    initer.Mode = GPIO_MODE_OUTPUT_OD;
    initer.Speed = GPIO_SPEED_FREQ_HIGH;
    initer.Pull = GPIO_NOPULL;

    HAL_GPIO_Init(handle->scl.port, &initer);
    HAL_GPIO_Init(handle->sda.port, &initer);
    set_scl_pin(handle, 1);
    set_sda_pin(handle, 1);
}

static inline void __start_iic(CCIIC_SoftIICHandle* handle)
{
    set_sda_pin(handle, 1);
    set_scl_pin(handle, 1);
    set_sda_pin(handle, 0);
    set_scl_pin(handle, 0);
}

static void __stop_iic(
    CCIIC_SoftIICHandle* handle)
{
    set_sda_pin(handle, 0);
    set_scl_pin(handle, 1);
    set_sda_pin(handle, 1);
}

static void __pvt_send_real_bytes(CCIIC_SoftIICHandle* handle, uint8_t data)
{
    for(uint8_t i = 0; i < 8; i++)
    {
        set_sda_pin(handle, data & (0x80 >> i));
        set_scl_pin(handle, 1);
        set_scl_pin(handle, 0);
    }
}

static uint8_t __pvt_receive_real_bytes(CCIIC_SoftIICHandle* handle)
{
    uint8_t blank = 0;
    for(uint8_t i = 0; i < 8; i++)
    {
        set_scl_pin(handle, 1);
        if(from_sda(handle)){
            blank |= (0x80 >> i);
        }
        set_scl_pin(handle, 0);
    }    
    return blank;
}


static void __pvt_receive_data(CCIIC_SoftIICHandle* handle, uint8_t* data, uint16_t data_size)
{
    for(uint16_t i = 0; i < data_size; i++)
    {
        data[i] = __pvt_receive_real_bytes(handle);
    }
}

static void __pvt_send_data(CCIIC_SoftIICHandle* handle, uint8_t* data, uint16_t data_size)
{
    for(uint16_t i = 0; i < data_size; i++)
    {
        __pvt_send_real_bytes(handle, data[i]);
    }
}

static void __pvt_send_ack(CCIIC_SoftIICHandle* handle, uint8_t ack_level)
{
    set_sda_pin(handle, ack_level);
    set_scl_pin(handle, 1);
    set_scl_pin(handle, 0);    
}

static uint8_t __pvt_receive_ack(CCIIC_SoftIICHandle* handle)
{
	uint8_t ack_bit;
	set_sda_pin(handle, 1);
	set_scl_pin(handle, 1);
	ack_bit = from_sda(handle);
	set_scl_pin(handle, 0);
	return ack_bit; 
}

static IIC_Operations operations = {
    (SendData)__pvt_send_data, 
    (ReceiveData)__pvt_receive_data, 
    (OpenIIC)__start_iic,
    (CloseIIC)__stop_iic,
    (SendACK)__pvt_send_ack,
    (WaitACK)__pvt_receive_ack
};

void init_soft_iic_handle(
    CCIIC_SoftIICHandle*    handle,
    SoftIICGPIOPackageType*     scl,
    SoftIICGPIOPackageType*     sda,
    IICCommonConfig*        configs
)
{
    handle->scl         = *scl;
    handle->sda         = *sda;
    handle->configs     = *configs;
    handle->operations  = &operations;
    __pvt_config_given_port(handle);
}

