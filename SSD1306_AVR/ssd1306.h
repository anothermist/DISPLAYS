#ifndef SSD1306_H_
#define SSD1306_H_

#ifdef __cplusplus
extern C {
	#endif

	#include "main.h"
	
	#define LCD_HEIGHT							   64 // 32 64
	#define LCD_WIDTH						      128
	#define SSD1306_DEFAULT_SPACE					5
	#define SSD1306_TWI_ADDRESS					 0x3C

	#define SSD1306_SETCONTRAST                  0x81
	#define SSD1306_DISPLAYALLON_RESUME          0xA4
	#define SSD1306_DISPLAYALLON                 0xA5
	#define SSD1306_NORMALDISPLAY                0xA6
	#define SSD1306_INVERTDISPLAY                0xA7
	#define SSD1306_DISPLAYOFF                   0xAE
	#define SSD1306_DISPLAYON                    0xAF
	#define SSD1306_SETDISPLAYOFFSET             0xD3
	#define SSD1306_SETCOMPINS                   0xDA
	#define SSD1306_SETVCOMDETECT                0xDB
	#define SSD1306_SETDISPLAYCLOCKDIV           0xD5
	#define SSD1306_SETPRECHARGE                 0xD9
	#define SSD1306_SETMULTIPLEX                 0xA8
	#define SSD1306_SETLOWCOLUMN                 0x00
	#define SSD1306_SETHIGHCOLUMN                0x10
	#define SSD1306_SETSTARTLINE                 0x40
	#define SSD1306_MEMORYMODE                   0x20
	#define SSD1306_COLUMNADDR                   0x21
	#define SSD1306_PAGEADDR                     0x22
	#define SSD1306_COMSCANINC                   0xC0
	#define SSD1306_COMSCANDEC                   0xC8
	#define SSD1306_SEGREMAP                     0xA1
	#define SSD1306_CHARGEPUMP                   0x8D
	#define SSD1306_EXTERNALVCC                  0x1
	#define SSD1306_SWITCHCAPVCC                 0x2
	#define SSD1306_ACTIVATE_SCROLL              0x2F
	#define SSD1306_DEACTIVATE_SCROLL            0x2E
	#define SSD1306_SET_VERTICAL_SCROLL_AREA     0xA3
	#define SSD1306_RIGHT_HORIZONTAL_SCROLL      0x26
	#define SSD1306_LEFT_HORIZONTAL_SCROLL       0x27
	#define SSD1306_VERT_AND_RIGHT_HORIZ_SCROLL  0x29
	#define SSD1306_VERT_AND_LEFT_HORIZ_SCROLL   0x2A

	#define COMAND		                           0x00
	#define DATA		                             0x40

	typedef enum {
		SSD1306_COLOR_BLACK = 0x00,
		SSD1306_COLOR_WHITE = 0x01
	} SSD1306_COLOR_t;

typedef struct { // Data stored PER GLYPH
	uint16_t bitmapOffset;     // Pointer into GFXfont->bitmap
	uint8_t  width, height;    // Bitmap dimensions in pixels
	uint8_t  xAdvance;         // Distance to advance cursor (x axis)
	int8_t   xOffset, yOffset; // Dist from cursor position to UL corner
} GFXglyph;

typedef struct { // Data stored for FONT AS A WHOLE:
	uint8_t  *bitmap;      // Glyph bitmaps, concatenated
	GFXglyph *glyph;       // Glyph array
	uint8_t   first, last; // ASCII extents
	uint8_t   yAdvance;    // Newline distance (y axis)
} GFXfont;

void SSD1306_Init(void);
void LCD_Contrast(char set_contrast);
void LCD_ON(void);
void LCD_OFF(void);
void LCD_UpdateScreen(void);
void LCD_Mode(char set_mode);
void LCD_Sleep(char set);
void LCD_ToggleInvert(void);
void LCD_Fill(SSD1306_COLOR_t color);
void LCD_Pixel(uint16_t x, uint16_t y, SSD1306_COLOR_t color);
void LCD_Line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, SSD1306_COLOR_t color);
void LCD_Rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, SSD1306_COLOR_t color);
void LCD_Rect_Fill(uint16_t x, uint16_t y, uint16_t w, uint16_t h, SSD1306_COLOR_t color);
void LCD_Triangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, SSD1306_COLOR_t color);
void LCD_Triangle_Fill(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, SSD1306_COLOR_t color);
void LCD_Ellipse(int16_t x0, int16_t y0, int16_t rx, int16_t ry, uint8_t fill, SSD1306_COLOR_t color);
void LCD_Circle(uint16_t x, uint16_t y, uint8_t radius, uint8_t fill, uint8_t size, SSD1306_COLOR_t color);
void LCD_Rect_Round(uint16_t x, uint16_t y, uint16_t length, uint16_t width, uint16_t r, SSD1306_COLOR_t color);
void LCD_Rect_Round_Fill(uint16_t x, uint16_t y, uint16_t length, uint16_t width, uint16_t r, uint32_t color);
void LCD_Char(int16_t x, int16_t y, const GFXglyph *glyph, const GFXfont *font, uint8_t size, SSD1306_COLOR_t color);
void LCD_Font(uint16_t x, uint16_t y, char *text, const GFXfont *p_font, uint8_t size, SSD1306_COLOR_t color);
void LCD_Battery(unsigned char y,unsigned char x, unsigned char z);

	#ifdef __cplusplus
}
#endif

#endif
