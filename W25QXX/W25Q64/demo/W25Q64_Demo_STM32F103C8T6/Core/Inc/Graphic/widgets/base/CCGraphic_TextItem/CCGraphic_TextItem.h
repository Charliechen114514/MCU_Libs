#ifndef CCGraphic_TextItem_H
#define CCGraphic_TextItem_H

#include "Graphic/widgets/base/CCGraphic_TextItem/CCGraphic_TextConfig.h"
#include "Graphic/base/CCGraphic_Point/CCGraphic_Point.h"

typedef struct __CCGraphic_TextHandle{
    char*               sources_borrowed;
    CCGraphic_Point     tl_point;
    CCGraphic_Point     indexed_point; 
    CCGraphic_Size      TexthandleSize;   
    Ascii_Font_Size     font_size;
    uint8_t             req_update;
}CCGraphic_AsciiTextItem;


/**
 * @brief Initializes an AsciiTextItem with text and font size.
 *
 * This function initializes a `CCGraphic_AsciiTextItem` by setting its 
 * text and font size. The item will be ready for rendering with the 
 * specified properties (text content and font size).
 *
 * @param item       
 *      A pointer to the `CCGraphic_AsciiTextItem` that 
 *      needs to be initialized.
 * @param item_text  
 *      The text string that will be displayed by the 
 *      `CCGraphic_AsciiTextItem`.
 * @param tl_point
 *      the place where the text_draw
 * @param text_size  
 *      The font size for the text. 
 *      Should be one of the values from the 
 *      `Ascii_Font_Size` enum.
 */
void CCGraphicWidget_init_AsciiTextItem(
    CCGraphic_AsciiTextItem*    item,
    CCGraphic_Point             tl_point,
    CCGraphic_Size              textHandleSize,
    Ascii_Font_Size             text_size
);

/**
 * @brief Sets the text of an already initialized AsciiTextItem.
 *
 * This function allows changing the text of a previously initialized 
 * `CCGraphic_AsciiTextItem`. 
 * The font size remains unchanged.
 *
 * @param item  
 *  A pointer to the `CCGraphic_AsciiTextItem` 
 *  whose text needs to be updated.
 * @param text  The new text string that 
 *  will replace the current text.
 */
void CCGraphicWidget_AsciiTextItem_setAsciiText(
    CCGraphic_AsciiTextItem*    item,
    char*                       text
);

/*
 * @brief Move the draw indexed
 * @param item  
 *  A pointer to the `CCGraphic_AsciiTextItem` 
 *  whose text needs to be updated.
 * @param text  The new text string that 
 *  will replace the current text.
*/
void CCGraphicWidget_AsciiTextItem_setIndexedPoint(
    CCGraphic_AsciiTextItem*    item,
    CCGraphic_Point*            p
);

void CCGraphicWidget_AsciiTextItem_relocate(
    CCGraphic_AsciiTextItem*    item,
    CCGraphic_Point             tl_point,
    CCGraphic_Size              textHandleSize
);


/**
 * @brief Draws an AsciiTextItem on the specified device.
 *
 *  This function renders the text of a `CCGraphic_AsciiTextItem` 
 *  onto the device specified by the `device_handle`. The function will 
 *  use the font size and font data that were previously initialized 
 *  or set for the item.
 * 
 * @param device_handle  
 *      A pointer to the `CCDeviceHandler`, representing the 
 *      device on which the text will be drawn (e.g., oled).
 * @param item           
 *      A pointer to the `CCGraphic_AsciiTextItem` that contains 
 *      the text and font data to be rendered.
 */
void CCGraphicWidget_drawAsciiTextItem(
    CCDeviceHandler*            device_handle,
    CCGraphic_AsciiTextItem*    item
);


/**
 * @brief Draws an ASCII text item on a device with a given final point.
 * 
 * This function takes a device handler and an ASCII text item, 
 * and draws the text 
 * on the device at the specified final point. 
 * It returns the point at which the drawing operation was completed.
 * 
 * @param device_handle 
 *          A pointer to the device handler 
 *          where the text will be drawn.
 * @param item  
 *          A pointer to the ASCII text item that 
 *          contains the text to be drawn.
 * 
 * @return 
 *          The point (CCGraphic_Point) representing 
 *          the afterward point you should draw
 */

typedef enum {
    /* 
        This enum promised that, the point next using in set the 
        tl point will directly append the text, this can be using in
        the upper level widget to implement the appendText()
    */
    CCGraphic_AsciiTextItem_AppendContinously,
    /*
        This enum will directly tells the point that the newline should be 
        drawn, which locates the next line
    */
    CCGraphic_AsciiTextItem_AppendNextLine, 
    /* 
        do nothing, using in self defined behaviour, this will returns the 
        final char's drawing tl_pont
    */
    CCGraphic_AsciiTextItem_LastDrawPoint
}AppendMethod;

CCGraphic_Point  CCGraphicWidget_drawAsciiTextItem_with_finPoint(
    CCDeviceHandler*            device_handle,
    CCGraphic_AsciiTextItem*    item,
    AppendMethod                method
);

/* on provide the nextline draw point for the item */
CCGraphic_Point CCGraphicWidget_AsciiTextItem_on_newLine_point(CCGraphic_AsciiTextItem* item);
/* on provide the appensive draw point for the item */
CCGraphic_Point CCGraphicWidget_AsciiTextItem_on_append_point(CCGraphic_AsciiTextItem* item);
#endif