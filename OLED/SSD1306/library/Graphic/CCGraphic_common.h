#ifndef __CCGraphic_COMMON_H
#define __CCGraphic_COMMON_H

// points abstraction
#ifndef uint8_t
typedef unsigned char   uint8_t;
#endif

#ifndef int8_t
typedef signed char     int8_t;
#endif

#ifndef uint16_t
typedef unsigned short  uint16_t;
#endif

#ifndef int16_t
typedef short           int16_t;
#endif


/* graphic device handler */
typedef struct __DeviceProperty CCDeviceHandler;

/*  device all base object, a generic pointer type that can point to any type of 
    graphical item or object in the graphics system.
*/
typedef void*       CCGraphicItem;
typedef uint16_t    SizeBaseType;

#ifndef NULL
#define NULL    ((void*)0)
#endif

#endif