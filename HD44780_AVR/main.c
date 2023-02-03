#include "main.h"

int main(void)
{
	DDRD = 0xFF; PORTD = 0x00;
	
	LCD_Init();
	LCD_DisplEnable_CursOnOffBlink(1, 0, 0);
	
	LCD_String("                ", 0, 0);
	LCD_String("                ", 1, 0);

	drawBigDigits(0, 0);
	drawBigDigits(1, 4);
	drawBigDigits(2, 9);
	drawBigDigits(3, 13);
	
	while (1)
	{
		LCD_String("+ ", 0, 7);
		LCD_String(" +", 1, 7);
		LCD_String("+", 1, 3);
		LCD_String("+", 0, 12);
		LCD_String(" ", 0, 3);
		LCD_String(" ", 1, 12);
		
		_delay_ms(1000);
		
		LCD_String(" +", 0, 7);
		LCD_String("+ ", 1, 7);
		LCD_String("+", 1, 3);
		LCD_String("+", 0, 12);
		LCD_String(" ", 0, 3);
		LCD_String(" ", 1, 12);
		
		_delay_ms(1000);
	}
}