#include "ssd1306.h"

unsigned char LCD_X, LCD_Y;

static uint8_t SSD1306_Buffer[(LCD_WIDTH + 1) * LCD_HEIGHT / 8];

typedef struct {
	uint16_t CurrentX;
	uint16_t CurrentY;
	uint8_t Inverted;
	uint8_t Initialized;
} SSD1306_t;

static SSD1306_t SSD1306;

inline static void TWI_Command(unsigned char ControByte, unsigned char DataByte)
{
	TWI_Start();
	TWI_SendAddress(SSD1306_TWI_ADDRESS);
	TWI_SendByte(ControByte);
	TWI_SendByte(DataByte);
	TWI_Stop();
}

inline static void TWI_WriteMulti(uint8_t address, uint8_t reg, uint8_t* data, uint16_t count)
{
	uint8_t dt[count + 1];
	dt[0] = reg;
	uint8_t i;
	for(i = 1; i <= count; i++)
	{
		dt[i] = data[i-1];
		TWI_Command(reg, dt[i]);
	}
}

inline static void LCD_Goto(unsigned char x, unsigned char y)
{
	LCD_X = x;
	LCD_Y = y;
	TWI_Command(COMAND, 0xB0 + y);
	TWI_Command(COMAND, x & 0xf);
	TWI_Command(COMAND,0x10 | (x >> 4));
}

inline static void LCD_Goto2X(unsigned char x, unsigned char y)
{
	LCD_X = x;
	LCD_Y = y;
	TWI_Command(COMAND, 0xB0 + y);
	TWI_Command(COMAND, 2*x & 0xf);
	TWI_Command(COMAND, 0x10 | (2*x >> 4));
}

void SSD1306_Init(void)
{
	_delay_ms(100);
	TWI_Command(0x00, SSD1306_DISPLAYOFF);
	TWI_Command(0x00, SSD1306_SETDISPLAYCLOCKDIV);
	TWI_Command(0x00, 0x80);
	TWI_Command(0x00, SSD1306_SETMULTIPLEX);
	if (LCD_HEIGHT == 32) { TWI_Command(0x00, 0x1F); }
	else { TWI_Command(0x00, 0x3F); }
	TWI_Command(0x00, SSD1306_SETDISPLAYOFFSET);
	TWI_Command(0x00, 0x00);
	TWI_Command(0x00, SSD1306_SETSTARTLINE | 0x00);
	TWI_Command(0x00, SSD1306_CHARGEPUMP);
	TWI_Command(0x00, 0x14);
	TWI_Command(0x00, SSD1306_MEMORYMODE);
	TWI_Command(0x00, 0x00);
	TWI_Command(0x00, SSD1306_SEGREMAP | 0x1);
	TWI_Command(0x00, SSD1306_COMSCANDEC);
	TWI_Command(0x00, SSD1306_SETCOMPINS);
	if (LCD_HEIGHT == 32) { TWI_Command(0x00, 0x02); }
	else { TWI_Command(0x00, 0x12); }
	TWI_Command(0x00, SSD1306_SETCONTRAST);
	TWI_Command(0x00, 0xCF);
	TWI_Command(0x00, SSD1306_SETPRECHARGE);
	TWI_Command(0x00, 0xF1);
	TWI_Command(0x00, SSD1306_SETVCOMDETECT);
	TWI_Command(0x00, 0x40);
	TWI_Command(0x00, SSD1306_DISPLAYALLON_RESUME);
	TWI_Command(0x00, SSD1306_DISPLAYON);
	
	LCD_Fill(SSD1306_COLOR_BLACK);
	LCD_UpdateScreen();

	SSD1306.CurrentX = 0;
	SSD1306.CurrentY = 0;
	SSD1306.Initialized = 1;
}

void LCD_Contrast(char set_contrast)
{
	TWI_Command(COMAND, SSD1306_DISPLAYOFF);
	_delay_ms(10);
	TWI_Command(COMAND, SSD1306_SETCONTRAST);
	TWI_Command(COMAND, set_contrast);
	TWI_Command(COMAND, SSD1306_DISPLAYON);
}

void LCD_ON(void)
{
	TWI_Command(0x00, 0x8D);
	TWI_Command(0x00, 0x14);
	TWI_Command(0x00, 0xAF);
}

void LCD_OFF(void)
{
	TWI_Command(0x00, 0x8D);
	TWI_Command(0x00, 0x10);
	TWI_Command(0x00, 0xAE);
}

