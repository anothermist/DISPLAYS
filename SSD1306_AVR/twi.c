#include "twi.h"

void TWI_Init(void)
{
	TWBR = (((F_CPU)/(F_SCL)-16)/2);
	TWSR = 0;
}

void TWI_Start(void){
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT))){};
}

void TWI_Stop(void){
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

void TWI_SendByte(int data){
	TWDR = data;
	TWCR = (1<<TWINT)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT))){};
}

void TWI_SendAddress(int addr) {
	TWDR = (addr<<1)|0;
	TWCR = (1<<TWINT)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT))){};
}
