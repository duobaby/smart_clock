#ifndef __LCD_H_
#define __LCD_H_


#include "main.h"
#include "spi.h"

class lcd_io {
public:
    virtual void init();
};

class lcd_dev : public lcd_io , public spi_dev{
private:
    void write_bus(uint8_t dat);
    void write_bit8(uint8_t dat);
    void write_bit16(uint16_t dat);
    void write_regsiter(uint8_t dat);
    void addr_set(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
public:
    lcd_dev(SPI_TypeDef *spi,uint32_t spi_mode,SPI_HandleTypeDef * spi_handle, \
            DMA_Stream_TypeDef *dma_stream,uint32_t dma_channel,uint32_t dma_direction,DMA_HandleTypeDef *spi_dma_handle) \
            :spi_dev(spi,spi_mode,spi_handle,dma_stream, \
            dma_channel,dma_direction,spi_dma_handle) {}
    virtual void init(void);
    void dis_flush(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t *color_p);
    void sleep_in(void);
    void sleep_out(void);
    void putstring(unsigned short x, unsigned short y, const unsigned char *p, unsigned char sizey, unsigned char mode, unsigned short fc = 0xffff, unsigned short bc = 0x0000);
    void putschar(unsigned short x,unsigned short y,unsigned char num,unsigned short fc,unsigned short bc,unsigned char sizey,unsigned char mode);
    void drawpoint(unsigned short x,unsigned short y,unsigned short color);
    void fill(unsigned short xsta,unsigned short ysta,unsigned short xend,unsigned short yend,unsigned short color=0x0000);
};

extern lcd_dev lcd;

#define USE_HORIZONTAL 1 //设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏

#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
    #define LCD_W 240
    #define LCD_H 280
#else
    #define LCD_W 280
    #define LCD_H 240
#endif

#if USE_HORIZONTAL == 0 || USE_HORIZONTAL == 1
	#define OFFSET_Y 20
	#define OFFSET_X 0
#else
	#define OFFSET_Y 0
	#define OFFSET_X 20
#endif
//-----------------LCD端口定义---------------- 
#define RES_PORT			GPIOB
#define RES_PIN				GPIO_PIN_4

#define DC_PORT				GPIOC
#define DC_PIN				GPIO_PIN_12

#define CS_PORT				GPIOD
#define CS_PIN				GPIO_PIN_2

#define LCD_RES_Clr()  HAL_GPIO_WritePin(RES_PORT,RES_PIN,GPIO_PIN_RESET)//RES
#define LCD_RES_Set()  HAL_GPIO_WritePin(RES_PORT,RES_PIN,GPIO_PIN_SET)

#define LCD_DC_Clr()   HAL_GPIO_WritePin(DC_PORT,DC_PIN,GPIO_PIN_RESET)//DC
#define LCD_DC_Set()   HAL_GPIO_WritePin(DC_PORT,DC_PIN,GPIO_PIN_SET)
 		     
#define LCD_CS_Clr()   HAL_GPIO_WritePin(CS_PORT,CS_PIN,GPIO_PIN_RESET)//CS
#define LCD_CS_Set()   HAL_GPIO_WritePin(CS_PORT,CS_PIN,GPIO_PIN_SET)


#endif // !__LCD_H_
