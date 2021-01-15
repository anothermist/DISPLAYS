#ifndef SSD1289_H_
#define SSD1289_H_

#include "main.h"

#define REG_PART_1_PORT PORTC
#define REG_PART_1_DDR DDRC

#define REG_PART_2_PORT PORTD
#define REG_PART_2_DDR DDRD

#define COMMAND_PORT PORTA
#define COMMAND_DDR DDRA

#define LCD_RS_PIN PA0
#define LCD_RS_DDR DDRA
#define LCD_RS_PORT PORTA

#define LCD_WR_PIN PA1
#define LCD_WR_DDR DDRA
#define LCD_WR_PORT PORTA

#define LCD_RD_PIN PA2
#define LCD_RD_DDR DDRA
#define LCD_RD_PORT PORTA

#define LCD_CS_PIN PA3
#define LCD_CS_DDR DDRA
#define LCD_CS_PORT PORTA

#define LCD_RT_PIN PA4
#define LCD_RT_DDR DDRA
#define LCD_RT_PORT PORTA

#define LCD_RS_S LCD_RS_PORT |= (1 << LCD_RS_PIN);
#define LCD_RS_U LCD_RS_PORT &= ~(1 << LCD_RS_PIN);

#define LCD_WR_S LCD_WR_PORT |= (1 << LCD_WR_PIN);
#define LCD_WR_U LCD_WR_PORT &= ~(1 << LCD_WR_PIN);

#define LCD_RD_S LCD_RD_PORT |= (1 << LCD_RD_PIN);
#define LCD_RD_U LCD_RD_PORT &= ~(1 << LCD_RD_PIN);

#define LCD_CS_S LCD_CS_PORT |= (1 << LCD_CS_PIN);
#define LCD_CS_U LCD_CS_PORT &= ~(1 << LCD_CS_PIN);

#define LCD_RT_SOFT 1 

#define LCD_RT_S LCD_RT_PORT |= (1 << LCD_RT_PIN);
#define LCD_RT_U LCD_RT_PORT &= ~(1 << LCD_RT_PIN);

#define MIRROR_V 0
#define MIRROR_H 0

#define LSHIFT 0

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

void LCD_Init(void);

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

#define LCD_ON 			LCD_Send_Reg(0x0007, 0x0033);
#define LCD_OFF			LCD_Send_Reg(0x0007, 0x0000);
#define LCD_RAM_PREPARE	LCD_Send_Cmd(0x0022);

#endif /* SSD1289_H_ */
