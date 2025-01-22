#ifndef __CCGraphic_COMMON_H
#define __CCGraphic_COMMON_H

// points abstraction
#ifndef uint8_t
typedef unsigned char   uint8_t;
#endif

/* graphic device handler */
typedef struct __DeviceProperty CCDeviceHandler;

/*  device all base object, a generic pointer type that can point to any type of 
    graphical item or object in the graphics system.
*/
typedef void* CCGraphicItem;


#endif