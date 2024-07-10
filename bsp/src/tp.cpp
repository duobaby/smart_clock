#include "tp.h"
#include "delay.h"

#define touch_pad_config GPIOB,GPIOB,GPIO_PIN_7,GPIO_PIN_6
tp touch_pad(touch_pad_config);
/* static function */
// static void CST816_RESET(void);
// static uint8_t CST816_Get_FingerNum(void);
// static uint8_t CST816_Get_ChipID(void);
// static void CST816_Config_MotionMask(uint8_t mode);
static void CST816_Config_AutoSleepTime(uint8_t time);
// static void CST816_Sleep(void);
// static void CST816_Wakeup(void);
// static void CST816_Config_MotionSlAngle(uint8_t x_right_y_up_angle);
// static void CST816_Config_NorScanPer(uint8_t Period);
// static void CST816_Config_IrqPluseWidth(uint8_t Width);
// static void CST816_Config_LpScanTH(uint8_t TH);

void tp::soft_iic_io::init(void) {
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    GPIO_InitStructure.Pin = soft_iic_io::IIC_SDA_PIN ;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(soft_iic_io::IIC_SDA_PORT, &GPIO_InitStructure);
		
    GPIO_InitStructure.Pin = soft_iic_io::IIC_SCL_PIN;
    HAL_GPIO_Init(soft_iic_io::IIC_SCL_PORT, &GPIO_InitStructure);
}   

void tp::init(void)
{   
	tp::soft_iic_io::init();
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    TOUCH_RST_CLK_ENABLE;

    /* 初始化复位引脚 */
	GPIO_InitStructure.Pin = TOUCH_RST_PIN;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Pull = GPIO_PULLUP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(TOUCH_RST_PORT, &GPIO_InitStructure);
	
	HAL_GPIO_WritePin(TOUCH_RST_PORT,TOUCH_RST_PIN,GPIO_PIN_SET);
	CST816_Config_AutoSleepTime(5);
}

void tp::get_xy(short*x,short *y) {
	uint8_t data[4];
	IIC_Read_Multi_Byte(Device_Addr,XposH,4,data);
	*x=((data[0]&0x0F)<<8)|data[1];//(temp[0]&0X0F)<<4|
	*y=((data[2]&0x0F)<<8)|data[3] + TOUCH_OFFSET_Y;//(temp[2]&0X0F)<<4|
	#if REVERSE
        *x = 239 - *x;
        *y = 279 - *y;
    #endif
}

/*
    toupad 
*/
/*
*********************************************************************************************************
*	函 数 名: CST816_IIC_ReadREG
*	功能说明: 读取触摸屏单个寄存器的数据
*	形    参：reg：寄存器地址
*	返 回 值: 返回寄存器存储的数据
*********************************************************************************************************
*/
uint8_t tp::CST816_IIC_ReadREG(uint8_t addr)
{
	return IIC_Read_One_Byte(Device_Addr,addr);
}

/*
*********************************************************************************************************
*	函 数 名: CST816_IIC_WriteREG
*	功能说明: 向触摸屏的寄存器写入数据
*	形    参：addr：寄存器地址
*						dat:	写入的数据
*	返 回 值: 返回寄存器存储的数据
*********************************************************************************************************
*/
void tp::CST816_IIC_WriteREG(uint8_t addr, uint8_t dat)
{
	IIC_Write_One_Byte(Device_Addr,addr,dat);
}

/*
*********************************************************************************************************
*	函 数 名: TOUCH_RESET
*	功能说明: 触摸屏复位
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void CST816_RESET(void)
{
	TOUCH_RST_0;
	delay.ms(10);
	TOUCH_RST_1;
	delay.ms(100);
}


/*
*********************************************************************************************************
*	函 数 名: CST816_Get_FingerNum
*	功能说明: 读取触摸屏的手指触摸个数,0xFF为睡眠
*	形    参：无
*	返 回 值: 返回芯片ID
*********************************************************************************************************
*/



/*
*********************************************************************************************************
*	函 数 名: CST816_Get_ChipID
*	功能说明: 读取触摸屏的芯片ID
*	形    参：无
*	返 回 值: 返回芯片ID
*********************************************************************************************************
*/
// uint8_t CST816_Get_ChipID(void)
// {
// 	return touch_pad.CST816_IIC_ReadREG(ChipID);
// }


/*
*********************************************************************************************************
*	函 数 名: CST816_Config_MotionMask
*	功能说明: 使能连续动作（连续左右滑动，连续上下滑动，双击）
*	形    参：mode：模式(5种)
*	返 回 值: 无
*	注    意：使能连续动作会增加响应时间
*********************************************************************************************************
*/
// void CST816_Config_MotionMask(uint8_t mode)
// {
// 	touch_pad.CST816_IIC_WriteREG(MotionMask,mode);
// }


