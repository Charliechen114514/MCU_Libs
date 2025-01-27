#include "Graphic/widgets/components/CCGraphic_Menu/CCGraphic_Menu.h"
#include "Graphic/widgets/components/CCGraphic_Menu/CCGraphic_MenuItem.h"
#include "Graphic/widgets/components/CCGraphic_TextEdit/CCGraphic_TextEdit.h"
#include "Graphic/widgets/base/CCGraphic_TextItem/CCGraphic_TextConfig.h"
#include "Graphic/widgets/base/CCGraphic_TextItem/CCGraphic_TextItem.h"
#include "Graphic/widgets/base/CCGraphic_Image/CCGraphic_Image.h"
#include "Graphic/widgets/components/CCGraphic_Menu/CCGraphic_MenuConfigure.h"
#include "Graphic/CCGraphic_device_adapter.h"

// update the menu
static void __pvt_update(CCGraphic_Menu* menu)
{
    menu->internelTextEdit->operations.operation.update(
        menu->internelTextEdit
    );
}

// update the animation state
static void __pvt_setAnimationShowState(
    CCGraphic_MenuAnimations* animations, uint8_t is_doing)
{
    /* inited state is undoing */
    if(is_doing == animations->is_doing){
        return;
    }
    animations->handler->operations.reverseArea_function(
        animations->handler, 
        animations->tl_point.x, animations->tl_point.y,
        animations->animationOffsetSize.width, 
        animations->animationOffsetSize.height
    );
    animations->is_doing = is_doing;
    animations->handler->operations.update_device_function(
        animations->handler);
}

/*
    followings provide the show/hide Icon's
    layout caculations
*/
static void __pvt_providePoint(
    CCGraphic_Menu* menu, 
    CCGraphic_Point* p, 
    uint8_t icons_enabled)
{
    p->x = icons_enabled ? ICON_WIDTH : 0;
    p->y = 0;
}

static void __pvt_provideSize(
    CCGraphic_Menu* menu, 
    CCGraphic_Size* size, 
    uint8_t icons_enabled
){
    size->width = menu->internelTextEdit->handle->TexthandleSize.width - 
        (icons_enabled ? ICON_HEIGHT : 0);
    size->height = menu->internelTextEdit->handle->TexthandleSize.height;
}

static inline CCGraphic_Menu* __pvt_current_owns_subMenu(CCGraphic_Menu* menu)
{
    return  menu->menuItemArrays[
            menu->current_offset].subMenu;
}

static inline CCGraphic_Menu* __pvt_owns_parent_current(CCGraphic_Menu* menu)
{
    return  menu->menuItemArrays[
            menu->current_offset].parentMenu;
}

void __pvt_show_textEditOnly(CCGraphic_Menu* menu)
{
    if(menu->menuArraySize == 0){
        return;
    }
    __pvt_setAnimationShowState(menu->animation_holder, 0);
    CCGraphicTextEdit* edit = menu->internelTextEdit;
    edit->operations.setText(edit, menu->menuItemArrays[0].text);
    for(uint8_t i = 1; i < menu->menuArraySize; i++)
    {
        edit->operations.newLineText(edit, menu->menuItemArrays[i].text);
    }
    __pvt_setAnimationShowState(menu->animation_holder, 1);    
}

static void __pvt_showIcon(CCGraphic_Menu* menu)
{
    if(!menu->icons_sources) return;
    menu->icon_state = 1;
    CCGraphic_Point tlp;
    CCGraphic_Size  _size;
    __pvt_providePoint(menu, &tlp, 1);
    __pvt_provideSize(menu, &_size, 1);
    __pvt_setAnimationShowState(menu->animation_holder, 0);
    menu->internelTextEdit->operations.relocate(
        menu->internelTextEdit, tlp, _size
    );
    for(uint8_t i = 0; i < menu->icon_size; i++)
    {
        CCGraphicWidget_draw_image(
            menu->internelTextEdit->borrowed_device, 
            &menu->icons_sources[i]);
    }
    __pvt_setAnimationShowState(menu->animation_holder, 1);
    __pvt_show_textEditOnly(menu);
}

