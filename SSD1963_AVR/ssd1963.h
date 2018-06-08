#ifndef SSD1963_H_
#define SSD1963_H_

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

#define BLACK   0x000000 /*   0,   0,   0 */
#define WHITE   0xFFFFFF /* 255, 255, 255 */
#define RED     0xFF0000 /* 255,   0,   0 */
#define BLUE    0x0000FF /*   0,   0, 255 */
#define BLUE_D  0x0000A0 /*   0,   0, 160 */
#define CYAN    0x00FFFF /*   0, 255, 255 */
#define CYAN_D  0x008080 /*   0, 128, 128 */
#define YELLOW  0xFFFF00 /* 255, 255,   0 */
#define MAGENTA 0xFF00FF /* 255,   0, 255 */
#define GREEN   0x00FF00 /*   0, 255,   0 */
#define GREEN_D 0x008000 /*   0, 128,   0 */
#define PURPLE  0x800080 /* 128,   0, 128 */
#define TEAL    0x008080 /*   0, 128, 128 */
#define NAVY    0x000080 /*   0,   0, 128 */
#define SILVER  0xC0C0C0 /* 192, 192, 192 */
#define GRAY    0x808080 /* 128, 128, 128 */
#define ORANGE  0xFFA500 /* 255, 165,   0 */
#define BROWN   0xA52A2A /* 165, 255,  42 */
#define MAROON  0x800000 /* 128,   0,   0 */
#define OLIVE   0x808000 /* 128, 128,   0 */
#define LIME    0xBFFF00 /* 191, 255,   0 */

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

uint16_t RGB(uint8_t r, uint8_t g, uint8_t b);

void LCD_Init(void);
void LCD_Bright(uint8_t bright);

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

#define LCD_RESET			 		  0x0001
#define LCD_SLEEP_OUT		  	0x0011
#define LCD_GAMMA			    	0x0026
#define LCD_DISPLAY_OFF			0x0028
#define LCD_DISPLAY_ON			0x0029
#define LCD_COLUMN_ADDR			0x002A
#define LCD_PAGE_ADDR			  0x002B
#define LCD_GRAM				    0x002C
#define LCD_MAC			        0x0036
#define LCD_PIXEL_FORMAT    0x003A
#define LCD_WDB			    	  0x0051
#define LCD_WCD				      0x0053
#define LCD_RGB_INTERFACE   0x00B0
#define LCD_FRC					    0x00B1
#define LCD_BPC					    0x00B5
#define LCD_DFC				 	    0x00B6
#define LCD_POWER1					0x00C0
#define LCD_POWER2					0x00C1
#define LCD_VCOM1						0x00C5
#define LCD_VCOM2						0x00C7
#define LCD_POWERA					0x00CB
#define LCD_POWERB					0x00CF
#define LCD_PGAMMA					0x00E0
#define LCD_NGAMMA					0x00E1
#define LCD_DTCA						0x00E8
#define LCD_DTCB						0x00EA
#define LCD_POWER_SEQ				0x00ED
#define LCD_3GAMMA_EN				0x00F2
#define LCD_INTERFACE				0x00F6
#define LCD_PRC				   	  0x00F7
#define LCD_VERTICAL_SCROLL 0x0033

#endif /* SSD1963_H_ */
