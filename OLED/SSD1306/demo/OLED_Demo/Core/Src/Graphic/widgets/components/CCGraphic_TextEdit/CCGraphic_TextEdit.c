#include "Graphic/widgets/components/CCGraphic_TextEdit/CCGraphic_TextEdit.h"
#include "Graphic/widgets/base/CCGraphic_TextItem/CCGraphic_TextItem.h"
#include "Graphic/CCGraphic_device_adapter.h"

static void __pvt_update_text(CCGraphicTextEdit* text_self)
{
    text_self->borrowed_device->operations.update_device_function(
        text_self->borrowed_device
    );
}

static void __pvt_show(CCGraphicTextEdit* text_self)
{
    CCGraphicWidget_drawAsciiTextItem(
        text_self->borrowed_device, text_self->handle);
    if(text_self->acquired_stepped_update) 
        __pvt_update_text(text_self);
}

static void __pvt_hide(CCGraphicTextEdit* text_self)
{
    text_self->borrowed_device->operations.clearArea_function(
        text_self->borrowed_device, 
        text_self->handle->tl_point.x,
        text_self->handle->tl_point.y,
        text_self->handle->TexthandleSize.width,
        text_self->handle->TexthandleSize.height
    );
     __pvt_update_text(text_self);
}

static void __pvt_clear_text(CCGraphicTextEdit* text_self)
{
    // fetch the area that should be cleaned
    CCGraphic_Point tl      = text_self->handle->tl_point; 
    CCGraphic_Size  size    = text_self->handle->TexthandleSize;
    text_self->borrowed_device->operations.clearArea_function(
        text_self->borrowed_device, tl.x, tl.y, size.width, size.height
    );
    __pvt_update_text(text_self);
}


static void __pvt_append_text(
    CCGraphicTextEdit* text_self, char* text)
{
    /* just continued draw */
    CCGraphicWidget_AsciiTextItem_setAsciiText(text_self->handle, text);
    __pvt_show(text_self);
}

static void __pvt_newLine_text(
    CCGraphicTextEdit* text_self, char* text
)
{
    CCGraphic_Point new_begin = 
        CCGraphicWidget_AsciiTextItem_on_newLine_point(text_self->handle);
    CCGraphicWidget_AsciiTextItem_setAsciiText(text_self->handle, text);
    CCGraphicWidget_AsciiTextItem_setIndexedPoint(text_self->handle, &new_begin);
    __pvt_show(text_self);
}   

static void __pvt_setText(
    CCGraphicTextEdit* text_self, char* text    
)
{
    __pvt_clear_text(text_self);
    CCGraphicWidget_AsciiTextItem_setIndexedPoint(
        text_self->handle, 
        &(text_self->handle->tl_point));
    CCGraphicWidget_AsciiTextItem_setAsciiText(text_self->handle, text);
    __pvt_show(text_self);
}

void CCGraphic_init_CCGraphicTextEdit(
    CCGraphicTextEdit*          text_self,
    CCDeviceHandler*            handler,
    CCGraphic_AsciiTextItem*    inited
)
{
    text_self->acquired_stepped_update  = 0; 
    text_self->borrowed_device = handler;
    text_self->handle = inited;
    text_self->operations.appendText        = __pvt_append_text;
    text_self->operations.clear             = __pvt_clear_text;
    text_self->operations.newLineText       = __pvt_newLine_text;
    text_self->operations.setText           = __pvt_setText;

    text_self->operations.operation.hide    = (Hide)__pvt_hide;
    text_self->operations.operation.show    = (Show)__pvt_show;
    text_self->operations.operation.update  
            = (Update)__pvt_update_text;
}


