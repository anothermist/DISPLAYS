#include "hd44780.h"

#include <stdarg.h>
#include <stdio.h>
#include <util/delay.h>

void lcd_send(unsigned char value, unsigned char mode);
void lcd_write_nibble(unsigned char nibble);

static unsigned char lcd_displayparams;
static char lcd_buffer[LCD_COL_COUNT + 1];

void lcd_command(unsigned char command) {
	lcd_send(command, 0);
}

void lcd_write(unsigned char value) {
	lcd_send(value, 1);
}

void lcd_send(unsigned char value, unsigned char mode) {
	if (mode) {
		LCD_PORT = LCD_PORT | (1 << LCD_RS);
		} else {
		LCD_PORT = LCD_PORT & ~(1 << LCD_RS);
	}

	//LCD_PORT = LCD_PORT & ~(1 << LCD_RW);

	lcd_write_nibble(value >> 4);
	lcd_write_nibble(value);
}

void lcd_write_nibble(unsigned char nibble) {
	LCD_PORT = (LCD_PORT & 0xff & ~(0x0f << LCD_D0)) | ((nibble & 0x0f) << LCD_D0);

	LCD_PORT = LCD_PORT & ~(1 << LCD_EN);
	LCD_PORT = LCD_PORT | (1 << LCD_EN);
	LCD_PORT = LCD_PORT & ~(1 << LCD_EN);
	_delay_ms(0.3); // If delay less than this value, the data is not correctly displayed
}

unsigned char UserSymbol[8][8] = {
	{ 0x07, 0x0F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F },
	{ 0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x1C, 0x1E, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F },
	{ 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x0F, 0x07 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F },
	{ 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1E, 0x1C },
	{ 0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x1F, 0x1F },
	{ 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F },
};

void lcd_init(void) {
	//// Configure pins as output
	LCD_DDR = LCD_DDR
	| (1 << LCD_RS)
	//| (1 << LCD_RW)
	| (1 << LCD_EN)
	| (1 << LCD_D0)
	| (1 << LCD_D1)
	| (1 << LCD_D2)
	| (1 << LCD_D3);

	// Wait for LCD to become ready (docs say 15ms+)
	_delay_ms(15);

	LCD_PORT = LCD_PORT
	& ~(1 << LCD_EN)
	& ~(1 << LCD_RS)
	; //& ~(1 << LCD_RW);

	_delay_ms(4.1);

	lcd_write_nibble(0x03); // Switch to 4 bit mode
	_delay_ms(4.1);

	lcd_write_nibble(0x03); // 2nd time
	_delay_ms(4.1);

	lcd_write_nibble(0x03); // 3rd time
	_delay_ms(4.1);

	lcd_write_nibble(0x02); // Set 8-bit mode (?)

	lcd_command(LCD_FUNCTIONSET | LCD_4BITMODE | LCD_2LINE | LCD_5x8DOTS);

	lcd_displayparams = LCD_CURSOROFF | LCD_BLINKOFF;
	lcd_command(LCD_DISPLAYCONTROL | lcd_displayparams);
	
	for (unsigned char i = 0; i < 8; i++) lcd_create_char(i, &UserSymbol[i][0]);
	
	lcd_on();
	lcd_clear();
}

void lcd_on(void) {
	lcd_displayparams |= LCD_DISPLAYON;
	lcd_command(LCD_DISPLAYCONTROL | lcd_displayparams);
}

void lcd_off(void) {
	lcd_displayparams &= ~LCD_DISPLAYON;
	lcd_command(LCD_DISPLAYCONTROL | lcd_displayparams);
}

void lcd_clear(void) {
	lcd_command(LCD_CLEARDISPLAY);
	_delay_ms(2);
}

void lcd_return_home(void) {
	lcd_command(LCD_RETURNHOME);
	_delay_ms(2);
}

void lcd_enable_blinking(void) {
	lcd_displayparams |= LCD_BLINKON;
	lcd_command(LCD_DISPLAYCONTROL | lcd_displayparams);
}

void lcd_disable_blinking(void) {
	lcd_displayparams &= ~LCD_BLINKON;
	lcd_command(LCD_DISPLAYCONTROL | lcd_displayparams);
}

void lcd_enable_cursor(void) {
	lcd_displayparams |= LCD_CURSORON;
	lcd_command(LCD_DISPLAYCONTROL | lcd_displayparams);
}

void lcd_disable_cursor(void) {
	lcd_displayparams &= ~LCD_CURSORON;
	lcd_command(LCD_DISPLAYCONTROL | lcd_displayparams);
}

void lcd_scroll_left(void) {
	lcd_command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}

