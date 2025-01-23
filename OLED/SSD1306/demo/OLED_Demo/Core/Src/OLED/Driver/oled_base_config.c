#include "OLED/Driver/oled_base_driver.h"
#include "OLED/Driver/hard_iic/hard_iic.h"
#include "OLED/Driver/soft_iic/soft_iic.h"
#include <memory.h>
/* oled init commands */
uint8_t oled_init_commands[] = {
    0xAE,  // Display off
    0xD5,  // Set display clock divide ratio/oscillator frequency
    0x80,  // 0x00~0xFF
    0xA8,  // Set multiplex ratio
    0x3F,  // 0x0E~0x3F
    0xD3,  // Set display offset
    0x00,  // 0x00~0x7F
    0x40,  // Set display start line
    0xA1,  // Set segment re-map (0xA1 normal, 0xA0 flip horizontally)
    0xC8,  // Set COM scan direction (0xC8 normal, 0xC0 flip vertically)
    0xDA,  // Set COM pins hardware configuration
    0x12,  // COM pins hardware configuration
    0x81,  // Set contrast control
    0xCF,  // 0x00~0xFF
    0xD9,  // Set pre-charge period
    0xF1,  // Pre-charge period
    0xDB,  // Set VCOMH deselect level
    0x30,  // VCOMH deselect level
    0xA4,  // Entire display on
    0xA6,  // Normal display (0xA6 normal, 0xA7 inverse)
    0x8D,  // Set charge pump
    0x14,  // Enable charge pump
    0xAF   // Display on
};

#define CMD_TABLE_SZ ( (sizeof(oled_init_commands)) / sizeof(oled_init_commands[0]) )

uint8_t OLED_GRAM[OLED_HEIGHT][OLED_WIDTH];

/*
    __on_fetch_oled_table: fetch the operation tables back
*/
static void __on_fetch_oled_table(
    const OLED_Handle* handle, 
    OLED_Operations* blank_operations)
{
    switch (handle->stored_handle_type)
    {
        case OLED_HARD_IIC_DRIVER_TYPE:
        {
            OLED_HARD_IIC_Private_Config* config = 
                (OLED_HARD_IIC_Private_Config*)(handle->private_handle);
            blank_operations->command_sender = config->operation.command_sender;
            blank_operations->data_sender = config->operation.data_sender;
        }break;
        case OLED_SOFT_IIC_DRIVER_TYPE:
        {
            OLED_SOFT_IIC_Private_Config* config = 
                (OLED_SOFT_IIC_Private_Config*)(handle->private_handle);
            blank_operations->command_sender = config->operation.command_sender;
            blank_operations->data_sender = config->operation.data_sender;
        }break;
        default:
            break;
    }
}

/*
    set operating cursor
*/
void __pvt_oled_set_cursor(
    OLED_Handle* handle, 
    const uint8_t y,
    const uint8_t x)
{
    OLED_Operations op_table;
    __on_fetch_oled_table(handle, &op_table);
    op_table.command_sender(handle->private_handle, 0xB0 | y);
	op_table.command_sender(handle->private_handle,0x10 | ((x & 0xF0) >> 4));	//设置X位置高4位
	op_table.command_sender(handle->private_handle,0x00 | (x & 0x0F));			//设置X位置低4位
}

void oled_helper_clear_frame(OLED_Handle* handle)
{
    memset(OLED_GRAM, 0, sizeof(OLED_GRAM));
}

void oled_helper_update(OLED_Handle* handle)
{
    OLED_Operations op_table;
    __on_fetch_oled_table(handle, &op_table);
    	
	for (uint8_t j = 0; j < 8; j ++)
	{
		/*设置光标位置为每一页的第一列*/
		__pvt_oled_set_cursor(handle, j, 0);
		/*连续写入128个数据，将显存数组的数据写入到OLED硬件*/
		op_table.data_sender(handle->private_handle, OLED_GRAM[j], 128);
	}
}

void oled_init_hardiic_handle(
    OLED_Handle* handle, 
    OLED_HARD_IIC_Private_Config* config)
{
    handle->private_handle = config;
    handle->stored_handle_type = OLED_HARD_IIC_DRIVER_TYPE;
    for(uint8_t i = 0; i < CMD_TABLE_SZ; i++)
        config->operation.command_sender(config, oled_init_commands[i]);
    oled_helper_clear_frame(handle);
    oled_helper_update(handle);
}

void oled_init_softiic_handle(
    OLED_Handle* handle,
    OLED_SOFT_IIC_Private_Config* config)
{
    handle->private_handle = config;
    handle->stored_handle_type = OLED_SOFT_IIC_DRIVER_TYPE;
    for(uint8_t i = 0; i < CMD_TABLE_SZ; i++)
        config->operation.command_sender(config, oled_init_commands[i]);
    oled_helper_clear_frame(handle);
    oled_helper_update(handle);
}

void oled_helper_setpixel(OLED_Handle* handle, uint16_t x, uint16_t y)
{
    // current unused
    (void)handle;
    if( 
        0 <= x && x <= OLED_WIDTH &&
        0 <= y && y <= OLED_HEIGHT * 8
    )
        OLED_GRAM[y / 8][x] |= 0x01 << (y % 8);
}

