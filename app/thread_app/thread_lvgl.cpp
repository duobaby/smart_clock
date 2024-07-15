#include "lvgl.h"
#include <rtthread.h>
#include "thread_config.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"

static void lvgl_thread_entry(void *parameter);

/**
 * @brief thread config
 *            obj         name        entry    stack_size  priority  tick
 */
thread_config thread_lvgl("lvgl", lvgl_thread_entry, 1024, 5, 5);

/**
 * @brief lvgl thread entry
 *
 * @param parameter
 */
static void lvgl_thread_entry(void *parameter)
{
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();
    while (1) {
        lv_timer_handler();
        thread_lvgl.sleep(5);
    }
}
