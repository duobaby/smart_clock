/**
 * @file thread_config.h
 * @author 周大珂 (2324603761@qq.com)
 * @brief 
 * @version master
 * @date 2024-07-15
 * 
 * @copyright 个人开发者 zkk
 * 
 */
#ifndef __THREAD_CONFIG_H
#define __THREAD_CONFIG_H

#include "rtthread.h"

/**
 * @brief thread config，快速创建线程，
 * @use   thread.create()
 * @use   thread.sleep(1000)
 */
class thread_config
{  
private:
    const char *name;
    void (*entry)(void *param);
    rt_uint32_t stack_size;
    rt_uint8_t priority;
    rt_uint32_t tick;
public:
    rt_thread_t tid;
    thread_config(const char *name,void (*entry)(void *param),rt_uint32_t stack_size,rt_uint8_t priority,rt_uint32_t tick) {
        this->name = name;
        this->entry = entry;
        this->stack_size = stack_size;
        this->priority = priority;
        this->tick = tick;    
    }
    int create() {
        tid = rt_thread_create(name, entry, RT_NULL, stack_size, priority, tick);
        if (tid == RT_NULL) {
            rt_kprintf("%s thread create failed\n", name);
            return -1;
        }
        rt_thread_startup(tid);
        return 0;
    }
    void sleep(rt_uint16_t tick) {
        rt_thread_mdelay(tick);
    }
};

/**
 * @brief thread extern
 * 
 */
extern thread_config thread_lvgl;
extern thread_config thread_key;


#endif // !__THREAD_CONFIG_H
