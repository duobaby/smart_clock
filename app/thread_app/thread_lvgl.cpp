#include <rtthread.h>
#include "lvgl.h"
#include "PageManager.h"
#include "thread_config.h"
#include "lcd.h"

static void lvgl_thread_entry(void *parameter);

/**
 * @brief thread config
 *            obj         name        entry    stack_size  priority  tick
 */
thread_config thread_lvgl("lvgl", lvgl_thread_entry, 1536, 11, 20);

/**
 * @brief lvgl thread entry
 *
 * @param parameter
 */
static void lvgl_thread_entry(void *parameter)
{
    ui_init();
    while (1) {
        lv_timer_handler();
        thread_lvgl.sleep(10);
    }
}
