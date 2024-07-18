/**
 * @file ipc_config.h
 * @author 周大珂 (2324603761@qq.com)
 * @brief 对5种ipc进行抽象
 * @version master
 * @date 2024-07-18
 * 
 * @copyright 个人开发者 zkk
 * 
 */
#ifndef __IPC_CONFIG_H_
#define __IPC_CONFIG_H_

#include <rtthread.h>

class ipc_sem_config {
private:
    const char *name;
    rt_uint8_t start_value;
    rt_uint8_t rt_ipc_flag;
public:
    rt_sem_t sem;
    ipc_sem_config(const char *name, rt_uint8_t start_value, rt_uint8_t rt_ipc_flag) {
        this->name = name;
        this->start_value = start_value;
        this->rt_ipc_flag = rt_ipc_flag;
    }
    int create() {
        sem = rt_sem_create(name, start_value, rt_ipc_flag);
        if (sem == RT_NULL) {
            rt_kprintf("%s sem create fail\n", name);
            return -1;
        }
        return 0;
    }
    void release() {
        rt_sem_release(sem);
    }
    void sem_delete() {
        rt_sem_delete(sem);
    }
    void take(rt_tick_t timeout) {
        rt_sem_take(sem, RT_WAITING_FOREVER);
    }
};

// class ipc_mutex_config {
// private:
//     const char *name;
//     rt_uint8_t rt_ipc_flag;
// public:
//     rt_mutex_t mutex;
//     ipc_mutex_config(const char *name, rt_uint8_t rt_ipc_flag) {
//         this->name = name;
//         this->rt_ipc_flag = rt_ipc_flag;
//     }
//     int create() {
//         mutex = rt_mutex_create(name, rt_ipc_flag);
//         if (mutex == RT_NULL) {
//             rt_kprintf("%s mutex create fail\n", name);
//             return -1;
//         }
//         return 0;
//     }
//     void release() {
//         rt_mutex_release(mutex);
//     }
//     void mutex_delete() {
//         rt_mutex_delete(mutex);
//     }
//     void take(rt_tick_t timeout) {
//         rt_mutex_take(mutex, RT_WAITING_FOREVER);
//     }
// };

// class ipc_mailbox_config {
// private:
//     const char *name;
//     rt_uint32_t size;
//     rt_uint8_t rt_ipc_flag;
// public:
//     rt_mailbox_t mailbox;
//     ipc_mailbox_config(const char *name, rt_uint32_t size, rt_uint8_t rt_ipc_flag) {
//         this->name = name;
//         this->size = size;
//         this->rt_ipc_flag = rt_ipc_flag;
//     }
//     int create() {
//         mailbox = rt_mb_create(name, size, rt_ipc_flag);
//         if (mailbox == RT_NULL) {
//             rt_kprintf("%s mailbox create fail\n", name);
//             return -1;
//         }
//         return 0;
//     }
//     void mb_delete() {
//         rt_mb_delete(mailbox);
//     }
//     void send(rt_ubase_t data) {
//         rt_mb_send(mailbox, data);
//     }
//     void recv(rt_ubase_t *data, rt_uint32_t timeout) {
//         rt_mb_recv(mailbox, data, timeout);
//     }
// };

// class ipc_msgqueue_config {
// private:
//     const char *name;
//     rt_uint32_t size;
//     rt_uint32_t max_msgs;
//     rt_uint8_t rt_ipc_flag;
// public:
//     rt_mq_t msgqueue;
//     ipc_msgqueue_config(const char *name, rt_uint32_t size, rt_uint32_t max_msgs, rt_uint8_t rt_ipc_flag) {
//         this->name = name;
//         this->size = size;
//         this->max_msgs = max_msgs;
//         this->rt_ipc_flag = rt_ipc_flag;
//     }
//     int create() {
//         msgqueue = rt_mq_create(name, size, max_msgs, rt_ipc_flag);
//         if (msgqueue == RT_NULL) {
//             rt_kprintf("%s msgqueue create fail\n", name);
//             return -1;
//         }
//         return 0;
//     }

//     void msgqueue_delete() {
//         rt_mq_delete(msgqueue);
//     }
//     void send(void *data, rt_uint32_t timeout) {
//         rt_mq_send(msgqueue, data, timeout);
//     }
//     void recv(void *data, rt_uint32_t timeout) {
//         rt_mq_recv(msgqueue, data, size, timeout);
//     }
// };

// class ipc_event_config {
// private:
//     const char *name;
//     rt_uint8_t rt_ipc_flag;
// public:
//     rt_event_t event;
//     ipc_event_config(const char *name, rt_uint8_t rt_ipc_flag) {
//         this->name = name;
//         this->rt_ipc_flag = rt_ipc_flag;
//     }
//     int create() {
//         event = rt_event_create(name, rt_ipc_flag);
//         if (event == RT_NULL) {
//             rt_kprintf("%s event create fail\n", name);
//             return -1;
//         }
//         return 0;
//     }

//     void event_delete() {
//         rt_event_delete(event);
//     }
//     void send(rt_uint32_t set) {
//         rt_event_send(event,set);
//     }
//     void recv(rt_uint32_t set, rt_uint32_t opt, rt_uint32_t timeout, rt_uint32_t *recv) {
//         rt_event_recv(event, set, opt, timeout, recv);
//     }
// };
/**
 * @brief ipc_semaphare extern 
 * 
 */
extern ipc_sem_config ipc_sem_key;
void ipc_sem_create();



#endif // !__IPC_CONFIG_H_