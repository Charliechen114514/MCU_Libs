#include "light_sensor/light_sensor.h"

#ifdef STM32F1
#include "stm32f1xx_hal_gpio.h"
#endif

static void __fetch_from_remote(LightSensor* sensor, void* package)
{
    uint8_t*    value_from_remote = (uint8_t*)package;
    *value_from_remote = !HAL_GPIO_ReadPin(sensor->gpio_package.gpio, sensor->gpio_package.pin);
}

LightSensorOperation op = {
    __fetch_from_remote
};

void init_light_sensor(
    LightSensor* blankSensor, LightSensorGPIOPack* package)
{
    blankSensor->gpio_package = *package;
    blankSensor->operations = &op;
}