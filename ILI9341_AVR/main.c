#include "main.h"

//#include "fonts/bitmapImage.h"
#include "fonts/Font_3x3_Tiny.h"
#include "fonts/Font_3x5_PicoPixel.h"
#include "fonts/Font_3x5_TomThumb_Extended.h"
#include "fonts/Font_5x5_Org.h"
#include "fonts/Font_8x8_Sinclair.h"
#include "fonts/Font_8x8_Sinclair_Inverted.h"
#include "fonts/Font_8x8_Tiny.h"
#include "fonts/Font_8x9_Myke.h"
#include "fonts/Font_8x12_Default.h"
#include "fonts/Font_8x16_Retro.h"
#include "fonts/Font_9x18_Mono.h"
#include "fonts/Font_9x18_Mono_Bold.h"
#include "fonts/Font_9x18_Mono_Bold_Oblique.h"
#include "fonts/Font_9x18_Mono_Oblique.h"
#include "fonts/Font_9x22_Sans.h"
#include "fonts/Font_9x22_Sans_Bold.h"
#include "fonts/Font_9x22_Sans_Bold_Oblique.h"
#include "fonts/Font_9x22_Sans_Oblique.h"
#include "fonts/Font_9x22_Serif.h"
#include "fonts/Font_9x22_Serif_Bold.h"
#include "fonts/Font_9x22_Serif_Bold_Italic.h"
#include "fonts/Font_9x22_Serif_Italic.h"
#include "fonts/Font_12x24_Mono.h"
#include "fonts/Font_12x24_Mono_Bold.h"
#include "fonts/Font_12x24_Mono_Bold_Oblique.h"
#include "fonts/Font_12x24_Mono_Oblique.h"
#include "fonts/Font_12x29_Sans.h"
#include "fonts/Font_12x29_Sans_Bold.h"
#include "fonts/Font_12x29_Sans_Bold_Oblique.h"
#include "fonts/Font_12x29_Sans_Oblique.h"
#include "fonts/Font_12x29_Serif.h"
#include "fonts/Font_12x29_Serif_Bold.h"
#include "fonts/Font_12x29_Serif_Bold_Italic.h"
#include "fonts/Font_12x29_Serif_Italic.h"
#include "fonts/Font_16x16_Arial.h"
#include "fonts/Font_16x16_Arial_Bold.h"
#include "fonts/Font_16x16_Arial_Italic.h"
#include "fonts/Font_16x16_Default.h"
#include "fonts/Font_16x16_FranklinGothic.h"
#include "fonts/Font_16x16_Hallfetica.h"
#include "fonts/Font_16x16_Nadianne.h"
#include "fonts/Font_16x16_Sinclair.h"
#include "fonts/Font_16x16_Sinclair_Inverted.h"
#include "fonts/Font_16x16_Swiss_Outline.h"
#include "fonts/Font_16x22_Matrix_Full.h"
#include "fonts/Font_16x22_Matrix_Full_Slash.h"
#include "fonts/Font_16x22_Matrix_Num.h"
#include "fonts/Font_16x24_Arial_Round.h"
#include "fonts/Font_16x24_OCR.h"
#include "fonts/Font_16x24_Segment_16_Full.h"
#include "fonts/Font_16x32_Grotesk.h"
#include "fonts/Font_16x32_Grotesk_Bold.h"
#include "fonts/Font_16x32_Retro.h"
#include "fonts/Font_18x35_Mono.h"
#include "fonts/Font_18x35_Mono_Bold.h"
#include "fonts/Font_18x35_Mono_Bold_Oblique.h"
#include "fonts/Font_18x35_Mono_Oblique.h"
#include "fonts/Font_18x42_Sans.h"
#include "fonts/Font_18x42_Sans_Bold.h"
#include "fonts/Font_18x42_Sans_Bold_Oblique.h"
#include "fonts/Font_18x42_Sans_Oblique.h"
#include "fonts/Font_18x42_Serif.h"
#include "fonts/Font_18x42_Serif_Bold.h"
#include "fonts/Font_18x42_Serif_Bold_Italic.h"
#include "fonts/Font_18x42_Serif_Italic.h"
#include "fonts/Font_24x29_Matrix_Num.h"
#include "fonts/Font_24x32_Inconsola.h"
#include "fonts/Font_24x32_Ubuntu.h"
#include "fonts/Font_24x32_Ubuntu_Bold.h"
#include "fonts/Font_24x36_Segment_16_Full.h"
#include "fonts/Font_24x47_Mono.h"
#include "fonts/Font_24x47_Mono_Bold.h"
#include "fonts/Font_24x47_Mono_Bold_Oblique.h"
#include "fonts/Font_24x47_Mono_Oblique.h"
#include "fonts/Font_24x48_Grotesk.h"
#include "fonts/Font_24x48_Grotesk_Bold.h"
#include "fonts/Font_24x56_Sans.h"
#include "fonts/Font_24x56_Sans_Bold.h"
#include "fonts/Font_24x56_Sans_Bold_Oblique.h"
#include "fonts/Font_24x56_Sans_Oblique.h"
#include "fonts/Font_24x56_Serif.h"
#include "fonts/Font_24x56_Serif_Bold.h"
#include "fonts/Font_24x56_Serif_Bold_Italic.h"
#include "fonts/Font_24x56_SerifItalic.h"
#include "fonts/Font_32x24_Dingbats.h"
#include "fonts/Font_32x32_Special.h"
#include "fonts/Font_32x48_Calibri_Bold.h"
#include "fonts/Font_32x48_Segment_16_Full.h"
#include "fonts/Font_32x50_Arial_Num_Plus.h"
#include "fonts/Font_32x50_Matrix_Num.h"
#include "fonts/Font_32x50_Segment_7_Full.h"
#include "fonts/Font_32x50_Segment_7_Num_Plus.h"
#include "fonts/Font_32x50_Segment_16_Full.h"
#include "fonts/Font_32x52_Segment_18_Full.h"
#include "fonts/Font_32x64_Grotesk.h"
#include "fonts/Font_32x64_Grotesk_Bold.h"
#include "fonts/Font_40x60_Segment_16_Full.h"
#include "fonts/Font_48x24_Battery.h"
#include "fonts/Font_48x72_Segment_16_Num.h"
#include "fonts/Font_64x96_Segment_16_Num.h"
#include "fonts/Font_64x100_Segment_7_Num.h"
//#include "fonts/Font_96x144_Segment_7_Num.h"
//#include "fonts/Font_96x144_Segment_16_Num.h"
//#include "fonts/Font_128x192_Segment_16_Num.h"
int main(void)
{
	LCD_Init();
	
	LCD_Rect_Fill(0, 0, 320, 240, BLUE);
	LCD_Rect_Fill(1, 1, 318, 238, BLACK);

	//LCD_Bitmap_Mono(16, 4, &bitmapImageMono, BLUE, BLACK);
	
	_delay_ms(1000);
	for(uint8_t x = 8; x <= 128; x += 8) LCD_Line(0, 0, x, 128, 1, GREEN);
	for(uint8_t y = 8; y <= 128; y += 8) LCD_Line(0, 0, 128, y, 1, GREEN);

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
	LCD_Font(5, 40, "This is\n just a Test\n TomThumb Ext\n", _3x5_TomThumb_Extended, 1, YELLOW);
	LCD_Line(23, 20, 137, 20, 1, MAGENTA);
	LCD_Line(23, 21, 137, 21, 1, BLUE);
	LCD_Line(23, 21, 137, 21, 1, BLUE);
	LCD_Font(41, 10, "DISPLAY DRIVER", _5x5_Org, 1, MAGENTA);
	LCD_Font(45, 35, "SERIF BOLD", _9x22_Serif_Bold, 1, RED);
	LCD_Circle(40, 90, 30, 0, 1, RED);
	LCD_Circle(45, 90, 20, 1, 1, BLUE);
	LCD_Triangle(5, 5, 5, 20, 25, 25, 2, BLUE);
	LCD_Rect(60, 45, 30, 20, 2, GREEN);
	LCD_Rect_Round(80, 70, 60, 25, 10, 3, WHITE);
	LCD_Rect_Round_Fill(80, 100, 60, 25, 10, WHITE);
	LCD_Ellipse(60, 100, 30, 20, 0, 2, YELLOW);
	LCD_Ellipse(125, 60, 25, 15, 1, 1, YELLOW);
	LCD_Font(0, 200, "1234567890", _32x50_Segment_7_Num_Plus, 1, RED);
	LCD_Font(10, 220, "1234567890 Default Font", _8x12_Default, 1, RED);
	
	//	LCD_Bitmap(120, 45, &bitmapImage);
	
	while (1)
	{
		//LCD_Rect_Fill(0, 0, 320, 240, WHITE);
		//LCD_Rect_Fill(0, 0, 320, 240, BLACK);
	}
}
