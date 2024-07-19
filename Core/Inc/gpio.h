#ifndef __GPIO_H_
#define __GPIO_H_

#include "main.h"

class gpio_dev {
private:
    GPIO_TypeDef *gpio;
    uint32_t pin;
    uint32_t mode;
    uint32_t pull;
    uint32_t speed;
    uint32_t alternate;
public:
    gpio_dev(GPIO_TypeDef *_gpio, uint32_t _pin, uint32_t _mode, uint32_t _pull, uint32_t _speed,uint32_t alternate=0)
    : gpio(_gpio), pin(_pin), mode(_mode), pull(_pull), speed(_speed),alternate(alternate) {}
    void init();
    void set(GPIO_PinState dat) {HAL_GPIO_WritePin(gpio, pin, dat);}
    uint8_t get() {return HAL_GPIO_ReadPin(gpio, pin);}
    void toggle() {HAL_GPIO_TogglePin(gpio, pin);}
};
#endif // !__GPIO_H_