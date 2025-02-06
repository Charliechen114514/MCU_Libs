#ifndef TOUCH_BUTTON_H
#define TOUCH_BUTTON_H

#ifdef STM32F1
#include "stm32f1xx_hal.h"
#else
#error "Unsupportive chip type"
#endif

/* Enable Clocks settings */
#define ENABLE_TOUCHBUTTON_CLK() \
    do{\
        __HAL_RCC_GPIOA_CLK_ENABLE();\
    }while(0)

typedef struct {
    GPIO_TypeDef*   port;
    uint16_t        pin;
}TouchButtonGPIOPack;
typedef struct __TouchButton TouchButtons;
typedef uint8_t*    DetectResult;
/* callbacks */
typedef void(*TouchButtonCallback)(void);

#define DEFAULT_CALLBACK    ((TouchButtonCallback)1)
#define DUMMY_CALLBACK      ((TouchButtonCallback)0)

typedef struct {
    /* using in detect the result */
    /* you should provide a blankee array containes result */
    void (*DetectResult)(TouchButtons*, DetectResult, uint8_t);
    /* Do the callback directly! */
    void (*DoCallBack)(TouchButtons*, DetectResult, uint8_t);
    /* busy check, using in rtos for a single thread for checking*/
    void (*BusyCheck)(TouchButtons*, DetectResult, uint8_t);
}TouchButtonOperations;

typedef struct __TouchButton{
    TouchButtonGPIOPack*    detecting_gpios;
    uint8_t                 number_for_detections;
    TouchButtonCallback*    callback_group;
    TouchButtonCallback     dummy_callback;
    TouchButtonCallback     default_callback;
    TouchButtonOperations*  operations;
}TouchButtons;

void init_touchbutton(
    TouchButtons* buttons, 
    TouchButtonGPIOPack* blank_packs_array, 
    uint8_t arr_size);

typedef void(*InitFunction)(TouchButtons*);
// this means the absolute control of init
void init_touchbuttonEx(
    TouchButtons* buttons, InitFunction pvt_init);

void register_callback_group(
    TouchButtons* buttons, 
    TouchButtonCallback* group);

void register_special_dummy_callback(
    TouchButtons* button, TouchButtonCallback callback);

void register_special_default_callback(
    TouchButtons* button, TouchButtonCallback callback);

void unregister_callback_group(TouchButtons* buttons);
void scan_touchbutton(
    TouchButtons* button, DetectResult result, uint8_t check_how_many);

#endif