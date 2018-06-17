#include "hd44780.h"

uint8_t UserSymbol[8][8] =
{
	{ 0x07, 0x0F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F },
	{ 0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00 },
	{ 0x1C, 0x1E, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F },
	{ 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x0F, 0x07 },
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x1F },
	{ 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F },
	{ 0x1F, 0x1F, 0x1F, 0x00, 0x00, 0x00, 0x1F, 0x1F },
	{ 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F },
};

#if Data_Length == 1

uint8_t *data_bus_port[8]={(uint8_t*)&PORT_bus_0, (uint8_t*)&PORT_bus_1, (uint8_t*)&PORT_bus_2, (uint8_t*)&PORT_bus_3,
(uint8_t*)&PORT_bus_4, (uint8_t*)&PORT_bus_5, (uint8_t*)&PORT_bus_6, (uint8_t*)&PORT_bus_7};
uint8_t data_bus_pin[8]={PIN_bus_0, PIN_bus_1, PIN_bus_2, PIN_bus_3, PIN_bus_4, PIN_bus_5, PIN_bus_6, PIN_bus_7};

void BusLinesState(uint8_t *data, uint8_t RS)
{
	uint8_t time = 40;
	
	for (uint8_t i = 0; i < 8; i++)
	if (CheckBit(*data,i)) Sbit(*data_bus_port[i],data_bus_pin[i]);
	else Cbit(*data_bus_port[i],data_bus_pin[i]);
	
	if (RS == 0)
	{
		Sbit(PORT_Strob_Signal_E, PIN_Strob_Signal_E);
		_delay_us(time);
		Cbit(PORT_Strob_Signal_E, PIN_Strob_Signal_E);
		_delay_us(time);
	}
	else
	if (RS == 1)
	{
		Sbit(PORT_Strob_Signal_RS, PIN_Strob_Signal_RS);
		Sbit(PORT_Strob_Signal_E, PIN_Strob_Signal_E);
		_delay_us(time);
		Cbit(PORT_Strob_Signal_E, PIN_Strob_Signal_E);
		Cbit(PORT_Strob_Signal_RS, PIN_Strob_Signal_RS);
		_delay_us(time);
	}
	else
	if (RS == 2)
	{
		Sbit(PORT_Strob_Signal_E, PIN_Strob_Signal_E);
		_delay_ms(5);
		Cbit(PORT_Strob_Signal_E, PIN_Strob_Signal_E);
		_delay_ms(5);
	}
}

void LCD_Init(void)
{
	uint8_t bus_data = 0b100000;
	
	if (Data_Length == 1) Sbit(bus_data, 4);
	else Cbit(bus_data, 4);
	if (NumberOfLines == 1) Sbit(bus_data, 3);
	else Cbit(bus_data, 3);
	if (Font==1) Sbit(bus_data, 2);
	else Cbit(bus_data, 2);
	BusLinesState(&bus_data, 0);
	
	for (uint8_t i = 0; i < 7; i++)
	LCD_UserSymbolsWrite(i, &UserSymbol[i][0]);
}

#elif Data_Length == 0

uint8_t *data_bus_port[4] = { (uint8_t*)&PORT_bus_4, (uint8_t*)&PORT_bus_5, (uint8_t*)&PORT_bus_6, (uint8_t*)&PORT_bus_7};
uint8_t data_bus_pin[4] = { PIN_bus_4, PIN_bus_5, PIN_bus_6, PIN_bus_7};

