#ifndef CCGraphic_TextEdit_H
#define CCGraphic_TextEdit_H
#include "Graphic/widgets/common/CCGraphic_WidgetBase.h"
#include "Graphic/base/CCGraphic_Point/CCGraphic_Point.h"
#include "Graphic/widgets/common/CCGraphic_Size/CCGraphic_Size.h"
#include "Graphic/widgets/common/CCGraphic_WidgetBase.h"
typedef struct __CCGraphicTextEdit CCGraphicTextEdit;
typedef struct __CCGraphic_TextHandle CCGraphic_AsciiTextItem;

typedef struct{
    CCGraphicWidgetCommonOperation  operation;
    void (*appendText)(CCGraphicTextEdit*, char* appendee);
    void (*setText)(CCGraphicTextEdit*, char* text);
    void (*newLineText)(CCGraphicTextEdit*, char* text);
    void (*clear)(CCGraphicTextEdit*);
    void (*relocate)(CCGraphicTextEdit*, CCGraphic_Point p, CCGraphic_Size size);
}CCGraphicTextEdit_SupportiveOperations;

typedef struct __CCGraphicTextEdit
{
    uint8_t                                 acquired_stepped_update;
    CCDeviceHandler*                        borrowed_device;
    CCGraphicTextEdit_SupportiveOperations  operations;
    CCGraphic_AsciiTextItem*                handle;
}CCGraphicTextEdit;

void CCGraphic_init_CCGraphicTextEdit(
    CCGraphicTextEdit*          text_self,
    CCDeviceHandler*            handler,
    CCGraphic_AsciiTextItem*    inited
);


#endif