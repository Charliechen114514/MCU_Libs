#include "Graphic/widgets/components/CCGraphic_TextEdit/CCGraphic_TextEdit.h"
#include "Graphic/sim_app/simple_text.h"
CCGraphic_AsciiTextItem item;
static uint8_t  is_inited = 0;

static void __helper_on_set_text(CCGraphicTextEdit* edit, char* sources)
{
    edit->operations.setText(edit, sources);
}

#define SET_TEXT_CONV(SRC) do{ sources = SRC;\
    __helper_on_set_text(&edit, sources);}while(0)


static void __pvt_set_up(CCGraphicTextEdit* edit, CCDeviceHandler* handler)
{
    CCGraphic_Point p;
    p.x = 0;
    p.y = 0;
    CCGraphic_Size acceptablesize = 
        CCGraphicWidget_MaxAcceptable_Size(handler);
    CCGraphicWidget_init_AsciiTextItem(
        &item, p, acceptablesize, ASCII_6x8
    );
    CCGraphic_init_CCGraphicTextEdit(
        edit, handler, &item
    );
    edit->acquired_stepped_update = 1;
    is_inited = 1;
}


void set_simple_text(
    CCGraphicTextEdit* edit, CCDeviceHandler* handler,char* sources)
{
    if(!is_inited) __pvt_set_up(edit, handler);
    SET_TEXT_CONV(sources);
}