void BusLinesState(uint8_t *data, uint8_t RS)
{
	uint8_t time = 40;
	uint8_t HB, LB;
	uint8_t *temp;
	
	HB = *data >> 4;
	LB = *data &~(1 << 7) &~(1 << 6) &~(1 << 5) &~(1 << 4);
	
	for (uint8_t z = 0; z < 2; z++)
	{
		if (z == 0) temp = &HB;
		else
		if (z == 1) temp = &LB;
		
		for (uint8_t i = 0; i < 4; i++)
		if (CheckBit(*temp,i)) Sbit(*data_bus_port[i], data_bus_pin[i]);
		else Cbit(*data_bus_port[i], data_bus_pin[i]);
		
		if (RS == 0)
		{
			Sbit(PORT_Strob_Signal_E, PIN_Strob_Signal_E);
			_delay_us(time);
			Cbit(PORT_Strob_Signal_E, PIN_Strob_Signal_E);
			_delay_us(time);
		}
		else
		if (RS == 1)
		{
			if (z == 0)
			Sbit(PORT_Strob_Signal_RS, PIN_Strob_Signal_RS);
			Sbit(PORT_Strob_Signal_E, PIN_Strob_Signal_E);
			_delay_us(time);
			Cbit(PORT_Strob_Signal_E, PIN_Strob_Signal_E);
			if (z == 1)
			Cbit(PORT_Strob_Signal_RS, PIN_Strob_Signal_RS);
			_delay_us(time);
		}
		else
		if (RS == 2)
		{
			Sbit(PORT_Strob_Signal_E, PIN_Strob_Signal_E);
			_delay_ms(5);
			Cbit(PORT_Strob_Signal_E, PIN_Strob_Signal_E);
			_delay_ms(5);
		}
	}
}

void LCD_Init(void)
{
	_delay_ms(15);
	
	uint8_t bus_data = 0b100000;
	uint8_t empty_Init = 0x33;
	
	for (uint8_t i = 0; i < 2; i++)
	{
		if (i == 0)
		BusLinesState(&empty_Init, 0);
		else if (i == 1)
		{
			empty_Init--;
			BusLinesState(&empty_Init, 0);
		}
	}
	
	if (Data_Length == 1) Sbit(bus_data, 4);
	else Cbit(bus_data, 4);
	if (NumberOfLines == 1) Sbit(bus_data, 3);
	else Cbit(bus_data, 3);
	if (Font == 1) Sbit(bus_data, 2);
	else Cbit(bus_data, 2);
	
	BusLinesState(&bus_data, 0);
	
	for (uint8_t i = 0; i < 7; i++)
	LCD_UserSymbolsWrite(i, &UserSymbol[i][0]);
}

#endif

void LCD_Full_Clean(void)
{
	uint8_t bus_data = 0b1;
	BusLinesState(&bus_data, 2);
	Sbit(PORT_Strob_Signal_E, PIN_Strob_Signal_E);
	_delay_ms(5);
	Cbit(PORT_Strob_Signal_E, PIN_Strob_Signal_E);
	_delay_ms(5);
}

void LCD_CursorPosition_ToStart(void)
{
	uint8_t bus_data = 0b10;
	BusLinesState(&bus_data, 2);
	Sbit(PORT_Strob_Signal_E, PIN_Strob_Signal_E);
	_delay_ms(5);
	Cbit(PORT_Strob_Signal_E, PIN_Strob_Signal_E);
	_delay_ms(5);
}

void LCD_AutoMovCurDispDirect(uint8_t I_D, uint8_t S)
{
	uint8_t bus_data = 0b100;
	
	if (I_D == 1) Sbit(bus_data, 1);
	else Cbit(bus_data, 1);
	if (S == 1) Sbit(bus_data, 0);
	else Cbit(bus_data,0);
	BusLinesState(&bus_data, 0);
}

void LCD_DisplEnable_CursOnOffBlink(uint8_t D, uint8_t C, uint8_t B)
{
	uint8_t bus_data = 0b1000;
	
	if (D == 1) Sbit(bus_data, 2);
	else Cbit(bus_data, 2);
	if (C == 1) Sbit(bus_data, 1);
	else Cbit(bus_data, 1);
	if (B == 1) Sbit(bus_data, 0);
	else Cbit(bus_data, 0);
	BusLinesState(&bus_data, 0);
}

void LCD_MovingCurDispDirection(uint8_t S_C, uint8_t R_L)
{
	uint8_t bus_data = 0b10000;
	
	if (S_C == 1) Sbit(bus_data, 3);
	else Cbit(bus_data, 3);
	if (R_L == 1) Sbit(bus_data, 2);
	else Cbit(bus_data, 2);
	BusLinesState(&bus_data, 0);
}

