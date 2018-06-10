
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"

/* USER CODE BEGIN Includes */
#include "ssd1306.h"

#include "fonts/Font_3_Tiny.h"
#include "fonts/Font_3_PicoPixel.h"
#include "fonts/Font_3_TomThumb_Extended.h"
#include "fonts/Font_5_Org.h"
#include "fonts/Font_8_Sinclair.h"
#include "fonts/Font_8_Sinclair_Inverted.h"
#include "fonts/Font_8_Tiny.h"
#include "fonts/Font_8_Myke.h"
#include "fonts/Font_8_Default.h"
#include "fonts/Font_8_Retro.h"
#include "fonts/Font_9_Mono.h"
#include "fonts/Font_9_Mono_Bold.h"
#include "fonts/Font_9_Mono_Bold_Oblique.h"
#include "fonts/Font_9_Mono_Oblique.h"
#include "fonts/Font_9_Sans.h"
#include "fonts/Font_9_Sans_Bold.h"
#include "fonts/Font_9_Sans_Bold_Oblique.h"
#include "fonts/Font_9_Sans_Oblique.h"
#include "fonts/Font_9_Serif.h"
#include "fonts/Font_9_Serif_Bold.h"
#include "fonts/Font_9_Serif_Bold_Italic.h"
#include "fonts/Font_9_Serif_Italic.h"
#include "fonts/Font_12_Mono.h"
#include "fonts/Font_12_Mono_Bold.h"
#include "fonts/Font_12_Mono_Bold_Oblique.h"
#include "fonts/Font_12_Mono_Oblique.h"
#include "fonts/Font_12_Sans.h"
#include "fonts/Font_12_Sans_Bold.h"
#include "fonts/Font_12_Sans_Bold_Oblique.h"
#include "fonts/Font_12_Sans_Oblique.h"
#include "fonts/Font_12_Serif.h"
#include "fonts/Font_12_Serif_Bold.h"
#include "fonts/Font_12_Serif_Bold_Italic.h"
#include "fonts/Font_12_Serif_Italic.h"
#include "fonts/Font_16_Arial.h"
#include "fonts/Font_16_Arial_Bold.h"
#include "fonts/Font_16_Arial_Italic.h"
#include "fonts/Font_16_Default.h"
#include "fonts/Font_16_FranklinGothic.h"
#include "fonts/Font_16_Hallfetica.h"
#include "fonts/Font_16_Nadianne.h"
#include "fonts/Font_16_Sinclair.h"
#include "fonts/Font_16_Sinclair_Inverted.h"
#include "fonts/Font_16_Swiss_Outline.h"
#include "fonts/Font_16_Matrix_Full.h"
#include "fonts/Font_16_Matrix_Full_Slash.h"
#include "fonts/Font_16_Matrix_Num.h"
#include "fonts/Font_16_Arial_Round.h"
#include "fonts/Font_16_OCR.h"
#include "fonts/Font_16_Segment_16_Full.h"
#include "fonts/Font_16_Grotesk.h"
#include "fonts/Font_16_Grotesk_Bold.h"
#include "fonts/Font_16_Retro.h"
#include "fonts/Font_18_Mono.h"
#include "fonts/Font_18_Mono_Bold.h"
#include "fonts/Font_18_Mono_Bold_Oblique.h"
#include "fonts/Font_18_Mono_Oblique.h"
#include "fonts/Font_18_Sans.h"
#include "fonts/Font_18_Sans_Bold.h"
#include "fonts/Font_18_Sans_Bold_Oblique.h"
#include "fonts/Font_18_Sans_Oblique.h"
#include "fonts/Font_18_Serif.h"
#include "fonts/Font_18_Serif_Bold.h"
#include "fonts/Font_18_Serif_Bold_Italic.h"
#include "fonts/Font_18_Serif_Italic.h"
#include "fonts/Font_24_Matrix_Num.h"
#include "fonts/Font_24_Inconsola.h"
#include "fonts/Font_24_Ubuntu.h"
#include "fonts/Font_24_Ubuntu_Bold.h"
#include "fonts/Font_24_Segment_16_Full.h"
#include "fonts/Font_24_Mono.h"
#include "fonts/Font_24_Mono_Bold.h"
#include "fonts/Font_24_Mono_Bold_Oblique.h"
#include "fonts/Font_24_Mono_Oblique.h"
#include "fonts/Font_24_Grotesk.h"
#include "fonts/Font_24_Grotesk_Bold.h"
#include "fonts/Font_24_Sans.h"
#include "fonts/Font_24_Sans_Bold.h"
#include "fonts/Font_24_Sans_Bold_Oblique.h"
#include "fonts/Font_24_Sans_Oblique.h"
#include "fonts/Font_24_Serif.h"
#include "fonts/Font_24_Serif_Bold.h"
#include "fonts/Font_24_Serif_Bold_Italic.h"
#include "fonts/Font_24_SerifItalic.h"
#include "fonts/Font_32_Dingbats.h"
#include "fonts/Font_32_Special.h"
#include "fonts/Font_32_Calibri_Bold.h"
#include "fonts/Font_32_Arial_Num_Plus.h"
#include "fonts/Font_32_Matrix_Num.h"
#include "fonts/Font_32_Segment_7_Full.h"
#include "fonts/Font_32_Segment_7_Num_Plus.h"
#include "fonts/Font_32_Segment_16_Full.h"
#include "fonts/Font_32_Segment_18_Full.h"
#include "fonts/Font_32_Grotesk.h"
#include "fonts/Font_32_Grotesk_Bold.h"
#include "fonts/Font_40_Segment_16_Full.h"
#include "fonts/Font_48_Battery.h"
#include "fonts/Font_48_Segment_16_Num.h"
#include "fonts/Font_64_Segment_16_Num.h"
#include "fonts/Font_64_Segment_7_Num.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
unsigned int out=0;
float t=0;

char buff[40];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
	SSD1306_Init();

	//LCD_Rect_Fill(100, 50, 10, 10, 1);	
	//LCD_Circle(100, 50, 15, 0, 3, 1);	
	//LCD_Rect_Round(100, 47, 15, 15, 3, 1);
	
	LCD_Ellipse(100, 47, 15, 10, 0, 1);
	
	//LCD_Fill(1);
	
	LCD_Font(5, 25, "OLED Test", _8_Retro, 1, 1);
	LCD_Font(5, 45, "DISPLAY", _16_Default, 1, 1);
	LCD_Font(10, 60, "0123 Font", _9_Mono, 1, 1);
	
	LCD_UpdateScreen();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
		HAL_Delay(500);
		
		LCD_Battery(0, 110, out);

		out++; t = t + 0.1;
		if (t > 9.9) { t = 0.1; }
		if (out > 10) { out = 0; }
  }
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* I2C1 init function */
static void MX_I2C1_Init(void)
{

  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
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
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
