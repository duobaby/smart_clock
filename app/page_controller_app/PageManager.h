/**
 * @file PageManager.h
 * @author 周大珂 (2324603761@qq.com)
 * @brief 
 * @version master
 * @date 2024-07-13
 * 
 * @copyright 个人开发者 zkk
 * 
 */
#ifndef __PAGEMANAGER_H
#define __PAGEMANAGER_H

#include <stdint.h>
#include <lvgl.h>


/**
 * @brief 实现主页面ui以及应用逻辑
 * 
 */

/**
 * @brief 实现子页面下的ui，以及页面深度处理
 * 
 */
typedef struct {
    // No additional members or functions needed
    void (*page_ui_init)();

}page_t;

class pagemanager {
private:
    uint8_t size;
    page_t *stack = new page_t[size];
public:
    lv_obj_t *screen;
    pagemanager(lv_obj_t *screen, const uint8_t size, void (*ui_init)()) 
        : screen(screen), size(size), ui_init(ui_init) {
      //  screen = lv_obj_create(lv_scr_act());
    }
    void (*ui_init)();
    friend void home_init();
    friend void left_init();
    friend void right_init();
    friend void event_cb(lv_event_t *e);
};

extern pagemanager home;
extern pagemanager left;
extern pagemanager right;

void ui_init(void);

#endif
