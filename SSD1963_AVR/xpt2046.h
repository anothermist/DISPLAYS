#ifndef _XPT2046_H_
#define _XPT2046_H_

#include "main.h"

#define	XPT2046_MIRROR_X 	0
#define	XPT2046_MIRROR_Y 	1

#define	XPT2046_ADDR_I 	0x80
//#define	XPT2046_ADDR_X 	0xD0
//#define	XPT2046_ADDR_Y 	0x90

#define	XPT2046_ADDR_X 	0x90
#define	XPT2046_ADDR_Y 	0xD0

#define RAW_MIN_X	650
#define RAW_MAX_X	3100
#define OUT_MIN_X	0
#define OUT_MAX_X	479

#define RAW_MIN_Y	550
#define RAW_MAX_Y	3400
#define OUT_MIN_Y	0
#define OUT_MAX_Y	799

#define XPT2046_SPI_DDR DDRB
#define XPT2046_SPI_PORT PORTB

#define XPT2046_CLK_PIN	PB7
#define XPT2046_MISO_PIN PB6
#define XPT2046_MOSI_PIN PB5

#define XPT2046_CS_PIN PB4
#define XPT2046_CS_DDR DDRB
#define XPT2046_CS_PORT PORTB

#define XPT2046_IRQ_PIN PB2
#define XPT2046_IRQ_DDR DDRB
#define XPT2046_IRQ_PORT PORTB

#define XPT2046_CS_S XPT2046_CS_PORT |= (1 << XPT2046_CS_PIN);
#define XPT2046_CS_U XPT2046_CS_PORT &= ~(1 << XPT2046_CS_PIN);

void XPT2046_Init(void);

uint16_t getRaw(uint8_t address);
uint16_t getX(void);
uint16_t getY(void);

#endif /* _XPT2046_H_ */
