#include "Test/GraphicTest/graphic_test.h"
#include "stm32f1xx_hal.h"
#include "Graphic/widgets/base/CCGraphic_TextItem/CCGraphic_TextItem.h"
#include "Graphic/widgets/components/CCGraphic_TextEdit/CCGraphic_TextEdit.h"
#include "Graphic/widgets/components/CCGraphic_Clock/CCGraphic_Clock.h"
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
    int expected_price = 20;

    char jackWord[64];

    snprintf(jackWord, 64, "Jack: Is the lemon juice %d dollar?", expected_price);
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
#include "Graphic/widgets/components/CCGraphic_Menu/CCGraphic_Menu.h"
#include "Graphic/widgets/components/CCGraphic_Menu/CCGraphic_MenuItem.h"
#include "Graphic/widgets/base/CCGraphic_Image/CCGraphic_Image.h"


CCGraphic_MenuAnimations animations;
CCGraphic_Menu      menu;
CCGraphic_Menu      submenu;
CCGraphic_MenuItem items[] = {
    {"Play", &submenu, &menu},
    {"Help", NO_SUB_MENU, &menu},
    {"Settings", NO_SUB_MENU, &menu},
    {"Quit", NO_SUB_MENU, &menu}
};

extern const uint8_t settingsImage[];
extern const uint8_t helpImage[];
extern const uint8_t quitImage[];
extern const uint8_t playImage[];
CCGraphic_Image     icons[] = {
    {{0, 0}, {0, 0}, (uint8_t*)playImage},
    {{0, 0}, {0, 0}, (uint8_t*)helpImage},
    {{0, 0}, {0, 0}, (uint8_t*)settingsImage},
    {{0, 0}, {0, 0}, (uint8_t*)quitImage},
};

CCGraphic_MenuItem itemsSub[] = {
    {"Try",    NO_SUB_MENU, &menu},
    {"Normally", NO_SUB_MENU, &menu}
};

CCGraphic_Image     iconsSub[] = {
    {{0, 0}, {0, 0}, (uint8_t*)playImage},
    {{0, 0}, {0, 0}, (uint8_t*)playImage}
};


void on_test_component_menu(CCDeviceHandler* handler)
{
    CCGraphicTextEdit   edit;
    CCGraphic_AsciiTextItem item;
    CCGraphic_Point p;
    p.x = 0;
    p.y = 0;
    CCGraphic_Size acceptablesize = 
        CCGraphicWidget_MaxAcceptable_Size(handler);
    CCGraphicWidget_init_AsciiTextItem(
        &item, p, acceptablesize, ASCII_8x16
    );
    CCGraphic_init_CCGraphicTextEdit(
        &edit, handler, &item
    );

    CCGraphic_init_Menu(&menu, items, 4, &edit, &animations, ENABLE_ANIMATIONS);
    CCGraphic_init_Menu(&submenu, itemsSub, 2, &edit, &animations, ENABLE_ANIMATIONS);
    
    menu.operations.common.show(&menu);
    HAL_Delay(1000);
    menu.operations.switchToIndex(&menu, 1);
    HAL_Delay(500);
    menu.operations.enabled_showAnimations(&menu, 0);
    HAL_Delay(500);
    menu.operations.enabled_showAnimations(&menu, 1);
    HAL_Delay(500);
    menu.operations.enabled_showAnimations(&menu, 0);
    HAL_Delay(500);
    menu.operations.enabled_showAnimations(&menu, 1);
    
    HAL_Delay(500);
    menu.operations.switchToIndex(&menu, 2);
    HAL_Delay(500);
    menu.operations.switchToIndex(&menu, 3);
    HAL_Delay(500);
    menu.operations.switchToIndex(&menu, 1);
    HAL_Delay(500);
    // // icons
    menu.operations.setIcon(&menu, icons, 4);
    HAL_Delay(500);
    menu.operations.switchToIndex(&menu, 2);
    HAL_Delay(500);
    menu.operations.switchToIndex(&menu, 3);
    HAL_Delay(500);
    menu.operations.hideIcon(&menu);
    HAL_Delay(500);
    menu.operations.showIcon(&menu);
    HAL_Delay(500);
    menu.operations.switchToIndex(&menu, 0);
    HAL_Delay(500);
    menu.operations.switchToIndex(&menu, 0);
    HAL_Delay(1000);
    CCGraphic_Menu* sub = menu.operations.enterSub(&menu);
    HAL_Delay(1000);
    sub->operations.setIcon(sub, iconsSub, 2);
    HAL_Delay(1000);
    sub->operations.switchToIndex(sub, 1);
    HAL_Delay(1000);
    sub->operations.switchToIndex(sub, 0);
    HAL_Delay(1000);
    CCGraphic_Menu* parent = sub->operations.backParent(sub);
    (void)parent;
}

void on_test_draw_clk(CCDeviceHandler* handler)
{
    CCGrapghic_Clock    clk;
    CCGraphic_Circle    circle;
    CCGraphic_Point p;
    p.x = 32;
    p.y = 32;
    CCGraphic_init_circle(&circle, p, 30);
    initCCGraphic_Clock(&clk, handler, &circle);
    CCGraphic_Time time = {0, 0, 0};
    CCGraphic_Time addee = {1, 0, 0};
    for(uint16_t i = 0; i <= 9600; i++){
        CCGrapgic_Time_addTime(&time, &addee);
        clk.op.updateTime(&clk, &time);
        HAL_Delay(10);
    }
}