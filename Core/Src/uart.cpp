#include "uart.h"


extern "C" {
    UART_HandleTypeDef uart1;
}
uart_dev uart_terminal(USART1, 115200, &uart1);

void uart_dev::init() {
    uart_handle->Instance = uart;
    uart_handle->Init.BaudRate = baud;
    uart_handle->Init.WordLength = USART_WORDLENGTH_8B;
    uart_handle->Init.StopBits = USART_STOPBITS_1;
    uart_handle->Init.Parity = USART_PARITY_NONE;
    uart_handle->Init.Mode = USART_MODE_TX_RX;
    uart_handle->Init.HwFlowCtl = UART_HWCONTROL_NONE;
    uart_handle->Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(uart_handle) != HAL_OK) {
        Error_Handler();
    }
}

void uart_dev::io_init() {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if (uart == USART1) {
        __HAL_RCC_GPIOA_CLK_ENABLE();
        GPIO_InitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_10;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    }
    else if (uart == USART2) {
        __HAL_RCC_GPIOA_CLK_ENABLE();
        GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    }
}
