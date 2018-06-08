#include "st7735.h"

uint16_t RGB(uint8_t r, uint8_t g, uint8_t b)
{
	return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

inline static uint16_t H24_RGB565(uint8_t reverse, uint32_t color24)
{
	uint8_t b = (color24 >> 16) & 0xFF;
	uint8_t g = (color24 >> 8) & 0xFF;
	uint8_t r = color24 & 0xFF;
	if (reverse) return ((b / 8) << 11) | ((g / 4) << 5) | (r / 8);
	else return ((r / 8) << 11) | ((g / 4) << 5) | (b / 8);
}

inline static void LCD_Command(uint8_t cmd)
{
	LCD_U_CS
	LCD_U_DC
	SPDR = cmd;
	while(!(SPSR & (1 << SPIF)));
	LCD_S_CS
}

inline static void LCD_Data_8(uint8_t data)
{
	LCD_U_CS
	LCD_S_DC
	SPDR = data;
	while(!(SPSR & (1 << SPIF)));
	LCD_S_CS
}

inline static void LCD_Data_16(uint16_t word)
{
	LCD_U_CS
	LCD_S_DC
	SPDR = (word >> 8) & 0x00FF;
	while(!(SPSR & (1 << SPIF)));
	SPDR = word & 0x00FF;
	while(!(SPSR & (1 << SPIF)));
	LCD_S_CS
}

inline static void LCD_Window(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	LCD_Command(CASET);
	LCD_Data_16(y1);
	LCD_Data_16(y2);
	LCD_Command(RASET);
	LCD_Data_16(x1);
	LCD_Data_16(x2);
	LCD_Command(RAMWR);
}

void LCD_Pixel(uint16_t x, uint16_t y, uint32_t color24)
{
	LCD_Window(x, y, x, y);
	LCD_Data_16(H24_RGB565(0, color24));
}

void LCD_Rect_Fill(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint32_t color24)
{
	uint32_t i = 0;
	uint32_t j = (uint32_t) w * (uint32_t) h;
	LCD_Window(y, x, y + h - 1, x + w - 1);
	for (i = 0; i < j; i++) LCD_Data_16(H24_RGB565(0, color24));
}

void LCD_Line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t size, uint32_t color24)
{
	int deltaX = abs(x2 - x1);
	int deltaY = abs(y2 - y1);
	int signX = x1 < x2 ? 1 : -1;
	int signY = y1 < y2 ? 1 : -1;
	int error = deltaX - deltaY;
	int error2 = 0;
	for (;;)
	{
		LCD_Rect_Fill(x1, y1, size, size, color24);
		if (x1 == x2 && y1 == y2)
		break;
		error2 = error * 2;
		if (error2 > -deltaY)
		{
			error -= deltaY;
			x1 += signX;
		}
		if (error2 < deltaX)
		{
			error += deltaX;
			y1 += signY;
		}
	}
}

void LCD_Rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t size, uint32_t color24)
{
	LCD_Line(x, y, x + w, y, size, color24);
	LCD_Line(x, y + h, x + w, y + h, size, color24);
	LCD_Line(x, y, x, y + h, size, color24);
	LCD_Line(x + w, y, x + w, y + h, size, color24);
}

void LCD_Triangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint8_t size, uint32_t color24)
{
	LCD_Line(x1, y1, x2, y2, size, color24);
	LCD_Line(x2, y2, x3, y3, size, color24);
	LCD_Line(x3, y3, x1, y1, size, color24);
}

#define ABS(x) ((x) > 0 ? (x) : -(x))

