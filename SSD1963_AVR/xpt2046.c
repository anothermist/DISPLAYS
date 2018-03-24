#include "xpt2046.h"

static inline float remap(float x, float in_min, float in_max, float out_min, float out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

uint8_t Spi_Master_Transmit(uint8_t out_data)
{
	SPDR = out_data;
	while(!(SPSR & (1 << SPIF)));
	return SPDR;
}

void XPT2046_Init(void)
{
	XPT2046_SPI_PORT |= (1 << XPT2046_CLK_PIN) | (1 << XPT2046_MISO_PIN) | (1 << XPT2046_MOSI_PIN);
	XPT2046_SPI_DDR  |= (1 << XPT2046_CLK_PIN) | (1 << XPT2046_MISO_PIN) | (1 << XPT2046_MOSI_PIN);
	XPT2046_CS_PORT |= (1 << XPT2046_CS_PIN);
	XPT2046_CS_DDR |= (1 << XPT2046_CS_PIN);
	XPT2046_IRQ_PORT |= (0 << XPT2046_IRQ_PIN);
	XPT2046_IRQ_DDR |= (0 << XPT2046_IRQ_PIN);
	SPCR |= (1 << SPE) | (1 << MSTR);
	SPSR |= (0 << SPI2X) | (1 << SPR1) | (1 << SPR0);
	XPT2046_CS_U
	Spi_Master_Transmit(XPT2046_ADDR_I);
	Spi_Master_Transmit(0x00);
	Spi_Master_Transmit(0x00);
	XPT2046_CS_S
}

uint16_t getRaw(uint8_t address)
{
	uint16_t LSB, MSB;
	XPT2046_CS_U
	_delay_ms(10);
	Spi_Master_Transmit(address);
	MSB = Spi_Master_Transmit(0x00);
	LSB = Spi_Master_Transmit(0x00);
	XPT2046_CS_S
	return ((MSB << 8) | (LSB)) >> 3;
}

static inline uint16_t X(void)
{
	uint16_t x;
	x = (uint16_t) remap(getRaw(XPT2046_ADDR_X), RAW_MIN_X, RAW_MAX_X, OUT_MIN_X, OUT_MAX_X);
	if (XPT2046_MIRROR_X) x = OUT_MAX_X - x;
	if (x > OUT_MIN_X && x < OUT_MAX_X) return x;
	else return 0;
}

static inline uint16_t Y(void)
{
	uint16_t y;
	y = (uint16_t) remap(getRaw(XPT2046_ADDR_Y), RAW_MIN_Y, RAW_MAX_Y, OUT_MIN_Y, OUT_MAX_Y);
	if (XPT2046_MIRROR_Y) y = OUT_MAX_Y - y;
	if (y > OUT_MIN_Y && y < OUT_MAX_Y) return y;
	else return 0;
}

uint16_t getX(void)
{
	if (XPT2046_ACCURACY)
	{
		uint16_t x[2] = { 1, 2 };
		while (x[0] != x[1])
		{
			if (XPT2046_REVERSED) { x[0] = Y(); x[1] = Y(); }
			else { x[0] = X(); x[1] = X(); }
		}
		return x[0];
	}
	else if (XPT2046_REVERSED) return Y(); else return X();
}

uint16_t getY(void)
{
	if (XPT2046_ACCURACY)
	{
		uint16_t y[2] = { 1, 2 };
		while (y[0] != y[1])
		{
			if (XPT2046_REVERSED) { y[0] = X(); y[1] = X(); }
			else { y[0] = Y(); y[1] = Y(); }
		}
		return y[0];
	}
	else if (XPT2046_REVERSED) return X(); else return Y();
}
