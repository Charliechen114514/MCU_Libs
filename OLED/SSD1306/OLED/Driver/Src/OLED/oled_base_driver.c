#include "oled_base_driver.h"
#include "hard_iic/hard_iic.h"
#include "soft_iic/soft_iic.h"
#include <stdlib.h>
#include <memory.h>

const uint8_t ssd1306_init_cmds[] = {
    0xAE, // turn off OLED panel
    0x00, // set low column address
    0x10, // set high column address
    0x40, // set start line address
    0x81, // set contrast control register
    0xCF, // set SEG output current brightness
    0xA1, // set SEG/Column mapping (0xa0: reverse, 0xa1: normal)
    0xC8, // set COM/Row scan direction (0xc0: reverse, 0xc8: normal)
    0xA6, // set normal display
    0xA8, // set multiplex ratio (1 to 64)
    0x3F, // 1/64 duty
    0xD3, // set display offset
    0x00, // no offset
    0xD5, // set display clock divide ratio/oscillator frequency
    0x80, // set divide ratio, 100 frames/sec
    0xD9, // set pre-charge period
    0xF1, // set pre-charge as 15 clocks & discharge as 1 clock
    0xDA, // set COM pins hardware configuration
    0x12, // configuration for COM pins
    0xDB, // set VCOMH
    0x40, // set VCOM deselect level
    0x20, // set page addressing mode
    0x02, // page address mode
    0x8D, // set charge pump enable/disable
    0x14, // disable charge pump (0x10: disable, 0x14: enable)
    0xA4, // disable entire display on
    0xA6, // disable inverse display on
    0xAF  // turn on OLED panel
};
#define CMD_TABLE_SZ ( sizeof(ssd1306_init_cmds) / sizeof(ssd1306_init_cmds[0]))

/* draw box */
uint8_t OLED_GRAM[OLED_HEIGHT][OLED_WIDTH];

typedef struct {
    void (*sendData)(
        void*, 
        const uint8_t*, 
        const uint16_t);
    void (*sendCommand)(
        void*, 
        const uint8_t);
}OLED_OperationTable;

typedef void(*SendData)(void*, const uint8_t*, const uint16_t);
typedef void(*SendCommand)(void*, const uint8_t);

static void __pvt_fetch_operation_table(
    OLED_Handle* handle,
    OLED_OperationTable* table)
{
    switch(handle->type)
    {
        case OLED_SOFTIIC_PACK:
        { 
            OLED_Handle_HardIIC_Private*
            hardiic = (OLED_Handle_HardIIC_Private*)(handle->private_data);
            table->sendCommand = (SendCommand)hardiic->sendCommand;
            table->sendData = (SendData)hardiic->sendData;}
        break;
        case OLED_HARDIIC_PACK:
        {            
            OLED_Handle_SoftIIC_Handle_Private*
            softiic = (OLED_Handle_SoftIIC_Handle_Private*)(handle->private_data);
            table->sendCommand = (SendCommand)softiic->sendCommand;
            table->sendData = (SendData)softiic->sendData;
        }
        break;
    }
}


static void __pvt_set_ready_write_cursor(
    OLED_Handle*    handle,
    uint8_t         X,
    uint8_t         Y
)
{
    OLED_OperationTable table;
    __pvt_fetch_operation_table(handle, &table);
    table.sendCommand(handle->private_data, 0xB0 | Y);
    table.sendCommand(handle->private_data, 0x10 | ((X & 0xF0) >> 4));
    table.sendCommand(handle->private_data, 0x00 | (X & 0x0F));
}

/*
    only in calling this shell we refresh the table
*/
static void __pvt_update_oled_frame(OLED_Handle* handle)
{
    OLED_OperationTable table;
    __pvt_fetch_operation_table(handle, &table);
    for(uint8_t i = 0; i < OLED_HEIGHT; i++)
    {
        __pvt_set_ready_write_cursor(handle, i, 0);
        table.sendData(handle->private_data, OLED_GRAM[i], OLED_WIDTH);
    }
}

static void __pvt_clean_oled_frame(OLED_Handle* handle)
{
    memset(OLED_GRAM, 0, sizeof(OLED_GRAM));
    __pvt_update_oled_frame(handle);
}



void init_oled_handle_softiic(
    OLED_Handle* handle, OLED_Handle_SoftIIC_Handle_Private* pvts
)
{
    handle->type = OLED_SOFTIIC_PACK;
    handle->private_data = pvts;
    __pvt_clean_oled_frame(handle);
}

void init_oled_handle_hardiic(
    OLED_Handle* handle, 
    OLED_Handle_HardIIC_Private* pvts
)
{
    handle->type = OLED_HARDIIC_PACK;
    handle->private_data = pvts;
pvts->sendCommand(pvts, 0xAE);  // 设置显示开启/关闭，0xAE关闭，0xAF开启

pvts->sendCommand(pvts, 0xD5);  // 设置显示时钟分频比/振荡器频率
pvts->sendCommand(pvts, 0x80);  // 0x00~0xFF

pvts->sendCommand(pvts, 0xA8);  // 设置多路复用率
pvts->sendCommand(pvts, 0x3F);  // 0x0E~0x3F

pvts->sendCommand(pvts, 0xD3);  // 设置显示偏移
pvts->sendCommand(pvts, 0x00);  // 0x00~0x7F

pvts->sendCommand(pvts, 0x40);  // 设置显示开始行，0x40~0x7F

pvts->sendCommand(pvts, 0xA1);  // 设置左右方向，0xA1正常，0xA0左右反置

pvts->sendCommand(pvts, 0xC8);  // 设置上下方向，0xC8正常，0xC0上下反置

pvts->sendCommand(pvts, 0xDA);  // 设置COM引脚硬件配置
pvts->sendCommand(pvts, 0x12);

pvts->sendCommand(pvts, 0x81);  // 设置对比度
pvts->sendCommand(pvts, 0xCF);  // 0x00~0xFF

pvts->sendCommand(pvts, 0xD9);  // 设置预充电周期
pvts->sendCommand(pvts, 0xF1);

pvts->sendCommand(pvts, 0xDB);  // 设置VCOMH取消选择级别
pvts->sendCommand(pvts, 0x30);

pvts->sendCommand(pvts, 0xA4);  // 设置整个显示打开/关闭

pvts->sendCommand(pvts, 0xA6);  // 设置正常/反色显示，0xA6正常，0xA7反色

pvts->sendCommand(pvts, 0x8D);  // 设置充电泵
pvts->sendCommand(pvts, 0x14);

pvts->sendCommand(pvts, 0xAF);  // 开启显示


        
    __pvt_clean_oled_frame(handle);
}

void oled_set_pixel(OLED_Handle* handle, uint8_t x, uint8_t y)
{
    OLED_GRAM[y / 8][x] |= 0x01 << (y % 8);
}

void oled_update(OLED_Handle* handle)
{
    __pvt_update_oled_frame(handle);
}