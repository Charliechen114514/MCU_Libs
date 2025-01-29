#include "OLED/Driver/soft_spi/soft_spi.h"

#define SET_SCL(config, pinstate) \
        do{\
            HAL_GPIO_WritePin(config->scl.port, config->scl.pin, (pinstate));\
        }while(0)

#define SET_SDA(config, pinstate) \
        do{\
            HAL_GPIO_WritePin(config->sda.port, config->sda.pin, (pinstate));\
        }while(0)

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


static void __pvt_init_soft_spi_gpio_init(OLED_SOFT_SPI_Private_Config* config)
{
    OLED_SPI_ENABLE_GPIO_SDA_CLK();
    OLED_SPI_ENABLE_GPIO_SCL_CLK();
    OLED_SPI_ENABLE_GPIO_RES_CLK();
    OLED_SPI_ENABLE_GPIO_CS_CLK();
    OLED_SPI_ENABLE_GPIO_DC_CLK();

    GPIO_InitTypeDef GPIO_InitStructure = {0};
    /* configuration */
    GPIO_InitStructure.Pin = 
        config->sda.pin | config->scl.pin | config->cs.pin |
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
    OLED_SOFT_SPI_Private_Config* config = (OLED_SOFT_SPI_Private_Config*)_config;
    SET_DC(config, 0);
    SET_CS(config, 0);
    for(uint8_t i = 0; i < 8; i++)
    {
		SET_SCL(config, 0);
        SET_SDA(config, cmd&0x80);
        SET_SCL(config, 1);
		cmd<<=1;          
    }
    SET_CS(config, 1);
    SET_DC(config, 1);
}

static inline void __pvt_send_single_data(
    OLED_SOFT_SPI_Private_Config* config, uint8_t dat
)
{   
    SET_DC(config, 1);
    SET_CS(config, 0);
    for(uint8_t i = 0; i < 8; i++)
    {
		SET_SCL(config, 0);
        SET_SDA(config, dat&0x80);
        SET_SCL(config, 1);
		dat<<=1;          
    }
    SET_CS(config, 1);
    SET_DC(config, 1);
}

static void __pvt_send_data(
    void* config, uint8_t* data, uint16_t size)
{
    for(uint16_t i = 0; i < size; i++){
        __pvt_send_single_data(config, data[i]);
    }
}

void oled_bind_softspi_pack(OLED_SOFT_SPI_Private_Config* config,
    OLED_SPIGPIOPack* sda,
    OLED_SPIGPIOPack* scl,
    OLED_SPIGPIOPack* res,
    OLED_SPIGPIOPack* dc,
    OLED_SPIGPIOPack* cs)
{
    config->cs = *cs;
    config->dc = *dc;
    config->res = *res;
    config->scl = *scl;
    config->sda = *sda;
    config->operation.command_sender    = __pvt_send_command;
    config->operation.data_sender       = __pvt_send_data;
    __pvt_init_soft_spi_gpio_init(config);    
}