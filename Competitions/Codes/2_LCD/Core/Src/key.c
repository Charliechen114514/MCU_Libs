#include "key.h"


void key_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    // enables the led clocks
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    
    uint16_t key_pins = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 ;
    
    GPIO_InitStruct.Pin = key_pins;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    
    key_pins = GPIO_PIN_0;
    GPIO_InitStruct.Pin = key_pins;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

static struct {
    GPIO_TypeDef*   key_port;
    uint16_t        pin_state;
    uint8_t         state;
    uint8_t         prev_state;
}states[4] = {
    {GPIOB, GPIO_PIN_0, 1, 1},
    {GPIOB, GPIO_PIN_1, 1, 1},
    {GPIOB, GPIO_PIN_2, 1, 1},
    {GPIOA, GPIO_PIN_0, 1, 1}
};

uint8_t key_scanner(uint8_t index)
{
    uint8_t result = 0;
    states[index].state = HAL_GPIO_ReadPin(states[index].key_port, states[index].pin_state);
    if(!states[index].state && states[index].prev_state){
        result = 1;
    }
    states[index].prev_state = states[index].state;
    return result;
}