static void __pvt_hideIcon(CCGraphic_Menu* menu)
{
    if(!menu->icons_sources) return;
    CCGraphic_Point tlp;
    CCGraphic_Size  _size;
    menu->icon_state = 0;
    __pvt_providePoint(menu, &tlp, 0);
    __pvt_provideSize(menu, &_size, 0);
    __pvt_setAnimationShowState(menu->animation_holder, 0);
    menu->internelTextEdit->operations.relocate(
        menu->internelTextEdit, tlp, _size
    );
    // clear the icons
    menu->internelTextEdit->borrowed_device->operations.clearArea_function(
        menu->internelTextEdit->borrowed_device, 
        0, 0, ICON_WIDTH, ICON_HEIGHT * menu->icon_size
    );
    __pvt_show_textEditOnly(menu);
}

/* do by steps */
static void __pvt_doByStep(CCGraphic_MenuAnimations* animations)
{
    if(!animations->is_doing) return;
    animations->handler->operations.reverseArea_function(
        animations->handler, 
        animations->tl_point.x, animations->tl_point.y,
        animations->animationOffsetSize.width, 
        animations->animationOffsetSize.height
    );
    animations->tl_point.x += animations->x_step;
    animations->tl_point.y += animations->y_step;
    animations->handler->operations.reverseArea_function(
        animations->handler, 
        animations->tl_point.x, animations->tl_point.y,
        animations->animationOffsetSize.width, 
        animations->animationOffsetSize.height
    );
    animations->handler->operations.update_device_function(
        animations->handler);
}

static void __pvt_do_as_immediate(
    CCGraphic_MenuAnimations* animations, 
    CCGraphic_Point*        end_tpl)
{
    if(!animations->is_doing) return;
    animations->handler->operations.reverseArea_function(
        animations->handler, 
        animations->tl_point.x, animations->tl_point.y,
        animations->animationOffsetSize.width, 
        animations->animationOffsetSize.height
    );
    animations->tl_point = *end_tpl;
    animations->handler->operations.reverseArea_function(
        animations->handler, 
        animations->tl_point.x, animations->tl_point.y,
        animations->animationOffsetSize.width, 
        animations->animationOffsetSize.height
    );
    animations->handler->operations.update_device_function(
        animations->handler);
}



static void __pvt_setAnimationShowState_wrapper(CCGraphic_Menu* menu, uint8_t state)
{
    if(!menu->animation_holder) return;
    __pvt_setAnimationShowState(menu->animation_holder, state);
}


static void __pvt_init_animations(
    CCGraphic_Menu*             menu,
    CCGraphic_MenuAnimations*   animations)
{
    /* no animations are registered */
    if(animations == NULL){
        return;
    }
    CCGraphic_AsciiTextItem* internelTextEdit = 
        menu->internelTextEdit->handle;
    /* calculate the animations holding size */
    animations->tl_point = 
        internelTextEdit->tl_point;
    
    animations->animationOffsetSize.height = __fetch_font_size(
        internelTextEdit->font_size
    ).height;
    animations->animationOffsetSize.width = 
        internelTextEdit->TexthandleSize.width;
    animations->handler = menu->internelTextEdit->borrowed_device;
    animations->x_step = _DEFAULT_X_STEP;
    animations->y_step = _DEFAULT_Y_STEP;
    animations->op.doByStep = __pvt_doByStep;
    /* set state */
    animations->is_doing    = 0;
}

void __pvt_hide_CCGraphic_Menu(CCGraphic_Menu* menu)
{
    __pvt_hideIcon(menu);
    menu->internelTextEdit->operations.operation.hide(menu->internelTextEdit);
    CCGraphic_MenuAnimations* animation = menu->animation_holder;
    if(!animation) return;
    if(animation->is_doing){
        __pvt_setAnimationShowState(animation, 0);
    }
}

/* drawer functions */
void __pvt_show_CCGraphic_Menu(CCGraphic_Menu* menu)
{
    __pvt_show_textEditOnly(menu);   
}

void __pvt_do_stepped_animate(
    CCGraphic_MenuAnimations* animations, 
    CCGraphic_Point* end_tl_p 
)
{
    // do the down side animations
    if(animations->y_step < 0){
        while(animations->tl_point.y > end_tl_p->y){
            __pvt_doByStep(animations);
        }
    }
    // do the upper size animations
    else
    {
        while(animations->tl_point.y < end_tl_p->y){
            __pvt_doByStep(animations);
        }        
    }
    
}

