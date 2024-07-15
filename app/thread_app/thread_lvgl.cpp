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
thread_config thread_lvgl("lvgl", lvgl_thread_entry, 512, 5, 5);

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

    lv_obj_t *btn = lv_btn_create(lv_scr_act());
    lv_obj_set_style_bg_color(btn, lv_color_hex(0xfffffff), 0);
    lv_obj_t *btn1 = lv_btn_create(lv_scr_act());
    while (1) {
        lv_timer_handler();
        thread_lvgl.sleep(5);
    }
}