void LCD_Triangle_Fill(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint32_t color24)
{
	int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0,
	yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0,
	curpixel = 0;
	
	deltax = ABS(x2 - x1);
	deltay = ABS(y2 - y1);
	x = x1;
	y = y1;

	if (x2 >= x1)
	{
		xinc1 = 1;
		xinc2 = 1;
	}
	else
	{
		xinc1 = -1;
		xinc2 = -1;
	}

	if (y2 >= y1)
	{
		yinc1 = 1;
		yinc2 = 1;
	}
	else
	{
		yinc1 = -1;
		yinc2 = -1;
	}

	if (deltax >= deltay)
	{
		xinc1 = 0;
		yinc2 = 0;
		den = deltax;
		num = deltax / 2;
		numadd = deltay;
		numpixels = deltax;
	}
	else
	{
		xinc2 = 0;
		yinc1 = 0;
		den = deltay;
		num = deltay / 2;
		numadd = deltax;
		numpixels = deltay;
	}

	for (curpixel = 0; curpixel <= numpixels; curpixel++)
	{
		LCD_Line(x, y, x3, y3, 1, color24);

		num += numadd;
		if (num >= den)
		{
			num -= den;
			x += xinc1;
			y += yinc1;
		}
		x += xinc2;
		y += yinc2;
	}
}

void LCD_Ellipse(int16_t x0, int16_t y0, int16_t rx, int16_t ry, uint8_t fill, uint8_t size, uint32_t color24)
{
	int16_t x, y;
	int32_t rx2 = rx * rx;
	int32_t ry2 = ry * ry;
	int32_t fx2 = 4 * rx2;
	int32_t fy2 = 4 * ry2;
	int32_t s;
	if (fill)
	{
		for (x = 0, y = ry, s = 2 * ry2 + rx2 * (1 - 2 * ry); ry2 * x <= rx2 * y; x++)
		{
			LCD_Line(x0 - x, y0 - y, x0 + x + 1 - size, y0 - y, size, color24);
			LCD_Line(x0 - x, y0 + y, x0 + x + 1 - size, y0 + y, size, color24);
			if (s >= 0)
			{
				s += fx2 * (1 - y);
				y--;
			}
			s += ry2 * ((4 * x) + 6);
		}
		for (x = rx, y = 0, s = 2 * rx2 + ry2 * (1-2 * rx); rx2 * y <= ry2 * x; y++)
		{
			LCD_Line(x0 - x, y0 - y, x0 + x + 1 - size, y0 - y, size, color24);
			LCD_Line(x0 - x, y0 + y, x0 + x + 1 - size, y0 + y, size, color24);
			if (s >= 0)
			{
				s += fy2 * (1 - x);
				x--;
			}
			s += rx2 * ((4 * y) + 6);
		}
	}
	else
	{
		for (x = 0, y = ry, s = 2 * ry2 + rx2 * (1 - 2 * ry); ry2 * x <= rx2 * y; x++)
		{
			LCD_Rect_Fill(x0 + x, y0 + y, size, size, color24);
			LCD_Rect_Fill(x0 - x, y0 + y, size, size, color24);
			LCD_Rect_Fill(x0 + x, y0 - y, size, size, color24);
			LCD_Rect_Fill(x0 - x, y0 - y, size, size, color24);
			if (s >= 0)
			{
				s += fx2 * (1 - y);
				y--;
			}
			s += ry2 * ((4 * x) + 6);
		}
		for (x = rx, y = 0, s = 2 * rx2 + ry2 * (1 - 2 * rx); rx2 * y <= ry2 * x; y++)
		{
			LCD_Rect_Fill(x0 + x, y0 + y, size, size, color24);
			LCD_Rect_Fill(x0 - x, y0 + y, size, size, color24);
			LCD_Rect_Fill(x0 + x, y0 - y, size, size, color24);
			LCD_Rect_Fill(x0 - x, y0 - y, size, size, color24);
			if (s >= 0)
			{
				s += fy2 * (1 - x);
				x--;
			}
			s += rx2 * ((4 * y) + 6);
		}
	}
}

