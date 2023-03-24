#include "twi.h"

ISR(TWI_vect) { }

void twi_init(void) {
	sei();
	unsigned long gen_t = 0;
	gen_t = (((F_CPU/F_SCL) - 16) / 2) & 0xFF;
	TWBR = gen_t & 0xFF;
	TWCR = (1 << TWEN) | (1 << TWIE);
}

void twi_start(void) {
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT))) { };
}

void twi_stop(void) {
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN) | (1 << TWIE);
}

void twi_addr_write_ack(void) {
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWIE);
	while (!(TWCR & (1 << TWINT))) { };
}

void twi_data_write_ack(void) {
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWIE);
	while (!(TWCR & (1 << TWINT))) { };
}

void twi_addr_read_ack(void) {
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWIE);
	while (!(TWCR & (1 << TWINT))) { };
}

void twi_data_read_ack(unsigned char ack) {
	if (ack != 0) {
		TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWIE) | (1 << TWEA);
		while (!(TWCR & (1 << TWINT))) { };
	}
	else {
		TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWIE);
		while (!(TWCR & (1 << TWINT))) { };
	}
}

void twi_data_read(unsigned char addr, unsigned char reg, unsigned char *data, unsigned int len) {
	twi_start();
	TWDR = ((addr) << 1) | 0;
	twi_addr_write_ack();
	TWDR = reg;
	twi_data_write_ack();
	twi_start();
	TWDR = ((addr) << 1) | 1;
	twi_addr_read_ack();
	unsigned int i = 0;
	for (i = 0; i < (len - 1); i++) {
		twi_data_read_ack(1);
		data[i] = TWDR;
	}
	twi_data_read_ack(0);
	data[i] = TWDR;
	twi_stop();
}

void twi_data_write(unsigned char addr, unsigned char reg, unsigned char *data, unsigned int len) {
	twi_start();
	TWDR = ((addr) << 1) | 0;
	twi_addr_write_ack();
	TWDR = reg;
	twi_data_write_ack();
	
	for (unsigned int i = 0; i < len; i++) {
		TWDR = data[i];
		twi_data_write_ack();
	}
	twi_stop();
}

unsigned char twi_byte_read(void) {
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	while (!(TWCR & (1 << TWINT)));
	return TWDR;
}

unsigned char twi_byte_read_last(void) {
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
	return TWDR;
}

void twi_byte_send(unsigned char data) {
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT))) { };
}

void twi_addr_send(unsigned char addr) {
	TWDR = (addr << 1) | 0;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT))) { };
}

void twi_byte_send_by_addr(unsigned char b, unsigned char addr) {
	twi_start();
	twi_addr_send(addr);
	twi_byte_send(b);
	twi_stop();
}
