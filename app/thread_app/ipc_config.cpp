#include "ipc_config.h"

/**
 * @brief ipc semaphore config and cteate
 * 
 */
ipc_sem_config ipc_sem_key("sem_key", 0, RT_WAITING_FOREVER);
void ipc_sem_create() {
    ipc_sem_key.create();
}


/**
 * @brief ipc mutex config and cteate
 * 
 */








