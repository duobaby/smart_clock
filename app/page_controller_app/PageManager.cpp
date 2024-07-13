#include "PageManager.h"

void home_init();
lv_obj_t *page_home;
pagemanager home(page_home, 10, home_init);

void home_init() {
    lv_obj_t *label = lv_label_create(home.screen);
}