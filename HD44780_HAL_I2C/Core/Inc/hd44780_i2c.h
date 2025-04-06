#ifndef HD44780_I2C_H_
#define HD44780_I2C_H_

#include "stm32f1xx_hal.h"
#include "stdbool.h"
#include "main.h"

#define HD44780_INTERFACE hi2c1
#define HD44780_ADDRESS 0x4E

/* List of COMMANDS */
#define LCD_CLEARDISPLAY      0x01
#define LCD_RETURNHOME        0x02
#define LCD_ENTRYMODESET      0x04
#define LCD_DISPLAYCONTROL    0x08
#define LCD_CURSORSHIFT       0x10
#define LCD_FUNCTIONSET       0x20
#define LCD_SETCGRAMADDR      0x40
#define LCD_SETDDRAMADDR      0x80

//1) Entry mode Bitfields
#define LCD_ENTRY_SH          0x01
#define LCD_ENTRY_ID          0x02
//2) Entry mode Bitfields
#define LCD_ENTRY_SH          0x01
#define LCD_ENTRY_ID          0x02
//3) Display control
#define LCD_DISPLAY_B         0x01
#define LCD_DISPLAY_C         0x02
#define LCD_DISPLAY_D         0x04
//4) Shift control
#define LCD_SHIFT_RL          0x04
#define LCD_SHIFT_SC          0x08
//5) Function set control
#define LCD_FUNCTION_F        0x04
#define LCD_FUNCTION_N        0x08
#define LCD_FUNCTION_DL       0x10

void HD44780_init_i2c(void);
void HD44780_setCursor(uint8_t row, uint8_t col);
void HD44780_1stLine(void);
void HD44780_2ndLine(void);
void HD44780_twoLines(void);
void HD44780_oneLine(void);
void HD44780_cursorShow(bool state);
void HD44780_clear(void);
void HD44780_display(bool state);
void HD44780_shiftRight(uint8_t offset);
void HD44780_shiftLeft(uint8_t offset);
void HD44780_printf(const char *str, ...);
void HD44780_PutSpecialSymbols(void);
void HD44780_drawBigDigits(unsigned char digit, unsigned char place);

#endif /* HD44780_I2C_H_ */
