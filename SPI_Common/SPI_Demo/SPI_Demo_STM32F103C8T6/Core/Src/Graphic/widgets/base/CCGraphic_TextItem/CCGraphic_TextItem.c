#include "Graphic/widgets/base/CCGraphic_TextItem/CCGraphic_TextItem.h"
#include "Graphic/widgets/base/CCGraphic_TextItem/CCGraphic_TextConfig.h"
#include "Graphic/widgets/base/CCGraphic_Image/CCGraphic_Image.h"
#include "Graphic/CCGraphic_device_adapter.h"
#include <string.h>
void CCGraphicWidget_init_AsciiTextItem(
    CCGraphic_AsciiTextItem*    item,
    CCGraphic_Point             tl_point,
    CCGraphic_Size              textHandleSize,
    Ascii_Font_Size             text_size
)
{
    item->font_size         = text_size;
    item->sources_borrowed  = "";  
    item->tl_point          = tl_point;
    item->indexed_point     = tl_point;
    item->TexthandleSize    = textHandleSize;
    item->req_update        = 1;
}

void CCGraphicWidget_AsciiTextItem_setAsciiText(
    CCGraphic_AsciiTextItem*    item,
    char*                       text
)
{
    item->sources_borrowed = text;
}

void CCGraphicWidget_AsciiTextItem_setIndexedPoint(
    CCGraphic_AsciiTextItem*    item,
    CCGraphic_Point*            p
)
{
    item->indexed_point = *p;
}


void CCGraphicWidget_AsciiTextItem_relocate(
    CCGraphic_AsciiTextItem*    item,
    CCGraphic_Point             tl_point,
    CCGraphic_Size              textHandleSize
)
{
    item->tl_point          = tl_point;
    item->TexthandleSize    = textHandleSize;
}

static void __pvt_draw_char_each(
    CCDeviceHandler*    device_handle, 
    CCGraphic_Image*    borrowing_image, 
    const char ch, Ascii_Font_Size size)
{
    borrowing_image->image_size = __fetch_font_size(size);
    uint8_t* ascii = 
        __select_from_ascii_font_size(size, ch);
    borrowing_image->sources_register = ascii;
    CCGraphicWidget_draw_image(
        device_handle, 
        borrowing_image);
#if CCGraphic_TextDebug
    device_handle->operations.update_device_function(device_handle);
#endif
}

static uint8_t inline __pvt_should_be_next_line(
    CCDeviceHandler*                device_handle,
    CCGraphic_Point*                brpoint,
    CCGraphic_Point* cur_draw_p, Ascii_Font_Size s 
)
{
    return cur_draw_p->x + 
        (int16_t)(1.5 * __fetch_font_size(s).width) >= brpoint->x;
}

static CCGraphic_Point inline __pvt_fetch_valid_final_point(
    CCDeviceHandler* device_handle,
    CCGraphic_Size* size, CCGraphic_Point* tl
) 
{
    CCGraphic_Point br;
    /* check if the br valid */
    int16_t device_width = 0;
    device_handle->operations.property_function(
        device_handle, &device_width, CommonProperty_WIDTH
    );
    int16_t device_height = 0;
    device_handle->operations.property_function(
        device_handle, &device_height, CommonProperty_HEIGHT
    );
    br.x = tl->x + size->width;
    br.y = tl->y + size->height;
    if(device_width < br.x){br.x = device_width;}
    if(device_height < br.y){br.y = device_height;}
    return br;
}

