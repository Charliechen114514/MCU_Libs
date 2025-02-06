#include "TouchButton/touch_button.h"

static void __touch_button_dummy_callback(void){
    return;
}

static void __touch_button_default_callback(void){
    return;
}

void register_callback_group(
    TouchButtons* buttons, 
    TouchButtonCallback* group)
{
    buttons->callback_group = group;
}

void unregister_callback_group(
    TouchButtons* buttons
)
{
    buttons->callback_group = 0;
}

void register_special_dummy_callback(
    TouchButtons* button, TouchButtonCallback callback)
{
    button->dummy_callback = callback;
}

void register_special_default_callback(
    TouchButtons* button, TouchButtonCallback callback)
{
    button->default_callback = callback;
}

static void __pvt_enable_gpios(TouchButtons* buttons)
{
    ENABLE_TOUCHBUTTON_CLK();

    GPIO_InitTypeDef init = {0};
    for(uint8_t i = 0; i < buttons->number_for_detections; i++){
        init.Pin |= buttons->detecting_gpios[i].pin;
    }

    init.Mode   = GPIO_MODE_AF_INPUT;
    init.Speed  = GPIO_SPEED_FREQ_HIGH;
    init.Pull = GPIO_NOPULL;

    for(uint8_t i = 0; i < buttons->number_for_detections; i++){
        HAL_GPIO_Init(buttons->detecting_gpios[i].port, &init);
    }
}

static void __pvt_do_callback(
    TouchButtons* button, DetectResult result, uint8_t check_how_many)
{
    // prevent some bad call
    if(button->callback_group == 0) return;

    if(check_how_many > button->number_for_detections)
    {        
        check_how_many = button->number_for_detections;
    }

    for(uint8_t i = 0; i < check_how_many; i++){
        if(!result[i]) continue;

        if(button->callback_group[i] == DUMMY_CALLBACK){
            button->dummy_callback();
        }
        else if(button->callback_group[i] == DEFAULT_CALLBACK){
            button->default_callback();
        }else{
            button->callback_group[i]();
        }
    }    
}

static void __busy_check(
    TouchButtons* button, DetectResult result, uint8_t check_how_many)
{
    while(1){
        button->operations->DetectResult(
            button, result, check_how_many);
        button->operations->DoCallBack(
            button, result, check_how_many
        );
    }
}   

void scan_touchbutton(
    TouchButtons* button, DetectResult result, uint8_t check_how_many)
{
    // prevent some bad call
    if(check_how_many > button->number_for_detections)
    {        
        check_how_many = button->number_for_detections;
    }
    
    for(uint8_t i = 0; i < check_how_many; i++)
    {
        result[i] = HAL_GPIO_ReadPin(
            button->detecting_gpios[i].port,
            button->detecting_gpios[i].pin
        );
    }
}

static TouchButtonOperations op = {
    scan_touchbutton,
    __pvt_do_callback,
    __busy_check
};

void init_touchbutton(
    TouchButtons* buttons, 
    TouchButtonGPIOPack* blank_packs_array, 
    uint8_t arr_size)
{
    buttons->detecting_gpios = blank_packs_array;
    buttons->number_for_detections = arr_size; 
    buttons->callback_group = 0; 
    buttons->dummy_callback = __touch_button_dummy_callback;
    buttons->default_callback = __touch_button_default_callback;
    buttons->operations = &op;
    __pvt_enable_gpios(buttons);  
}

void init_touchbuttonEx(
    TouchButtons* buttons, InitFunction pvt_init)
{
    buttons->dummy_callback = __touch_button_dummy_callback;
    buttons->default_callback = __touch_button_default_callback;
    buttons->operations = &op;
    pvt_init(buttons);
}

