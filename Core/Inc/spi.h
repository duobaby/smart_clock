#ifndef __SPI_H_
#define __SPI_H_


#include "main.h"

#define use_spi_tx_dma 1

class spi_io {   
protected:
    SPI_TypeDef *spi_x;
public: 
    spi_io(SPI_TypeDef *spi) : spi_x(spi) {}
    virtual void init();
};

class spi_dev : public spi_io{
protected:
    uint32_t spi_mode_x;
    #if use_spi_tx_dma
        DMA_Stream_TypeDef *dma_stream_x;
        uint32_t dma_channel_x;
        uint32_t dma_direction_x;
    #endif
public:
    SPI_HandleTypeDef *spi_handle_x;
    DMA_HandleTypeDef *spi_dma_handle_x;
    #if use_spi_tx_dma
        spi_dev(SPI_TypeDef *spi,uint32_t spi_mode,SPI_HandleTypeDef * spi_handle, \
            DMA_Stream_TypeDef *dma_stream,uint32_t dma_channel,uint32_t dma_direction,DMA_HandleTypeDef *spi_dma_handle) \
            :spi_io (spi), spi_mode_x(spi_mode),dma_stream_x(dma_stream), dma_channel_x(dma_channel), \
            dma_direction_x(dma_direction),spi_handle_x(spi_handle),spi_dma_handle_x(spi_dma_handle){}
    #else
        spi_dev(SPI_TypeDef *spi,uint32_t spi_mode) 
            :spi_x(spi),spi_mode_x(spi_mode){}
    #endif
    virtual void init(void);
};

extern SPI_HandleTypeDef spi1;
extern DMA_HandleTypeDef spi_dma1;


#endif // !__SPI_H_
