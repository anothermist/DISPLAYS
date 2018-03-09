#include "main.h"

//#include "fonts/bitmapImage.h"
#include "fonts/bitmapImageMono.h"
#include "fonts/Dmd8x7Clock.h"
#include "fonts/Dmd13x20Clock.h"
#include "fonts/FreeMono9pt7b.h"
#include "fonts/FreeMono12pt7b.h"
#include "fonts/FreeMono18pt7b.h"
#include "fonts/FreeMono24pt7b.h"
#include "fonts/FreeMonoBold9pt7b.h"
#include "fonts/FreeMonoBold12pt7b.h"
#include "fonts/FreeMonoBold18pt7b.h"
#include "fonts/FreeMonoBold24pt7b.h"
#include "fonts/FreeMonoBoldOblique9pt7b.h"
#include "fonts/FreeMonoBoldOblique12pt7b.h"
#include "fonts/FreeMonoBoldOblique18pt7b.h"
#include "fonts/FreeMonoBoldOblique24pt7b.h"
#include "fonts/FreeMonoOblique9pt7b.h"
#include "fonts/FreeMonoOblique12pt7b.h"
#include "fonts/FreeMonoOblique18pt7b.h"
#include "fonts/FreeMonoOblique24pt7b.h"
#include "fonts/FreeSans9pt7b.h"
#include "fonts/FreeSans12pt7b.h"
#include "fonts/FreeSans18pt7b.h"
#include "fonts/FreeSans24pt7b.h"
#include "fonts/FreeSansBold9pt7b.h"
#include "fonts/FreeSansBold12pt7b.h"
#include "fonts/FreeSansBold18pt7b.h"
#include "fonts/FreeSansBold24pt7b.h"
#include "fonts/FreeSansBoldOblique9pt7b.h"
#include "fonts/FreeSansBoldOblique12pt7b.h"
#include "fonts/FreeSansBoldOblique18pt7b.h"
#include "fonts/FreeSansBoldOblique24pt7b.h"
#include "fonts/FreeSansOblique9pt7b.h"
#include "fonts/FreeSansOblique12pt7b.h"
#include "fonts/FreeSansOblique18pt7b.h"
#include "fonts/FreeSansOblique24pt7b.h"
#include "fonts/FreeSerif9pt7b.h"
#include "fonts/FreeSerif12pt7b.h"
#include "fonts/FreeSerif18pt7b.h"
#include "fonts/FreeSerif24pt7b.h"
#include "fonts/FreeSerifBold9pt7b.h"
#include "fonts/FreeSerifBold12pt7b.h"
#include "fonts/FreeSerifBold18pt7b.h"
#include "fonts/FreeSerifBold24pt7b.h"
#include "fonts/FreeSerifBoldItalic9pt7b.h"
#include "fonts/FreeSerifBoldItalic12pt7b.h"
#include "fonts/FreeSerifBoldItalic18pt7b.h"
#include "fonts/FreeSerifBoldItalic24pt7b.h"
#include "fonts/FreeSerifItalic9pt7b.h"
#include "fonts/FreeSerifItalic12pt7b.h"
#include "fonts/FreeSerifItalic18pt7b.h"
#include "fonts/FreeSerifItalic24pt7b.h"
#include "fonts/FreeSevenSegNum.h"
#include "fonts/Org_01.h"
#include "fonts/Picopixel.h"
#include "fonts/Tiny3x3a2pt7b.h"
#include "fonts/TomThumb.h"

int main(void)
{
	LCD_Init();
	
	LCD_Rect_Fill(0, 0, 320, 240, BLUE);
	LCD_Rect_Fill(1, 1, 318, 238, BLACK);

	LCD_Bitmap_Mono(16, 4, &bitmapImageMono, BLUE, BLACK);
	
	_delay_ms(500);
	for(uint8_t x = 8; x <= 160; x += 8)
	{
		LCD_Line(0, 0, x, 128, 1, GREEN);
	}
	for(uint8_t y = 8; y <= 128; y += 8) {
		LCD_Line(0, 0, 160, y, 1, GREEN);
	}
	_delay_ms(250);

	uint8_t h = 16;
	uint8_t w = 20;
	for(uint8_t i = 0; i < 8; i++)
	{
		LCD_Rect(80 - w / 2, 64 - h / 2, w, h, 2, YELLOW);
		h += 16;
		w += 20;
	}
	_delay_ms(250);
	LCD_Rect_Fill(0, 0, 160, 128, BLUE);
	LCD_Rect_Fill(1, 1, 158, 126, BLACK);
	LCD_Font(5, 40, "This is\n just a Test\nST7735\n", Thumb, 1, YELLOW);
	LCD_Line(23, 20, 137, 20, 1, MAGENTA);
	LCD_Line(23, 21, 137, 21, 1, BLUE);
	LCD_Line(23, 21, 137, 21, 1, BLUE);
	LCD_String(41, 10, "ST7735 DRIVER", MAGENTA, X1);
	LCD_String(53, 26, "ATMEGA 328 - 1284", RED, X2);
	LCD_Circle(40, 90, 30, 0, 1, RED);
	LCD_Circle(45, 90, 20, 1, 1, BLUE);
	LCD_Triangle(5, 5, 5, 20, 25, 25, 2, BLUE);
	LCD_Rect(60, 45, 30, 20, 2, GREEN);
	LCD_Rect_Round(80, 70, 60, 25, 10, 3, WHITE);
	LCD_Rect_Round_Fill(80, 100, 60, 25, 10, WHITE);
	LCD_Ellipse(60, 100, 30, 20, 0, 2, YELLOW);
	LCD_Ellipse(125, 60, 25, 15, 1, 1, YELLOW);
	//LCD_Font(0, 200, "1234567890", SevenSegNum, 1, RED);
	//LCD_Font(10, 220, "1234567890 TEST FONT", Clock8x7, 1, RED);
	
	//	LCD_Bitmap(120, 45, &bitmapImage);
	
	while (1)
	{
		//LCD_Rect_Fill(0, 0, 160, 128, WHITE);
		//LCD_Rect_Fill(0, 0, 160, 128, BLACK);
	}
}