void CCGraphicWidget_drawAsciiTextItem(
    CCDeviceHandler*            device_handle,
    CCGraphic_AsciiTextItem*    item
)
{
    if(strcmp(item->sources_borrowed, "") == 0){
        return;
    }

    CCGraphic_Image handle_draw_image;
    CCGraphic_Point draw_tl_point;

    draw_tl_point = item->indexed_point;

    const Ascii_Font_Size font_size = item->font_size;
    const CCGraphic_Size size = __fetch_font_size(font_size);
    const SizeBaseType font_width = size.width;
    const SizeBaseType font_height = size.height;

    CCGraphic_Point br = __pvt_fetch_valid_final_point(
        device_handle, &(item->TexthandleSize), &(item->tl_point) 
    );

    uint8_t offseterx = 0;
    uint8_t offsetery = 0;
    for(uint8_t i = 0; 
        item->sources_borrowed[i] != '\0'; 
        i++)
    {
        draw_tl_point.x = 
                item->indexed_point.x + offseterx * font_width;
        draw_tl_point.y = 
                item->indexed_point.y + offsetery * font_height;
        handle_draw_image.point = draw_tl_point;
        __pvt_draw_char_each(
            device_handle, 
            &handle_draw_image, 
            item->sources_borrowed[i], 
            item->font_size
        );
                // precheck if we need next line draw :)
        if(__pvt_should_be_next_line(
            device_handle,&br, &draw_tl_point, font_size))
        {
            offseterx = 0;
            // meet the max one, switch to the next line
            offsetery ++;
            item->indexed_point.x = item->tl_point.x;
        }else{
            offseterx ++;
        }
    }
    if(!item->req_update) return;
    item->indexed_point = draw_tl_point;
    item->indexed_point.x += font_width; 
}

CCGraphic_Point  CCGraphicWidget_drawAsciiTextItem_with_finPoint(
    CCDeviceHandler*            device_handle,
    CCGraphic_AsciiTextItem*    item,
    AppendMethod                method
)
{
    if(strcmp(item->sources_borrowed, "") == 0){
        return item->tl_point;
    }
    CCGraphic_Image handle_draw_image;
    CCGraphic_Point draw_tl_point;

    draw_tl_point = item->indexed_point;

    const Ascii_Font_Size font_size = item->font_size;
    const CCGraphic_Size size = __fetch_font_size(font_size);
    const SizeBaseType font_width = size.width;
    const SizeBaseType font_height = size.height;

    CCGraphic_Point br = __pvt_fetch_valid_final_point(
        device_handle, &(item->TexthandleSize), &(item->tl_point) 
    );

    uint8_t offseterx = 0;
    uint8_t offsetery = 0;
    for(uint8_t i = 0; 
        item->sources_borrowed[i] != '\0'; 
        i++)
    {
        draw_tl_point.x = 
                item->indexed_point.x + offseterx * font_width;
        draw_tl_point.y = 
                item->indexed_point.y + offsetery * font_height;
        handle_draw_image.point = draw_tl_point;
        __pvt_draw_char_each(
            device_handle, 
            &handle_draw_image, 
            item->sources_borrowed[i], 
            item->font_size
        );
                // precheck if we need next line draw :)
        if(__pvt_should_be_next_line(
            device_handle,&br, &draw_tl_point, font_size))
        {
            offseterx = 0;
            // meet the max one, switch to the next line
            offsetery ++;
            item->indexed_point.x = item->tl_point.x;
        }else{
            offseterx ++;
        }
    }
    if(!item->req_update) return draw_tl_point;
    item->indexed_point = draw_tl_point;
    item->indexed_point.x += font_width; 
    switch(method)
    {
        case CCGraphic_AsciiTextItem_AppendNextLine:
            draw_tl_point.x = item->tl_point.x;
            draw_tl_point.y += font_height;
            break;
        case CCGraphic_AsciiTextItem_AppendContinously:
            draw_tl_point.x += font_width;
            break;
        default:
            break;
    }
    return draw_tl_point;
}

CCGraphic_Point CCGraphicWidget_AsciiTextItem_on_append_point(CCGraphic_AsciiTextItem* item)
{
    return item->indexed_point;
}

CCGraphic_Point CCGraphicWidget_AsciiTextItem_on_newLine_point(CCGraphic_AsciiTextItem* item)
{
    CCGraphic_Point draw_tl_point;
    draw_tl_point.x = item->tl_point.x;
    const CCGraphic_Size size = __fetch_font_size(item->font_size);
    draw_tl_point.y = item->indexed_point.y + size.height;
    return draw_tl_point;    
}