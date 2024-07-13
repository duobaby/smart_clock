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
protected:
    lv_obj_t *screen;  //
private:
    uint8_t size;
    page_t *stack = new page_t[size];
public:
    pagemanager(lv_obj_t *screen, const uint8_t sizee, void (*ui_init)()) 
        : screen(screen), size(sizee), home_ui_init(ui_init) {
        screen = lv_obj_create(lv_scr_act());
    }
    void (*home_ui_init)();
    friend void home_init();
};


// pagemanager<> page_main;
// pagemanager page_left;
// pagemanager page_right;

#endif
