#include "spi.h"

SPI_HandleTypeDef spi1;
DMA_HandleTypeDef spi_dma1;

#define spi_dev1_config SPI1,SPI_MODE_MASTER,&spi1,DMA2_Stream2,DMA_CHANNEL_2,DMA_MEMORY_TO_PERIPH,&spi_dma1
void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA2_Stream2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream2_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);

}
void DMA2_Stream2_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream2_IRQn 0 */

  /* USER CODE END DMA2_Stream2_IRQn 0 */
  HAL_DMA_IRQHandler(&spi_dma1);
  /* USER CODE BEGIN DMA2_Stream2_IRQn 1 */

  /* USER CODE END DMA2_Stream2_IRQn 1 */
}
void spi_dev::init(void) {
    spi_io::init();
    spi_dev::spi_handle_x->Instance = spi_dev::spi_io::spi_x;
    spi_dev::spi_handle_x->Init.Mode = spi_dev::spi_mode_x;
    spi_dev::spi_handle_x->Init.Direction = SPI_DIRECTION_2LINES;
    spi_dev::spi_handle_x->Init.DataSize = SPI_DATASIZE_8BIT;
    spi_dev::spi_handle_x->Init.CLKPolarity = SPI_POLARITY_HIGH;
    spi_dev::spi_handle_x->Init.CLKPhase = SPI_PHASE_2EDGE;
    spi_dev::spi_handle_x->Init.NSS = SPI_NSS_SOFT;
    spi_dev::spi_handle_x->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
    spi_dev::spi_handle_x->Init.FirstBit = SPI_FIRSTBIT_MSB;
    spi_dev::spi_handle_x->Init.TIMode = SPI_TIMODE_DISABLE;
    spi_dev::spi_handle_x->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    spi_dev::spi_handle_x->Init.CRCPolynomial = 10;
    if(HAL_SPI_Init(spi_dev::spi_handle_x) != HAL_OK) {
        printf("spi init error");
        return;
    }
    MX_DMA_Init();
    #if use_spi_tx_dma
        spi_dev::spi_dma_handle_x->Instance = spi_dev::dma_stream_x;
        spi_dev::spi_dma_handle_x->Init.Channel = spi_dev::dma_channel_x;
        spi_dev::spi_dma_handle_x->Init.Direction =  spi_dev::dma_direction_x;
        spi_dev::spi_dma_handle_x->Init.PeriphInc = DMA_PINC_DISABLE;
        spi_dev::spi_dma_handle_x->Init.MemInc = DMA_MINC_ENABLE;
        spi_dev::spi_dma_handle_x->Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
        spi_dev::spi_dma_handle_x->Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
        spi_dev::spi_dma_handle_x->Init.Mode = DMA_NORMAL;
        spi_dev::spi_dma_handle_x->Init.Priority = DMA_PRIORITY_LOW;
        spi_dev::spi_dma_handle_x->Init.FIFOMode = DMA_FIFOMODE_DISABLE;
        if(HAL_DMA_Init(spi_dev::spi_dma_handle_x) !=HAL_OK) {
            printf("spi_dma init error");
            return;
        }
        __HAL_LINKDMA(&spi1, hdmatx,  spi_dma1);
    #endif
}

void spi_dev::spi_io::init(void) {
    GPIO_InitTypeDef spi_gpio;
    if(spi_x == SPI1) {
        __HAL_RCC_SPI1_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();
        spi_gpio.Pin = GPIO_PIN_3 | GPIO_PIN_5;
        spi_gpio.Mode = GPIO_MODE_AF_PP;
        spi_gpio.Pull = GPIO_NOPULL;
        spi_gpio.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        spi_gpio.Alternate = GPIO_AF5_SPI1;
        HAL_GPIO_Init(GPIOB, &spi_gpio);
    }
}   

