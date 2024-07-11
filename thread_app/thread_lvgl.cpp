/**
 * @file thread_lvgl.cpp
 * @author 周大珂 (2324603761@qq.com)
 * @brief 
 * @version master
 * @date 2024-07-11
 * 
 * @copyright 个人开发者 zkk
 * 
 */
#include <rtthread.h>
#include "lv_port_disp.h"
#include "lv_port_indev.h"

/**
 * @brief 
 * lvgl线程入口函数
 * @param param 
 */
static void lvgl_thread_entry(void *param) {
    lv_init();            
    lv_port_disp_init();  
    lv_port_indev_init(); 
    while (1)
    {
        lv_task_handler();
        rt_thread_mdelay(5);
    }
}

/**
 * @brief 
 * lvgl线程初始化
 * @return int 
 */
int lvgl_thread_init(void) {
    rt_thread_t tid;
    //创建一个rtt的线程，并启动它
    tid = rt_thread_create("lvgl", lvgl_thread_entry, RT_NULL, 1024, 5, 10);
    if (tid != RT_NULL) {
        rt_thread_startup(tid);
        return 1;
    }
    return 0;
}
