#include "hd44780_i2c.h"
#include "string.h"
#include "stdio.h"
#include "stdarg.h"

extern I2C_HandleTypeDef HD44780_INTERFACE;

void HD44780_writeCommand(char cmd) {
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (cmd & 0xf0);
	data_l = ((cmd << 4) & 0xf0);
	data_t[0] = data_u | 0x0C;  //en=1, rs=0
	data_t[1] = data_u | 0x08;  //en=0, rs=0
	data_t[2] = data_l | 0x0C;  //en=1, rs=0
	data_t[3] = data_l | 0x08;  //en=0, rs=0
	HAL_I2C_Master_Transmit(&HD44780_INTERFACE, HD44780_ADDRESS,
			(uint8_t*) data_t, 4, 100);
}

void HD44780_writeData(char data) {
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (data & 0xf0);
	data_l = ((data << 4) & 0xf0);
	data_t[0] = data_u | 0x0D;  //en=1, rs=0
	data_t[1] = data_u | 0x09;  //en=0, rs=0
	data_t[2] = data_l | 0x0D;  //en=1, rs=0
	data_t[3] = data_l | 0x09;  //en=0, rs=0
	HAL_I2C_Master_Transmit(&HD44780_INTERFACE, HD44780_ADDRESS,
			(uint8_t*) data_t, 4, 1000);
}

static uint8_t DisplayControl = 0x0F;
static uint8_t FunctionSet = 0x38;

void HD44780_init_i2c(void){
	HAL_Delay(20);
	HD44780_writeData(0x3);
	HAL_Delay(5);
	HD44780_writeData(0x3);
	HAL_Delay(1);
	HD44780_writeData(0x3);
	HAL_Delay(1);
	HD44780_writeData(0x2);  //4 bit mode
	HAL_Delay(1);
	HD44780_writeCommand(LCD_FUNCTIONSET | LCD_FUNCTION_N);
	HD44780_writeCommand(
	LCD_DISPLAYCONTROL | LCD_DISPLAY_B | LCD_DISPLAY_C | LCD_DISPLAY_D);
	HD44780_writeCommand(LCD_CLEARDISPLAY);
	HAL_Delay(3);
	HD44780_cursorShow(0);
	HD44780_PutSpecialSymbols();
}

void HD44780_setCursor(uint8_t row, uint8_t col) {
	switch (row) {
	case 0:
		col |= 0x80;
		break;
	case 1:
		col |= 0xC0;
		break;
	case 2:
		col |= 0x80 + 0x14;
		break;
	case 3:
		col |= 0xC0 + 0x14;
		break;
	}
	HD44780_writeCommand(col);
}

void HD44780_1stLine(void) {
	HD44780_setCursor(0, 0);
}

void HD44780_2ndLine(void) {
	HD44780_setCursor(1, 0);
}

void HD44780_twoLines(void) {
	FunctionSet |= (0x08);
	HD44780_writeCommand(FunctionSet);
}

void HD44780_oneLine(void) {
	FunctionSet &= ~(0x08);
	HD44780_writeCommand(FunctionSet);
}

void HD44780_cursorShow(bool state) {
	if (state) {
		DisplayControl |= (0x03);
		HD44780_writeCommand(DisplayControl);
	} else {
		DisplayControl &= ~(0x03);
		HD44780_writeCommand(DisplayControl);
	}
}

void HD44780_clear(void) {
	HD44780_writeCommand(LCD_CLEARDISPLAY);
	HAL_Delay(3);
}

void HD44780_display(bool state) {
	if (state) {
		DisplayControl |= (0x04);
		HD44780_writeCommand(DisplayControl);
	} else {
		DisplayControl &= ~(0x04);
		HD44780_writeCommand(DisplayControl);
	}
}

void HD44780_shiftRight(uint8_t offset) {
	for (uint8_t i = 0; i < offset; i++) {
		HD44780_writeCommand(0x1c);
	}
}

void HD44780_shiftLeft(uint8_t offset) {
	for (uint8_t i = 0; i < offset; i++) {
		HD44780_writeCommand(0x18);
	}
}

void HD44780_printf(const char *str, ...) {
	char stringArray[20];
	va_list args;
	va_start(args, str);
	vsprintf(stringArray, str, args);
	va_end(args);
	for (uint8_t i = 0; i < strlen(stringArray) && i < 20; i++) {
		HD44780_writeData((uint8_t) stringArray[i]);
	}
}

char cc[] = { 0x07, 0x0F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x1E, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F,
		0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x0F, 0x07, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1E,
		0x1C, 0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F,
		0x1F, 0x1F, 0x1F, 0x1F, 0x1F };

void HD44780_PutSpecialSymbols(void) {
	HD44780_writeCommand(0x40);
	for (int i = 0; i < 64; i++)
		HD44780_writeData(cc[i]);
}