void LCD_Circle(uint16_t x, uint16_t y, uint8_t radius, uint8_t fill, uint8_t size, uint32_t color24)
{
	int a_, b_, P;
	a_ = 0;
	b_ = radius;
	P = 1 - radius;
	while (a_ <= b_)
	{
		if (fill == 1)
		{
			LCD_Rect_Fill(x - a_, y - b_, 2 * a_ + 1, 2 * b_ + 1, color24);
			LCD_Rect_Fill(x - b_, y - a_, 2 * b_ + 1, 2 * a_ + 1, color24);
		}
		else
		{
			LCD_Rect_Fill(a_ + x, b_ + y, size, size, color24);
			LCD_Rect_Fill(b_ + x, a_ + y, size, size, color24);
			LCD_Rect_Fill(x - a_, b_ + y, size, size, color24);
			LCD_Rect_Fill(x - b_, a_ + y, size, size, color24);
			LCD_Rect_Fill(b_ + x, y - a_, size, size, color24);
			LCD_Rect_Fill(a_ + x, y - b_, size, size, color24);
			LCD_Rect_Fill(x - a_, y - b_, size, size, color24);
			LCD_Rect_Fill(x - b_, y - a_, size, size, color24);
		}
		if (P < 0)
		{
			P = (P + 3) + (2 * a_);
			a_++;
		}
		else
		{
			P = (P + 5) + (2 * (a_ - b_));
			a_++;
			b_--;
		}
	}
}

void LCD_Circle_Helper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint8_t size, uint32_t color24)
{
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

	while (x < y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;
		if (cornername & 0x4) {
			LCD_Rect_Fill(x0 + x, y0 + y, size, size, color24);
			LCD_Rect_Fill(x0 + y, y0 + x, size, size, color24);
		}
		if (cornername & 0x2) {
			LCD_Rect_Fill(x0 + x, y0 - y, size, size, color24);
			LCD_Rect_Fill(x0 + y, y0 - x, size, size, color24);
		}
		if (cornername & 0x8) {
			LCD_Rect_Fill(x0 - y, y0 + x, size, size, color24);
			LCD_Rect_Fill(x0 - x, y0 + y, size, size, color24);
		}
		if (cornername & 0x1) {
			LCD_Rect_Fill(x0 - y, y0 - x, size, size, color24);
			LCD_Rect_Fill(x0 - x, y0 - y, size, size, color24);
		}
	}
}

void LCD_Rect_Round(uint16_t x, uint16_t y, uint16_t length, uint16_t width, uint16_t r, uint8_t size, uint32_t color24)
{
	LCD_Line(x + r, y, x + length + size - r, y, size, color24);
	LCD_Line(x + r, y + width - 1, x + length + size - r, y + width - 1, size, color24);
	LCD_Line(x, y + r, x, y + width - size - r, size, color24);
	LCD_Line(x + length - 1, y + r, x + length - 1, y + width - size - r, size, color24);

	LCD_Circle_Helper(x + r, y + r, r, 1, size, color24);
	LCD_Circle_Helper(x + length - r - 1, y + r, r, 2, size, color24);
	LCD_Circle_Helper(x + length - r - 1, y + width - r - 1, r, 4, size, color24);
	LCD_Circle_Helper(x + r, y + width - r - 1, r, 8, size, color24);
}

void LCD_Circle_Fill_Helper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint32_t color24)
{
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

	while (x < y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;

		if (cornername & 0x1) {
			LCD_Line(x0 + x, y0 - y, x0 + x, y0 - y + 2 * y + delta, 1, color24);
			LCD_Line(x0 + y, y0 - x, x0 + y, y0 - x + 2 * x + delta, 1, color24);
		}
		if (cornername & 0x2) {
			LCD_Line(x0 - x, y0 - y, x0 - x, y0 - y + 2 * y + delta, 1, color24);
			LCD_Line(x0 - y, y0 - x, x0 - y, y0 - x + 2 * x + delta, 1, color24);
		}
	}
}

void LCD_Rect_Round_Fill(uint16_t x, uint16_t y, uint16_t length, uint16_t width, uint16_t r, uint32_t color24)
{
	LCD_Rect_Fill(x + r, y, length - 2 * r, width, color24);
	LCD_Circle_Fill_Helper(x + length - r - 1, y + r, r, 1, width - 2 * r - 1, color24);
	LCD_Circle_Fill_Helper(x + r, y + r, r, 2, width - 2 * r - 1, color24);
}

