#include "hd44780_twi.h"

unsigned char portlcd = 0;

void lcd_twi_send(unsigned char value, unsigned char mode);
void lcd_twi_write_nibble(unsigned char nibble);

static unsigned char lcd_twi_displayparams;
static char lcd_twi_buffer[LCD_COL_COUNT + 1];

void lcd_twi_command(unsigned char command) {
	RS0
	lcd_twi_send(command, 0);
}

void lcd_twi_write(unsigned char value) {
	RS1
	lcd_twi_send(value, 1);
}

void lcd_twi_send(unsigned char value, unsigned char mode) {
	lcd_twi_write_nibble(value >> 4);
	lcd_twi_write_nibble(value);
}

void lcd_twi_write_nibble(unsigned char nibble) {
	nibble <<= 4;
	E1
	_delay_ms(0.3);
	twi_byte_send_by_addr(portlcd|nibble, 0x27);
	E0
	_delay_ms(0.3);
}

unsigned char UserSymbol_twi[8][8] = {
	{ 0x07, 0x0F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F },
	{ 0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x1C, 0x1E, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F },
	{ 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x0F, 0x07 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F },
	{ 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1E, 0x1C },
	{ 0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x1F, 0x1F },
	{ 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F },
};

void lcd_twi_init(void) {
	
	_delay_ms(15);
	lcd_twi_write_nibble(0b00000011);
	_delay_ms(4);
	lcd_twi_write_nibble(0b00000011);
	_delay_us(100);
	lcd_twi_write_nibble(0b00000011);
	_delay_ms(1);
	lcd_twi_write_nibble(0b00000010);
	_delay_ms(1);
	lcd_twi_send(0b00101000, 0); //4bit mode (DL=0) and 2 lines (N=1)
	_delay_ms(1);
	lcd_twi_send(0b00001100, 0); //disable show (D=1), no cursors (C=0, B=0)
	_delay_ms(1);
	lcd_twi_send(0b00000110, 0); //invisible cursor from right to left
	_delay_ms(1);
	SETLED
	SETWRITE
	
	for (unsigned char i = 0; i < 8; i++) lcd_twi_create_char(i, &UserSymbol_twi[i][0]);
	
	lcd_twi_on();
	lcd_twi_clear();
}

void lcd_twi_on(void) {
	lcd_twi_displayparams |= LCD_DISPLAYON;
	lcd_twi_command(LCD_DISPLAYCONTROL | lcd_twi_displayparams);
}

void lcd_twi_off(void) {
	lcd_twi_displayparams &= ~LCD_DISPLAYON;
	lcd_twi_command(LCD_DISPLAYCONTROL | lcd_twi_displayparams);
}

void lcd_twi_clear(void) {
	lcd_twi_command(LCD_CLEARDISPLAY);
	_delay_ms(2);
}

void lcd_twi_return_home(void) {
	lcd_twi_command(LCD_RETURNHOME);
	_delay_ms(2);
}

void lcd_twi_enable_blinking(void) {
	lcd_twi_displayparams |= LCD_BLINKON;
	lcd_twi_command(LCD_DISPLAYCONTROL | lcd_twi_displayparams);
}

void lcd_twi_disable_blinking(void) {
	lcd_twi_displayparams &= ~LCD_BLINKON;
	lcd_twi_command(LCD_DISPLAYCONTROL | lcd_twi_displayparams);
}

void lcd_twi_enable_cursor(void) {
	lcd_twi_displayparams |= LCD_CURSORON;
	lcd_twi_command(LCD_DISPLAYCONTROL | lcd_twi_displayparams);
}

void lcd_twi_disable_cursor(void) {
	lcd_twi_displayparams &= ~LCD_CURSORON;
	lcd_twi_command(LCD_DISPLAYCONTROL | lcd_twi_displayparams);
}

void lcd_twi_scroll_left(void) {
	lcd_twi_command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}

