#include "twi.h"

void TWI_Init (void) {
	TWBR=0x02; // TWBR = 0x20; // 100 khz at 8 mhz | TWBR=0x02 // 400 khz at 8 mhz | 8000000/(16+2*2)
	TWSR = (0<<TWPS1)|(0<<TWPS0);
}

void TWI_StartCondition(void) {
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
}

void TWI_StopCondition(void) {
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

void TWI_SendByte(unsigned char c) {
	TWDR = c;
	TWCR = (1<<TWINT)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
}

void TWI_SendByteByADDR(unsigned char c,unsigned char addr) {
	TWI_StartCondition();
	TWI_SendByte(addr);
	TWI_SendByte(c);
	TWI_StopCondition();
}

unsigned char TWI_ReadByte(void) {
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while (!(TWCR & (1<<TWINT)));
	return TWDR;
}

unsigned char TWI_ReadLastByte(void) {
	TWCR = (1<<TWINT)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
	return TWDR;
}
