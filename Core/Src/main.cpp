#include "lcd.h"
#include "spi.h"
#include "main.h"
#include "delay.h"
#include "tp.h"
#include "thread_config.h"
#include "lvgl.h"
extern "C" void SystemClock_Config(void);
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
int main(void)
{   
    
    // GPIO_InitTypeDef GPIO_InitStruct = {0};
    // __HAL_RCC_GPIOC_CLK_ENABLE();
    // GPIO_InitStruct.Pin = GPIO_PIN_13;
    // GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    // GPIO_InitStruct.Pull = GPIO_NOPULL;
    // GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    // HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
     delay.init();
//     // thread_key.create();
//     lcd_Dev.init();

//    // lcd_Dev.LCD_Fill(0,0,LCD_W,LCD_H-40,BLACK);
// 	delay.ms(10);
//     lcd_Dev.LCD_ShowString(240/2-40,280/2,(const unsigned char *)"hello",WHITE,BLACK,16,0);
//     lcd_Dev.LCD_Fill(0,0,240,280-40,WHITE);
//     delay.ms(1000);
// 	lcd_Dev.LCD_Fill(0,LCD_H/2-24-20,LCD_W,LCD_H/2+49-20,BLACK);
    MX_SPI1_Init();
    MX_DMA_Init();
  	LCD_Init();
	LCD_Fill(0,0,LCD_W,LCD_H,BLACK);
	delay.ms(10);
	LCD_ShowString(72,LCD_H/2-20,(uint8_t*)"Welcome!",WHITE,BLACK,24,0);//12*6,16*8,24*12,32*16
	LCD_ShowString(42,LCD_H/2+48-20,(uint8_t*)"OV-Watch V2.3",WHITE,BLACK,24,0);
	delay.ms(1000);
	LCD_Fill(0,LCD_H/2-24-20,LCD_W,LCD_H/2+49-20,BLACK);
   // touch_pad.init();
    //创建一个btn对象
    while (1) {
        // 设置引脚为高电平
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);

        // 延时一段时间
        rt_thread_mdelay(500);

        // 设置引脚为低电平
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
        // // 延时一段时间
        rt_thread_mdelay(500);
    }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
     */
   __HAL_RCC_PWR_CLK_ENABLE();
   __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 12;
    RCC_OscInitStruct.PLL.PLLN = 96;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 4;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
    {
        Error_Handler();
    }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
