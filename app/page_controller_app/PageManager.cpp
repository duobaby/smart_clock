#include "PageManager.h"

// void home_init();
// void left_init();
// void right_init();
// void event_cb(lv_event_t *e);
// lv_obj_t *page_home;
// lv_obj_t *page_left;
// lv_obj_t *page_right;
// pagemanager home(page_home, 10, home_init);
// pagemanager left(page_left, 10, left_init);
// pagemanager right(page_right, 10, right_init);

// void event_cb(lv_event_t *e) {
//     lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
//     if(e->target == home.screen) {
//         if(dir == LV_DIR_LEFT) 
//             lv_scr_load_anim(right.screen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 0, true);
//         else if (dir == LV_DIR_RIGHT)
//             lv_scr_load_anim(left.screen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0, true);
//         else
//             lv_log("home screen event cb warning,,no this dir");
//     }
//     else if (e->target == left.screen) {
//         if(dir == LV_DIR_LEFT) 
//             lv_scr_load_anim(home.screen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 0, true);
//         else
//             lv_log("left screen event cb warning,,no this dir");
//     }
//     else if (e->target == right.screen) {
//         if(dir == LV_DIR_RIGHT) 
//             lv_scr_load_anim(home.screen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0, true);
//         else
//             lv_log("right screen event cb warning,no this dir");
//     }
// }

// void home_init() {
//     home.screen = lv_obj_create(NULL);
//     lv_obj_t *label = lv_label_create(home.screen);
//     lv_label_set_text(label, "this is home screen!!!");
//     lv_obj_add_event_cb(home.screen, event_cb, LV_EVENT_GESTURE, NULL);
// }

// void left_init() {
//     home.screen = lv_obj_create(NULL);
//     lv_obj_t *label = lv_label_create(left.screen);
//     lv_label_set_text(label, "this is left screen!!!");
//     lv_obj_add_event_cb(left.screen, event_cb, LV_EVENT_GESTURE, NULL);
// }

// void right_init() {
//     home.screen = lv_obj_create(NULL);
//     lv_obj_t *label = lv_label_create(right.screen);
//     lv_label_set_text(label, "this is right screen!!!");
//     lv_obj_add_event_cb(right.screen, event_cb, LV_EVENT_GESTURE, NULL);
// }











