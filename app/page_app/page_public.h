/**
 * @file page_public.hpp
 * @author 周大珂 (2324603761@qq.com)
 * @brief 
 * @version master
 * @date 2024-07-12
 * 
 * @copyright 个人开发者 zkk
 * 
 */

#ifndef __PAGE_PUBLIC_H
#define __PAGE_PUBLIC_H

#include "lvgl.h"

typedef struct {
    void (*init)(void);
    void (*deinit)(void);
    lv_obj_t **page_obj;  /* 用二级指针避免初始化地址为null */
} Page_t;

extern Page_t;

// /**
//  * @brief 
//  * 
//  */
// inline void page::init(void) {
    


// }

// /**
//  * @brief 
//  *  
//  */
// inline void page::deinit(void) {

// }

#endif // !__PAGE_PUBLIC_H