static void LCD_Char(int16_t x, int16_t y, const GFXglyph *glyph, const GFXfont *font, uint8_t size, uint32_t color24)
{
	uint8_t  *bitmap = font -> bitmap;
	uint16_t bo = glyph -> bitmapOffset;
	uint8_t bits = 0, bit = 0;
	uint16_t set_pixels = 0;
	uint8_t  cur_x, cur_y;
	for (cur_y = 0; cur_y < glyph -> height; cur_y++)
	{
		for (cur_x = 0; cur_x < glyph -> width; cur_x++)
		{
			if (bit == 0)
			{
				bits = pgm_read_byte(&bitmap[bo++]);
				bit  = 0x80;
			}
			if (bits & bit) set_pixels++;
			else if (set_pixels > 0)
			{
				LCD_Rect_Fill(x + (glyph -> xOffset + cur_x - set_pixels) * size, y + (glyph -> yOffset + cur_y) * size, size * set_pixels, size, color24);
				set_pixels = 0;
			}
			bit >>= 1;
		}
		if (set_pixels > 0)
		{
			LCD_Rect_Fill(x + (glyph -> xOffset + cur_x-set_pixels) * size, y + (glyph -> yOffset + cur_y) * size, size * set_pixels, size, color24);
			set_pixels = 0;
		}
	}
}

void LCD_Font(uint16_t x, uint16_t y, char *text, const GFXfont *p_font, uint8_t size, uint32_t color24)
{
	int16_t cursor_x = x;
	int16_t cursor_y = y;
	GFXfont font;
	memcpy_P(&font, p_font, sizeof(GFXfont));
	for (uint16_t text_pos = 0; text_pos < strlen(text); text_pos++)
	{
		char c = text[text_pos];
		if (c == '\n')
		{
			cursor_x = x;
			cursor_y += font.yAdvance * size;
		}
		else if (c >= font.first && c <= font.last && c != '\r')
		{
			GFXglyph glyph;
			memcpy_P(&glyph, &font.glyph[c - font.first], sizeof(GFXglyph));
			LCD_Char(cursor_x, cursor_y, &glyph, &font, size, color24);
			cursor_x += glyph.xAdvance * size;
		}
	}
}

void LCD_Bitmap(uint16_t x, uint16_t y, PGM_P bitmap)
{
	uint8_t w = pgm_read_word(bitmap);
	bitmap += 2;
	uint8_t h = pgm_read_word(bitmap);
	bitmap += 2;
	LCD_Window(x, y, x + w - 1, y + h - 1);
	for (uint16_t i = 0; i < h; i++)
	{
		for (uint16_t j = 0; j < w; j++)
		{
			uint16_t color = pgm_read_word(bitmap);
			LCD_Data_16(color);
			bitmap += 2;
		}
	}
}

void LCD_Bitmap_Mono(uint16_t x, uint16_t y, PGM_P bitmap, uint32_t color24_set, uint32_t color24_unset)
{
	uint8_t w = pgm_read_byte(bitmap++);
	uint8_t h = pgm_read_byte(bitmap++);
	LCD_Window(x, y, x + w - 1, y + h - 1);
	uint16_t bit_pos = 0;
	uint16_t byte = 0;
	for (uint16_t i = 0; i < h; i++)
	{
		for (uint16_t j = 0; j < w; j++)
		{
			if (bit_pos % 8 == 0) byte = pgm_read_byte(bitmap++);
			if (byte & (1 << (bit_pos % 8))) LCD_Data_16(H24_RGB565(0, color24_set));
			else LCD_Data_16(H24_RGB565(0, color24_unset));
			bit_pos++;
		}
	}
}

void LCD_SPI(void)
{
	LCD_PORT |= (1 << LCD_SCK) | (1 << LCD_MOSI) | (1 << LCD_CS) | (1 << LCD_DC);
	LCD_DDR  |= (1 << LCD_SCK) | (1 << LCD_MOSI) | (1 << LCD_CS) | (1 << LCD_DC);
	SPCR |= (1 << SPE) | (1 << MSTR);
	SPSR |= (1 << SPI2X) | (0 << SPR1) | (0 << SPR0);
}

void LCD_Reset(void)
{
	LCD_PORT |= (1 << LCD_RST);
	LCD_DDR  |= (1 << LCD_RST);
	LCD_U_CS
	LCD_S_RST
	_delay_ms(150);
	LCD_U_RST
	_delay_ms(150);
	LCD_S_RST
}

