#include "hd44780_twi.h"

uint8_t buf[1] = { 0 };
extern I2C_HandleTypeDef HD44780_INTERFACE;
char str1[100];
uint8_t portlcd;

__STATIC_INLINE void DelayMicro(__IO uint32_t micros)
	
{
	micros *=(SystemCoreClock / 1000000) / 5;
	while (micros--);
}

void HD44780_Data(uint8_t dt)
{
	buf[0] = dt;
	HAL_I2C_Master_Transmit(&HD44780_INTERFACE, (uint16_t) HD44780_ADDRESS, buf, 1, 1000);
}

void sendHalfByte(uint8_t c)
{
	c <<= 4;
	e_set();
	DelayMicro(50);
	HD44780_Data(portlcd | c);
	e_reset();
	DelayMicro(50);
}

void sendByte(uint8_t c, uint8_t mode)
{
	if(mode == 0) rs_reset();
	else rs_set();
	uint8_t hc = 0;
	hc = c >> 4;
	sendHalfByte(hc);
	sendHalfByte(c);
}

void HD44780_Command(uint8_t dt)
{
	rs_reset();
	HD44780_Data(dt >> 4);
	e_set();
	HAL_Delay(1);
	e_reset();
	HD44780_Data(dt);
	e_set();
	HAL_Delay(1);
	e_reset();
}

void HD44780_SendChar(char ch)
{
	sendByte(ch, 1);
}

void HD44780_String(char* st)
{
	uint8_t i = 0;
	while(st[i] != 0)
	{
		sendByte(st[i], 1);
		i++;
	}
}

void HD44780_SetPos(uint8_t y, uint8_t x)
{
	switch(y)
	{
		case 0:
			sendByte(x | 0x80, 0);
			HAL_Delay(1);
			break;
		case 1:
			sendByte((0x40 + x) | 0x80, 0);
			HAL_Delay(1);
			break;
		case 2:
			sendByte((0x14 + x) | 0x80, 0);
			HAL_Delay(1);
			break;
		case 3:
			sendByte((0x54 + x) | 0x80, 0);
			HAL_Delay(1);
			break;
	}
}

void HD44780_Clear(void)
{
	sendByte(0x01, 0);
	HAL_Delay(2);
}

void HD44780_Init(void)
{
	HAL_Delay(15);
	sendHalfByte(0x03);
	HAL_Delay(4);
	sendHalfByte(0x03);
	DelayMicro(100);
	sendHalfByte(0x03);
	HAL_Delay(1);
	sendHalfByte(0x02);
	HAL_Delay(1);
	sendByte(0x28, 0);
	HAL_Delay(1);
	sendByte(0x0C, 0);
	HAL_Delay(1);
	sendByte(0x01, 0);
	HAL_Delay(2);
	sendByte(0x06, 0);
	HAL_Delay(1);
	setled();
	setwrite();
}
