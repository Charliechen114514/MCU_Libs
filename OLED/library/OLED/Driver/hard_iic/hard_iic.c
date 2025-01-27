#include "OLED/Driver/hard_iic/hard_iic.h"

#ifdef USE_DMA
static uint8_t dma_ready = 1;
static I2C_HandleTypeDef* current_handle;

void HAL_I2C_MemTxCpltCallback(I2C_HandleTypeDef *hi2c){
        if(hi2c == current_handle) 
            dma_ready =1;
}

static void __pvt_hardiic_send_data_dma(void* pvt_handle, uint8_t* data, uint16_t size)
{
    OLED_HARD_IIC_Private_Config* config = 
        (OLED_HARD_IIC_Private_Config*)pvt_handle;

    for (uint8_t i = 0; i < size; i ++)
	{
        while(dma_ready == 0);
		 HAL_I2C_Mem_Write_DMA(
            config->pvt_handle,
            config->device_address,
            DATA_PREFIX,
            I2C_MEMADD_SIZE_8BIT,
            &data[i], 1);	//依次发送Data的每一个数据
        dma_ready = 0;
	}
}

static void __pvt_hardiic_send_command_dma(void* pvt_handle, uint8_t cmd)
{
    OLED_HARD_IIC_Private_Config* config = 
        (OLED_HARD_IIC_Private_Config*)pvt_handle;
    while(dma_ready == 0);
    HAL_I2C_Mem_Write_DMA(
        config->pvt_handle, 
        config->device_address,
        CMD_PREFIX,
        I2C_MEMADD_SIZE_8BIT,
        &cmd,1);
    dma_ready = 0;
}

#else

static void __pvt_hardiic_send_data(void* pvt_handle, uint8_t* data, uint16_t size)
{
    OLED_HARD_IIC_Private_Config* config = 
        (OLED_HARD_IIC_Private_Config*)pvt_handle;
    for (uint8_t i = 0; i < size; i ++)
	{
		 HAL_I2C_Mem_Write(
            config->pvt_handle,
            config->device_address,
            DATA_PREFIX,
            I2C_MEMADD_SIZE_8BIT,
            &data[i], 1, config->accepted_time_delay);	//依次发送Data的每一个数据
	}
}

static void __pvt_hardiic_send_command(void* pvt_handle, uint8_t cmd)
{
    OLED_HARD_IIC_Private_Config* config = 
        (OLED_HARD_IIC_Private_Config*)pvt_handle;
    HAL_I2C_Mem_Write(
        config->pvt_handle, 
        config->device_address,
        CMD_PREFIX,
        I2C_MEMADD_SIZE_8BIT,
        &cmd,1,config->accepted_time_delay);
}

#endif

void bind_hardiic_handle(
    OLED_HARD_IIC_Private_Config* blank_config,
    I2C_HandleTypeDef* raw_handle,
    uint16_t    device_address,
    uint32_t    accepted_time_delay
)
{
    blank_config->accepted_time_delay = accepted_time_delay;
    blank_config->device_address = device_address;
    blank_config->pvt_handle = raw_handle;
#ifdef USE_DMA
    current_handle = raw_handle;
    blank_config->operation.command_sender  = __pvt_hardiic_send_command_dma;
    blank_config->operation.data_sender     = __pvt_hardiic_send_data_dma;
#else
    blank_config->operation.command_sender  = __pvt_hardiic_send_command;
    blank_config->operation.data_sender     = __pvt_hardiic_send_data;
#endif
}

