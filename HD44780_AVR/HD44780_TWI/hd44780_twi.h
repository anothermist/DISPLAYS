#ifndef HD44780_TWI_H_
#define HD44780_TWI_H_

#include "main.h"
#include "twi.h"

#define E1       twi_byte_send_by_addr(portlcd |=  0x04, 0x27);
#define E0       twi_byte_send_by_addr(portlcd &=~ 0x04, 0x27);
#define RS1      twi_byte_send_by_addr(portlcd |=  0x01, 0x27);
#define RS0      twi_byte_send_by_addr(portlcd &=~ 0x01, 0x27);
#define SETLED   twi_byte_send_by_addr(portlcd |=  0x08, 0x27);
#define SETWRITE twi_byte_send_by_addr(portlcd &=~ 0x02, 0x27);

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

void lcd_twi_init(void);

void lcd_twi_command(unsigned char command);
void lcd_twi_write(unsigned char value);

void lcd_twi_on(void);
void lcd_twi_off(void);

void lcd_twi_clear(void);
void lcd_twi_return_home(void);

void lcd_twi_enable_blinking(void);
void lcd_twi_disable_blinking(void);

void lcd_twi_enable_cursor(void);
void lcd_twi_disable_cursor(void);

void lcd_twi_scroll_left(void);
void lcd_twi_scroll_right(void);

void lcd_twi_set_left_to_right(void);
void lcd_twi_set_right_to_left(void);

void lcd_twi_enable_autoscroll(void);
void lcd_twi_disable_autoscroll(void);

void lcd_twi_create_char(unsigned char location, unsigned char *charmap);

void lcd_twi_set_cursor(unsigned char row, unsigned char col);

void lcd_twi_puts(char *string);

void lcd_twi_string(char *puts, unsigned char row, unsigned char col);

void lcd_twi_printf(char *format, ...);

void lcd_twi_symbol(unsigned char Addr, unsigned char Str, unsigned char Cursor);

void lcd_twi_drawBigDigits(uint8_t digit, uint8_t place);

#endif /* HD44780_TWI_H_ */