void lcd_twi_scroll_right(void) {
	lcd_twi_command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

void lcd_twi_set_left_to_right(void) {
	lcd_twi_displayparams |= LCD_ENTRYLEFT;
	lcd_twi_command(LCD_ENTRYMODESET | lcd_twi_displayparams);
}

void lcd_twi_set_right_to_left(void) {
	lcd_twi_displayparams &= ~LCD_ENTRYLEFT;
	lcd_twi_command(LCD_ENTRYMODESET | lcd_twi_displayparams);
}

void lcd_twi_enable_autoscroll(void) {
	lcd_twi_displayparams |= LCD_ENTRYSHIFTINCREMENT;
	lcd_twi_command(LCD_ENTRYMODESET | lcd_twi_displayparams);
}

void lcd_twi_disable_autoscroll(void) {
	lcd_twi_displayparams &= ~LCD_ENTRYSHIFTINCREMENT;
	lcd_twi_command(LCD_ENTRYMODESET | lcd_twi_displayparams);
}

void lcd_twi_create_char(unsigned char location, unsigned char *charmap) {
	lcd_twi_command(LCD_SETCGRAMADDR | ((location & 0x7) << 3));
	for (int i = 0; i < 8; i++) {
		lcd_twi_write(charmap[i]);
	}
	lcd_twi_command(LCD_SETDDRAMADDR);
}

void lcd_twi_set_cursor(unsigned char row, unsigned char col) {
	static unsigned char offsets[] = { 0x00, 0x40, 0x14, 0x54 };
	lcd_twi_command(LCD_SETDDRAMADDR | (col + offsets[row]));
}

void lcd_twi_puts(char *puts) {
	for (char *it = puts; *it; it++) lcd_twi_write(*it);
}

void lcd_twi_string(char *puts, unsigned char row, unsigned char col) {
	static unsigned char offsets[] = { 0x00, 0x40, 0x14, 0x54 };
	lcd_twi_command(LCD_SETDDRAMADDR | (col + offsets[row]));
	for (char *it = puts; *it; it++) lcd_twi_write(*it);
}

void lcd_twi_printf(char *format, ...) {
	va_list args;

	va_start(args, format);
	vsnprintf(lcd_twi_buffer, LCD_COL_COUNT + 1, format, args);
	va_end(args);

	lcd_twi_puts(lcd_twi_buffer);
}

#define FirstStr_StartPosition_DDRAM_Addr 0x80
#define SecondStr_StartPosition_DDRAM_Addr 0xC0

void lcd_twi_symbol(unsigned char Addr, unsigned char Str, unsigned char Cursor) {
	unsigned char x = 0;
	
	if (Str == 0) {
		x = FirstStr_StartPosition_DDRAM_Addr + Cursor;
		
		lcd_twi_command(x);
		lcd_twi_write(Addr);
	}
	else
	if (Str == 1) {
		x = SecondStr_StartPosition_DDRAM_Addr + Cursor;
		lcd_twi_command(x);
		lcd_twi_write(Addr);
	}
}

void lcd_twi_drawBigDigits(unsigned char digit, unsigned char place) {
	
	switch (digit) {
		
		case 0:
		lcd_twi_symbol(0, 0, place);
		lcd_twi_symbol(1, 0, place + 1);
		lcd_twi_symbol(2, 0, place + 2);
		lcd_twi_symbol(3, 1, place);
		lcd_twi_symbol(4, 1, place + 1);
		lcd_twi_symbol(5, 1, place + 2);
		break;
		
		case 1:
		lcd_twi_symbol(1, 0, place);
		lcd_twi_symbol(2, 0, place + 1);
		lcd_twi_string(" ", 0, place + 2);
		lcd_twi_symbol(4, 1, place);
		lcd_twi_symbol(7, 1, place + 1);
		lcd_twi_symbol(4, 1, place + 2);
		break;
		
		case 2:
		lcd_twi_symbol(6, 0, place);
		lcd_twi_symbol(6, 0, place + 1);
		lcd_twi_symbol(2, 0, place + 2);
		lcd_twi_symbol(3, 1, place);
		lcd_twi_symbol(4, 1, place + 1);
		lcd_twi_symbol(4, 1, place + 2);
		break;
		
		case 3:
		lcd_twi_symbol(6, 0, place);
		lcd_twi_symbol(6, 0, place + 1);
		lcd_twi_symbol(2, 0, place + 2);
		lcd_twi_symbol(4, 1, place);
		lcd_twi_symbol(4, 1, place + 1);
		lcd_twi_symbol(5, 1, place + 2);
		break;
		
		case 4:
		lcd_twi_symbol(3, 0, place);
		lcd_twi_symbol(4, 0, place + 1);
		lcd_twi_symbol(7, 0, place + 2);
		lcd_twi_string(" ", 1, place);
		lcd_twi_string(" ", 1, place + 1);
		lcd_twi_symbol(7, 1, place + 2);
		break;
		
		case 5:
		lcd_twi_symbol(3, 0, place);
		lcd_twi_symbol(6, 0, place + 1);
		lcd_twi_symbol(6, 0, place + 2);
		lcd_twi_symbol(4, 1, place);
		lcd_twi_symbol(4, 1, place + 1);
		lcd_twi_symbol(5, 1, place + 2);
		break;
		
		case 6:
		lcd_twi_symbol(0, 0, place);
		lcd_twi_symbol(6, 0, place + 1);
		lcd_twi_symbol(6, 0, place + 2);
		lcd_twi_symbol(3, 1, place);
		lcd_twi_symbol(4, 1, place + 1);
		lcd_twi_symbol(5, 1, place + 2);
		break;
		
		case 7:
		lcd_twi_symbol(1, 0, place);
		lcd_twi_symbol(1, 0, place + 1);
		lcd_twi_symbol(2, 0, place + 2);
		lcd_twi_string(" ", 1, place);
		lcd_twi_string(" ", 1, place + 1);
		lcd_twi_symbol(7, 1, place + 2);
		break;
		
		case 8:
		lcd_twi_symbol(0, 0, place);
		lcd_twi_symbol(6, 0, place + 1);
		lcd_twi_symbol(2, 0, place + 2);
		lcd_twi_symbol(3, 1, place);
		lcd_twi_symbol(4, 1, place + 1);
		lcd_twi_symbol(5, 1, place + 2);
		break;
		
		case 9:
		lcd_twi_symbol(0, 0, place);
		lcd_twi_symbol(6, 0, place + 1);
		lcd_twi_symbol(2, 0, place + 2);
		lcd_twi_symbol(4, 1, place);
		lcd_twi_symbol(4, 1, place + 1);
		lcd_twi_symbol(5, 1, place + 2);
		break;
	}
}
