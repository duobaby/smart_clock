#include "thread_config.h"
#include "stm32f4xx_hal.h"

static void dev_key_init();
static void key_thread_entry(void *parameter);
static GPIO_PinState dev_key_scan();

#define dev_key_clk_enable() __HAL_RCC_GPIOC_CLK_ENABLE()
#define dev_key_port GPIOC
#define dev_key_pin GPIO_PIN_13
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
    GPIO_PinState key_dev_state;
    dev_key_init();
    while (1) {
        key_dev_state = dev_key_scan();
        thread_key.sleep(10);
        if (key_dev_state == GPIO_PIN_RESET) {
            rt_kprintf("key down\r\n");
        }
        thread_key.sleep(10);
    }
}



/**
 * @brief 按键设备初始化
 * 
 */
static void dev_key_init() {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    dev_key_clk_enable();
    GPIO_InitStruct.Pin = dev_key_pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(dev_key_port, &GPIO_InitStruct);
}

/**
 * @brief 读取按键是否按下，不支持连按长按
 *
 * @return uint8_t
 */
static GPIO_PinState dev_key_scan() {
    return HAL_GPIO_ReadPin(dev_key_port, dev_key_pin);
}