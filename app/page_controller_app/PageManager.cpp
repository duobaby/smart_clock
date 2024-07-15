#include "PageManager.h"

void home_init();
void left_init();
void right_init();
lv_obj_t *page_home;
lv_obj_t *page_left;
lv_obj_t *page_right;
pagemanager home(page_home, 10, home_init);
pagemanager left(page_left, 10, left_init);
pagemanager right(page_right, 10, right_init);

void home_init() {
    lv_obj_t *label = lv_label_create(home.screen);
}

void left_init() {
    lv_obj_t *label = lv_label_create(left.screen);
}

void right_init() {
    lv_obj_t *label = lv_label_create(right.screen);
}