void LCD_UpdateScreen(void)
{
	uint8_t m;
	for (m = 0; m < 8; m++)
	{
		TWI_Command(0x00, 0xB0 + m);
		TWI_Command(0x00, 0x00);
		TWI_Command(0x00, 0x10);
		TWI_WriteMulti(SSD1306_TWI_ADDRESS, 0x40, &SSD1306_Buffer[(LCD_WIDTH + 1) * m], (LCD_WIDTH + 1));
	}
}

void LCD_Mode(char set_mode)
{
	if (set_mode == 0) { TWI_Command(COMAND, SSD1306_NORMALDISPLAY); }
	if (set_mode == 1) { TWI_Command(COMAND, SSD1306_INVERTDISPLAY); }
}

void LCD_Sleep(char set)
{
	if (set == 0) { TWI_Command(COMAND, SSD1306_DISPLAYOFF ); }
	if (set == 1) { TWI_Command(COMAND, SSD1306_DISPLAYON); }
}

void LCD_ToggleInvert(void)
{
	uint16_t i;
	
	SSD1306.Inverted = !SSD1306.Inverted;
	for (i = 0; i < sizeof(SSD1306_Buffer); i++) SSD1306_Buffer[i] = ~SSD1306_Buffer[i];
}

void LCD_Fill(SSD1306_COLOR_t color)
{
	memset(SSD1306_Buffer, (color == SSD1306_COLOR_BLACK) ? 0x00 : 0xFF, sizeof(SSD1306_Buffer));
}

void LCD_Pixel(uint16_t x, uint16_t y, SSD1306_COLOR_t color)
{
	if (x >= (LCD_WIDTH + 1) || y >= LCD_HEIGHT) return;
	if (SSD1306.Inverted) color = (SSD1306_COLOR_t)!color;
	if (color == SSD1306_COLOR_WHITE) SSD1306_Buffer[x + (y / 8) * (LCD_WIDTH + 1)] |= 1 << (y % 8);
	else SSD1306_Buffer[x + (y / 8) * (LCD_WIDTH + 1)] &= ~(1 << (y % 8));
}

void LCD_Line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, SSD1306_COLOR_t color)
{
	int16_t dx, dy, sx, sy, err, e2, i, tmp;

	if (x0 >= (LCD_WIDTH + 1)) x0 = (LCD_WIDTH + 1) - 1;
	if (x1 >= (LCD_WIDTH + 1)) x1 = (LCD_WIDTH + 1) - 1;
	if (y0 >= LCD_HEIGHT) y0 = LCD_HEIGHT - 1;
	if (y1 >= LCD_HEIGHT) y1 = LCD_HEIGHT - 1;
	
	dx = (x0 < x1) ? (x1 - x0) : (x0 - x1);
	dy = (y0 < y1) ? (y1 - y0) : (y0 - y1);
	sx = (x0 < x1) ? 1 : -1;
	sy = (y0 < y1) ? 1 : -1;
	err = ((dx > dy) ? dx : -dy) / 2;

	if (dx == 0)
	{
		if (y1 < y0)
		{
			tmp = y1;
			y1 = y0;
			y0 = tmp;
		}
		
		if (x1 < x0)
		{
			tmp = x1;
			x1 = x0;
			x0 = tmp;
		}

		for (i = y0; i <= y1; i++) LCD_Pixel(x0, i, color);
		return;
	}
	
	if (dy == 0)
	{
		if (y1 < y0)
		{
			tmp = y1;
			y1 = y0;
			y0 = tmp;
		}
		
		if (x1 < x0)
		{
			tmp = x1;
			x1 = x0;
			x0 = tmp;
		}
		
		for (i = x0; i <= x1; i++) LCD_Pixel(i, y0, color);
		return;
	}
	
	while (1)
	{
		LCD_Pixel(x0, y0, color);
		if (x0 == x1 && y0 == y1) break;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void LCD_Rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, SSD1306_COLOR_t color)
{
	if (x >= (LCD_WIDTH + 1) || y >= LCD_HEIGHT) return;
	if ((x + w) >= (LCD_WIDTH + 1)) w = (LCD_WIDTH + 1) - x;
	if ((y + h) >= LCD_HEIGHT) h = LCD_HEIGHT - y;
	
	LCD_Line(x, y, x + w, y, color);         /* Top line */
	LCD_Line(x, y + h, x + w, y + h, color); /* Bottom line */
	LCD_Line(x, y, x, y + h, color);         /* Left line */
	LCD_Line(x + w, y, x + w, y + h, color); /* Right line */
}

void LCD_Rect_Fill(uint16_t x, uint16_t y, uint16_t w, uint16_t h, SSD1306_COLOR_t color)
{
	uint8_t i;
	if (x >= (LCD_WIDTH + 1) || y >= LCD_HEIGHT) return;
	if ((x + w) >= (LCD_WIDTH + 1)) w = (LCD_WIDTH + 1) - x;
	if ((y + h) >= LCD_HEIGHT) h = LCD_HEIGHT - y;
	for (i = 0; i <= h; i++) LCD_Line(x, y + i, x + w, y + i, color);
}

void LCD_Triangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, SSD1306_COLOR_t color)
{
	LCD_Line(x1, y1, x2, y2, color);
	LCD_Line(x2, y2, x3, y3, color);
	LCD_Line(x3, y3, x1, y1, color);
}

