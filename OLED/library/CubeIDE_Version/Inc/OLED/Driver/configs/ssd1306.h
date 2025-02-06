#ifndef SSD1306_H
#define SSD1306_H

/* hardware level defines */
#define PORT_SCL    GPIOB
#define PORT_SDA    GPIOB
#define PIN_SCL     GPIO_PIN_8
#define PIN_SDA     GPIO_PIN_9

#define OLED_ENABLE_GPIO_SCL_CLK() __HAL_RCC_GPIOB_CLK_ENABLE()
#define OLED_ENABLE_GPIO_SDA_CLK() __HAL_RCC_GPIOB_CLK_ENABLE()


#define OLED_WIDTH  (128)
#define OLED_HEIGHT (8)

#define POINT_X_MAX     (OLED_WIDTH)
#define POINT_Y_MAX     (OLED_HEIGHT * 8)

#endif