#include "led.h"
#include "gpio.h"

uint16_t __compose_all_led_gpio(void)
{
    uint16_t gpio_type = 0;
    for(uint8_t i = 0; i < 8; i++)
    {
        gpio_type |= (GPIO_PIN_8 << (i) );
    }
    return gpio_type;
}

void LED_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    // enables the led clocks
    __HAL_RCC_GPIOC_CLK_ENABLE();
    
    uint16_t led_pins = __compose_all_led_gpio();
    
    GPIO_InitStruct.Pin = led_pins;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    
    // offset 
    HAL_GPIO_WritePin(GPIOC, led_pins, GPIO_PIN_SET);
    
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}


void led_set_status(uint8_t states)
{
    HAL_GPIO_WritePin(LOCKER_GPIO_Port, LOCKER_Pin, GPIO_PIN_SET);
    
    HAL_GPIO_WritePin(GPIOC, __compose_all_led_gpio(), !states);
    
    HAL_GPIO_WritePin(LOCKER_GPIO_Port, LOCKER_Pin, GPIO_PIN_RESET);
}

/* index is from 0 for the gpio8 */
void led_set_single_status(uint8_t states, uint8_t index)
{
    HAL_GPIO_WritePin(LOCKER_GPIO_Port, LOCKER_Pin, GPIO_PIN_SET);
    
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8 << (index), !states);
    
    HAL_GPIO_WritePin(LOCKER_GPIO_Port, LOCKER_Pin, GPIO_PIN_RESET);
}

void led_flip_status(uint8_t index)
{
    HAL_GPIO_WritePin(LOCKER_GPIO_Port, LOCKER_Pin, GPIO_PIN_SET);
    
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_8 << (index));
    
    HAL_GPIO_WritePin(LOCKER_GPIO_Port, LOCKER_Pin, GPIO_PIN_RESET);   
}
