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
    gpio_dev key(GPIOA,GPIO_PIN_0,GPIO_MODE_INPUT,GPIO_NOPULL,GPIO_SPEED_FREQ_LOW);
    while (1) {
        uint8_t state = key.get();
        thread_key.sleep(10);
        if (state == GPIO_PIN_RESET) {
            rt_kprintf("key down\r\n");
        }
        thread_key.sleep(10);
    }
}