#define ABS(x) ((x) > 0 ? (x) : -(x))

void LCD_Triangle_Fill(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, SSD1306_COLOR_t color)
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
		LCD_Line(x, y, x3, y3, color);

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

void LCD_Ellipse(int16_t x0, int16_t y0, int16_t rx, int16_t ry, uint8_t fill, SSD1306_COLOR_t color)
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
			LCD_Line(x0 - x, y0 - y, x0 + x, y0 - y, color);
			LCD_Line(x0 - x, y0 + y, x0 + x, y0 + y, color);
			if (s >= 0)
			{
				s += fx2 * (1 - y);
				y--;
			}
			s += ry2 * ((4 * x) + 6);
		}
		for (x = rx, y = 0, s = 2 * rx2 + ry2 * (1-2 * rx); rx2 * y <= ry2 * x; y++)
		{
			LCD_Line(x0 - x, y0 - y, x0 + x, y0 - y, color);
			LCD_Line(x0 - x, y0 + y, x0 + x, y0 + y, color);
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
			LCD_Pixel(x0 + x, y0 + y, color);
			LCD_Pixel(x0 - x, y0 + y, color);
			LCD_Pixel(x0 + x, y0 - y, color);
			LCD_Pixel(x0 - x, y0 - y, color);
			if (s >= 0)
			{
				s += fx2 * (1 - y);
				y--;
			}
			s += ry2 * ((4 * x) + 6);
		}
		for (x = rx, y = 0, s = 2 * rx2 + ry2 * (1 - 2 * rx); rx2 * y <= ry2 * x; y++)
		{
			LCD_Pixel(x0 + x, y0 + y, color);
			LCD_Pixel(x0 - x, y0 + y, color);
			LCD_Pixel(x0 + x, y0 - y, color);
			LCD_Pixel(x0 - x, y0 - y, color);
			if (s >= 0)
			{
				s += fy2 * (1 - x);
				x--;
			}
			s += rx2 * ((4 * y) + 6);
		}
	}
}

void LCD_Circle(uint16_t x, uint16_t y, uint8_t radius, uint8_t fill, uint8_t size, SSD1306_COLOR_t color)
{
	int a_, b_, P;
	a_ = 0;
	b_ = radius;
	P = 1 - radius;
	while (a_ <= b_)
	{
		if (fill == 1)
		{
			LCD_Rect_Fill(x - a_, y - b_, 2 * a_ + 1, 2 * b_ + 1, color);
			LCD_Rect_Fill(x - b_, y - a_, 2 * b_ + 1, 2 * a_ + 1, color);
		}
		else
		{
			LCD_Rect_Fill(a_ + x, b_ + y, size, size, color);
			LCD_Rect_Fill(b_ + x, a_ + y, size, size, color);
			LCD_Rect_Fill(x - a_, b_ + y, size, size, color);
			LCD_Rect_Fill(x - b_, a_ + y, size, size, color);
			LCD_Rect_Fill(b_ + x, y - a_, size, size, color);
			LCD_Rect_Fill(a_ + x, y - b_, size, size, color);
			LCD_Rect_Fill(x - a_, y - b_, size, size, color);
			LCD_Rect_Fill(x - b_, y - a_, size, size, color);
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

void LCD_Circle_Helper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint8_t size, SSD1306_COLOR_t color)
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
			LCD_Pixel(x0 + x, y0 + y, color);
			LCD_Pixel(x0 + y, y0 + x, color);
		}
		if (cornername & 0x2) {
			LCD_Pixel(x0 + x, y0 - y, color);
			LCD_Pixel(x0 + y, y0 - x, color);
		}
		if (cornername & 0x8) {
			LCD_Pixel(x0 - y, y0 + x, color);
			LCD_Pixel(x0 - x, y0 + y, color);
		}
		if (cornername & 0x1) {
			LCD_Pixel(x0 - y, y0 - x, color);
			LCD_Pixel(x0 - x, y0 - y, color);
		}
	}
}

