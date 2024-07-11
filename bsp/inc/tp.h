#ifndef __TP_H_
#define __TP_H_

#include "main.h"

class soft_iic_io {
protected:
    GPIO_TypeDef * IIC_SDA_PORT;
    GPIO_TypeDef * IIC_SCL_PORT;
    uint16_t IIC_SDA_PIN;
    uint16_t IIC_SCL_PIN;
    void SDA_Input_Mode();
    void SDA_Output_Mode();
    void SDA_Output(uint16_t val);
    void SCL_Output(uint16_t val);
    uint8_t SDA_Input();
    void IICStart();
    void IICStop();
    uint8_t IICWaitAck();
    void IICSendAck();
    void IICSendNotAck();
    void IICSendByte(uint8_t cSendByte);
    uint8_t IICReceiveByte();
    uint8_t IIC_Write_One_Byte(uint8_t daddr, uint8_t reg, uint8_t data);
    uint8_t IIC_Write_Multi_Byte(uint8_t daddr, uint8_t reg, uint8_t length, uint8_t buff[]);
    uint8_t IIC_Read_One_Byte(uint8_t daddr, uint8_t reg);
    uint8_t IIC_Read_Multi_Byte(uint8_t daddr, uint8_t reg, uint8_t length, uint8_t buff[]);

public:
    soft_iic_io(GPIO_TypeDef * sda_port,GPIO_TypeDef * scl_port,\
        uint16_t sda_pin,uint16_t scl_pin)
    : IIC_SDA_PORT(sda_port),IIC_SCL_PORT(scl_port),IIC_SDA_PIN(sda_pin),IIC_SCL_PIN(scl_pin) {}
    virtual void init();
};

class tp : public soft_iic_io{
private:
public:
    tp(GPIO_TypeDef * sda_port,GPIO_TypeDef * scl_port,\
        uint16_t sda_pin,uint16_t scl_pin) : soft_iic_io(sda_port,scl_port,sda_pin,scl_pin){}
    virtual void init();
    void get_xy(short *x, short *y);
    uint8_t CST816_IIC_ReadREG(uint8_t addr);
    void CST816_IIC_WriteREG(uint8_t addr, uint8_t dat);
    uint8_t Get_FingerNum(void) { return CST816_IIC_ReadREG(0x02); }   
};

extern tp touch_pad;

#define TOUCH_OFFSET_Y 15
#define REVERSE 1

#define TOUCH_RST_PIN   GPIO_PIN_8
#define TOUCH_RST_PORT  GPIOB
#define TOUCH_RST_CLK_ENABLE __HAL_RCC_GPIOB_CLK_ENABLE()
/* functions define */
#define TOUCH_RST_0 HAL_GPIO_WritePin(TOUCH_RST_PORT, TOUCH_RST_PIN, GPIO_PIN_RESET)
#define TOUCH_RST_1 HAL_GPIO_WritePin(TOUCH_RST_PORT, TOUCH_RST_PIN, GPIO_PIN_SET)

/* 设备地址 */
#define Device_Addr 	0x15

/* 触摸屏寄存器 */
#define GestureID 			0x01
#define FingerNum 			0x02
#define XposH 					0x03
#define XposL 					0x04
#define YposH 					0x05
#define YposL 					0x06
#define ChipID 					0xA7
#define SleepMode				0xE5
#define MotionMask 			0xEC
#define IrqPluseWidth 	0xED
#define NorScanPer 			0xEE
#define MotionSlAngle 	0xEF
#define LpAutoWakeTime 	0xF4
#define LpScanTH 				0xF5
#define LpScanWin 			0xF6
#define LpScanFreq 			0xF7
#define LpScanIdac 			0xF8
#define AutoSleepTime 	0xF9
#define IrqCtl 					0xFA
#define AutoReset 			0xFB
#define LongPressTime 	0xFC
#define IOCtl 					0xFD
#define DisAutoSleep 		0xFE


#endif // !__TP_H_
