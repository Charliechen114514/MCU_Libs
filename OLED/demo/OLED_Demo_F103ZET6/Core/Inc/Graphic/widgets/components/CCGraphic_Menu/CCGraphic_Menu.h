#ifndef CCGraphic_Menu_H
#define CCGraphic_Menu_H
#include "CCGraphic_MenuAnimations.h"
#include "Graphic/widgets/common/CCGraphic_WidgetBase.h"


typedef struct __CCGraphic_MenuItem CCGraphic_MenuItem;
typedef struct __CCGraphicTextEdit CCGraphicTextEdit;
typedef struct __CCGraphic_Menu CCGraphic_Menu;
typedef struct __CCGraphic_Image  CCGraphic_Image;  
#define ENABLE_ANIMATIONS           (1)
#define DISABLE_ANIMATIONS          (0)
#define SHOW_ANIMATION_EFFECT       (1)
#define HIDE_ANIMATION_EFFECT       (0)

typedef struct
{
    CCGraphicWidgetCommonOperation  common;
    void (*switchToIndex)(CCGraphic_Menu*, uint8_t index);
    void (*enabled_showAnimations)(CCGraphic_Menu*, uint8_t enabled);
    void (*setIcon)(CCGraphic_Menu*, CCGraphic_Image* image, uint8_t size);
    void (*showIcon)(CCGraphic_Menu*);
    void (*hideIcon)(CCGraphic_Menu*);
    CCGraphic_Menu* (*enterSub)(CCGraphic_Menu*);
    CCGraphic_Menu* (*backParent)(CCGraphic_Menu*);
}CCGraphic_MenuOperations;

typedef struct __CCGraphic_Menu{
    CCGraphic_MenuItem*         menuItemArrays;
    uint8_t                     menuArraySize;
    CCGraphicTextEdit*          internelTextEdit;
    CCGraphic_MenuAnimations*   animation_holder;
    CCGraphic_MenuOperations    operations;
    uint8_t                     current_offset;
    uint8_t                     enabled_animations;
    CCGraphic_Image*            icons_sources;
    uint8_t                     icon_size;
    uint8_t                     icon_state;
}CCGraphic_Menu;

void CCGraphic_init_Menu(
    CCGraphic_Menu*             blank_menu,
    CCGraphic_MenuItem*         menuItemArrays,
    uint8_t                     menuArraySize,
    CCGraphicTextEdit*          configured_menu,
    CCGraphic_MenuAnimations*   blank_animations,
    uint8_t                     enabled_animations
);




#endif