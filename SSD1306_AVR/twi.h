#ifndef TWI_H_
#define TWI_H_

#include "main.h"

void twi_init(void);
void twi_start(void);
void twi_stop(void);
void twi_data_read(unsigned char addr, unsigned char reg, unsigned char *data, unsigned int len);
void twi_data_write(unsigned char addr, unsigned char reg, unsigned char *data, unsigned int len);
unsigned char twi_byte_read(void);
unsigned char twi_byte_read_last(void);
void twi_byte_send(unsigned char data);
void twi_addr_send(unsigned char addr);
void twi_byte_send_by_addr(unsigned char c,unsigned char addr);

#endif /* TWI_H_ */