#include "gpio_driver.h"

static inline void __open_gpio_clk(char letter){
    switch(letter){
        case 'A': 
        case 'a': __HAL_RCC_GPIOA_CLK_ENABLE()  ;break;
        case 'B': 
        case 'b': __HAL_RCC_GPIOB_CLK_ENABLE()  ;break;
        case 'C': 
        case 'c': __HAL_RCC_GPIOC_CLK_ENABLE()  ;break;
        case 'D': 
        case 'd': __HAL_RCC_GPIOD_CLK_ENABLE()  ;break;
        case 'E': 
        case 'e': __HAL_RCC_GPIOE_CLK_ENABLE()  ;break;
        case 'F': 
        case 'f': __HAL_RCC_GPIOF_CLK_ENABLE()  ;break;
        case 'G': 
        case 'g': __HAL_RCC_GPIOG_CLK_ENABLE()  ;break;
        default: break;
    }
}

void createGPIO(CCGPIO* blank, GPIO_Letter gpio_base, GPIO_Offset offset, char letter)
{
    blank->letter_case      = gpio_base;
    blank->offset           = offset;
    __open_gpio_clk(letter);
}

void createGPIOConfig(CCGPIOConfig* config, SpeedConfigureType speed, 
                                        PullPushConfigureType pull_push, 
                                        ModeConfigureType mode)
{
    config->mode = mode;
    config->pull_or_push = pull_push;
    config->speed = speed;
}

void setGPIOConfig(CCGPIO* gpio, CCGPIOConfig* config)
{
    GPIO_InitTypeDef initing_gpio;
    initing_gpio.Mode = config->mode;
    initing_gpio.Pin = gpio->offset;
    initing_gpio.Pull = config->pull_or_push;
    initing_gpio.Speed = config->speed;
    HAL_GPIO_Init(gpio->letter_case, &initing_gpio);
}

void setGPIOState(CCGPIO* gpio, GPIOState state)
{
    if(state){
        HAL_GPIO_WritePin(gpio->letter_case, gpio->offset, GPIO_PIN_SET);
    }else{
        HAL_GPIO_WritePin(gpio->letter_case, gpio->offset, GPIO_PIN_RESET);
    }
}

void toggleGPIOState(CCGPIO* gpio)
{
    HAL_GPIO_TogglePin(gpio->letter_case, gpio->offset);
}

GPIOState gainGPIOState(CCGPIO* gpio)
{
    return HAL_GPIO_ReadPin(gpio->letter_case, gpio->offset) == GPIO_PIN_SET ? ON : OFF;
}