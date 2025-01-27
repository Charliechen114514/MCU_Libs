#include "OLED/Driver/soft_iic/soft_iic.h"

#define SET_SCL(config, pinstate) \
        do{\
            HAL_GPIO_WritePin(config->scl.port, config->scl.pin, pinstate);\
        }while(0)

#define SET_SDA(config, pinstate) \
        do{\
            HAL_GPIO_WritePin(config->sda.port, config->sda.pin, pinstate);\
        }while(0)


static void __pvt_on_init_iic_gpio(OLED_SOFT_IIC_Private_Config* config)
{
    /* Enable the GPIOB clock */
    OLED_ENABLE_GPIO_SCL_CLK();
    OLED_ENABLE_GPIO_SDA_CLK();

    GPIO_InitTypeDef GPIO_InitStructure = {0};
    /* configuration */
    GPIO_InitStructure.Pin = config->sda.pin | config->scl.pin;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
    SET_SCL(config, 1);
    SET_SDA(config, 1);
}


static void __pvt_on_start_iic(OLED_SOFT_IIC_Private_Config* config) 
{
    SET_SDA(config, 1);
    SET_SCL(config, 1);
    SET_SDA(config, 0);
    SET_SCL(config, 0);    
}

static void __pvt_on_stop_iic(OLED_SOFT_IIC_Private_Config* handle)
{
	SET_SDA(handle, 0);		
	SET_SCL(handle, 1);		
	SET_SDA(handle, 1);		 
}

static void __pvt_iic_send_bytes(OLED_SOFT_IIC_Private_Config* handle, uint8_t data)
{	
	for (uint8_t i = 0; i < 8; i++)
	{	
		SET_SDA(handle,!!(data & (0x80 >> i)));
		SET_SCL(handle,1);	
		SET_SCL(handle,0);	
	}
	
	SET_SCL(handle,1);		
	SET_SCL(handle,0);
}

static void __pvt_iic_send_command(void* pvt_handle, uint8_t cmd)
{
    OLED_SOFT_IIC_Private_Config* config = 
        (OLED_SOFT_IIC_Private_Config*)pvt_handle;

    __pvt_on_start_iic(config);
    __pvt_iic_send_bytes(config, config->device_address);
    __pvt_iic_send_bytes(config, CMD_PREFIX);
    __pvt_iic_send_bytes(config, cmd);
    __pvt_on_stop_iic(config);
}

static void __pvt_iic_send_data(
    void* pvt_handle, 
    uint8_t* data, uint16_t size)
{
    OLED_SOFT_IIC_Private_Config* config = 
        (OLED_SOFT_IIC_Private_Config*)pvt_handle;
    __pvt_on_start_iic(config);
    __pvt_iic_send_bytes(config, config->device_address);
    __pvt_iic_send_bytes(config, DATA_PREFIX);
    for(uint16_t i = 0; i < size; i++)
        __pvt_iic_send_bytes(config, data[i]);
    __pvt_on_stop_iic(config); 
}

void oled_bind_softiic_handle(
    OLED_SOFT_IIC_Private_Config*   config,
    OLED_GPIOPack*                  sda,  
    OLED_GPIOPack*                  scl,
    uint16_t                        device_address,
    uint32_t                        accepted_time_delay
)
{
    config->accepted_time_delay = accepted_time_delay;
    config->device_address = device_address;
    config->sda.pin = sda->pin;
    config->sda.port = sda->port;
    config->scl.port = scl->port;
    config->scl.pin = scl->pin;
    config->operation.command_sender    = __pvt_iic_send_command;
    config->operation.data_sender       = __pvt_iic_send_data;
    __pvt_on_init_iic_gpio(config);
}