#ifndef _ILI9341_H_
#define _ILI9341_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal_rcc.h"
#include "stm32f1xx_ll_fsmc.h"

#include <stdlib.h>
#include <string.h>

#define	LCD_SPI hspi2

#define LCD_HEIGHT 240
#define LCD_WIDTH  320

#define DEFAULT_ORIENTATION 3

#define SOFT_CS 0
#define LCD_CS_PORT	 GPIOB
#define LCD_CS_PIN	 GPIO_PIN_12
#define LCD_DC_PORT	 GPIOB
#define LCD_DC_PIN	 GPIO_PIN_1
#define LCD_RST_PORT GPIOB
#define LCD_RST_PIN	 GPIO_PIN_0
#define LCD_CS_S	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
#define LCD_CS_U	HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
#define LCD_DC_S	HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
#define LCD_DC_U	HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_RESET);
#define LCD_RST_S	HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_SET);
#define LCD_RST_U	HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_RESET);

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
void LCD_Bitmap(uint16_t x, uint16_t y, const char *bitmap);
void LCD_Bitmap_Mono(uint16_t x, uint16_t y, const char *bitmap, uint32_t color24_set, uint32_t color24_unset);

void LCD_setupScrollArea(uint16_t TFA, uint16_t BFA) ;
void LCD_scrollAddress(uint16_t VSP);
int LCD_scrollLine(void);

// The scrolling area must be a integral multiple of TEXT_HEIGHT
#define TEXT_HEIGHT 16 // Height of text to be printed and scrolled
#define BOT_FIXED_AREA 0 // Number of lines in bottom fixed area (lines counted from bottom of screen)
#define TOP_FIXED_AREA 16 // Number of lines in top fixed area (lines counted from top of screen)

// The scrolling area must be a integral multiple of TEXT_HEIGHT
#define TEXT_HEIGHT 16 // Height of text to be printed and scrolled
#define BOT_FIXED_AREA 0 // Number of lines in bottom fixed area (lines counted from bottom of screen)
#define TOP_FIXED_AREA 16 // Number of lines in top fixed area (lines counted from top of screen)

/* Level 1 Commands (from the display Datasheet) */
#define NOP                             0x00
#define SOFTWARE_RESET                  0x01
#define READ_DISP_ID                    0x04
#define READ_DISP_STATUS                0x09
#define READ_DISP_MADCTRL               0x0B
#define READ_DISP_PIXEL_FORMAT          0x0C
#define READ_DISP_IMAGE_FORMAT          0x0D
#define READ_DISP_SIGNAL_MODE           0x0E
#define READ_DISP_SELF_DIAGNOSTIC       0x0F
#define ENTER_SLEEP_MODE                0x10
#define SLEEP_OUT                       0x11
#define PARTIAL_MODE_ON                 0x12
#define NORMAL_DISP_MODE_ON             0x13
#define DISP_INVERSION_OFF              0x20
#define DISP_INVERSION_ON               0x21
#define GAMMA_SET                       0x26
#define DISPLAY_OFF                     0x28
#define DISPLAY_ON                      0x29
#define COLUMN_ADDRESS_SET              0x2A
#define PAGE_ADDRESS_SET                0x2B
#define MEMORY_WRITE                    0x2C
#define COLOR_SET                       0x2D
#define MEMORY_READ                     0x2E
#define PARTIAL_AREA                    0x30
#define VERT_SCROLL_DEFINITION          0x33
#define TEARING_EFFECT_LINE_OFF         0x34
#define TEARING_EFFECT_LINE_ON          0x35
#define MEMORY_ACCESS_CONTROL           0x36
#define VERT_SCROLL_START_ADDRESS       0x37
#define IDLE_MODE_OFF                   0x38
#define IDLE_MODE_ON                    0x39
#define COLMOD_PIXEL_FORMAT_SET         0x3A
#define WRITE_MEMORY_CONTINUE           0x3C
#define READ_MEMORY_CONTINUE            0x3E
#define SET_TEAR_SCANLINE               0x44
#define GET_SCANLINE                    0x45
#define WRITE_DISPLAY_BRIGHTNESS        0x51
#define READ_DISPLAY_BRIGHTNESS         0x52
#define WRITE_CTRL_DISPLAY              0x53
#define READ_CTRL_DISPLAY               0x54
#define WRITE_CONTENT_ADAPT_BRIGHTNESS  0x55
#define READ_CONTENT_ADAPT_BRIGHTNESS   0x56
#define WRITE_MIN_CAB_LEVEL             0x5E
#define READ_MIN_CAB_LEVEL              0x5F
#define READ_ID1                        0xDA
#define READ_ID2                        0xDB
#define READ_ID3                        0xDC
/* Level 2 Commands (from the display Datasheet) */
#define RGB_SIGNAL_CONTROL              0xB0
#define FRAME_RATE_CONTROL_NORMAL       0xB1
#define FRAME_RATE_CONTROL_IDLE_8COLOR  0xB2
#define FRAME_RATE_CONTROL_PARTIAL      0xB3
#define DISPLAY_INVERSION_CONTROL       0xB4
#define BLANKING_PORCH_CONTROL          0xB5
#define DISPLAY_FUNCTION_CONTROL        0xB6
#define ENTRY_MODE_SET                  0xB7
#define BACKLIGHT_CONTROL_1             0xB8
#define BACKLIGHT_CONTROL_2             0xB9
#define BACKLIGHT_CONTROL_3             0xBA
#define BACKLIGHT_CONTROL_4             0xBB
#define BACKLIGHT_CONTROL_5             0xBC
#define BACKLIGHT_CONTROL_6             0xBD
#define BACKLIGHT_CONTROL_7             0xBE
#define BACKLIGHT_CONTROL_8             0xBF
#define POWER_CONTROL_1                 0xC0
#define POWER_CONTROL_2                 0xC1
#define VCOM_CONTROL_1                  0xC5
#define VCOM_CONTROL_2                  0xC7
#define POWER_ON_SEQ_CONTROL            0xCB
#define POWER_CONTROL_A                 0xCD
#define POWER_CONTROL_B                 0xCF
#define NVMEM_WRITE                     0xD0
#define NVMEM_PROTECTION_KEY            0xD1
#define NVMEM_STATUS_READ               0xD2
#define READ_ID4                        0xD3
#define POSITIVE_GAMMA_CORRECTION       0xE0
#define NEGATIVE_GAMMA_CORRECTION       0xE1
#define DIGITAL_GAMMA_CONTROL_1         0xE2
#define DIGITAL_GAMMA_CONTROL_2         0xE3
#define DRIVER_TIMING_CONTROL_A         0xE8
#define DRIVER_TIMING_CONTROL_B         0xEA
#define POWER_ON_SEQUENCE				0xED
#define ENABLE_3_GAMMA_CONTROL          0xF2
#define INTERFACE_CONTROL               0xF6
#define PUMP_RATIO_CONTROL              0xF7

#ifdef __cplusplus
}
#endif

#endif /* _ILI9341_H_ */
