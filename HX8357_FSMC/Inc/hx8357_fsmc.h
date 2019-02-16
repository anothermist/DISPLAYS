#ifndef _HX8357_FSMC_H_
#define _HX8357_FSMC_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_rcc.h"
#include "stm32f4xx_ll_fsmc.h"

#include <stdlib.h>
#include <string.h>

#define CMD *(uint16_t *)0x60000000
#define DAT *(uint16_t *)0x60020000

#define LCD_RST_SET   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
#define LCD_RST_RESET HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
											
#define BGR 1

#define DEFAULT_ORIENTATION 2

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

inline uint16_t RGB(uint8_t r, uint8_t g, uint8_t b);

void LCD_Init(void);
void LCD_Orientation(uint8_t orientation);

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

#define MADCTL_MY  0x80
#define MADCTL_MX  0x40
#define MADCTL_MV  0x20
#define MADCTL_ML  0x10
#define MADCTL_RGB 0x00
#define MADCTL_BGR 0x08
#define MADCTL_MH  0x04

#define HX8357_SLPOUT 			0x11
#define HX8357_INVON 				0x21
#define HX8357_DISPOFF 			0x28
#define HX8357_DISPON 			0x29
#define HX8357_CASET 				0x2A
#define HX8357_PASET 				0x2B
#define HX83h7_RAMWR 				0x2C
#define HX8357_TEON 				0x35
#define HX8357_MADCTL 			0x36
#define HX8357_COLMOD 			0x3A
#define HX8357_WRDISBV 			0x51
#define HX8357_WRCTRLD 			0x53
#define HX8357_WRCABC 			0x55
#define HX8357_WRCABCMB 		0x5E
#define HX8257_SETDISPLAY 	0xB4
#define HX8357_SETPANEL 		0xC0
#define HX8357_SETNORTIM 		0xC1
#define HX8357_SETOSC 			0xC5
#define HX8357_SETGAMMA 		0xC8
#define HX8357_SETPOWER 		0xD0
#define HX8357_SETVCOM 			0xD1
#define HX8357_SETNORPOW 		0xD2
#define HX8357_SETPARPOW 		0xD3
#define HX8357_SETIDLPOW 		0xD4
#define HX8357_SETPANELREL 	0xE9
#define HX8357_SETEQ 				0xEE

#ifdef __cplusplus
}
#endif

#endif /* _HX8357_FSMC_H_ */