/*
*********************************************************************************************************
*	函 数 名: CST816_Config_AutoSleepTime
*	功能说明: 规定time内无触摸，自动进入低功耗模式
*	形    参：time：时间(s)
*	返 回 值: 无
*********************************************************************************************************
*/
void CST816_Config_AutoSleepTime(uint8_t time)
{
	touch_pad.CST816_IIC_WriteREG(AutoSleepTime,time);
}

/*
*********************************************************************************************************
*	函 数 名: CST816_Sleep
*	功能说明: 进入睡眠，无触摸唤醒功能
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
// void CST816_Sleep(void)
// {
// 	touch_pad.CST816_IIC_WriteREG(SleepMode,0x03);
// }

/*
*********************************************************************************************************
*	函 数 名: CST816_Wakeup
*	功能说明: 唤醒
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
// void CST816_Wakeup(void)
// {
// 	CST816_RESET();
// }

/*
*********************************************************************************************************
*	函 数 名: CST816_Config_MotionSlAngle
*	功能说明: 手势检测滑动分区角度控制。Angle=tan(c)*10 c为以x轴正方向为基准的角度。
*	形    参：x_right_y_up_angle：角度值
*	返 回 值: 无
*********************************************************************************************************
*/
// void CST816_Config_MotionSlAngle(uint8_t x_right_y_up_angle)
// {
// 	touch_pad.CST816_IIC_WriteREG(MotionSlAngle,x_right_y_up_angle);
// }


/*
*********************************************************************************************************
*	函 数 名: CST816_Config_NorScanPer
*	功能说明: 正常快速检测周期配置函数。
*						此值会影响到LpAutoWakeTime和AutoSleepTime。 
*						单位10ms，可选值：1～30。默认值为1。
*	形    参：Period：周期值
*	返 回 值: 无
*********************************************************************************************************
*/
// void CST816_Config_NorScanPer(uint8_t Period)
// {
// 	if(Period >= 30)
// 		Period = 30;
// 	touch_pad.CST816_IIC_WriteREG(NorScanPer,Period);
// }


/*
*********************************************************************************************************
*	函 数 名: CST816_Config_IrqPluseWidth
*	功能说明: 中断低脉冲输出宽度配置函数
*	形    参：Period：周期值
*	返 回 值: 无
*********************************************************************************************************
*/
// void CST816_Config_IrqPluseWidth(uint8_t Width)
// {
// 	if(Width >= 200)
// 		Width = 200;
// 	touch_pad.CST816_IIC_WriteREG(IrqPluseWidth,Width);
// }
/*
*********************************************************************************************************
*	函 数 名: CST816_Config_NorScanPer
*	功能说明: 低功耗扫描唤醒门限配置函数。越小越灵敏。默认值48
*	形    参：TH：门限值
*	返 回 值: 无
*********************************************************************************************************
*/
// void CST816_Config_LpScanTH(uint8_t TH)
// {
// 	touch_pad.CST816_IIC_WriteREG(LpScanTH,TH);
// }

/*
    softiic  
*/
/**
  * @brief SDA线输入模式配置
  * @param None
  * @retval None
  */
void soft_iic_io::SDA_Input_Mode(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    GPIO_InitStructure.Pin = soft_iic_io::IIC_SDA_PIN;
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(soft_iic_io::IIC_SDA_PORT, &GPIO_InitStructure);
}

/**
  * @brief SDA线输出模式配置
  * @param None
  * @retval None
  */
void soft_iic_io::SDA_Output_Mode(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    GPIO_InitStructure.Pin = soft_iic_io::IIC_SDA_PIN;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(soft_iic_io::IIC_SDA_PORT, &GPIO_InitStructure);
}

/**
  * @brief SDA线输出一个位
  * @param val 输出的数据
  * @retval None
  */
void soft_iic_io::SDA_Output(uint16_t val)
{
    if ( val )
    {
        soft_iic_io::IIC_SDA_PORT->BSRR |= soft_iic_io::IIC_SDA_PIN;
    }
    else
    {
        soft_iic_io::IIC_SDA_PORT->BSRR = (uint32_t)soft_iic_io::IIC_SDA_PIN << 16U;
    }
}

/**
  * @brief SCL线输出一个位
  * @param val 输出的数据
  * @retval None
  */
void soft_iic_io::SCL_Output(uint16_t val)
{
    if ( val )
    {
        soft_iic_io::IIC_SCL_PORT->BSRR |= soft_iic_io::IIC_SCL_PIN;
    }
    else
    {
         soft_iic_io::IIC_SCL_PORT->BSRR = (uint32_t)soft_iic_io::IIC_SCL_PIN << 16U;
    }
}

/**
  * @brief SDA输入一位
  * @param None
  * @retval GPIO读入一位
  */
uint8_t soft_iic_io::SDA_Input(void)
{
    return (HAL_GPIO_ReadPin(soft_iic_io::IIC_SDA_PORT, soft_iic_io::IIC_SDA_PIN));
}

/**
  * @brief IIC起始信号
  * @param None
  * @retval None
  */
void soft_iic_io::IICStart(void)
{
    SDA_Output(1);
    delay.us(2);
    SCL_Output(1);
    delay.us(1);
    SDA_Output(0);
    delay.us(1);
    SCL_Output(0);
    delay.us(1);
}

