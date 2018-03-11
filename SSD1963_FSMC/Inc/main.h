/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H__
#define __MAIN_H__

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define KEY_1_Pin GPIO_PIN_3
#define KEY_1_GPIO_Port GPIOE
#define KEY_0_Pin GPIO_PIN_4
#define KEY_0_GPIO_Port GPIOE
#define LED_A_Pin GPIO_PIN_6
#define LED_A_GPIO_Port GPIOA
#define LED_B_Pin GPIO_PIN_7
#define LED_B_GPIO_Port GPIOA
#define SD_CMD_Pin GPIO_PIN_2
#define SD_CMD_GPIO_Port GPIOD
#define TOUCH_IRQ_Pin GPIO_PIN_3
#define TOUCH_IRQ_GPIO_Port GPIOD
#define TOUCH_IRQ_EXTI_IRQn EXTI3_IRQn

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        HAL drivers code
  */
/* #define USE_FULL_ASSERT    1U */

/* USER CODE BEGIN Private defines */
#define Clock8x7			&Dmd8x7Clock
#define Clock13x20			&Dmd13x20Clock
#define Mono9							&FreeMono9pt7b
#define Mono12						&FreeMono12pt7b
#define Mono18						&FreeMono18pt7b
#define Mono24						&FreeMono24pt7b
#define MonoBold9					&FreeMonoBold9pt7b
#define MonoBold12				&FreeMonoBold12pt7b
#define MonoBold18				&FreeMonoBold18pt7b
#define MonoBold24				&FreeMonoBold24pt7b
#define MonoBoldOblique9	&FreeMonoBoldOblique9pt7b
#define MonoBoldOblique12	&FreeMonoBoldOblique12pt7b
#define MonoBoldOblique18	&FreeMonoBoldOblique18pt7b
#define MonoBoldOblique24	&FreeMonoBoldOblique24pt7b
#define MonoOblique9			&FreeMonoOblique9pt7b
#define MonoOblique12			&FreeMonoOblique12pt7b
#define MonoOblique18			&FreeMonoOblique18pt7b
#define MonoOblique24			&FreeMonoOblique24pt7b
#define Sans9							&FreeSans9pt7b
#define Sans12						&FreeSans12pt7b
#define Sans18						&FreeSans18pt7b
#define Sans24						&FreeSans24pt7b
#define SansBold9					&FreeSansBold9pt7b
#define SansBold12				&FreeSansBold12pt7b
#define SansBold18				&FreeSansBold18pt7b
#define SansBold24				&FreeSansBold24pt7b
#define SansBoldOblique9	&FreeSansBoldOblique9pt7b
#define SansBoldOblique12	&FreeSansBoldOblique12pt7b
#define SansBoldOblique18	&FreeSansBoldOblique18pt7b
#define SansBoldOblique24	&FreeSansBoldOblique24pt7b
#define SansOblique9			&FreeSansOblique9pt7b
#define SansOblique12			&FreeSansOblique12pt7b
#define SansOblique18			&FreeSansOblique18pt7b
#define SansOblique24			&FreeSansOblique24pt7b
#define Serif9						&FreeSerif9pt7b
#define Serif12						&FreeSerif12pt7b
#define Serif18						&FreeSerif18pt7b
#define Serif24						&FreeSerif24pt7b
#define SerifBold9				&FreeSerifBold9pt7b
#define SerifBold12				&FreeSerifBold12pt7b
#define SerifBold18				&FreeSerifBold18pt7b
#define SerifBold24				&FreeSerifBold24pt7b
#define SerifBoldItalic9	&FreeSerifBoldItalic9pt7b
#define SerifBoldItalic12	&FreeSerifBoldItalic12pt7b
#define SerifBoldItalic18	&FreeSerifBoldItalic18pt7b
#define SerifBoldItalic24	&FreeSerifBoldItalic24pt7b
#define SerifItalic9			&FreeSerifItalic9pt7b
#define SerifItalic12			&FreeSerifItalic12pt7b
#define SerifItalic18			&FreeSerifItalic18pt7b
#define SerifItalic24			&FreeSerifItalic24pt7b
#define SevenSegNum				&FreeSevenSegNum
#define Org								&Org_01
#define Pixel							&Picopixel
#define Tiny3							&Tiny3x3a2pt7b
#define Thumb							&TomThumb
/* USER CODE END Private defines */

#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
