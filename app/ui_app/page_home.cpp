#include "PageManager.h"

#define max_stack 3

typedef struct {
    lv_obj_t *scr[max_stack];
    lv_obj_t *btn;
    const char *txt;
    uint8_t now_depth;
}list_menu;

list_menu page_menu[] = {
    {NULL, NULL, NULL, NULL, "wifi", 0},
    {NULL, NULL, NULL, NULL, "bluetooth", 0},
    {NULL, NULL, NULL, NULL, "video", 0},
    {NULL, NULL, NULL, NULL, "usb", 0},
    {NULL, NULL, NULL, NULL, "about", 0},
};

enum menu_list {
    wifi,
    bluetooth,
    video,
    usb,
    about,
};

void list_event_cb(lv_event_t *e) {
    lv_obj_t *list = (lv_obj_t *)lv_event_get_user_data(e);
    lv_obj_t *obj = lv_event_get_target(e);
    if(e->code != LV_EVENT_LONG_PRESSED) 
        LV_LOG_USER("Clicked: %s", lv_list_get_btn_text(list, obj));
    else {

    }
}

/**
 * @brief 入栈创建新页面并加载，栈深度++
 * 
 * @param obj 
 */
void page_push(list_menu *obj) {
    obj->scr[obj->now_depth] = lv_obj_create(NULL);
    lv_scr_load(obj->scr[obj->now_depth]);
    obj->now_depth++;
}

void page_pop(list_menu *obj) {
    lv_scr_load(obj->scr[obj->now_depth]);
    obj->now_depth--;
}

void page_clear(list_menu *obj) {
    //lv_obj_del()
}

void page_left_init() {
    lv_obj_t *list = lv_list_create(left.screen);
    lv_list_add_text(list, "Setting");
    page_menu[wifi].btn = lv_list_add_btn(list, LV_SYMBOL_WIFI, page_menu[wifi].txt);
    lv_obj_add_event_cb(page_menu[wifi].btn, list_event_cb, LV_EVENT_PRESSED, list);

    page_menu[bluetooth].btn = lv_list_add_btn(list, LV_SYMBOL_BLUETOOTH, page_menu[bluetooth].txt);
    lv_obj_add_event_cb(page_menu[bluetooth].btn, list_event_cb, LV_EVENT_PRESSED, list);

    page_menu[video].btn = lv_list_add_btn(list, LV_SYMBOL_VIDEO, page_menu[video].txt);
    lv_obj_add_event_cb(page_menu[video].btn, list_event_cb, LV_EVENT_PRESSED, list);

    page_menu[usb].btn = lv_list_add_btn(list, LV_SYMBOL_USB, page_menu[usb].txt);
    lv_obj_add_event_cb(page_menu[usb].btn, list_event_cb, LV_EVENT_PRESSED, list);

    page_menu[about].btn = lv_list_add_btn(list, NULL, page_menu[about].txt);
    lv_obj_add_event_cb(page_menu[about].btn, list_event_cb, LV_EVENT_LONG_PRESSED, list);
}