/**
  * @brief IIC结束信号
  * @param None
  * @retval None
  */
void soft_iic_io::IICStop(void)
{
    SCL_Output(0);
    delay.us(2);
    SDA_Output(0);
    delay.us(1);
    SCL_Output(1);
    delay.us(1);
    SDA_Output(1);
    delay.us(1);
}

/**
  * @brief IIC等待确认信号
  * @param None
  * @retval None
  */
uint8_t soft_iic_io::IICWaitAck(void)
{
    unsigned short cErrTime = 5;
    SDA_Input_Mode();
    SCL_Output(1);
    while(SDA_Input())
    {
        cErrTime--;
        delay.us(1);
        if (0 == cErrTime)
        {
            SDA_Output_Mode();
            IICStop();
            return ERROR;
        }
    }
    SDA_Output_Mode();
    SCL_Output(0);
    delay.us(2);
    return SUCCESS;
}

/**
  * @brief IIC发送确认信号
  * @param None
  * @retval None
  */
void soft_iic_io::IICSendAck(void)
{
    SDA_Output(0);
    delay.us(1);
    SCL_Output(1);
    delay.us(1);
    SCL_Output(0);
    delay.us(1);
	
}

/**
  * @brief IIC发送非确认信号
  * @param None
  * @retval None
  */
void soft_iic_io::IICSendNotAck(void)
{
    SDA_Output(1);
    delay.us(1);
    SCL_Output(1);
    delay.us(1);
    SCL_Output(0);
    delay.us(2);

}

/**
  * @brief IIC发送一个字节
  * @param cSendByte 需要发送的字节
  * @retval None
  */
void soft_iic_io::IICSendByte(uint8_t cSendByte)
{
    uint8_t  i = 8;
    while (i--)
    {
        SCL_Output(0);
        delay.us(2);
        SDA_Output( cSendByte & 0x80);
        delay.us(1);
        cSendByte += cSendByte;
        delay.us(1);
        SCL_Output(1);
        delay.us(1);
    }
    SCL_Output(0);
    delay.us(2);
}

/**
  * @brief IIC接收一个字节
  * @param None
  * @retval 接收到的字节
  */
uint8_t soft_iic_io::IICReceiveByte(void)
{
    uint8_t i = 8;
    uint8_t cR_Byte = 0;
    SDA_Input_Mode();
    while (i--)
    {
        cR_Byte += cR_Byte;
        SCL_Output(0);
        delay.us(2);
        SCL_Output(1);
        delay.us(1);
        cR_Byte |=  SDA_Input();
    }
    SCL_Output(0);
    SDA_Output_Mode();
    return cR_Byte;
}

uint8_t soft_iic_io::IIC_Write_One_Byte( uint8_t daddr,uint8_t reg,uint8_t data)
{				   	  	    																 
    IICStart();  
	
	IICSendByte(daddr<<1);	    
	if(IICWaitAck())	//等待应答
	{
		IICStop();		 
		return 1;		
	}
	IICSendByte(reg);
	IICWaitAck();	   	 										  		   
	IICSendByte(data);     						   
	IICWaitAck();  		    	   
    IICStop();
	delay.us(1);
	return 0;
}

uint8_t soft_iic_io::IIC_Write_Multi_Byte( uint8_t daddr,uint8_t reg,uint8_t length,uint8_t buff[])
{			
	uint8_t i;	
    IICStart();  
	
	IICSendByte(daddr<<1);	    
	if(IICWaitAck())
	{
		IICStop();
		return 1;
	}
	IICSendByte(reg);
	IICWaitAck();	
	for(i=0;i<length;i++)
	{
		IICSendByte(buff[i]);     						   
		IICWaitAck(); 
	}		    	   
    IICStop();
	delay.us(1);
	return 0;
} 

uint8_t soft_iic_io::IIC_Read_One_Byte(uint8_t daddr,uint8_t reg)
{
	uint8_t dat;
	IICStart();
	IICSendByte(daddr<<1);
	IICWaitAck();
	IICSendByte(reg);
	IICWaitAck();
	
	IICStart();
	IICSendByte((daddr<<1)+1);
	IICWaitAck();
	dat = IICReceiveByte();
	IICSendNotAck();
	IICStop();
	return dat;
}


uint8_t soft_iic_io::IIC_Read_Multi_Byte( uint8_t daddr, uint8_t reg, uint8_t length, uint8_t buff[])
{
	uint8_t i;
	IICStart();
	IICSendByte(daddr<<1);
	if(IICWaitAck())
	{
		IICStop();		 
		return 1;		
	}
	IICSendByte(reg);
	IICWaitAck();
	
	IICStart();
	IICSendByte((daddr<<1)+1);
	IICWaitAck();
	for(i=0;i<length;i++)
	{
		buff[i] = IICReceiveByte();
		if(i<length-1)
		{IICSendAck();}
	}
	IICSendNotAck();
	IICStop();
	return 0;
}



