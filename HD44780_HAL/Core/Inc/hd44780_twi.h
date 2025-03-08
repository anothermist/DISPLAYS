#ifndef HD44780_TWI_H_
#define HD44780_TWI_H_

#include "stm32f1xx_hal.h"

#define HD44780_INTERFACE hi2c1
#define HD44780_ADDRESS 0x4E

void HD44780_Init(void);   // initialize lcd
void HD44780_Command(char cmd);  // send command to the lcd
void HD44780_Data(char data);  // send data to the lcd
void HD44780_String(char *str);  // send string to the lcd
void HD44780_Position(int row, int col); // put cursor at the entered position row (0 or 1), col (0-15);
void HD44780_Clear(void);

#endif /* HD44780_TWI_H_ */
