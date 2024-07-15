#include "thread_config.h"
#include "stm32f4xx_hal.h"

static void dev_key_init();
static void key_thread_entry(void *parameter);

/**
 * @brief thread config
 *            obj         name        entry    stack_size  priority  tick
 */
thread_config thread_key("key", key_thread_entry, 256, 6, 2);

/**
 * @brief 
 * 
 * @param parameter 
 */
static void key_thread_entry(void* parameter) {
    dev_key_init();
    while (1) {
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
        thread_key.sleep(500);
    }
}

/**
 * @brief 按键设备初始化
 * 
 */
static void dev_key_init() {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOC_CLK_ENABLE();
    GPIO_InitStruct.Pin = GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}