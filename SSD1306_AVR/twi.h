#ifndef TWI_H_
#define TWI_H_

#include "main.h"

void TWI_Init(void);
void TWI_Start(void);
void TWI_Stop(void);
void TWI_SendByte(int data);
void TWI_SendAddress(int addr);

#endif
