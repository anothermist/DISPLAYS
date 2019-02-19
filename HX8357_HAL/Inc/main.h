/* USER CODE BEGIN Header */
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
  * COPYRIGHT(c) 2019 STMicroelectronics
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
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_Pin GPIO_PIN_13
#define LED_GPIO_Port GPIOC
#define DB0_Pin GPIO_PIN_0
#define DB0_GPIO_Port GPIOA
#define DB1_Pin GPIO_PIN_1
#define DB1_GPIO_Port GPIOA
#define DB2_Pin GPIO_PIN_2
#define DB2_GPIO_Port GPIOA
#define DB3_Pin GPIO_PIN_3
#define DB3_GPIO_Port GPIOA
#define DB4_Pin GPIO_PIN_4
#define DB4_GPIO_Port GPIOA
#define DB5_Pin GPIO_PIN_5
#define DB5_GPIO_Port GPIOA
#define DB6_Pin GPIO_PIN_6
#define DB6_GPIO_Port GPIOA
#define DB7_Pin GPIO_PIN_7
#define DB7_GPIO_Port GPIOA
#define LCD_RST_Pin GPIO_PIN_0
#define LCD_RST_GPIO_Port GPIOB
#define LCD_CS_Pin GPIO_PIN_1
#define LCD_CS_GPIO_Port GPIOB
#define LCD_WR_Pin GPIO_PIN_10
#define LCD_WR_GPIO_Port GPIOB
#define LCD_RS_Pin GPIO_PIN_11
#define LCD_RS_GPIO_Port GPIOB
#define DB13_Pin GPIO_PIN_13
#define DB13_GPIO_Port GPIOB
#define DB14_Pin GPIO_PIN_14
#define DB14_GPIO_Port GPIOB
#define DB15_Pin GPIO_PIN_15
#define DB15_GPIO_Port GPIOB
#define DB8_Pin GPIO_PIN_8
#define DB8_GPIO_Port GPIOA
#define DB9_Pin GPIO_PIN_9
#define DB9_GPIO_Port GPIOA
#define DB10_Pin GPIO_PIN_10
#define DB10_GPIO_Port GPIOA
#define DB11_Pin GPIO_PIN_11
#define DB11_GPIO_Port GPIOA
#define DB12_Pin GPIO_PIN_12
#define DB12_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */
#define _3_Tiny                &Font_3_Tiny
#define _3_PicoPixel           &Font_3_PicoPixel
#define _3_TomThumb_Extended   &Font_3_TomThumb_Extended
#define _5_Org                 &Font_5_Org
#define _8_Sinclair            &Font_8_Sinclair
#define _8_Sinclair_Inverted   &Font_8_Sinclair_Inverted
#define _8_Tiny                &Font_8_Tiny
#define _8_Myke                &Font_8_Myke
#define _8_Default             &Font_8_Default
#define _8_Retro               &Font_8_Retro
#define _9_Mono                &Font_9_Mono
#define _9_Mono_Bold           &Font_9_Mono_Bold
#define _9_Mono_Bold_Oblique   &Font_9_Mono_Bold_Oblique
#define _9_Mono_Oblique        &Font_9_Mono_Oblique
#define _9_Sans                &Font_9_Sans
#define _9_Sans_Bold           &Font_9_Sans_Bold
#define _9_Sans_Bold_Oblique   &Font_9_Sans_Bold_Oblique
#define _9_Sans_Oblique        &Font_9_Sans_Oblique
#define _9_Serif               &Font_9_Serif
#define _9_Serif_Bold          &Font_9_Serif_Bold
#define _9_Serif_Bold_Italic   &Font_9_Serif_Bold_Italic
#define _9_Serif_Italic        &Font_9_Serif_Italic
#define _12_Mono               &Font_12_Mono
#define _12_Mono_Bold          &Font_12_Mono_Bold
#define _12_Mono_Bold_Oblique  &Font_12_Mono_Bold_Oblique
#define _12_Mono_Oblique       &Font_12_Mono_Oblique
#define _12_Sans               &Font_12_Sans
#define _12_Sans_Bold          &Font_12_Sans_Bold
#define _12_Sans_Bold_Oblique  &Font_12_Sans_Bold_Oblique
#define _12_Sans_Oblique       &Font_12_Sans_Oblique
#define _12_Serif              &Font_12_Serif
#define _12_Serif_Bold         &Font_12_Serif_Bold
#define _12_Serif_Bold_Italic  &Font_12_Serif_Bold_Italic
#define _12_Serif_Italic       &Font_12_Serif_Italic
#define _16_Arial              &Font_16_Arial
#define _16_Arial_Bold         &Font_16_Arial_Bold
#define _16_Arial_Italic       &Font_16_Arial_Italic
#define _16_Default            &Font_16_Default
#define _16_FranklinGothic     &Font_16_FranklinGothic
#define _16_Hallfetica         &Font_16_Hallfetica
#define _16_Nadianne           &Font_16_Nadianne
#define _16_Sinclair           &Font_16_Sinclair
#define _16_Sinclair_Inverted  &Font_16_Sinclair_Inverted
#define _16_Swiss_Outline      &Font_16_Swiss_Outline
#define _16_Matrix_Full        &Font_16_Matrix_Full
#define _16_Matrix_Full_Slash  &Font_16_Matrix_Full_Slash
#define _16_Matrix_Num         &Font_16_Matrix_Num
#define _16_Arial_Round        &Font_16_Arial_Round
#define _16_OCR                &Font_16_OCR
#define _16_Segment_16_Full    &Font_16_Segment_16_Full
#define _16_Grotesk            &Font_16_Grotesk
#define _16_Grotesk_Bold       &Font_16_Grotesk_Bold
#define _16_Retro              &Font_16_Retro
#define _18_Mono               &Font_18_Mono
#define _18_Mono_Bold          &Font_18_Mono_Bold
#define _18_Mono_Bold_Oblique  &Font_18_Mono_Bold_Oblique
#define _18_Mono_Oblique       &Font_18_Mono_Oblique
#define _18_Sans               &Font_18_Sans
#define _18_Sans_Bold          &Font_18_Sans_Bold
#define _18_Sans_Bold_Oblique  &Font_18_Sans_Bold_Oblique
#define _18_Sans_Oblique       &Font_18_Sans_Oblique
#define _18_Serif              &Font_18_Serif
#define _18_Serif_Bold         &Font_18_Serif_Bold
#define _18_Serif_Bold_Italic  &Font_18_Serif_Bold_Italic
#define _18_Serif_Italic       &Font_18_Serif_Italic
#define _24_Matrix_Num         &Font_24_Matrix_Num
#define _24_Inconsola          &Font_24_Inconsola
#define _24_Ubuntu             &Font_24_Ubuntu
#define _24_Ubuntu_Bold        &Font_24_Ubuntu_Bold
#define _24_Segment_16_Full    &Font_24_Segment_16_Full
#define _24_Mono               &Font_24_Mono
#define _24_Mono_Bold          &Font_24_Mono_Bold
#define _24_Mono_Bold_Oblique  &Font_24_Mono_Bold_Oblique
#define _24_Mono_Oblique       &Font_24_Mono_Oblique
#define _24_Grotesk            &Font_24_Grotesk
#define _24_Grotesk_Bold       &Font_24_Grotesk_Bold
#define _24_Sans               &Font_24_Sans
#define _24_Sans_Bold          &Font_24_Sans_Bold
#define _24_Sans_Bold_Oblique  &Font_24_Sans_Bold_Oblique
#define _24_Sans_Oblique       &Font_24_Sans_Oblique
#define _24_Serif              &Font_24_Serif
#define _24_Serif_Bold         &Font_24_Serif_Bold
#define _24_Serif_Bold_Italic  &Font_24_Serif_Bold_Italic
#define _24_SerifItalic        &Font_24_SerifItalic
#define _32_Dingbats           &Font_32_Dingbats
#define _32_Special            &Font_32_Special
#define _32_Calibri_Bold       &Font_32_Calibri_Bold
#define _32_Arial_Num_Plus     &Font_32_Arial_Num_Plus
#define _32_Matrix_Num         &Font_32_Matrix_Num
#define _32_Segment_7_Full     &Font_32_Segment_7_Full
#define _32_Segment_7_Num_Plus &Font_32_Segment_7_Num_Plus
#define _32_Segment_16_Full    &Font_32_Segment_16_Full
#define _32_Segment_18_Full    &Font_32_Segment_18_Full
#define _32_Grotesk            &Font_32_Grotesk
#define _32_Grotesk_Bold       &Font_32_Grotesk_Bold
#define _40_Segment_16_Full    &Font_40_Segment_16_Full
#define _48_Battery            &Font_48_Battery
#define _48_Segment_16_Num     &Font_48_Segment_16_Num
#define _64_Segment_16_Num     &Font_64_Segment_16_Num
#define _64_Segment_7_Num      &Font_64_Segment_7_Num
#define _96_Segment_7_Num      &Font_96_Segment_7_Num
#define _96_Segment_16_Num     &Font_96_Segment_16_Num
#define _128_Segment_16_Num    &Font_128_Segment_16_Num
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
