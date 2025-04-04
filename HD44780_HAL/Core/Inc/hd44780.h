#ifndef HD44780_H_
#define HD44780_H_

#include <stdbool.h>
#include "main.h"

/* List of COMMANDS */
#define LCD_CLEARDISPLAY      0x01
#define LCD_RETURNHOME        0x02
#define LCD_ENTRYMODESET      0x04
#define LCD_DISPLAYCONTROL    0x08
#define LCD_CURSORSHIFT       0x10
#define LCD_FUNCTIONSET       0x20
#define LCD_SETCGRAMADDR      0x40
#define LCD_SETDDRAMADDR      0x80

/* List of commands Bitfields */
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

//Floating point linker flag: -u _printf_float

/**
 * @brief Initialise LCD on 8-bits mode
 * @param[in] *port_rs_e RS and EN GPIO Port (e.g. GPIOB)
 * @param[in] *port_0_3 D0 to D3 GPIO Port
 * @param[in] *port_4_7 D4 to D7 GPIO Port
 * @param[in] x_pin GPIO pin (e.g. GPIO_PIN_1)
 */
void HD44780_init_8bits(GPIO_TypeDef *port_rs_e, uint16_t rs_pin,
		uint16_t e_pin, GPIO_TypeDef *port_0_3, uint16_t d0_pin,
		uint16_t d1_pin, uint16_t d2_pin, uint16_t d3_pin,
		GPIO_TypeDef *port_4_7, uint16_t d4_pin, uint16_t d5_pin,
		uint16_t d6_pin, uint16_t d7_pin);

/**
 * @brief Initialise LCD on 4-bits mode
 * @param[in] *port_4_7 D4 to D7 GPIO Port
 * @param[in] x_pin GPIO pin (e.g. GPIO_PIN_1)
 */
void HD44780_init_4bits(GPIO_TypeDef *port_rs_e, uint16_t rs_pin,
		uint16_t e_pin, GPIO_TypeDef *port_4_7, uint16_t d4_pin,
		uint16_t d5_pin, uint16_t d6_pin, uint16_t d7_pin);

/**
 * @brief Set cursor position
 * @param[in] row - 0 or 1 for line1 or line2
 * @param[in] col - 0 - 15 (16 columns LCD)
 */
void HD44780_setCursor(uint8_t row, uint8_t col);
/**
 * @brief Move to beginning of 1st line
 */
void HD44780_1stLine(void);
/**
 * @brief Move to beginning of 2nd line
 */
void HD44780_2ndLine(void);

/**
 * @brief Select LCD Number of lines mode
 */
void HD44780_twoLines(void);
void HD44780_oneLine(void);

/**
 * @brief Cursor ON/OFF
 */
void HD44780_cursorShow(bool state);

/**
 * @brief Display clear
 */
void HD44780_clear(void);

/**
 * @brief Display ON/OFF, to hide all characters, but not clear
 */
void HD44780_display(bool state);

/**
 * @brief Shift content to right
 */
void HD44780_shiftRight(uint8_t offset);

/**
 * @brief Shift content to left
 */
void HD44780_shiftLeft(uint8_t offset);

/**
 * @brief Print to display any datatype (e.g. HD44780_printf("Value1 = %.1f", 123.45))
 */
void HD44780_printf(const char *str, ...);


void HD44780_drawBigDigits(unsigned char digit, unsigned char place);

#endif /* HD44780_H_ */

