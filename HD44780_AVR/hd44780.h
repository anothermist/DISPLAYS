#ifndef HD44780_H_
#define HD44780_H_

#include "main.h"

#define Data_Length 0
#define uint8_t unsigned char
#define Sbit(reg,bit) (reg|=(1<<bit))
#define Cbit(reg,bit) (reg&=~(1<<bit))
#define CheckBit(reg,bit) (reg&(1<<bit))
#define FirstStr_StartPosition_DDRAM_Addr 0x80
#define SecondStr_StartPosition_DDRAM_Addr 0xC0

#define NumberOfLines 1
#define Font 1
#define PORT_Strob_Signal_RS PORTD
#define PIN_Strob_Signal_RS 2
#define PORT_Strob_Signal_E PORTD
#define PIN_Strob_Signal_E 3

#if Data_Length == 0
#define PORT_bus_4 PORTD
#define PIN_bus_4 4
#define PORT_bus_5 PORTD
#define PIN_bus_5 5
#define PORT_bus_6 PORTD
#define PIN_bus_6 6
#define PORT_bus_7 PORTD
#define PIN_bus_7 7

#elif Data_Length == 1
#define PORT_bus_0 PORTC
#define PIN_bus_0 0
#define PORT_bus_1 PORTC
#define PIN_bus_1 1
#define PORT_bus_2 PORTC
#define PIN_bus_2 2
#define PORT_bus_3 PORTC
#define PIN_bus_3 3
#define PORT_bus_4 PORTC
#define PIN_bus_4 4
#define PORT_bus_5 PORTC
#define PIN_bus_5 5
#define PORT_bus_6 PORTC
#define PIN_bus_6 6
#define PORT_bus_7 PORTC
#define PIN_bus_7 7
#endif

void LCD_Init(void);
void LCD_Full_Clean(void);
void LCD_CursorPosition_ToStart(void);
void LCD_AutoMovCurDispDirect(uint8_t I_D, uint8_t S);
void LCD_DisplEnable_CursOnOffBlink(uint8_t D, uint8_t C, uint8_t B);
void LCD_MovingCurDispDirection(uint8_t S_C, uint8_t R_L);
void LCD_Show(uint8_t Addr, uint8_t Str, uint8_t Cursor);
void LCD_UserSymbolsWrite(uint8_t Addr, uint8_t *data);
void BusLinesState(uint8_t *data, uint8_t RS);

void LCD_String (char str1[], uint8_t y, uint8_t x);
void drawBigDigits(uint8_t digit, uint8_t place);

#endif /* HD44780_H_ */
