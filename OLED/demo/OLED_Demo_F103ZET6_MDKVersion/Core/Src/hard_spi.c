#include "OLED/Driver/hard_spi/hard_spi.h"
#ifdef USE_HARDSPI_PROTOCOL

#define SET_RES(config, pinstate) \
        do{\
            HAL_GPIO_WritePin(config->res.port, config->res.pin, (pinstate));\
        }while(0)        

#define SET_DC(config, pinstate) \
        do{\
            HAL_GPIO_WritePin(config->dc.port, config->dc.pin, (pinstate));\
        }while(0)         

#define SET_CS(config, pinstate) \
        do{\
            HAL_GPIO_WritePin(config->cs.port, config->cs.pin, (pinstate));\
        }while(0)  


static void __pvt_init_soft_spi_gpio_init(OLED_HARD_SPI_Private_Config* config)
{
    OLED_SPI_ENABLE_GPIO_RES_CLK();
    OLED_SPI_ENABLE_GPIO_CS_CLK();
    OLED_SPI_ENABLE_GPIO_DC_CLK();

    GPIO_InitTypeDef GPIO_InitStructure = {0};
    /* configuration */
    GPIO_InitStructure.Pin = config->cs.pin |
            config->dc.pin | config->res.pin;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
    SET_RES(config, 0);
    HAL_Delay(200);
    SET_RES(config, 1);
}

static void __pvt_send_command(
    void* _config, uint8_t cmd)
{
    OLED_HARD_SPI_Private_Config* config = (OLED_HARD_SPI_Private_Config*)_config;
    SET_DC(config, 0);
    SET_CS(config, 0);

    HAL_SPI_Transmit(
        config->pvt_handle, &cmd, 1, 
        config->delay_time_out);

    SET_CS(config, 1);
    SET_DC(config, 1);
}

static inline void __pvt_send_data(
    void* __config, uint8_t* data, uint16_t size
)
{   
    OLED_HARD_SPI_Private_Config* config = (OLED_HARD_SPI_Private_Config*)__config;
    SET_DC(config, 1);
    SET_CS(config, 0);

    HAL_SPI_Transmit(config->pvt_handle, data, size, config->delay_time_out);

    SET_CS(config, 1);
    SET_DC(config, 1);
}


void oled_bind_hard_spi(
    OLED_HARD_SPI_Private_Config* blank_config,
    SPI_HandleTypeDef*  pvt_handle,
    OLED_HARDSPIGPIOPack*    res,
    OLED_HARDSPIGPIOPack*    dc,
    OLED_HARDSPIGPIOPack*    cs,
    uint32_t                 delay_time_out
)
{
    blank_config->pvt_handle = pvt_handle;
    blank_config->cs = *cs;
    blank_config->dc = *dc;
    blank_config->res = *res;
    blank_config->delay_time_out = delay_time_out;
    blank_config->operation.command_sender = __pvt_send_command;
    blank_config->operation.data_sender = __pvt_send_data;
    __pvt_init_soft_spi_gpio_init(blank_config);
}

#endif