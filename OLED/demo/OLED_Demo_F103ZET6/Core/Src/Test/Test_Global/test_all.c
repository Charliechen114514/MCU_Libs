#include "Test/OLED_TEST/oled_test.h"
#include "Test/GraphicTest/graphic_test.h"
#include "Graphic/widgets/components/CCGraphic_TextEdit/CCGraphic_TextEdit.h"
#if defined(USE_SOFTIIC_PROTOCOL) || defined(USE_HARDIIC_PROTOCOL)
void test_oled_iic_functionalities()
{
    OLED_Handle handle;
    user_init_hard_iic_oled_handle(&handle);
    test_set_pixel_line(&handle, 1, 2);
    HAL_Delay(1000);
    test_clear(&handle);
    test_set_pixel_line(&handle, 2, 1);
    HAL_Delay(1000);
    test_clear(&handle);
}
#endif

#if defined(USE_SOFTSPI_PROTOCOL) || defined(USE_HARDSPI_PROTOCOL) 
void test_oled_spi_functionalities()
{
    OLED_Handle handle;
    user_init_soft_spi_oled_handle(&handle);
    test_set_pixel_line(&handle, 1, 2);
    HAL_Delay(1000);
    test_clear(&handle);
    test_set_pixel_line(&handle, 2, 1);
    HAL_Delay(1000);
    test_clear(&handle);
}
#endif

static void __helper_on_set_text(CCGraphicTextEdit* edit, char* sources, uint32_t shown_time)
{
    edit->operations.setText(edit, sources);
    HAL_Delay(shown_time * 1000);
    edit->operations.clear(edit);
}

#define SET_TEXT_CONV(SRC, SECS) do{ sources = SRC;\
    __helper_on_set_text(&edit, sources, SECS);}while(0)

static void __test_common(CCDeviceHandler* handler)
{
    CCGraphicTextEdit   edit;
    CCGraphic_AsciiTextItem item;
    CCGraphic_Point p;
    p.x = 0;
    p.y = 0;
    CCGraphic_Size acceptablesize = 
        CCGraphicWidget_MaxAcceptable_Size(handler);
    CCGraphicWidget_init_AsciiTextItem(
        &item, p, acceptablesize, ASCII_6x8
    );
    CCGraphic_init_CCGraphicTextEdit(
        &edit, handler, &item
    );
    edit.acquired_stepped_update = 1;
    char* sources;
    SET_TEXT_CONV("Hello! Welcome CCGraphic SimpleTest!", 5);
    SET_TEXT_CONV("If you see this sentences, "
    "it means that you have passed the GraphicTest"
    "and congratulations!", 7);

    SET_TEXT_CONV("Graphic Test On Base begin", 4);
    SET_TEXT_CONV("Test Points", 4);
    on_test_draw_points(handler);
    HAL_Delay(1000);
    SET_TEXT_CONV("Test Lines", 4);
    on_test_draw_line(handler);
    HAL_Delay(1000);
    SET_TEXT_CONV("Test Circles", 4);
    on_test_draw_circle(handler);
    HAL_Delay(1000);
    SET_TEXT_CONV("Test Rectangle", 4);
    on_test_draw_rectangle(handler);
    HAL_Delay(1000);
    SET_TEXT_CONV("Test Triangle", 4);
    on_test_draw_triangle(handler);
    HAL_Delay(1000);
    SET_TEXT_CONV("Test Ellipse", 4);
    on_test_draw_ellipse(handler);
    HAL_Delay(1000);
    SET_TEXT_CONV("Test Arc", 4);
    on_test_draw_arc(handler);
    HAL_Delay(1000);
    SET_TEXT_CONV("Graphic Test On Base end", 4);
    SET_TEXT_CONV("Graphic Test On widget begin", 4);
    SET_TEXT_CONV("Test Image Drawing", 4);

    /* widget test */
    on_test_draw_image(handler);
    HAL_Delay(1000);
    SET_TEXT_CONV("Test Ascii Draw", 4);
    on_test_draw_ascii(handler);
    HAL_Delay(1000);
    SET_TEXT_CONV("Graphic Test On widget end", 4);
    SET_TEXT_CONV("Graphic Test On component begin", 4);
    SET_TEXT_CONV("Test TextEdit", 4);
    /* components test */
    on_test_component_textEdit_test(handler);
    HAL_Delay(1000);
    SET_TEXT_CONV("Test Frame", 4);
    on_test_component_frame_test(handler);
    HAL_Delay(1000);
    SET_TEXT_CONV("Test Menu", 4);
    on_test_component_menu(handler);
    HAL_Delay(1000);
    SET_TEXT_CONV("Graphic Test On component end", 4);
    SET_TEXT_CONV("Finish Testing, enjoy!", 4);
}

#ifdef USE_SOFTIIC_PROTOCOL
void test_graphic_softiic_functionalities()
{
    CCDeviceHandler handler;
    on_test_init_softiic_oled(&handler);

    __test_common(&handler);
}
#endif

#ifdef USE_HARDIIC_PROTOCOL
void test_graphic_hardiic_functionalities()
{
    CCDeviceHandler handler;
    on_test_init_hardiic_oled(&handler);

    __test_common(&handler);
}
#endif

#ifdef USE_SOFTSPI_PROTOCOL
void test_graphic_softspi_functionalities()
{
    CCDeviceHandler handler;
    on_test_init_softspi_oled(&handler);

    __test_common(&handler);
}
#endif

#ifdef USE_HARDSPI_PROTOCOL
void test_graphic_hardspi_functionalities()
{
    CCDeviceHandler handler;
    on_test_init_hardspi_oled(&handler);

    __test_common(&handler);
}
#endif