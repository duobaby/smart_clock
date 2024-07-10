/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rthw.h>
#include <rtconfig.h>

#ifndef RT_USING_FINSH
#error Please uncomment the line <#include "finsh_config.h"> in the rtconfig.h 
#endif


#ifdef RT_USING_FINSH

RT_WEAK char rt_hw_console_getchar(void)
{
    /* Note: the initial value of ch must < 0 */
    volatile int ch = -1;
    // if (__HAL_UART_GET_FLAG(&huart1, UART_FLAG_RXNE) != RESET)
    // {
    //     ch = huart1.Instance->DR & 0xff;
    // }
    // else
    // {
    //     
    // }

//#error "TODO 4: Read a char from the uart and assign it to 'ch'."
    rt_thread_mdelay(10);
    return ch;
}

#endif /* RT_USING_FINSH */

