#ifndef SSD1306_H_
#define SSD1306_H_

#include "main.h"

#define SSD1306_I2C_ADDRESS					 0x3C
// size
#define SSD1306_WIDTH                         128
#define SSD1306_HEIGHT                         64
#define SSD1306_DEFAULT_SPACE                   5
// Commands
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
#define SSD1306_SEGREMAP                     0xA0
#define SSD1306_CHARGEPUMP                   0x8D
#define SSD1306_EXTERNALVCC                   0x1
#define SSD1306_SWITCHCAPVCC                  0x2
// Scrolling #defines
#define SSD1306_ACTIVATE_SCROLL               0x2F
#define SSD1306_DEACTIVATE_SCROLL             0x2E
#define SSD1306_SET_VERTICAL_SCROLL_AREA      0xA3
#define SSD1306_RIGHT_HORIZONTAL_SCROLL       0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL        0x27
#define SSD1306_VERT_AND_RIGHT_HORIZ_SCROLL   0x29
#define SSD1306_VERT_AND_LEFT_HORIZ_SCROLL    0x2A

#define COMAND		                          0x00
#define DATA		                          0x40

void LCD_init(void);
void LCD_Command(unsigned char ControByte, unsigned char DataByte);
void LCD_Goto(unsigned char x, unsigned char y);
void LCD_Goto2X(unsigned char x, unsigned char y);
void LCD_Clear(void);
void LCD_Contrast(char set_contrast);
void LCD_BigNum(unsigned char num);
void LCD_Char(unsigned int c);
void LCD_CharBig(unsigned int c);
void LCD_Printf(unsigned char* buf, unsigned char size);
void LCD_DrawImage(unsigned char num_image);
void LCD_Bat(unsigned char y,unsigned char x, unsigned char z);
void LCD_Mode(char set_mode); //1 - inverted / 0 - normal
void LCD_Sleep(char set);   //1 - on sleep / 0 - off sleep

extern const unsigned char image0[1026];
extern const unsigned char LCD_Buffer[0x0500];
extern const unsigned char BigNum[15][96];

void OLED_Init();
void OLED_Command(int command);
void OLED_Data(int data);
void OLED_Clear();
void OLED_Test();

#endif
