#ifndef __UART_H_
#define __UART_H_

#include "main.h"

class uart_dev {
private:
    USART_TypeDef *uart;
    uint32_t baud;
    UART_HandleTypeDef *uart_handle;
    void io_init();
public:
    uart_dev(USART_TypeDef *uart,uint32_t band,UART_HandleTypeDef *uart_handle) 
        : uart(uart), baud(band), uart_handle(uart_handle) {}
    void init();
};

extern uart_dev uart_terminal;

#endif // !__UART_H_