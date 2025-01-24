#include "Test/GraphicTest/graphic_test.h"
#include "stm32f1xx_hal.h"
#include "Graphic/widgets/base/CCGraphic_TextItem/CCGraphic_TextItem.h"
#include "Graphic/widgets/components/CCGraphic_TextEdit/CCGraphic_TextEdit.h"
#include <stdio.h> // for snprintf


void on_test_component_textEdit_test(CCDeviceHandler* handle)
{
    CCGraphicTextEdit   edit;
    CCGraphic_AsciiTextItem item;
    CCGraphic_Point p;
    p.x = 0;
    p.y = 0;
    CCGraphic_Size acceptablesize = 
        CCGraphicWidget_MaxAcceptable_Size(handle);
    CCGraphicWidget_init_AsciiTextItem(
        &item, p, acceptablesize, ASCII_6x8
    );
    CCGraphic_init_CCGraphicTextEdit(
        &edit, handle, &item
    );
    edit.acquired_stepped_update = 1;
    char* sources = "Charlie: Hello, World!This is Charlie's Speeking!";
    edit.operations.setText(&edit, sources);
    HAL_Delay(3000);
    sources = "...May I Help you?";
    edit.operations.appendText(&edit, sources);
    HAL_Delay(3000);
    sources = "Jack: Yes!Please Offer me a lemon juice";
    edit.operations.newLineText(&edit, sources);
    HAL_Delay(3000);
    edit.operations.clear(&edit);
    float expected_price = 20.22;

    char jackWord[64];

    snprintf(jackWord, 64, "Jack: Is the lemon juice %.2f dollar?", expected_price);
    edit.operations.setText(&edit, jackWord);
    HAL_Delay(3000);
    sources = "Charlie: Yes, it is";
    edit.operations.newLineText(&edit, sources);
    HAL_Delay(3000);
    edit.operations.clear(&edit);
    sources = "That's the end of the conversation!";
    edit.operations.setText(&edit, sources);
    HAL_Delay(3000);
    edit.operations.operation.hide(&edit);
}

#include "Graphic/widgets/components/CCGraphic_Frame/CCGraphic_Frame.h"
void on_test_component_frame_test(CCDeviceHandler* device)
{
    CCGraphic_Frame frame;
    CCGraphic_createDeviceFrame(&frame, device,5, 5, 2);
    frame.operation.operation.show(&frame);
    HAL_Delay(1000);
    frame.operation.operation.hide(&frame);
}