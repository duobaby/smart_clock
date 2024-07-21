#include "thread_config.h"
#include "gpio.h"
#include "stm32f4xx_hal.h"

static void key_thread_entry(void *parameter);

/**
 * @brief thread config
 *            obj         name        entry    stack_size  priority  tick
 */
thread_config thread_key("key", key_thread_entry, 256, 12, 20);

/**
 * @brief 
 * 
 * @param parameter 
 */
static void key_thread_entry(void* parameter) {
    static uint8_t state = GPIO_PIN_SET;
    gpio_dev key(GPIOA,GPIO_PIN_0,GPIO_MODE_INPUT,GPIO_PULLUP,GPIO_SPEED_FREQ_LOW);
    key.init();
    while (1) {
        state = key.get();
        if (state == GPIO_PIN_RESET) {
            rt_kprintf("key down\r\n");
        }
        thread_key.sleep(50);
    }
}