void LCD_UserSymbolsWrite(uint8_t Addr, uint8_t *data)
{
	uint8_t bus_data = 0b1000000;
	
	bus_data |= Addr*8;
	BusLinesState(&bus_data, 0);
	
	for (uint8_t i = 0; i < 8; i++)
	{
		BusLinesState(data, 1);
		data++;
	}
}

void LCD_Show(uint8_t Addr, uint8_t Str, uint8_t Cursor)
{
	uint8_t x = 0;
	
	if (Str == 0)
	{
		x=FirstStr_StartPosition_DDRAM_Addr+Cursor;
		
		BusLinesState(&x, 0);
		BusLinesState(&Addr, 1);
	}
	else
	if (Str == 1)
	{
		x=SecondStr_StartPosition_DDRAM_Addr+Cursor;
		
		BusLinesState(&x, 0);
		BusLinesState(&Addr, 1);
	}
}

void LCD_String(char str1[], uint8_t y, uint8_t x)
{
	uint8_t n;
	for(n = 0; str1[n] != '\0'; n++)
	LCD_Show(str1[n], y, n + x);
}

void drawBigDigits(uint8_t digit, uint8_t place)
{

	switch (digit) {
		case 0:
		LCD_Show(0, 0, place);
		LCD_Show(1, 0, place + 1);
		LCD_Show(2, 0, place + 2);
		LCD_Show(3, 1, place);
		LCD_Show(4, 1, place + 1);
		LCD_Show(5, 1, place + 2);
		break;
		
		case 1:
		LCD_Show(1, 0, place);
		LCD_Show(2, 0, place + 1);
		LCD_String(" ", 0, place + 2);
		LCD_Show(4, 1, place);
		LCD_Show(7, 1, place + 1);
		LCD_Show(4, 1, place + 2);
		break;
		
		case 2:
		LCD_Show(6, 0, place);
		LCD_Show(6, 0, place + 1);
		LCD_Show(2, 0, place + 2);
		LCD_Show(3, 1, place);
		LCD_Show(4, 1, place + 1);
		LCD_Show(4, 1, place + 2);
		break;
		
		case 3:
		LCD_Show(6, 0, place);
		LCD_Show(6, 0, place + 1);
		LCD_Show(2, 0, place + 2);
		LCD_Show(4, 1, place);
		LCD_Show(4, 1, place + 1);
		LCD_Show(5, 1, place + 2);
		break;
		
		case 4:
		LCD_Show(3, 0, place);
		LCD_Show(4, 0, place + 1);
		LCD_Show(7, 0, place + 2);
		LCD_String(" ", 1, place);
		LCD_String(" ", 1, place + 1);
		LCD_Show(7, 1, place + 2);
		break;
		
		case 5:
		LCD_Show(3, 0, place);
		LCD_Show(6, 0, place + 1);
		LCD_Show(6, 0, place + 2);
		LCD_Show(4, 1, place);
		LCD_Show(4, 1, place + 1);
		LCD_Show(5, 1, place + 2);
		break;
		
		case 6:
		LCD_Show(0, 0, place);
		LCD_Show(6, 0, place + 1);
		LCD_Show(6, 0, place + 2);
		LCD_Show(3, 1, place);
		LCD_Show(4, 1, place + 1);
		LCD_Show(5, 1, place + 2);
		break;
		
		case 7:
		LCD_Show(1, 0, place);
		LCD_Show(1, 0, place + 1);
		LCD_Show(2, 0, place + 2);
		LCD_String(" ", 1, place);
		LCD_String(" ", 1, place + 2);
		LCD_Show(7, 1, place + 2);
		break;
		
		case 8:
		LCD_Show(0, 0, place);
		LCD_Show(6, 0, place + 1);
		LCD_Show(2, 0, place + 2);
		LCD_Show(3, 1, place);
		LCD_Show(4, 1, place + 1);
		LCD_Show(5, 1, place + 2);
		break;
		
		case 9:
		LCD_Show(0, 0, place);
		LCD_Show(6, 0, place + 1);
		LCD_Show(2, 0, place + 2);
		LCD_Show(4, 1, place);
		LCD_Show(4, 1, place + 1);
		LCD_Show(5, 1, place + 2);
		break;
	}
}
