#ifndef TWI_H_
#define TWI_H_

#include "main.h"

void TWI_Init(void);
void TWI_Start(void);
void TWI_Stop(void);
void TWI_SendByte(uint8_t data);
void TWI_SendAddress(uint8_t addr);

#endif
