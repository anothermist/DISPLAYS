/*
 * delay.h
 *
 *  Created on: 07-Aug-2019
 *      Author: arunr
 */

#ifndef DELAY_H_
#define DELAY_H_

#include "stdint.h"

void delay_init ();

void delay_us (uint16_t delay);

void delay_ms(uint16_t delay);


#endif /* DELAY_H_ */