void LCD_Rect_Round(uint16_t x, uint16_t y, uint16_t length, uint16_t width, uint16_t r, SSD1306_COLOR_t color)
{
	LCD_Line(x + r, y, x + length + 1 - r, y, color);
	LCD_Line(x + r, y + width - 1, x + length + 1 - r, y + width - 1, color);
	LCD_Line(x, y + r, x, y + width - 1 - r, color);
	LCD_Line(x + length - 1, y + r, x + length - 1, y + width - 1 - r, color);

	LCD_Circle_Helper(x + r, y + r, r, 1, 1, color);
	LCD_Circle_Helper(x + length - r - 1, y + r, r, 2, 1, color);
	LCD_Circle_Helper(x + length - r - 1, y + width - r - 1, r, 4, 1, color);
	LCD_Circle_Helper(x + r, y + width - r - 1, r, 8, 1, color);
}

void LCD_Circle_Fill_Helper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, SSD1306_COLOR_t color)
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
			LCD_Line(x0 + x, y0 - y, x0 + x, y0 - y + 2 * y + delta, color);
			LCD_Line(x0 + y, y0 - x, x0 + y, y0 - x + 2 * x + delta, color);
		}
		if (cornername & 0x2) {
			LCD_Line(x0 - x, y0 - y, x0 - x, y0 - y + 2 * y + delta, color);
			LCD_Line(x0 - y, y0 - x, x0 - y, y0 - x + 2 * x + delta, color);
		}
	}
}

void LCD_Rect_Round_Fill(uint16_t x, uint16_t y, uint16_t length, uint16_t width, uint16_t r, uint32_t color)
{
	LCD_Rect_Fill(x + r, y, length - 2 * r, width, color);
	LCD_Circle_Fill_Helper(x + length - r - 1, y + r, r, 1, width - 2 * r - 1, color);
	LCD_Circle_Fill_Helper(x + r, y + r, r, 2, width - 2 * r - 1, color);
}

void LCD_Char(int16_t x, int16_t y, const GFXglyph *glyph, const GFXfont *font, uint8_t size, SSD1306_COLOR_t color)
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
				LCD_Rect_Fill(x + (glyph -> xOffset + cur_x - set_pixels) * size, y + (glyph -> yOffset + cur_y) * size, size * set_pixels, size, color);
				set_pixels = 0;
			}
			bit >>= 1;
		}
		if (set_pixels > 0)
		{
			LCD_Rect_Fill(x + (glyph -> xOffset + cur_x-set_pixels) * size, y + (glyph -> yOffset + cur_y) * size, size * set_pixels, size, color);
			set_pixels = 0;
		}
	}
}

void LCD_Font(uint16_t x, uint16_t y, char *text, const GFXfont *p_font, uint8_t size, SSD1306_COLOR_t color)
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
			LCD_Char(cursor_x, cursor_y, &glyph, &font, size, color);
			cursor_x += glyph.xAdvance * size;
		}
	}
}

void LCD_Battery(unsigned char y, unsigned char x, unsigned char z)
{
	unsigned char i = 0;

	LCD_Goto2X(x-1, y);
	TWI_Command(DATA, 0xFF); TWI_Command(DATA, 0xFF);
	LCD_Goto2X(x + 2, y);
	for (i = 0; i < 14; i++)
	{
		if(i < 11)
		{
			if(z >= i) { TWI_Command(DATA, 0xBD); }
			else { TWI_Command(DATA, 0x81); TWI_Command(DATA, 0x81); }
		}
		if (i == 11) { TWI_Command(DATA, 0xFF); TWI_Command(DATA, 0xFF); }
		if (i == 12) { TWI_Command(DATA, 0x3C); TWI_Command(DATA, 0x3C); }
		if (i == 13) { TWI_Command(DATA, 0x3C); TWI_Command(DATA, 0x3C); }
		LCD_Goto2X(x + i, y);
	}
}
