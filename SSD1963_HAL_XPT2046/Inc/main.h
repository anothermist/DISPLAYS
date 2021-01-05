/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#define XPT2046_IRQ_Pin GPIO_PIN_13
#define XPT2046_IRQ_GPIO_Port GPIOC
#define LCD_DB14_Pin GPIO_PIN_14
#define LCD_DB14_GPIO_Port GPIOC
#define LCD_DB15_Pin GPIO_PIN_15
#define LCD_DB15_GPIO_Port GPIOC
#define LCD_DB00_Pin GPIO_PIN_0
#define LCD_DB00_GPIO_Port GPIOA
#define LCD_DB01_Pin GPIO_PIN_1
#define LCD_DB01_GPIO_Port GPIOA
#define LCD_DB02_Pin GPIO_PIN_2
#define LCD_DB02_GPIO_Port GPIOA
#define LCD_DB03_Pin GPIO_PIN_3
#define LCD_DB03_GPIO_Port GPIOA
#define LCD_DB04_Pin GPIO_PIN_4
#define LCD_DB04_GPIO_Port GPIOA
#define LCD_DB05_Pin GPIO_PIN_5
#define LCD_DB05_GPIO_Port GPIOA
#define LCD_DB06_Pin GPIO_PIN_6
#define LCD_DB06_GPIO_Port GPIOA
#define LCD_DB07_Pin GPIO_PIN_7
#define LCD_DB07_GPIO_Port GPIOA
#define LCD_DB08_Pin GPIO_PIN_0
#define LCD_DB08_GPIO_Port GPIOB
#define LCD_DB09_Pin GPIO_PIN_1
#define LCD_DB09_GPIO_Port GPIOB
#define LCD_DB10_Pin GPIO_PIN_12
#define LCD_DB10_GPIO_Port GPIOB
#define LCD_DB11_Pin GPIO_PIN_13
#define LCD_DB11_GPIO_Port GPIOB
#define LCD_DB12_Pin GPIO_PIN_14
#define LCD_DB12_GPIO_Port GPIOB
#define LCD_DB13_Pin GPIO_PIN_15
#define LCD_DB13_GPIO_Port GPIOB
#define LCD_CS_Pin GPIO_PIN_6
#define LCD_CS_GPIO_Port GPIOB
#define LCD_RD_Pin GPIO_PIN_7
#define LCD_RD_GPIO_Port GPIOB
#define LCD_WR_Pin GPIO_PIN_8
#define LCD_WR_GPIO_Port GPIOB
#define LCD_RS_Pin GPIO_PIN_9
#define LCD_RS_GPIO_Port GPIOB
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
