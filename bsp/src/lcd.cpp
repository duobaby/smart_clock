#include "lcd.h"
#include "spi.h"
#include "delay.h"
#include "stdio.h"
#include "stdlib.h"
#define lcd_dev_config SPI1,SPI_MODE_MASTER,&spi1,DMA2_Stream2,DMA_CHANNEL_2,DMA_MEMORY_TO_PERIPH,&spi_dma1

lcd_dev lcd_Dev(lcd_dev_config);
void lcd_dev::lcd_io::init(void) {
    GPIO_InitTypeDef lcd_gpio = {0};
	
	__HAL_RCC_GPIOC_CLK_ENABLE();
 	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
    
	lcd_gpio.Pin = RES_PIN;	 
 	lcd_gpio.Mode = GPIO_MODE_OUTPUT_PP; 		 //推挽输出
	lcd_gpio.Speed = GPIO_SPEED_FREQ_VERY_HIGH;//速度50MHz
 	HAL_GPIO_Init(RES_PORT, &lcd_gpio);	  //初始化GPIOB
 	HAL_GPIO_WritePin(RES_PORT, RES_PIN, GPIO_PIN_SET);

	lcd_gpio.Pin = DC_PIN;	 
 	lcd_gpio.Mode = GPIO_MODE_OUTPUT_PP; 		 //推挽输出
	lcd_gpio.Speed = GPIO_SPEED_FREQ_VERY_HIGH;//速度50MHz
 	HAL_GPIO_Init(DC_PORT, &lcd_gpio);	  //初始化GPIOC
 	HAL_GPIO_WritePin(DC_PORT, DC_PIN, GPIO_PIN_SET);

	lcd_gpio.Pin = CS_PIN;	 
 	lcd_gpio.Mode = GPIO_MODE_OUTPUT_PP; 		 //推挽输出
	lcd_gpio.Speed = GPIO_SPEED_FREQ_VERY_HIGH;//速度50MHz
 	HAL_GPIO_Init(CS_PORT, &lcd_gpio);	  //初始化GPIOD
 	HAL_GPIO_WritePin(CS_PORT, CS_PIN, GPIO_PIN_SET);
}

