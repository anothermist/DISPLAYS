#ifndef _ST7735_H_
#define _ST7735_H_

#include "main.h"

#define LCD_HEIGHT 128
#define LCD_WIDTH  160

#define LCD_PORT PORTB
#define LCD_DDR  DDRB
#define LCD_DC	 PB3 // PB1 | PB3
#define LCD_CS	 PB4 // PB2 | PB4
#define LCD_MOSI PB5 // PB3 | PB5
#define LCD_SCK	 PB7 // PB5 | PB7
#define LCD_RST	0

#define LCD_S_DC	LCD_PORT |= (1 << LCD_DC);
#define LCD_U_DC	LCD_PORT &= ~(1 << LCD_DC);
#define LCD_S_CS	LCD_PORT |= (1 << LCD_CS);
#define LCD_U_CS	LCD_PORT &= ~(1 << LCD_CS);
#define LCD_S_RST	LCD_PORT |= (1 << LCD_RST);
#define LCD_U_RST	LCD_PORT &= ~(1 << LCD_RST);

#define BLACK   0x000000
#define WHITE   0xFFFFFF
#define RED     HUE_17
#define BLUE    HUE_01
#define BLUE_D  0x0000A0 /*   0,   0, 160 */
#define CYAN    HUE_05
#define YELLOW  HUE_13 /* 255, 255,   0 */
#define MAGENTA HUE_21 /* 255,   0, 255 */
#define GREEN   HUE_09 /*   0, 255,   0 */
#define GREEN_D 0x007F00 /*   0, 128,   0 */
#define PURPLE  0x7F007F /* 128,   0, 128 */
#define TEAL    0x007F7F /*   0, 128, 128 */
#define NAVY    0x00007F /*   0,   0, 128 */
#define SILVER  0xBFBFBF /* 191, 191, 191 */
#define GRAY    0x7F7F7F /* 128, 128, 128 */
#define ORANGE  0xFFA500 /* 255, 165,   0 */
#define BROWN   0xA52A2A /* 165, 255,  42 */
#define MAROON  0x7F0000 /* 128,   0,   0 */
#define OLIVE   0x7F7F00 /* 128, 128,   0 */
#define LIME    HUE_12

#define HUE_01 0x0000FF // 000, 000, 255 - BLUE
#define HUE_02 0x003FFF // 000, 063, 255 - 
#define HUE_03 0x007FFF // 000, 127, 255 - 
#define HUE_04 0x00BFFF // 000, 191, 255 - 
#define HUE_05 0x00FFFF // 000, 255, 255 - CYAN
#define HUE_06 0x00FFBF // 000, 255, 191 - 
#define HUE_07 0x00FF7F // 000, 255, 127 - 
#define HUE_08 0x00FF00 // 000, 255, 063 - 
#define HUE_09 0x00FF00 // 000, 255, 000 - GREEN
#define HUE_10 0x3FFF00 // 063, 255, 000 - 
#define HUE_11 0x7FFF7F // 127, 255, 000 - 
#define HUE_12 0xBFFF00 // 191, 255, 000 - LIME
#define HUE_13 0xFFFF00 // 255, 255, 000 - YELLOW
#define HUE_14 0xFFBF00 // 255, 191, 000 - 
#define HUE_15 0xFF7F00 // 255, 127, 000 - 
#define HUE_16 0xFF3F00 // 255, 063, 000 - 
#define HUE_17 0xFF0000 // 255, 000, 000 - RED
#define HUE_18 0xFF003F // 255, 000, 063 - 
#define HUE_19 0xFF007F // 255, 000, 127 - 
#define HUE_20 0xFF00BF // 255, 000, 191 - 
#define HUE_21 0xFF00FF // 255, 000, 255 - MAGENTA
#define HUE_22 0xBF00FF // 191, 000, 255 - 
#define HUE_23 0x7F00FF // 127, 000, 255 - 
#define HUE_24 0x3F00FF // 063, 000, 255 - 

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

uint32_t RGB(uint8_t r, uint8_t g, uint8_t b);

void LCD_SPI(void);
void LCD_Init(uint8_t type, uint8_t orientation);
void LCD_Orientation(uint8_t type, uint8_t orientation);
void LCD_Pixel(uint16_t x, uint16_t y, uint32_t color24);
void LCD_Rect_Fill(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint32_t color24);
void LCD_Line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t size, uint32_t color24);
void LCD_Rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t size, uint32_t color24);
void LCD_Triangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint8_t size, uint32_t color24);
void LCD_Triangle_Fill(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint32_t color24);
void LCD_Ellipse(int16_t x0, int16_t y0, int16_t rx, int16_t ry, uint8_t fill, uint8_t size, uint32_t color24);
void LCD_Circle(uint16_t x, uint16_t y, uint8_t radius, uint8_t fill, uint8_t size, uint32_t color24);
void LCD_Rect_Round(uint16_t x, uint16_t y, uint16_t length, uint16_t width, uint16_t r, uint8_t size, uint32_t color24);
void LCD_Rect_Round_Fill(uint16_t x, uint16_t y, uint16_t length, uint16_t width, uint16_t r, uint32_t color24);
void LCD_Font(uint16_t x, uint16_t y, char *text, const GFXfont *p_font, uint8_t size, uint32_t color24);
void LCD_Bitmap(uint16_t x, uint16_t y, PGM_P bitmap);
void LCD_Bitmap_Mono(uint16_t x, uint16_t y, PGM_P bitmap, uint32_t color24_set, uint32_t color24_unset);

enum LCD_MADCTL_ARGS {
	MADCTL_MY	= 0x80,	// Mirror Y
	MADCTL_MX	= 0x40,	// Mirror x
	MADCTL_MV	= 0x20,	// Swap XY
	MADCTL_ML	= 0x10,	// Scan address order
	MADCTL_RGB	= 0x00,
	MADCTL_BGR	= 0x08,
	MADCTL_MH	= 0x04 	// Horizontal scan oder
};

#define DELAY_FLAG 0x80

enum LCD_COMMANDS {
	NOP		= 0x00,
	SWRESET	= 0x01,
	RDDID	= 0x04,
	RDDST	= 0x09,

	SLPIN	= 0x10,
	SLPOUT	= 0x11,
	PTLON	= 0x12,
	NORON	= 0x13,

	INVOFF	= 0x20,
	INVON	= 0x21,
	DISPOFF	= 0x28,
	DISPON	= 0x29,
	CASET	= 0x2A,
	RASET	= 0x2B,
	RAMWR	= 0x2C,
	RAMRD	= 0x2E,

	PTLAR	= 0x30,
	COLMOD	= 0x3A,
	MADCTL	= 0x36,

	FRMCTR1	= 0xB1,
	FRMCTR2	= 0xB2,
	FRMCTR3	= 0xB3,
	INVCTR	= 0xB4,
	DISSET5	= 0xB6,

	PWCTR1	= 0xC0,
	PWCTR2	= 0xC1,
	PWCTR3	= 0xC2,
	PWCTR4	= 0xC3,
	PWCTR5	= 0xC4,
	VMCTR1	= 0xC5,

	RDID1	= 0xDA,
	RDID2	= 0xDB,
	RDID3	= 0xDC,
	RDID4	= 0xDD,

	PWCTR6	= 0xFC,

	GMCTRP1	= 0xE0,
	GMCTRN1	= 0xE1
};

#endif /* _ST7735_H_ */
