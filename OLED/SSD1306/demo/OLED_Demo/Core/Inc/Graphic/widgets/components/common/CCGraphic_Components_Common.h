#ifndef CCGraphic_Components_Common_H
#define CCGraphic_Components_Common_H
#include "Graphic/CCGraphic_common.h"
#include "Graphic/widgets/common/CCGraphic_Size/CCGraphic_Size.h"  
typedef void* CCGraphic_Components;  

typedef struct
{
    void(*Resize)(CCGraphic_Components, CCGraphic_Size size);
}CCGraphic_Components_CommonOperations;


#endif