static void __pvt_switchIndex(
    CCGraphic_Menu* menu, uint8_t index)
{
    // if is same, do nothing
    if(index == menu->current_offset) return;

    // down case
    if(index > menu->current_offset){
        if(menu->animation_holder->y_step < 0){
            menu->animation_holder->y_step = 
                -menu->animation_holder->y_step;
        }
    }
    // upper case
    else{
        if(menu->animation_holder->y_step > 0){
            menu->animation_holder->y_step = 
                -menu->animation_holder->y_step;
        }
    }
    menu->current_offset = index;
    CCGraphic_Point end_tlp;
    end_tlp = menu->animation_holder->tl_point; 
    end_tlp.y = index * menu->animation_holder->animationOffsetSize.height;
    if(menu->enabled_animations)
        __pvt_do_stepped_animate(menu->animation_holder, &end_tlp);
    else
        __pvt_do_as_immediate(menu->animation_holder, &end_tlp);
}

static void __pvt_setIcon(CCGraphic_Menu* menu,CCGraphic_Image* sources, uint8_t size)
{
    menu->icons_sources = sources;
    menu->icon_size = size;
    for(uint8_t i = 0; i < menu->icon_size; i++)
    {
        sources[i].image_size.height    = ICON_HEIGHT;
        sources[i].image_size.width     = ICON_WIDTH;
        sources[i].point.x              = 0;
        sources[i].point.y              = i * ICON_HEIGHT;
    }
    __pvt_showIcon(menu);
}



static CCGraphic_Menu* __pvt_enterSub(CCGraphic_Menu* parentMenu)
{
    uint8_t cached_icon_state = parentMenu->icon_state;
    CCGraphic_Menu* subone = __pvt_current_owns_subMenu(parentMenu);
    if(!subone) return NULL;
    // clear the display of self
    parentMenu->operations.common.hide(parentMenu);
    parentMenu->icon_state = cached_icon_state;
    if(subone->icon_state){
        subone->operations.showIcon(subone);
    }else{
        subone->operations.common.show(subone);
    }
    return subone;
}

static CCGraphic_Menu* __pvt_backParent(CCGraphic_Menu* subMenu)
{
    uint8_t cached_icon_state = subMenu->icon_state;
    CCGraphic_Menu* parentMenu = __pvt_owns_parent_current(subMenu);
    if(!parentMenu) return NULL;
    // clear the display of self
    subMenu->operations.common.hide(subMenu);
    subMenu->icon_state = cached_icon_state;
    if(parentMenu->icon_state){
        parentMenu->operations.showIcon(parentMenu);
    }else{
        parentMenu->operations.common.show(parentMenu);
    }
    
    return parentMenu;
}

void CCGraphic_init_Menu(
    CCGraphic_Menu*             blank_menu,
    CCGraphic_MenuItem*         menuItemArrays,
    uint8_t                     menuArraySize,
    CCGraphicTextEdit*          configured_menu,
    CCGraphic_MenuAnimations*   blank_animations,
    uint8_t                     enabled_animations 
)
{
    blank_menu->internelTextEdit    = configured_menu;
    blank_menu->menuItemArrays      = menuItemArrays;
    blank_menu->menuArraySize       = menuArraySize;
    blank_menu->animation_holder    = blank_animations;
    blank_menu->current_offset      = 0;
    blank_menu->icon_state          = 0;
    blank_menu->enabled_animations = enabled_animations;

    // map the functions
    blank_menu->operations.common.hide      = (Hide)__pvt_hide_CCGraphic_Menu;
    blank_menu->operations.common.show      = (Show)__pvt_show_CCGraphic_Menu;
    blank_menu->operations.common.update    = (Update)__pvt_update;
    blank_menu->operations.switchToIndex    = __pvt_switchIndex;
    blank_menu->operations.enabled_showAnimations = 
        __pvt_setAnimationShowState_wrapper;
    
    // icons
    blank_menu->operations.setIcon = __pvt_setIcon;
    blank_menu->operations.hideIcon = __pvt_hideIcon;
    blank_menu->operations.showIcon = __pvt_showIcon;
    blank_menu->operations.enterSub = __pvt_enterSub;
    blank_menu->operations.backParent = __pvt_backParent;
    __pvt_init_animations(blank_menu, blank_animations);
}