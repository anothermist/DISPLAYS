#ifndef MAIN_H_
#define MAIN_H_


#define F_CPU 8000000UL
#define UART_BAUD 9600

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>


#include <string.h>
#include "hd44780.h"
#include "hd44780_twi.h"

#endif /* MAIN_H_ */