void lcd_scroll_right(void) {
	lcd_command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

void lcd_set_left_to_right(void) {
	lcd_displayparams |= LCD_ENTRYLEFT;
	lcd_command(LCD_ENTRYMODESET | lcd_displayparams);
}

void lcd_set_right_to_left(void) {
	lcd_displayparams &= ~LCD_ENTRYLEFT;
	lcd_command(LCD_ENTRYMODESET | lcd_displayparams);
}

void lcd_enable_autoscroll(void) {
	lcd_displayparams |= LCD_ENTRYSHIFTINCREMENT;
	lcd_command(LCD_ENTRYMODESET | lcd_displayparams);
}

void lcd_disable_autoscroll(void) {
	lcd_displayparams &= ~LCD_ENTRYSHIFTINCREMENT;
	lcd_command(LCD_ENTRYMODESET | lcd_displayparams);
}

void lcd_create_char(unsigned char location, unsigned char *charmap) {
	lcd_command(LCD_SETCGRAMADDR | ((location & 0x7) << 3));
	for (int i = 0; i < 8; i++) {
		lcd_write(charmap[i]);
	}
	lcd_command(LCD_SETDDRAMADDR);
}

void lcd_set_cursor(unsigned char row, unsigned char col) {
	static unsigned char offsets[] = { 0x00, 0x40, 0x14, 0x54 };
	lcd_command(LCD_SETDDRAMADDR | (col + offsets[row]));
}

void lcd_puts(char *puts) {
	for (char *it = puts; *it; it++) {
		lcd_write(*it);
	}
}

void lcd_string(char *puts, unsigned char row, unsigned char col) {
	static unsigned char offsets[] = { 0x00, 0x40, 0x14, 0x54 };
	lcd_command(LCD_SETDDRAMADDR | (col + offsets[row]));
	for (char *it = puts; *it; it++) lcd_write(*it);
}

void lcd_printf(char *format, ...) {
	va_list args;

	va_start(args, format);
	vsnprintf(lcd_buffer, LCD_COL_COUNT + 1, format, args);
	va_end(args);

	lcd_puts(lcd_buffer);
}

#define FirstStr_StartPosition_DDRAM_Addr 0x80
#define SecondStr_StartPosition_DDRAM_Addr 0xC0

void lcd_symbol(unsigned char Addr, unsigned char Str, unsigned char Cursor) {
	unsigned char x = 0;
	
	if (Str == 0) {
		x=FirstStr_StartPosition_DDRAM_Addr+Cursor;
		
		lcd_command(x);
		lcd_write(Addr);
	}
	else
	if (Str == 1) {
		x=SecondStr_StartPosition_DDRAM_Addr+Cursor;
		
		lcd_command(x);
		lcd_write(Addr);
	}
}

void lcd_drawBigDigits(unsigned char digit, unsigned char place) {
	
	switch (digit) {
		
		case 0:
		lcd_symbol(0, 0, place);
		lcd_symbol(1, 0, place + 1);
		lcd_symbol(2, 0, place + 2);
		lcd_symbol(3, 1, place);
		lcd_symbol(4, 1, place + 1);
		lcd_symbol(5, 1, place + 2);
		break;
		
		case 1:
		lcd_symbol(1, 0, place);
		lcd_symbol(2, 0, place + 1);
		lcd_string(" ", 0, place + 2);
		lcd_symbol(4, 1, place);
		lcd_symbol(7, 1, place + 1);
		lcd_symbol(4, 1, place + 2);
		break;
		
		case 2:
		lcd_symbol(6, 0, place);
		lcd_symbol(6, 0, place + 1);
		lcd_symbol(2, 0, place + 2);
		lcd_symbol(3, 1, place);
		lcd_symbol(4, 1, place + 1);
		lcd_symbol(4, 1, place + 2);
		break;
		
		case 3:
		lcd_symbol(6, 0, place);
		lcd_symbol(6, 0, place + 1);
		lcd_symbol(2, 0, place + 2);
		lcd_symbol(4, 1, place);
		lcd_symbol(4, 1, place + 1);
		lcd_symbol(5, 1, place + 2);
		break;
		
		case 4:
		lcd_symbol(3, 0, place);
		lcd_symbol(4, 0, place + 1);
		lcd_symbol(7, 0, place + 2);
		lcd_string(" ", 1, place);
		lcd_string(" ", 1, place + 1);
		lcd_symbol(7, 1, place + 2);
		break;
		
		case 5:
		lcd_symbol(3, 0, place);
		lcd_symbol(6, 0, place + 1);
		lcd_symbol(6, 0, place + 2);
		lcd_symbol(4, 1, place);
		lcd_symbol(4, 1, place + 1);
		lcd_symbol(5, 1, place + 2);
		break;
		
		case 6:
		lcd_symbol(0, 0, place);
		lcd_symbol(6, 0, place + 1);
		lcd_symbol(6, 0, place + 2);
		lcd_symbol(3, 1, place);
		lcd_symbol(4, 1, place + 1);
		lcd_symbol(5, 1, place + 2);
		break;
		
		case 7:
		lcd_symbol(1, 0, place);
		lcd_symbol(1, 0, place + 1);
		lcd_symbol(2, 0, place + 2);
		lcd_string(" ", 1, place);
		lcd_string(" ", 1, place + 1);
		lcd_symbol(7, 1, place + 2);
		break;
		
		case 8:
		lcd_symbol(0, 0, place);
		lcd_symbol(6, 0, place + 1);
		lcd_symbol(2, 0, place + 2);
		lcd_symbol(3, 1, place);
		lcd_symbol(4, 1, place + 1);
		lcd_symbol(5, 1, place + 2);
		break;
		
		case 9:
		lcd_symbol(0, 0, place);
		lcd_symbol(6, 0, place + 1);
		lcd_symbol(2, 0, place + 2);
		lcd_symbol(4, 1, place);
		lcd_symbol(4, 1, place + 1);
		lcd_symbol(5, 1, place + 2);
		break;
	}
}
