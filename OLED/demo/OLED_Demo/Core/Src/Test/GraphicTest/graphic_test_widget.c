#include "Test/GraphicTest/graphic_test.h"
#include "stm32f1xx_hal.h"
#include "Graphic/widgets/base/CCGraphic_TextItem/CCGraphic_TextItem.h"
#include "Graphic/widgets/base/CCGraphic_Image/CCGraphic_Image.h"

extern const uint8_t test_image[];
// extern const uint8_t temperatureData[];
void on_test_draw_image(CCDeviceHandler* handle)
{
    CCGraphic_Image image;
    /* test_image_size is 16 x 16 */
    CCGraphic_Size size;
    size.height = 16;
    size.width = 16;
    CCGraphic_Point p;
    p.x = 64 - size.width / 2;
    p.y = 32 - size.height / 2;
    CCGraphicWidget_init_image(
        &image, p, size, (uint8_t*)test_image);
    CCGraphicWidget_draw_image(handle, &image);

    handle->operations.update_device_function(handle);
}

void on_test_draw_ascii(CCDeviceHandler* handle)
{
    /* print sources */
    char* source = "Hello, World!This is Charlie's Speeking!";
    CCGraphic_AsciiTextItem item;
    CCGraphic_Point p;
    p.x = 0;
    p.y = 0;
    CCGraphic_Size acceptablesize = CCGraphicWidget_MaxAcceptable_Size(handle);
    acceptablesize.width /= 2;
    CCGraphicWidget_init_AsciiTextItem(
        &item, p, acceptablesize, ASCII_6x8
    );
    CCGraphicWidget_AsciiTextItem_setAsciiText(&item, source);
    p = CCGraphicWidget_drawAsciiTextItem_with_finPoint(
        handle, &item, CCGraphic_AsciiTextItem_AppendContinously);
    CCGraphicWidget_AsciiTextItem_setIndexedPoint(
        &item, &p
    );
    handle->operations.update_device_function(handle);
    HAL_Delay(1000);

    /* after delay, print new_sources */
    char* new_source = "May I Help You?";   
    CCGraphicWidget_AsciiTextItem_setAsciiText(
        &item, new_source
    );
    p = CCGraphicWidget_drawAsciiTextItem_with_finPoint(
        handle, &item, CCGraphic_AsciiTextItem_AppendNextLine
    );
    CCGraphicWidget_AsciiTextItem_setIndexedPoint(
        &item, &p
    );
    handle->operations.update_device_function(handle);
    HAL_Delay(1000);

    new_source = "Yes!Please Offer me a lemon juice";
    CCGraphicWidget_AsciiTextItem_setAsciiText(
        &item, new_source
    );
    CCGraphicWidget_AsciiTextItem_setIndexedPoint(
        &item, &p
    );
    CCGraphicWidget_drawAsciiTextItem(
        handle, &item);
    handle->operations.update_device_function(handle);
}