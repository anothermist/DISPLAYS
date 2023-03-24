#ifndef SSD1306_H_
#define SSD1306_H_

#include "main.h"
// 32x128 32x64
#define LCD_HEIGHT							 64
#define LCD_WIDTH						     128
//#define SSD1306_DEFAULT_SPACE				 5
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

#define COMAND		                         0x00
#define DATA		                         0x40

typedef enum {
	SSD1306_COLOR_BLACK = 0x00,
	SSD1306_COLOR_WHITE = 0x01
} SSD1306_COLOR_t;

typedef struct { // Data stored PER GLYPH
	unsigned int bitmapOffset;     // Pointer into GFXfont->bitmap
	unsigned char  width, height;    // Bitmap dimensions in pixels
	unsigned char  xAdvance;         // Distance to advance cursor (x axis)
	int8_t   xOffset, yOffset; // Dist from cursor position to UL corner
} GFXglyph;

typedef struct { // Data stored for FONT AS A WHOLE:
	unsigned char  *bitmap;      // Glyph bitmaps, concatenated
	GFXglyph *glyph;       // Glyph array
	unsigned char   first, last; // ASCII extents
	unsigned char   yAdvance;    // Newline distance (y axis)
} GFXfont;

void SSD1306_Init(void);
void LCD_Contrast(unsigned char set_contrast);
void LCD_ON(void);
void LCD_OFF(void);
void LCD_UpdateScreen(void);
void LCD_Mode(unsigned char set_mode);
void LCD_Sleep(unsigned char set);
void LCD_ToggleInvert(void);
void LCD_Fill(SSD1306_COLOR_t color);
void LCD_Pixel(unsigned int x, unsigned int y, SSD1306_COLOR_t color);
void LCD_Line(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, SSD1306_COLOR_t color);
void LCD_Rect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, SSD1306_COLOR_t color);
void LCD_Rect_Fill(unsigned int x, unsigned int y, unsigned int w, unsigned int h, SSD1306_COLOR_t color);
void LCD_Triangle(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int x3, unsigned int y3, SSD1306_COLOR_t color);
void LCD_Triangle_Fill(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int x3, unsigned int y3, SSD1306_COLOR_t color);
void LCD_Ellipse(int x0, int y0, int rx, int ry, unsigned char fill, SSD1306_COLOR_t color);
void LCD_Circle(unsigned int x, unsigned int y, unsigned char radius, unsigned char fill, unsigned char size, SSD1306_COLOR_t color);
void LCD_Rect_Round(unsigned int x, unsigned int y, unsigned int length, unsigned int width, unsigned int r, unsigned char size, SSD1306_COLOR_t color);
void LCD_Rect_Round_Fill(unsigned int x, unsigned int y, unsigned int length, unsigned int width, unsigned int r, SSD1306_COLOR_t color);
void LCD_Char(int x, int y, const GFXglyph *glyph, const GFXfont *font, unsigned char size, SSD1306_COLOR_t color);
void LCD_Font(unsigned int x, unsigned int y, const char *text, const GFXfont *p_font, unsigned char size, SSD1306_COLOR_t color);
void LCD_Battery(unsigned int y, unsigned int x, unsigned char z);

#endif
