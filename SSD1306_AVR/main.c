#include "main.h"

unsigned int out=0;
float t=0;

char buff[40];


void main(void)
{
	
	PORTB=0x00;
	DDRB=0x00;
	
	PORTC=0x00;
	DDRC=0x00;
	
	PORTD=0x60;
	DDRD=0x00;
	
	TWI_Init();
	LCD_init();
	//      LCD_Clear();
	//	   LCD_Contrast(1);
	OLED_Test();
	_delay_ms(1000);
	OLED_Clear();



	while (1)
	{
	_delay_ms(500);

	LCD_Goto(0, 0);
	sprintf(buff,"X=%i ", out);
	LCD_Printf(buff, 1);

	LCD_Goto(0, 1);
	sprintf(buff, "SSD1306");
	LCD_Printf(buff, 0);

	//LCD_Goto(5, 2);
	//sprintf(buff, "%.1f:C",t);
	//LCD_Printf(buff, 2);

	LCD_Bat(0, 110, out);

	out++; t = t + 0.1;
	if (t > 9.9) { t = 0.1; }
	if (out > 10) { out = 0; }

	LCD_Goto(1, 6);
	sprintf(buff,"12345678910");
	LCD_Printf(buff, 1);

	LCD_Goto(0,7);
	sprintf(buff,"test 8");
	LCD_Printf(buff, 0);

	LCD_Goto(0, 7);
	sprintf(buff, "test 8");
	LCD_Printf(buff, 0);

	//LCD_Goto(5, 2);
	//LCD_Char("1");
		
	}
}
