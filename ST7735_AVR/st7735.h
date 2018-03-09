#ifndef _LCD_H_
#define _LCD_H_

#include "main.h"

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

enum DISPLAY_TYPE {
	BLUE,
	RED_18_GREENTAB,
	RED_18_REDTAB,
	RED_18_BLACKTAB,
	RED_144_GREENTAB
};

static const enum DISPLAY_TYPE Type = 2;

#define LCD_HEIGHT 128
#define LCD_WIDTH  160

#define DEFAULT_ORIENTATION 0

enum ORIENTATION {
	LANDSCAPE,
	PORTRAIT,
	LANDSCAPE_INV,
	PORTRAIT_INV
};

#define BLACK 	0x000000 /*   0,   0,   0 */
#define WHITE 	0xFFFFFF /* 255, 255, 255 */
#define RED 	0xFF0000 /* 255,   0,   0 */
#define BLUE 	0x0000FF /*   0,   0, 255 */
#define BLUE_D 	0x0000A0 /*   0,   0, 160 */
#define CYAN 	0x00FFFF /*   0, 255, 255 */
#define CYAN_D	0x008080 /*   0, 128, 128 */
#define YELLOW 	0xFFFF00 /* 255, 255,   0 */
#define MAGENTA 0xFF00FF /* 255,   0, 255 */
#define GREEN 	0x00FF00 /*   0, 255,   0 */
#define GREEN_D 0x008000 /*   0, 128,   0 */
#define PURPLE 	0x800080 /* 128,   0, 128 */
#define TEAL 	0x008080
#define NAVY 	0x000080 /*   0,   0, 128 */
#define SILVER 	0xC0C0C0 /* 192, 192, 192 */
#define GRAY 	0x808080 /* 128, 128, 128 */
#define ORANGE 	0xFFA500 /* 255, 165,   0 */
#define BROWN 	0xA52A2A
#define MAROON 	0x800000 /* 128,   0,   0 */
#define OLIVE 	0x808000 /* 128, 128,   0 */
#define LIME 	0xBFFF00 /* 191, 255,   0 */

#define CHARS_COLS_LEN 5
#define CHARS_ROWS_LEN 8

extern const uint8_t CHARACTERS[][CHARS_COLS_LEN];

typedef enum {
	X1 = 0x00,
	X2 = 0x01,
	X3 = 0x0A
} ESizes;

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

inline uint16_t RGB(uint8_t r, uint8_t g, uint8_t b);

void LCD_SPI(void);
void LCD_Init(void);
void LCD_Orientation(uint8_t orientation);

void LCD_Pixel(uint16_t x, uint16_t y, uint32_t color24);
void LCD_Rect_Fill(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint32_t color24);
void LCD_Line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t size, uint32_t color24);
void LCD_Rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t size, uint32_t color24);
void LCD_Triangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint8_t size, uint32_t color24);
void LCD_Ellipse(int16_t x0, int16_t y0, int16_t rx, int16_t ry, uint8_t fill, uint8_t size, uint32_t color24);
void LCD_Circle(uint16_t x, uint16_t y, uint8_t radius, uint8_t fill, uint8_t size, uint32_t color24);
void LCD_Rect_Round(uint16_t x, uint16_t y, uint16_t length, uint16_t width, uint16_t r, uint8_t size, uint32_t color24);
void LCD_Rect_Round_Fill(uint16_t x, uint16_t y, uint16_t length, uint16_t width, uint16_t r, uint32_t color24);
void LCD_String(uint16_t x, uint16_t y, char *str, uint32_t color24, ESizes size);
void LCD_Font(uint16_t x, uint16_t y, char *text, const GFXfont *p_font, uint8_t size, uint32_t color24);
void LCD_Bitmap(uint16_t x, uint16_t y, PGM_P bitmap);
void LCD_Bitmap_Mono(uint16_t x, uint16_t y, PGM_P bitmap, uint32_t color24_set, uint32_t color24_unset);

static const uint8_t LCD_Default_Width = 128;
static const uint8_t LCD_Default_Height_144 = 128;
static const uint8_t LCD_Default_Height_18 = 160;

extern const uint8_t LCD_Blue_Init[];
extern const uint8_t LCD_Red_Init_1[];
extern const uint8_t LCD_Red_Init_Green_2[];
extern const uint8_t LCD_Red_Init_Red_2[];
extern const uint8_t LCD_Red_Init_Green_144_2[];
extern const uint8_t LCD_Red_Init_3[];

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

#endif /* _LCD_H_ */
