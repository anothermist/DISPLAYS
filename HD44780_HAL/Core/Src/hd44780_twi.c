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
	HAL_I2C_Master_Transmit(&HD44780_INTERFACE, HD44780_ADDRESS,
			(uint8_t*) data_t, 4, 100);
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
	HAL_I2C_Master_Transmit(&HD44780_INTERFACE, HD44780_ADDRESS,
			(uint8_t*) data_t, 4, 100);
}

void HD44780_Clear(void) {
	HD44780_Command(0x80);
	for (int i = 0; i < 70; i++)
		HD44780_Data(' ');
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

void HD44780_String(char *str) {
	while (*str)
		HD44780_Data(*str++);
}

char cc[] = { 0x07, 0x0F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x1E, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F,
		0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x0F, 0x07, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1E,
		0x1C, 0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F,
		0x1F, 0x1F, 0x1F, 0x1F, 0x1F };

void HD44780_PutSpecialSymbols() {
	HD44780_Command(0x40);
	for (int i = 0; i < 64; i++)
		HD44780_Data(cc[i]);
}

void HD44780_drawBigDigits(unsigned char digit, unsigned char place) {

	switch (digit) {

	case 0:
		HD44780_SetPos(0, place);
		HD44780_Data(0);
		HD44780_SetPos(0, place + 1);
		HD44780_Data(1);
		HD44780_SetPos(0, place + 2);
		HD44780_Data(2);
		HD44780_SetPos(1, place);
		HD44780_Data(3);
		HD44780_SetPos(1, place + 1);
		HD44780_Data(4);
		HD44780_SetPos(1, place + 2);
		HD44780_Data(5);
		break;

	case 1:
		HD44780_SetPos(0, place);
		HD44780_Data(1);
		HD44780_SetPos(0, place + 1);
		HD44780_Data(2);
		HD44780_SetPos(0, place + 2);
		HD44780_String(' ');
		HD44780_SetPos(1, place);
		HD44780_Data(4);
		HD44780_SetPos(1, place + 1);
		HD44780_Data(7);
		HD44780_SetPos(1, place + 2);
		HD44780_Data(4);
		break;

	case 2:
		HD44780_SetPos(0, place);
		HD44780_Data(6);
		HD44780_SetPos(0, place + 1);
		HD44780_Data(6);
		HD44780_SetPos(0, place + 2);
		HD44780_Data(2);
		HD44780_SetPos(1, place);
		HD44780_Data(3);
		HD44780_SetPos(1, place + 1);
		HD44780_Data(4);
		HD44780_SetPos(1, place + 2);
		HD44780_Data(4);
		break;

	case 3:
		HD44780_SetPos(0, place);
		HD44780_Data(6);
		HD44780_SetPos(0, place + 1);
		HD44780_Data(6);
		HD44780_SetPos(0, place + 2);
		HD44780_Data(2);
		HD44780_SetPos(1, place);
		HD44780_Data(4);
		HD44780_SetPos(1, place + 1);
		HD44780_Data(4);
		HD44780_SetPos(1, place + 2);
		HD44780_Data(5);
		break;

	case 4:
		HD44780_SetPos(0, place);
		HD44780_Data(3);
		HD44780_SetPos(0, place + 1);
		HD44780_Data(4);
		HD44780_SetPos(0, place + 2);
		HD44780_Data(7);
		HD44780_SetPos(1, place);
		HD44780_String(' ');
		HD44780_SetPos(1, place + 1);
		HD44780_String(' ');
		HD44780_SetPos(1, place + 2);
		HD44780_Data(7);
		break;

	case 5:
		HD44780_SetPos(0, place);
		HD44780_Data(3);
		HD44780_SetPos(0, place + 1);
		HD44780_Data(6);
		HD44780_SetPos(0, place + 2);
		HD44780_Data(6);
		HD44780_SetPos(1, place);
		HD44780_Data(4);
		HD44780_SetPos(1, place + 1);
		HD44780_Data(4);
		HD44780_SetPos(1, place + 2);
		HD44780_Data(5);
		break;

	case 6:
		HD44780_SetPos(0, place);
		HD44780_Data(0);
		HD44780_SetPos(0, place + 1);
		HD44780_Data(6);
		HD44780_SetPos(0, place + 2);
		HD44780_Data(6);
		HD44780_SetPos(1, place);
		HD44780_Data(3);
		HD44780_SetPos(1, place + 1);
		HD44780_Data(4);
		HD44780_SetPos(1, place + 2);
		HD44780_Data(5);
		break;

	case 7:
		HD44780_SetPos(0, place);
		HD44780_Data(1);
		HD44780_SetPos(0, place + 1);
		HD44780_Data(1);
		HD44780_SetPos(0, place + 2);
		HD44780_Data(2);
		HD44780_SetPos(1, place);
		HD44780_String(' ');
		HD44780_SetPos(1, place + 1);
		HD44780_String(' ');
		HD44780_SetPos(1, place + 2);
		HD44780_Data(7);
		break;

	case 8:
		HD44780_SetPos(0, place);
		HD44780_Data(0);
		HD44780_SetPos(0, place + 1);
		HD44780_Data(6);
		HD44780_SetPos(0, place + 2);
		HD44780_Data(2);
		HD44780_SetPos(1, place);
		HD44780_Data(3);
		HD44780_SetPos(1, place + 1);
		HD44780_Data(4);
		HD44780_SetPos(1, place + 2);
		HD44780_Data(5);
		break;

	case 9:
		HD44780_SetPos(0, place);
		HD44780_Data(0);
		HD44780_SetPos(0, place + 1);
		HD44780_Data(6);
		HD44780_SetPos(0, place + 2);
		HD44780_Data(2);
		HD44780_SetPos(1, place);
		HD44780_Data(4);
		HD44780_SetPos(1, place + 1);
		HD44780_Data(4);
		HD44780_SetPos(1, place + 2);
		HD44780_Data(5);
		break;
	}
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

	HD44780_PutSpecialSymbols();
	HD44780_Clear();

}