void lcd_dev::init(void)
{   
	lcd_io::init();
    spi_dev::init();
    LCD_CS_Clr();
	
	LCD_RES_Clr();	//复位
	delay.ms(100);
	LCD_RES_Set();
	delay.ms(100);
	
	LCD_WR_REG(0x11); 
	delay.ms(120); 
	LCD_WR_REG(0x36); 
	if(USE_HORIZONTAL==0)LCD_WR_DATA8(0x00);
	else if(USE_HORIZONTAL==1)LCD_WR_DATA8(0xC0);
	else if(USE_HORIZONTAL==2)LCD_WR_DATA8(0x70);
	else LCD_WR_DATA8(0xA0);

	LCD_WR_REG(0x3A);
	LCD_WR_DATA8(0x05);

	LCD_WR_REG(0xB2);
	LCD_WR_DATA8(0x0C);
	LCD_WR_DATA8(0x0C);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x33);
	LCD_WR_DATA8(0x33); 

	LCD_WR_REG(0xB7); 
	LCD_WR_DATA8(0x35);  

	LCD_WR_REG(0xBB);
	LCD_WR_DATA8(0x19);

	LCD_WR_REG(0xC0);
	LCD_WR_DATA8(0x2C);

	LCD_WR_REG(0xC2);
	LCD_WR_DATA8(0x01);

	LCD_WR_REG(0xC3);
	LCD_WR_DATA8(0x12);   

	LCD_WR_REG(0xC4);
	LCD_WR_DATA8(0x20);  

	LCD_WR_REG(0xC6); 
	LCD_WR_DATA8(0x0F);    

	LCD_WR_REG(0xD0); 
	LCD_WR_DATA8(0xA4);
	LCD_WR_DATA8(0xA1);

	LCD_WR_REG(0xE0);
	LCD_WR_DATA8(0xD0);
	LCD_WR_DATA8(0x04);
	LCD_WR_DATA8(0x0D);
	LCD_WR_DATA8(0x11);
	LCD_WR_DATA8(0x13);
	LCD_WR_DATA8(0x2B);
	LCD_WR_DATA8(0x3F);
	LCD_WR_DATA8(0x54);
	LCD_WR_DATA8(0x4C);
	LCD_WR_DATA8(0x18);
	LCD_WR_DATA8(0x0D);
	LCD_WR_DATA8(0x0B);
	LCD_WR_DATA8(0x1F);
	LCD_WR_DATA8(0x23);

	LCD_WR_REG(0xE1);
	LCD_WR_DATA8(0xD0);
	LCD_WR_DATA8(0x04);
	LCD_WR_DATA8(0x0C);
	LCD_WR_DATA8(0x11);
	LCD_WR_DATA8(0x13);
	LCD_WR_DATA8(0x2C);
	LCD_WR_DATA8(0x3F);
	LCD_WR_DATA8(0x44);
	LCD_WR_DATA8(0x51);
	LCD_WR_DATA8(0x2F);
	LCD_WR_DATA8(0x1F);
	LCD_WR_DATA8(0x1F);
	LCD_WR_DATA8(0x20);
	LCD_WR_DATA8(0x23);

	LCD_WR_REG(0x21); 

	LCD_WR_REG(0x29); 
}
void lcd_dev::dis_flush(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t *color_p)
{
	uint16_t width,height; 
	width = xend-xsta+1;
	height = yend-ysta+1;
	uint32_t size = width * height;
	LCD_Address_Set( xsta,ysta + OFFSET_Y, xend, yend + OFFSET_Y);
	
	spi_dev::spi_handle_x->Init.DataSize = SPI_DATASIZE_16BIT;
	spi_dev::spi_handle_x->Instance->CR1|=SPI_CR1_DFF;
	HAL_SPI_Transmit_DMA(spi_dev::spi_handle_x,(uint8_t*)color_p,size);
	while(__HAL_DMA_GET_COUNTER(spi_dev::spi_dma_handle_x)!=0);
	
	spi_dev::spi_handle_x->Init.DataSize = SPI_DATASIZE_8BIT;
	spi_dev::spi_handle_x->Instance->CR1&=~SPI_CR1_DFF;
}
void lcd_dev::sleep_in(void)
{
	LCD_WR_REG(0x10);
	delay.ms(100);
}

void lcd_dev::sleep_out(void)
{
	LCD_WR_REG(0x11);
	delay.ms(100);
}
/******************************************************************************
      函数说明：LCD串行数据写入函数(software SPI)
      入口数据：dat  要写入的串行数据
      返回值：  无
******************************************************************************/
inline void lcd_dev::LCD_Writ_Bus(uint8_t dat) 
{	
	HAL_SPI_Transmit(spi_dev::spi_handle_x,&dat,1,1);
}
/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void lcd_dev::LCD_WR_DATA8(uint8_t dat)
{
	LCD_Writ_Bus(dat);
}
/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void lcd_dev::LCD_WR_DATA(uint16_t dat)
{
	uint8_t temp[2];
	temp[0]=(dat>>8)&0xff;
	temp[1]=dat&0xff;
	HAL_SPI_Transmit(spi_dev::spi_handle_x,temp,2,1);
}
/******************************************************************************
      函数说明：LCD写入命令
      入口数据：dat 写入的命令
      返回值：  无
******************************************************************************/
void lcd_dev::LCD_WR_REG(uint8_t dat)
{
	LCD_DC_Clr();//写命令
	LCD_Writ_Bus(dat);
	LCD_DC_Set();//写数据
}


/******************************************************************************
      函数说明：设置起始和结束地址
      入口数据：x1,x2 设置列的起始和结束地址
                y1,y2 设置行的起始和结束地址
      返回值：  无
******************************************************************************/
void lcd_dev::LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
	LCD_WR_REG(0x2a);//列地址设置
	LCD_WR_DATA(x1);
	LCD_WR_DATA(x2);
	LCD_WR_REG(0x2b);//行地址设置
	LCD_WR_DATA(y1);
	LCD_WR_DATA(y2);
	LCD_WR_REG(0x2c);//储存器写
}