void HD44780_drawBigDigits(unsigned char digit, unsigned char place) {

	switch (digit) {

	case 0:
		HD44780_setCursor(0, place);
		HD44780_writeData(0);
		HD44780_setCursor(0, place + 1);
		HD44780_writeData(1);
		HD44780_setCursor(0, place + 2);
		HD44780_writeData(2);
		HD44780_setCursor(1, place);
		HD44780_writeData(3);
		HD44780_setCursor(1, place + 1);
		HD44780_writeData(4);
		HD44780_setCursor(1, place + 2);
		HD44780_writeData(5);
		break;

	case 1:
		HD44780_setCursor(0, place);
		HD44780_writeData(1);
		HD44780_setCursor(0, place + 1);
		HD44780_writeData(2);
		HD44780_setCursor(0, place + 2);
		HD44780_printf(" ");
		HD44780_setCursor(1, place);
		HD44780_writeData(4);
		HD44780_setCursor(1, place + 1);
		HD44780_writeData(7);
		HD44780_setCursor(1, place + 2);
		HD44780_writeData(4);
		break;

	case 2:
		HD44780_setCursor(0, place);
		HD44780_writeData(6);
		HD44780_setCursor(0, place + 1);
		HD44780_writeData(6);
		HD44780_setCursor(0, place + 2);
		HD44780_writeData(2);
		HD44780_setCursor(1, place);
		HD44780_writeData(3);
		HD44780_setCursor(1, place + 1);
		HD44780_writeData(4);
		HD44780_setCursor(1, place + 2);
		HD44780_writeData(4);
		break;

	case 3:
		HD44780_setCursor(0, place);
		HD44780_writeData(6);
		HD44780_setCursor(0, place + 1);
		HD44780_writeData(6);
		HD44780_setCursor(0, place + 2);
		HD44780_writeData(2);
		HD44780_setCursor(1, place);
		HD44780_writeData(4);
		HD44780_setCursor(1, place + 1);
		HD44780_writeData(4);
		HD44780_setCursor(1, place + 2);
		HD44780_writeData(5);
		break;

	case 4:
		HD44780_setCursor(0, place);
		HD44780_writeData(3);
		HD44780_setCursor(0, place + 1);
		HD44780_writeData(4);
		HD44780_setCursor(0, place + 2);
		HD44780_writeData(7);
		HD44780_setCursor(1, place);
		HD44780_printf(" ");
		HD44780_setCursor(1, place + 1);
		HD44780_printf(" ");
		HD44780_setCursor(1, place + 2);
		HD44780_writeData(7);
		break;

	case 5:
		HD44780_setCursor(0, place);
		HD44780_writeData(3);
		HD44780_setCursor(0, place + 1);
		HD44780_writeData(6);
		HD44780_setCursor(0, place + 2);
		HD44780_writeData(6);
		HD44780_setCursor(1, place);
		HD44780_writeData(4);
		HD44780_setCursor(1, place + 1);
		HD44780_writeData(4);
		HD44780_setCursor(1, place + 2);
		HD44780_writeData(5);
		break;

	case 6:
		HD44780_setCursor(0, place);
		HD44780_writeData(0);
		HD44780_setCursor(0, place + 1);
		HD44780_writeData(6);
		HD44780_setCursor(0, place + 2);
		HD44780_writeData(6);
		HD44780_setCursor(1, place);
		HD44780_writeData(3);
		HD44780_setCursor(1, place + 1);
		HD44780_writeData(4);
		HD44780_setCursor(1, place + 2);
		HD44780_writeData(5);
		break;

	case 7:
		HD44780_setCursor(0, place);
		HD44780_writeData(1);
		HD44780_setCursor(0, place + 1);
		HD44780_writeData(1);
		HD44780_setCursor(0, place + 2);
		HD44780_writeData(2);
		HD44780_setCursor(1, place);
		HD44780_printf(" ");
		HD44780_setCursor(1, place + 1);
		HD44780_printf(" ");
		HD44780_setCursor(1, place + 2);
		HD44780_writeData(7);
		break;

	case 8:
		HD44780_setCursor(0, place);
		HD44780_writeData(0);
		HD44780_setCursor(0, place + 1);
		HD44780_writeData(6);
		HD44780_setCursor(0, place + 2);
		HD44780_writeData(2);
		HD44780_setCursor(1, place);
		HD44780_writeData(3);
		HD44780_setCursor(1, place + 1);
		HD44780_writeData(4);
		HD44780_setCursor(1, place + 2);
		HD44780_writeData(5);
		break;

	case 9:
		HD44780_setCursor(0, place);
		HD44780_writeData(0);
		HD44780_setCursor(0, place + 1);
		HD44780_writeData(6);
		HD44780_setCursor(0, place + 2);
		HD44780_writeData(2);
		HD44780_setCursor(1, place);
		HD44780_writeData(4);
		HD44780_setCursor(1, place + 1);
		HD44780_writeData(4);
		HD44780_setCursor(1, place + 2);
		HD44780_writeData(5);
		break;
	}
}
