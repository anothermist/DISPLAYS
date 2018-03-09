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

#include "st7735.h"

#define Clock8x7			&Dmd8x7Clock
#define Clock13x20			&Dmd13x20Clock
#define Mono9				&FreeMono9pt7b
#define Mono12				&FreeMono12pt7b
#define Mono18				&FreeMono18pt7b
#define Mono24				&FreeMono24pt7b
#define MonoBold9			&FreeMonoBold9pt7b
#define MonoBold12			&FreeMonoBold12pt7b
#define MonoBold18			&FreeMonoBold18pt7b
#define MonoBold24			&FreeMonoBold24pt7b
#define MonoBoldOblique9	&FreeMonoBoldOblique9pt7b
#define MonoBoldOblique12	&FreeMonoBoldOblique12pt7b
#define MonoBoldOblique18	&FreeMonoBoldOblique18pt7b
#define MonoBoldOblique24	&FreeMonoBoldOblique24pt7b
#define MonoOblique9		&FreeMonoOblique9pt7b
#define MonoOblique12		&FreeMonoOblique12pt7b
#define MonoOblique18		&FreeMonoOblique18pt7b
#define MonoOblique24		&FreeMonoOblique24pt7b
#define Sans9				&FreeSans9pt7b
#define Sans12				&FreeSans12pt7b
#define Sans18				&FreeSans18pt7b
#define Sans24				&FreeSans24pt7b
#define SansBold9			&FreeSansBold9pt7b
#define SansBold12			&FreeSansBold12pt7b
#define SansBold18			&FreeSansBold18pt7b
#define SansBold24			&FreeSansBold24pt7b
#define SansBoldOblique9	&FreeSansBoldOblique9pt7b
#define SansBoldOblique12	&FreeSansBoldOblique12pt7b
#define SansBoldOblique18	&FreeSansBoldOblique18pt7b
#define SansBoldOblique24	&FreeSansBoldOblique24pt7b
#define SansOblique9		&FreeSansOblique9pt7b
#define SansOblique12		&FreeSansOblique12pt7b
#define SansOblique18		&FreeSansOblique18pt7b
#define SansOblique24		&FreeSansOblique24pt7b
#define Serif9				&FreeSerif9pt7b
#define Serif12				&FreeSerif12pt7b
#define Serif18				&FreeSerif18pt7b
#define Serif24				&FreeSerif24pt7b
#define SerifBold9			&FreeSerifBold9pt7b
#define SerifBold12			&FreeSerifBold12pt7b
#define SerifBold18			&FreeSerifBold18pt7b
#define SerifBold24			&FreeSerifBold24pt7b
#define SerifBoldItalic9	&FreeSerifBoldItalic9pt7b
#define SerifBoldItalic12	&FreeSerifBoldItalic12pt7b
#define SerifBoldItalic18	&FreeSerifBoldItalic18pt7b
#define SerifBoldItalic24	&FreeSerifBoldItalic24pt7b
#define SerifItalic9		&FreeSerifItalic9pt7b
#define SerifItalic12		&FreeSerifItalic12pt7b
#define SerifItalic18		&FreeSerifItalic18pt7b
#define SerifItalic24		&FreeSerifItalic24pt7b
#define SevenSegNum			&FreeSevenSegNum
#define Org					&Org_01
#define Pixel				&Picopixel
#define Tiny3				&Tiny3x3a2pt7b
#define Thumb				&TomThumb

#endif /* MAIN_H_ */
