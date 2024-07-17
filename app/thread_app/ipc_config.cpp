#ifndef _IPC_CONFIG_CPP_
#define _IPC_CONFIG_CPP_

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

ipc_sem_config ipc_sem_key("sem_key", 0, RT_WAITING_FOREVER);

// void ipc_sem_create() {
//     ipc_sem_key.create();
// }











#endif // !_IPC_CONFIG_CPP_