#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 20000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "ili9341.h"

#define _3x3_Tiny                 &Font_3x3_Tiny
#define _3x5_PicoPixel            &Font_3x5_PicoPixel
#define _3x5_TomThumb_Extended    &Font_3x5_TomThumb_Extended
#define _5x5_Org                  &Font_5x5_Org
#define _8x8_Sinclair             &Font_8x8_Sinclair
#define _8x8_Sinclair_Inverted    &Font_8x8_Sinclair_Inverted
#define _8x8_Tiny                 &Font_8x8_Tiny
#define _8x9_Myke                 &Font_8x9_Myke
#define _8x12_Default             &Font_8x12_Default
#define _8x16_Retro               &Font_8x16_Retro
#define _9x18_Mono                &Font_9x18_Mono
#define _9x18_Mono_Bold           &Font_9x18_Mono_Bold
#define _9x18_Mono_Bold_Oblique   &Font_9x18_Mono_Bold_Oblique
#define _9x18_Mono_Oblique        &Font_9x18_Mono_Oblique
#define _9x22_Sans                &Font_9x22_Sans
#define _9x22_Sans_Bold           &Font_9x22_Sans_Bold
#define _9x22_Sans_Bold_Oblique   &Font_9x22_Sans_Bold_Oblique
#define _9x22_Sans_Oblique        &Font_9x22_Sans_Oblique
#define _9x22_Serif               &Font_9x22_Serif
#define _9x22_Serif_Bold          &Font_9x22_Serif_Bold
#define _9x22_Serif_Bold_Italic   &Font_9x22_Serif_Bold_Italic
#define _9x22_Serif_Italic        &Font_9x22_Serif_Italic
#define _12x24_Mono               &Font_12x24_Mono
#define _12x24_Mono_Bold          &Font_12x24_Mono_Bold
#define _12x24_Mono_Bold_Oblique  &Font_12x24_Mono_Bold_Oblique
#define _12x24_Mono_Oblique       &Font_12x24_Mono_Oblique
#define _12x29_Sans               &Font_12x29_Sans
#define _12x29_Sans_Bold          &Font_12x29_Sans_Bold
#define _12x29_Sans_Bold_Oblique  &Font_12x29_Sans_Bold_Oblique
#define _12x29_Sans_Oblique       &Font_12x29_Sans_Oblique
#define _12x29_Serif              &Font_12x29_Serif
#define _12x29_Serif_Bold         &Font_12x29_Serif_Bold
#define _12x29_Serif_Bold_Italic  &Font_12x29_Serif_Bold_Italic
#define _12x29_Serif_Italic       &Font_12x29_Serif_Italic
#define _16x16_Arial              &Font_16x16_Arial
#define _16x16_Arial_Bold         &Font_16x16_Arial_Bold
#define _16x16_Arial_Italic       &Font_16x16_Arial_Italic
#define _16x16_Default            &Font_16x16_Default
#define _16x16_FranklinGothic     &Font_16x16_FranklinGothic
#define _16x16_Hallfetica         &Font_16x16_Hallfetica
#define _16x16_Nadianne           &Font_16x16_Nadianne
#define _16x16_Sinclair           &Font_16x16_Sinclair
#define _16x16_Sinclair_Inverted  &Font_16x16_Sinclair_Inverted
#define _16x16_Swiss_Outline      &Font_16x16_Swiss_Outline
#define _16x22_Matrix_Full        &Font_16x22_Matrix_Full
#define _16x22_Matrix_Full_Slash  &Font_16x22_Matrix_Full_Slash
#define _16x22_Matrix_Num         &Font_16x22_Matrix_Num
#define _16x24_Arial_Round        &Font_16x24_Arial_Round
#define _16x24_OCR                &Font_16x24_OCR
#define _16x24_Segment_16_Full    &Font_16x24_Segment_16_Full
#define _16x32_Grotesk            &Font_16x32_Grotesk
#define _16x32_Grotesk_Bold       &Font_16x32_Grotesk_Bold
#define _16x32_Retro              &Font_16x32_Retro
#define _18x35_Mono               &Font_18x35_Mono
#define _18x35_Mono_Bold          &Font_18x35_Mono_Bold
#define _18x35_Mono_Bold_Oblique  &Font_18x35_Mono_Bold_Oblique
#define _18x35_Mono_Oblique       &Font_18x35_Mono_Oblique
#define _18x42_Sans               &Font_18x42_Sans
#define _18x42_Sans_Bold          &Font_18x42_Sans_Bold
#define _18x42_Sans_Bold_Oblique  &Font_18x42_Sans_Bold_Oblique
#define _18x42_Sans_Oblique       &Font_18x42_Sans_Oblique
#define _18x42_Serif              &Font_18x42_Serif
#define _18x42_Serif_Bold         &Font_18x42_Serif_Bold
#define _18x42_Serif_Bold_Italic  &Font_18x42_Serif_Bold_Italic
#define _18x42_Serif_Italic       &Font_18x42_Serif_Italic
#define _24x29_Matrix_Num         &Font_24x29_Matrix_Num
#define _24x32_Inconsola          &Font_24x32_Inconsola
#define _24x32_Ubuntu             &Font_24x32_Ubuntu
#define _24x32_Ubuntu_Bold        &Font_24x32_Ubuntu_Bold
#define _24x36_Segment_16_Full    &Font_24x36_Segment_16_Full
#define _24x47_Mono               &Font_24x47_Mono
#define _24x47_Mono_Bold          &Font_24x47_Mono_Bold
#define _24x47_Mono_Bold_Oblique  &Font_24x47_Mono_Bold_Oblique
#define _24x47_Mono_Oblique       &Font_24x47_Mono_Oblique
#define _24x48_Grotesk            &Font_24x48_Grotesk
#define _24x48_Grotesk_Bold       &Font_24x48_Grotesk_Bold
#define _24x56_Sans               &Font_24x56_Sans
#define _24x56_Sans_Bold          &Font_24x56_Sans_Bold
#define _24x56_Sans_Bold_Oblique  &Font_24x56_Sans_Bold_Oblique
#define _24x56_Sans_Oblique       &Font_24x56_Sans_Oblique
#define _24x56_Serif              &Font_24x56_Serif
#define _24x56_Serif_Bold         &Font_24x56_Serif_Bold
#define _24x56_Serif_Bold_Italic  &Font_24x56_Serif_Bold_Italic
#define _24x56_SerifItalic        &Font_24x56_SerifItalic
#define _32x24_Dingbats           &Font_32x24_Dingbats
#define _32x32_Special            &Font_32x32_Special
#define _32x48_Calibri_Bold       &Font_32x48_Calibri_Bold
#define _32x48_Segment_16_Full    &Font_32x48_Segment_16_Full
#define _32x50_Arial_Num_Plus     &Font_32x50_Arial_Num_Plus
#define _32x50_Matrix_Num         &Font_32x50_Matrix_Num
#define _32x50_Segment_7_Full     &Font_32x50_Segment_7_Full
#define _32x50_Segment_7_Num_Plus &Font_32x50_Segment_7_Num_Plus
#define _32x50_Segment_16_Full    &Font_32x50_Segment_16_Full
#define _32x52_Segment_18_Full    &Font_32x52_Segment_18_Full
#define _32x64_Grotesk            &Font_32x64_Grotesk
#define _32x64_Grotesk_Bold       &Font_32x64_Grotesk_Bold
#define _40x60_Segment_16_Full    &Font_40x60_Segment_16_Full
#define _48x24_Battery            &Font_48x24_Battery
#define _48x72_Segment_16_Num     &Font_48x72_Segment_16_Num
#define _64x96_Segment_16_Num     &Font_64x96_Segment_16_Num
#define _64x100_Segment_7_Num     &Font_64x100_Segment_7_Num
#define _96x144_Segment_7_Num     &Font_96x144_Segment_7_Num
#define _96x144_Segment_16_Num    &Font_96x144_Segment_16_Num
#define _128x192_Segment_16_Num   &Font_128x192_Segment_16_Num

#endif /* MAIN_H_ */