const uint8_t LCD_Blue_Init[] PROGMEM = // Initialization commands for 7735B screens
{	18,                       		// 18 commands in list:
	SWRESET, DELAY_FLAG,  	//  1: Software reset, no args, w/delay
	50,                     	//     50 ms delay
	SLPOUT, DELAY_FLAG,  	//  2: Out of sleep mode, no args, w/delay
	255,                    	//     255 = 500 ms delay
	COLMOD, 1 | DELAY_FLAG,  //  3: Set color mode, 1 arg + delay:
	0x05,                   	//     16-bit color
	10,                     	//     10 ms delay
	FRMCTR1, 3 | DELAY_FLAG, //  4: Frame rate control, 3 args + delay:
	0x00,                   	//     fastest refresh
	0x06,                   	//     6 lines front porch
	0x03,                   	//     3 lines back porch
	10,                     	//     10 ms delay
	MADCTL, 1,		  		//  5: Memory access ctrl (directions), 1 arg:
	0x08,                   	//     Row addr/col addr, bottom to top refresh
	DISSET5, 2,  			//  6: Display settings #5, 2 args, no delay:
	0x15,                   	//     1 clk cycle nonoverlap, 2 cycle gate
	//     rise, 3 cycle osc equalize
	0x02,                   	//     Fix on VTL
	INVCTR, 1,		  		//  7: Display inversion control, 1 arg:
	0x0,                    	//     Line inversion
	PWCTR1, 2 | DELAY_FLAG,  //  8: Power control, 2 args + delay:
	0x02,                   	//     GVDD = 4.7V
	0x70,                   	//     1.0uA
	10,                     	//     10 ms delay
	PWCTR2, 1,  				//  9: Power control, 1 arg, no delay:
	0x05,                   	//     VGH = 14.7V, VGL = -7.35V
	PWCTR3, 2,  				// 10: Power control, 2 args, no delay:
	0x01,                   	//     Opamp current small
	0x02,                   	//     Boost frequency
	VMCTR1, 2 | DELAY_FLAG,  // 11: Power control, 2 args + delay:
	0x3C,                   	//     VCOMH = 4V
	0x38,                   	//     VCOML = -1.1V
	10,                     	//     10 ms delay
	PWCTR6, 2,  				// 12: Power control, 2 args, no delay:
	0x11, 0x15,
	GMCTRP1, 16,  			// 13: Magical unicorn dust, 16 args, no delay:
	0x09, 0x16, 0x09, 0x20, 	//     (seriously though, not sure what
	0x21, 0x1B, 0x13, 0x19, 	//      these config values represent)
	0x17, 0x15, 0x1E, 0x2B,
	0x04, 0x05, 0x02, 0x0E,
	GMCTRN1, 16 | DELAY_FLAG,// 14: Sparkles and rainbows, 16 args + delay:
	0x0B, 0x14, 0x08, 0x1E, 	//     (ditto)
	0x22, 0x1D, 0x18, 0x1E,
	0x1B, 0x1A, 0x24, 0x2B,
	0x06, 0x06, 0x02, 0x0F,
	10,                     	//     10 ms delay
	CASET, 4,  				// 15: Column addr set, 4 args, no delay:
	0x00, 0x02,             	//     XSTART = 2
	0x00, 0x81,             	//     XEND = 129
	RASET, 4,  				// 16: Row addr set, 4 args, no delay:
	0x00, 0x02,             	//     XSTART = 1
	0x00, 0x81,             	//     XEND = 160
	NORON, DELAY_FLAG,  		// 17: Normal display on, no args, w/delay
	10,                     	//     10 ms delay
	DISPON, DELAY_FLAG,  	// 18: Main screen turn on, no args, w/delay
	255							//     255 = 500 ms delay
};

