#ifndef CCGraphic_MenuItem_H
#define CCGraphic_MenuItem_H
#include "Graphic/CCGraphic_common.h"
/* This version we use simple menu Item */

/* announced the menu type for the further usage */
typedef struct __CCGraphic_Menu CCGraphic_Menu;

#define NO_SUB_MENU     (NULL)

typedef struct __CCGraphic_MenuItem{
    char*               text;
    CCGraphic_Menu*     subMenu;
    CCGraphic_Menu*     parentMenu;
}CCGraphic_MenuItem;


void CCGraphic_MenuItem_register_menuItem(
    CCGraphic_MenuItem* item, 
    CCGraphic_Menu*     parentMenu, 
    char*               text,
    CCGraphic_Menu*     subMenu
);

#endif