#ifndef HD44780_H_
#define HD44780_H_

#include "main.h"

#pragma once

#define LCD_DDR  DDRD
#define LCD_PORT PORTD

//#define LCD_RW
#define LCD_RS 2
#define LCD_EN 3
#define LCD_D0 4
#define LCD_D1 5
#define LCD_D2 6
#define LCD_D3 7


#define LCD_COL_COUNT 16
#define LCD_ROW_COUNT 2

// The rest should be left alone
#define LCD_CLEARDISPLAY   0x01
#define LCD_RETURNHOME     0x02
#define LCD_ENTRYMODESET   0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT    0x10
#define LCD_FUNCTIONSET    0x20
#define LCD_SETCGRAMADDR   0x40
#define LCD_SETDDRAMADDR   0x80

#define LCD_ENTRYRIGHT          0x00
#define LCD_ENTRYLEFT           0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

#define LCD_DISPLAYON  0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON   0x02
#define LCD_CURSOROFF  0x00
#define LCD_BLINKON    0x01
#define LCD_BLINKOFF   0x00

#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE  0x00
#define LCD_MOVERIGHT   0x04
#define LCD_MOVELEFT    0x00

#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE    0x08
#define LCD_1LINE    0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS  0x00

void lcd_init(void);

void lcd_command(unsigned char command);
void lcd_write(unsigned char value);

void lcd_on(void);
void lcd_off(void);

void lcd_clear(void);
void lcd_return_home(void);

void lcd_enable_blinking(void);
void lcd_disable_blinking(void);

void lcd_enable_cursor(void);
void lcd_disable_cursor(void);

void lcd_scroll_left(void);
void lcd_scroll_right(void);

void lcd_set_left_to_right(void);
void lcd_set_right_to_left(void);

void lcd_enable_autoscroll(void);
void lcd_disable_autoscroll(void);

void lcd_create_char(unsigned char location, unsigned char *charmap);

void lcd_set_cursor(unsigned char row, unsigned char col);

void lcd_puts(char *string);

void lcd_string(char *puts, unsigned char row, unsigned char col);

void lcd_printf(char *format, ...);

void lcd_symbol(unsigned char Addr, unsigned char Str, unsigned char Cursor);

void lcd_drawBigDigits(uint8_t digit, uint8_t place);

#endif /* HD44780_H_ */