const uint8_t LCD_Red_Init_1[] PROGMEM = // Init for 7735R, part 1 (red or green tab)
{	15,                       	// 15 commands in list:
	SWRESET,	DELAY_FLAG, //  1: Software reset, 0 args, w/delay
	150,                    //     150 ms delay
	SLPOUT, DELAY_FLAG,  //  2: Out of sleep mode, 0 args, w/delay
	255,                    //     500 ms delay
	FRMCTR1, 3,  		//  3: Frame rate ctrl - normal mode, 3 args:
	0x01, 0x2C, 0x2D,       //     Rate = fosc/(1x2+40) * (LINE+2C+2D)
	FRMCTR2, 3,  		//  4: Frame rate control - idle mode, 3 args:
	0x01, 0x2C, 0x2D,      	//     Rate = fosc/(1x2+40) * (LINE+2C+2D)
	FRMCTR3, 6,  		//  5: Frame rate ctrl - partial mode, 6 args:
	0x01, 0x2C, 0x2D,       //     Dot inversion mode
	0x01, 0x2C, 0x2D,       //     Line inversion mode
	INVCTR, 1,  			//  6: Display inversion ctrl, 1 arg, no delay:
	0x07,                   //     No inversion
	PWCTR1, 3,  			//  7: Power control, 3 args, no delay:
	0xA2,
	0x02,                   //     -4.6V
	0x84,                   //     AUTO mode
	PWCTR2, 1,  			//  8: Power control, 1 arg, no delay:
	0xC5,                   //     VGH25 = 2.4C VGSEL = -10 VGH = 3 * AVDD
	PWCTR3, 2,  			//  9: Power control, 2 args, no delay:
	0x0A,                   //     Opamp current small
	0x00,                   //     Boost frequency
	PWCTR4, 2,  			// 10: Power control, 2 args, no delay:
	0x8A,                   //     BCLK/2, Opamp current small & Medium low
	0x2A,
	PWCTR5, 2,  			// 11: Power control, 2 args, no delay:
	0x8A, 0xEE,
	VMCTR1, 1,  			// 12: Power control, 1 arg, no delay:
	0x0E,
	INVOFF, 0,  			// 13: Don't invert display, no args, no delay
	MADCTL, 1,  			// 14: Memory access control (directions), 1 arg:
	0xC8,                   //     row addr/col addr, bottom to top refresh
	COLMOD, 1,  			// 15: set color mode, 1 arg, no delay:
	0x05					//     16-bit color
};

const uint8_t LCD_Red_Init_Green_2[] PROGMEM = // Init for 7735R, part 2 (green tab only)
{	2,                        	//  2 commands in list:
	CASET, 4,  			//  1: Column addr set, 4 args, no delay:
	0x00, 0x02,            	//     XSTART = 0
	0x00, 0x7F+0x02,        //     XEND = 127
	RASET, 4,  			//  2: Row addr set, 4 args, no delay:
	0x00, 0x01,             //     XSTART = 0
	0x00, 0x9F+0x01			//     XEND = 159
};

const uint8_t LCD_Red_Init_Red_2[] PROGMEM =  // Init for 7735R, part 2 (red tab only)
{	2,                 	//  2 commands in list:
	CASET, 4,  	//  1: Column addr set, 4 args, no delay:
	0x00, 0x00,     //     XSTART = 0
	0x00, 0x7F,     //     XEND = 127
	RASET, 4,  	//  2: Row addr set, 4 args, no delay:
	0x00, 0x00,     //     XSTART = 0
	0x00, 0x9F,     //     XEND = 159
};

const uint8_t LCD_Red_Init_Green_144_2[] PROGMEM = // Init for 7735R, part 2 (green 1.44 tab)
{	2,                    	//  2 commands in list:
	CASET, 4,  		//  1: Column addr set, 4 args, no delay:
	0x00, 0x00,         //     XSTART = 0
	0x00, 0x7F,         //     XEND = 127
	RASET, 4,  		//  2: Row addr set, 4 args, no delay:
	0x00, 0x00,         //     XSTART = 0
	0x00, 0x7F          //     XEND = 127
};

