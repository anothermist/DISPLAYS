#include "hd44780_twi.h"

extern I2C_HandleTypeDef HD44780_INTERFACE;


void HD44780_Command(char cmd) {
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (cmd & 0xf0);
	data_l = ((cmd << 4) & 0xf0);
	data_t[0] = data_u | 0x0C;  //en=1, rs=0
	data_t[1] = data_u | 0x08;  //en=0, rs=0
	data_t[2] = data_l | 0x0C;  //en=1, rs=0
	data_t[3] = data_l | 0x08;  //en=0, rs=0
	HAL_I2C_Master_Transmit(&HD44780_INTERFACE, HD44780_ADDRESS, (uint8_t*) data_t, 4,
			100);
}

void HD44780_Data(char data) {
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (data & 0xf0);
	data_l = ((data << 4) & 0xf0);
	data_t[0] = data_u | 0x0D;  //en=1, rs=0
	data_t[1] = data_u | 0x09;  //en=0, rs=0
	data_t[2] = data_l | 0x0D;  //en=1, rs=0
	data_t[3] = data_l | 0x09;  //en=0, rs=0
	HAL_I2C_Master_Transmit(&HD44780_INTERFACE, HD44780_ADDRESS, (uint8_t*) data_t, 4,
			100);
}

void HD44780_Clear(void) {
	HD44780_Command(0x80);
	for (int i = 0; i < 70; i++) HD44780_Data(' ');
}

void HD44780_SetPos(int row, int col) {
	switch (row) {
	case 0:
		col |= 0x80;
		break;
	case 1:
		col |= 0xC0;
		break;
	}

	HD44780_Command(col);
}

void HD44780_Init(void) {
	// 4 bit initialisation
	HAL_Delay(50);  // wait for >40ms
	HD44780_Command(0x30);
	HAL_Delay(5);  // wait for >4.1ms
	HD44780_Command(0x30);
	HAL_Delay(1);  // wait for >100us
	HD44780_Command(0x30);
	HAL_Delay(10);
	HD44780_Command(0x20);  // 4bit mode
	HAL_Delay(10);

	// dislay initialisation
	HD44780_Command(0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
	HAL_Delay(1);
	HD44780_Command(0x08); //Display on/off control --> D=0,C=0, B=0  ---> display off
	HAL_Delay(1);
	HD44780_Command(0x01);  // clear display
	HAL_Delay(1);
	HAL_Delay(1);
	HD44780_Command(0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
	HAL_Delay(1);
	HD44780_Command(0x0C); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)
}

void HD44780_String(char *str) {
	while (*str) HD44780_Data(*str++);
}
