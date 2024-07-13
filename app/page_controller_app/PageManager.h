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

template <class T>
class pagemanager {
private:
    lv_obj_t *srceen;
    constexpr uint8_t size;
    T *stack;
public:
    pagemanager(lv_obj_t *srceenn,constexpr uint8_t sizee,T *stackk) {
        this->srceen = srceenn,
        this->size = sizee,
        this->stack = stackk
    }
};

pagemanager page_main;
pagemanager page_left;
pagemanager page_right;

#endif
