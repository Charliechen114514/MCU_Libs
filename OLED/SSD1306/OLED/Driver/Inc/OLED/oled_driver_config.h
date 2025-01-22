#ifndef OLED_DRIVER_CONFIG_H
#define OLED_DRIVER_CONFIG_H

typedef \
    struct __OLED_Handle_SoftIIC_Handle \
    OLED_Handle_SoftIIC_Handle_Private;

typedef struct __OLED_Handle_HardIIC_Private \
OLED_Handle_HardIIC_Private;

#define OLED_ADDRESS    (0x78)
#define CMD_PREFIX      (0x00)
#define DATA_PREFIX     (0x40)

/* supportive size config */
#ifdef SSD1306
#define OLED_WIDTH      (128)
#define OLED_HEIGHT     (8)
#else
#error "Unknown OLED Chip!"
#endif

#endif