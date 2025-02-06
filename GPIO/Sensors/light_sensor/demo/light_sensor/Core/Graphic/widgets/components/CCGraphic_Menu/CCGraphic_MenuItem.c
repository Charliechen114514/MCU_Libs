#include "Graphic/widgets/components/CCGraphic_Menu/CCGraphic_MenuItem.h"

void CCGraphic_MenuItem_register_menuItem(
    CCGraphic_MenuItem* item, 
    CCGraphic_Menu*     parentMenu, 
    char*               text,
    CCGraphic_Menu*     subMenu
)
{
    item->subMenu       = subMenu;
    item->text          = text;
    item->parentMenu    = parentMenu;
}


