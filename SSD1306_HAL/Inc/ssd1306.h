#ifndef SSD1306_H_
#define SSD1306_H_

#ifdef __cplusplus
extern C {
#endif

#include "stm32f1xx_hal.h"
#include "fonts.h"

#include "stdlib.h"
#include "string.h"

#define SSD1306_HEIGHT           64 // 32 64
#define SSD1306_WIDTH            128

#define	SSD1306_I2C					   hi2c1
#define SSD1306_I2C_ADDRESS         0x78 // 0x78 0x7A 0x3C

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

void I2C_Init(void);
void I2C_Write(uint8_t address, uint8_t reg, uint8_t data);
void I2C_WriteMulti(uint8_t address, uint8_t reg, uint8_t *data, uint16_t count);

uint8_t SSD1306_Init(void);
void LCD_ON(void);
void LCD_OFF(void);
void LCD_UpdateScreen(void);
void LCD_ToggleInvert(void);
void LCD_Fill(SSD1306_COLOR_t color);
void LCD_GotoXY(uint16_t x, uint16_t y);
void LCD_Pixel(uint16_t x, uint16_t y, SSD1306_COLOR_t color);
char LCD_Char(char ch, FontDef_t* Font, SSD1306_COLOR_t color);
char LCD_String(uint16_t x, uint16_t y, char* str, FontDef_t* Font, SSD1306_COLOR_t color);
void LCD_Line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, SSD1306_COLOR_t c);
void LCD_Rectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, SSD1306_COLOR_t c);
void LCD_Rectangle_Fill(uint16_t x, uint16_t y, uint16_t w, uint16_t h, SSD1306_COLOR_t c);
void LCD_Triangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, SSD1306_COLOR_t color);
void LCD_Triangle_Fill(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, SSD1306_COLOR_t color);
void LCD_Circle(int16_t x0, int16_t y0, int16_t r, SSD1306_COLOR_t c);
void LCD_Circle_Fill(int16_t x0, int16_t y0, int16_t r, SSD1306_COLOR_t c);

#ifdef __cplusplus
}
#endif

#endif
