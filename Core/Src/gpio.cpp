#include "gpio.h"

void gpio_dev::init() {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if(gpio == GPIOA)
        __HAL_RCC_GPIOA_CLK_ENABLE();
    else if(gpio == GPIOB)
        __HAL_RCC_GPIOB_CLK_ENABLE();
    else if(gpio == GPIOC)
        __HAL_RCC_GPIOC_CLK_ENABLE();
    else if(gpio == GPIOD)
        __HAL_RCC_GPIOD_CLK_ENABLE();
    else if(gpio == GPIOE)
        __HAL_RCC_GPIOE_CLK_ENABLE();
    else
        while (1);
    GPIO_InitStruct.Pin = pin;
    GPIO_InitStruct.Mode = mode;
    GPIO_InitStruct.Pull = pull;
    GPIO_InitStruct.Speed = speed;
    GPIO_InitStruct.Alternate = alternate;
    HAL_GPIO_Init(gpio, &GPIO_InitStruct);
}