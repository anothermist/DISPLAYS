#ifndef TWI_H_
#define TWI_H_

#include "main.h"

void TWI_Init (void);
void TWI_StartCondition(void);
void TWI_StopCondition(void);
void TWI_SendByte(unsigned char c);
void TWI_SendByteByADDR(unsigned char c,unsigned char addr);
unsigned char TWI_ReadByte(void);
unsigned char TWI_ReadLastByte(void);

#endif
