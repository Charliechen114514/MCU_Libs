#ifndef CCGraphic_Image_H
#define CCGraphic_Image_H
#include "Graphic/CCGraphic_common.h"
#include "Graphic/widgets/common/CCGraphic_Size/CCGraphic_Size.h"
#include "Graphic/base/CCGraphic_Point/CCGraphic_Point.h"

typedef struct __CCGraphic_Image{
    CCGraphic_Point point;
    CCGraphic_Size  image_size;
    uint8_t*        sources_register;
}CCGraphic_Image;

void CCGraphicWidget_init_image(
    CCGraphic_Image*    image,
    CCGraphic_Point     tl_point,
    CCGraphic_Size      image_size,
    uint8_t*      sources_register
);

void CCGraphicWidget_draw_image(
    CCDeviceHandler*    handler,
    CCGraphic_Image*    image
);


#endif