const uint8_t LCD_Red_Init_3[] PROGMEM = // Init for 7735R, part 3 (red or green tab)
{	4,                        		//  4 commands in list:
	GMCTRP1, 16, 			//  1: Magical unicorn dust, 16 args, no delay:
	0x02, 0x1c, 0x07, 0x12,
	0x37, 0x32, 0x29, 0x2d,
	0x29, 0x25, 0x2B, 0x39,
	0x00, 0x01, 0x03, 0x10,
	GMCTRN1, 16, 			//  2: Sparkles and rainbows, 16 args, no delay:
	0x03, 0x1d, 0x07, 0x06,
	0x2E, 0x2C, 0x29, 0x2D,
	0x2E, 0x2E, 0x37, 0x3F,
	0x00, 0x00, 0x02, 0x10,
	NORON, DELAY_FLAG, 		//  3: Normal display on, no args, w/delay
	10,                     	//     10 ms delay
	DISPON, DELAY_FLAG, 		//  4: Main screen turn on, no args w/delay
	100                  		//     100 ms delay
};


void LCD_Command_List(const uint8_t *addr)
{
	uint8_t  cmd_count, arg_count, has_delay;

	cmd_count = pgm_read_byte(addr++);   // Number of commands to follow
	for(uint8_t cmd_pos = 0; cmd_pos < cmd_count; cmd_pos++)
	{
		LCD_Command(pgm_read_byte(addr++)); 	// Read, send command
		arg_count  = pgm_read_byte(addr++);    		// Number of args to follow
		has_delay = arg_count & DELAY_FLAG;         // If set, delay follows args
		arg_count &= ~DELAY_FLAG;                  	// Number of args
		for(uint8_t arg_pos = 0; arg_pos < arg_count; arg_pos++)
		{ // For each argument...
			LCD_Data_8(pgm_read_byte(addr++));  		// Read, send argument
		}

		if(has_delay)
		{
			uint8_t ms;
			ms = pgm_read_byte(addr++); // Read post-command delay time (ms)
			if(ms == 255)
			{  // If 255, delay for 500 ms
				_delay_ms(500);
			} else
			{
				for(int i = 0; i < ms; i += 5)
				{
					_delay_ms(5);
				}
			}

		}
	}
}

void LCD_Orientation(uint8_t type, uint8_t orientation)
{
	LCD_Command(MADCTL);

	switch (orientation)
	{
		case 0:
		if(type == 3) LCD_Data_8(MADCTL_MX | MADCTL_MY | MADCTL_RGB);
		else LCD_Data_8(MADCTL_MX | MADCTL_MY | MADCTL_BGR);
		break;

		case 1:
		if(type == 3) LCD_Data_8(MADCTL_MY | MADCTL_MV | MADCTL_RGB);
		else LCD_Data_8(MADCTL_MY | MADCTL_MV | MADCTL_BGR);
		break;

		case 2:
		if (type == 3) LCD_Data_8(MADCTL_RGB);
		else LCD_Data_8(MADCTL_BGR);
		break;

		case 3:
		if (type == 3) LCD_Data_8(MADCTL_MX | MADCTL_MV | MADCTL_RGB);
		else LCD_Data_8(MADCTL_MX | MADCTL_MV | MADCTL_BGR);
		break;
	}
}

void LCD_Init(uint8_t type, uint8_t orientation)
{
	LCD_SPI();
	LCD_Reset();
	
	switch(type)
	{
		case 0:
		LCD_Command_List(LCD_Blue_Init);
		break;

		case 1:
		LCD_Command_List(LCD_Red_Init_1);
		LCD_Command_List(LCD_Red_Init_Green_2);
		LCD_Command_List(LCD_Red_Init_3);
		break;

		case 2:
		LCD_Command_List(LCD_Red_Init_1);
		LCD_Command_List(LCD_Red_Init_Red_2);
		LCD_Command_List(LCD_Red_Init_3);
		break;

		case 3:
		LCD_Command_List(LCD_Red_Init_1);
		LCD_Command_List(LCD_Red_Init_Red_2);
		LCD_Command_List(LCD_Red_Init_3);
		LCD_Command(MADCTL);
		LCD_Data_8(0xC0);
		break;
		
		case 4:
		LCD_Command_List(LCD_Red_Init_1);
		LCD_Command_List(LCD_Red_Init_Green_144_2);
		LCD_Command_List(LCD_Red_Init_3);
		break;
	}
	LCD_Command(DISPON);
	LCD_Orientation(type, orientation);
	LCD_Rect_Fill(1, 1, LCD_WIDTH, LCD_WIDTH, BLACK);
}
