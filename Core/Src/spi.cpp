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
    GPIO_InitTypeDef spi_gpio = {0};
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

SPI_HandleTypeDef hspi1;
DMA_HandleTypeDef hdma_spi1_tx;

/* SPI1 init function */
void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi1.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

void HAL_SPI_MspInit(SPI_HandleTypeDef* spiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(spiHandle->Instance==SPI1)
  {
  /* USER CODE BEGIN SPI1_MspInit 0 */

  /* USER CODE END SPI1_MspInit 0 */
    /* SPI1 clock enable */
    __HAL_RCC_SPI1_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**SPI1 GPIO Configuration
    PB3     ------> SPI1_SCK
    PB5     ------> SPI1_MOSI
    */
    GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* SPI1 DMA Init */
    /* SPI1_TX Init */
    hdma_spi1_tx.Instance = DMA2_Stream2;
    hdma_spi1_tx.Init.Channel = DMA_CHANNEL_2;
    hdma_spi1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_spi1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_spi1_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_spi1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    hdma_spi1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    hdma_spi1_tx.Init.Mode = DMA_NORMAL;
    hdma_spi1_tx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_spi1_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_spi1_tx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(spiHandle,hdmatx,hdma_spi1_tx);

  /* USER CODE BEGIN SPI1_MspInit 1 */

  /* USER CODE END SPI1_MspInit 1 */
  }
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef* spiHandle)
{

  if(spiHandle->Instance==SPI1)
  {
  /* USER CODE BEGIN SPI1_MspDeInit 0 */

  /* USER CODE END SPI1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SPI1_CLK_DISABLE();

    /**SPI1 GPIO Configuration
    PB3     ------> SPI1_SCK
    PB5     ------> SPI1_MOSI
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_3|GPIO_PIN_5);

    /* SPI1 DMA DeInit */
    HAL_DMA_DeInit(spiHandle->hdmatx);
  /* USER CODE BEGIN SPI1_MspDeInit 1 */

  /* USER CODE END SPI1_MspDeInit 1 */
  }
}

