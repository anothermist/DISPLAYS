#include "ili9341.h"

uint16_t LCD_Width = 0;
uint16_t LCD_Height = 0;
uint16_t LCD_Row_Start = 0;
uint16_t LCD_Column_Start = 0;
uint16_t cacheMemIndexRow = 0;
uint16_t cacheMemIndexCol = 0;

inline uint16_t RGB(uint8_t r, uint8_t g, uint8_t b)
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
	while(!(SPSR & (1<<SPIF)));
	LCD_S_CS
}

inline static void LCD_Data_8(uint8_t data)
{
	LCD_U_CS
	LCD_S_DC
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
	LCD_S_CS
}

inline static void LCD_Data_16(uint16_t word)
{
	LCD_U_CS
	LCD_S_DC
	SPDR = (word >> 8) & 0x00FF;
	while(!(SPSR & (1<<SPIF)));
	SPDR = word & 0x00FF;
	while(!(SPSR & (1<<SPIF)));
	LCD_S_CS
}

inline static void LCD_Cursor(uint16_t x, uint16_t y)
{
	if ((x > LCD_WIDTH - (CHARS_COLS_LEN + 1)) && (y < LCD_HEIGHT - (CHARS_ROWS_LEN)))
	{
		cacheMemIndexRow = y + CHARS_ROWS_LEN;
		cacheMemIndexCol = x;
	}
	else
	{
		cacheMemIndexRow = y;
		cacheMemIndexCol = x;
	}
}

inline static void LCD_Window(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	LCD_Command(COLUMN_ADDRESS_SET);
	LCD_Data_16(x1);
	LCD_Data_16(x2);
	LCD_Command(PAGE_ADDRESS_SET);
	LCD_Data_16(y1);
	LCD_Data_16(y2);
	LCD_Command(MEMORY_WRITE);
}

void LCD_Pixel(uint16_t x, uint16_t y, uint32_t color24)
{
	LCD_Window(x, y, x, y);
	LCD_Data_16(H24_RGB565(1, color24));
}

void LCD_Rect_Fill(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint32_t color24)
{
	if ((x + w - 1) >= LCD_Width) w = LCD_Width - x;
	if ((y + h - 1) >= LCD_Height) h = LCD_Height - y;
	LCD_Window(x, y, x + w - 1, y + h - 1);
	for (y = h; y > 0; y--)
	for (x = w; x > 0; x--)
	LCD_Data_16(H24_RGB565(1, color24));
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

void LCD_Triangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint8_t size, uint32_t color24)
{
	LCD_Line(x1, y1, x2, y2, size, color24);
	LCD_Line(x2, y2, x3, y3, size, color24);
	LCD_Line(x3, y3, x1, y1, size, color24);
}

void LCD_Rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t size, uint32_t color24)
{
	LCD_Line(x, y, x + w, y, size, color24);
	LCD_Line(x, y + h, x + w, y + h, size, color24);
	LCD_Line(x, y, x, y + h, size, color24);
	LCD_Line(x + w, y, x + w, y + h, size, color24);
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

static void LCD_Ch(char character, uint32_t color24, ESizes size)
{
	uint16_t letter, idxCol, idxRow;
	idxCol = CHARS_COLS_LEN; // last column of character array - 5 columns
	idxRow = CHARS_ROWS_LEN; // last row of character array - 8 rows / bits
	if (size == X1)
	{
		while (idxCol--)
		{ // loop through 5 bytes
			letter = pgm_read_byte(&CHARACTERS[character - 32][idxCol]); // read from ROM memory
			while (idxRow--) { // loop through 8 bits
				if ((letter & 0x80) == 0x80) { // check if bit set
					LCD_Pixel(cacheMemIndexCol + idxCol, cacheMemIndexRow + idxRow, color24);
				}
				letter = letter << 1; // byte move to left / next bit
			}
			idxRow = CHARS_ROWS_LEN; // fill index row again
		}
	} else if (size == X2)
	{
		while (idxCol--)
		{ // loop through 5 bytes
			letter = pgm_read_byte(&CHARACTERS[character - 32][idxCol]); // read from ROM memory
			while (idxRow--)
			{ // loop through 8 bits
				if ((letter & 0x80) == 0x80)
				{ // check if bit set
					LCD_Pixel(cacheMemIndexCol + idxCol, cacheMemIndexRow + (idxRow << 1), color24); // Draw first up pixel; note: (idxRow << 1) - 2x multiplied
					LCD_Pixel(cacheMemIndexCol + idxCol, cacheMemIndexRow + (idxRow << 1) + 1, color24); // Draw second down pixel
				}
				letter = letter << 1; // byte move to left / next bit
			}
			idxRow = CHARS_ROWS_LEN; // fill index row again
		}
	} else if (size == X3)
	{
		while (idxCol--)
		{ // loop through 5 bytes
			letter = pgm_read_byte(&CHARACTERS[character - 32][idxCol]); // read from ROM memory
			while (idxRow--)
			{ // loop through 8 bits
				if ((letter & 0x80) == 0x80)
				{ // check if bit set
					LCD_Pixel(cacheMemIndexCol + (idxCol << 1), cacheMemIndexRow + (idxRow << 1), color24); // Draw first left up pixel; note: (idxRow << 1) - 2x multiplied
					LCD_Pixel(cacheMemIndexCol + (idxCol << 1), cacheMemIndexRow + (idxRow << 1) + 1, color24); // Draw second left down pixel
					LCD_Pixel(cacheMemIndexCol + (idxCol << 1) + 1, cacheMemIndexRow + (idxRow << 1), color24); // Draw third right up pixel
					LCD_Pixel(cacheMemIndexCol + (idxCol << 1) + 1, cacheMemIndexRow + (idxRow << 1) + 1, color24); // Draw fourth right down pixel
				}
				letter = letter << 1; // byte move to left / next bit
			}
			idxRow = CHARS_ROWS_LEN; // fill index row again
		}
	}
}

void LCD_String(uint16_t x, uint16_t y, char *str, uint32_t color24, ESizes size)
{
	LCD_Cursor(x, y);
	uint16_t i = 0;
	while (str[i] != '\0')
	{
		LCD_Ch(str[i++], color24, size);
		LCD_Cursor(cacheMemIndexCol + (CHARS_COLS_LEN + 1) + (size >> 1), cacheMemIndexRow);
	}
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

const uint8_t CHARACTERS[][5] PROGMEM =
{
	{ 0x00, 0x00, 0x00, 0x00, 0x00 }, // 20 space
	{ 0x00, 0x00, 0x5f, 0x00, 0x00 }, // 21 !
	{ 0x00, 0x07, 0x00, 0x07, 0x00 }, // 22 "
	{ 0x14, 0x7f, 0x14, 0x7f, 0x14 }, // 23 #
	{ 0x24, 0x2a, 0x7f, 0x2a, 0x12 }, // 24 $
	{ 0x23, 0x13, 0x08, 0x64, 0x62 }, // 25 %
	{ 0x36, 0x49, 0x55, 0x22, 0x50 }, // 26 &
	{ 0x00, 0x05, 0x03, 0x00, 0x00 }, // 27 '
	{ 0x00, 0x1c, 0x22, 0x41, 0x00 }, // 28 (
	{ 0x00, 0x41, 0x22, 0x1c, 0x00 }, // 29 )
	{ 0x14, 0x08, 0x3e, 0x08, 0x14 }, // 2a *
	{ 0x08, 0x08, 0x3e, 0x08, 0x08 }, // 2b +
	{ 0x00, 0x50, 0x30, 0x00, 0x00 }, // 2c ,
	{ 0x08, 0x08, 0x08, 0x08, 0x08 }, // 2d -
	{ 0x00, 0x60, 0x60, 0x00, 0x00 }, // 2e .
	{ 0x20, 0x10, 0x08, 0x04, 0x02 }, // 2f /
	{ 0x3e, 0x51, 0x49, 0x45, 0x3e }, // 30 0
	{ 0x00, 0x42, 0x7f, 0x40, 0x00 }, // 31 1
	{ 0x42, 0x61, 0x51, 0x49, 0x46 }, // 32 2
	{ 0x21, 0x41, 0x45, 0x4b, 0x31 }, // 33 3
	{ 0x18, 0x14, 0x12, 0x7f, 0x10 }, // 34 4
	{ 0x27, 0x45, 0x45, 0x45, 0x39 }, // 35 5
	{ 0x3c, 0x4a, 0x49, 0x49, 0x30 }, // 36 6
	{ 0x01, 0x71, 0x09, 0x05, 0x03 }, // 37 7
	{ 0x36, 0x49, 0x49, 0x49, 0x36 }, // 38 8
	{ 0x06, 0x49, 0x49, 0x29, 0x1e }, // 39 9
	{ 0x00, 0x36, 0x36, 0x00, 0x00 }, // 3a :
	{ 0x00, 0x56, 0x36, 0x00, 0x00 }, // 3b ;
	{ 0x08, 0x14, 0x22, 0x41, 0x00 }, // 3c <
	{ 0x14, 0x14, 0x14, 0x14, 0x14 }, // 3d =
	{ 0x00, 0x41, 0x22, 0x14, 0x08 }, // 3e >
	{ 0x02, 0x01, 0x51, 0x09, 0x06 }, // 3f ?
	{ 0x32, 0x49, 0x79, 0x41, 0x3e }, // 40 @
	{ 0x7e, 0x11, 0x11, 0x11, 0x7e }, // 41 A
	{ 0x7f, 0x49, 0x49, 0x49, 0x36 }, // 42 B
	{ 0x3e, 0x41, 0x41, 0x41, 0x22 }, // 43 C
	{ 0x7f, 0x41, 0x41, 0x22, 0x1c }, // 44 D
	{ 0x7f, 0x49, 0x49, 0x49, 0x41 }, // 45 E
	{ 0x7f, 0x09, 0x09, 0x09, 0x01 }, // 46 F
	{ 0x3e, 0x41, 0x49, 0x49, 0x7a }, // 47 G
	{ 0x7f, 0x08, 0x08, 0x08, 0x7f }, // 48 H
	{ 0x00, 0x41, 0x7f, 0x41, 0x00 }, // 49 I
	{ 0x20, 0x40, 0x41, 0x3f, 0x01 }, // 4a J
	{ 0x7f, 0x08, 0x14, 0x22, 0x41 }, // 4b K
	{ 0x7f, 0x40, 0x40, 0x40, 0x40 }, // 4c L
	{ 0x7f, 0x02, 0x0c, 0x02, 0x7f }, // 4d M
	{ 0x7f, 0x04, 0x08, 0x10, 0x7f }, // 4e N
	{ 0x3e, 0x41, 0x41, 0x41, 0x3e }, // 4f O
	{ 0x7f, 0x09, 0x09, 0x09, 0x06 }, // 50 P
	{ 0x3e, 0x41, 0x51, 0x21, 0x5e }, // 51 Q
	{ 0x7f, 0x09, 0x19, 0x29, 0x46 }, // 52 R
	{ 0x46, 0x49, 0x49, 0x49, 0x31 }, // 53 S
	{ 0x01, 0x01, 0x7f, 0x01, 0x01 }, // 54 T
	{ 0x3f, 0x40, 0x40, 0x40, 0x3f }, // 55 U
	{ 0x1f, 0x20, 0x40, 0x20, 0x1f }, // 56 V
	{ 0x3f, 0x40, 0x38, 0x40, 0x3f }, // 57 W
	{ 0x63, 0x14, 0x08, 0x14, 0x63 }, // 58 X
	{ 0x07, 0x08, 0x70, 0x08, 0x07 }, // 59 Y
	{ 0x61, 0x51, 0x49, 0x45, 0x43 }, // 5a Z
	{ 0x00, 0x7f, 0x41, 0x41, 0x00 }, // 5b [
	{ 0x02, 0x04, 0x08, 0x10, 0x20 }, // 5c backslash
	{ 0x00, 0x41, 0x41, 0x7f, 0x00 }, // 5d ]
	{ 0x04, 0x02, 0x01, 0x02, 0x04 }, // 5e ^
	{ 0x40, 0x40, 0x40, 0x40, 0x40 }, // 5f _
	{ 0x00, 0x01, 0x02, 0x04, 0x00 }, // 60 `
	{ 0x20, 0x54, 0x54, 0x54, 0x78 }, // 61 a
	{ 0x7f, 0x48, 0x44, 0x44, 0x38 }, // 62 b
	{ 0x38, 0x44, 0x44, 0x44, 0x20 }, // 63 c
	{ 0x38, 0x44, 0x44, 0x48, 0x7f }, // 64 d
	{ 0x38, 0x54, 0x54, 0x54, 0x18 }, // 65 e
	{ 0x08, 0x7e, 0x09, 0x01, 0x02 }, // 66 f
	{ 0x0c, 0x52, 0x52, 0x52, 0x3e }, // 67 g
	{ 0x7f, 0x08, 0x04, 0x04, 0x78 }, // 68 h
	{ 0x00, 0x44, 0x7d, 0x40, 0x00 }, // 69 i
	{ 0x20, 0x40, 0x44, 0x3d, 0x00 }, // 6a j
	{ 0x7f, 0x10, 0x28, 0x44, 0x00 }, // 6b k
	{ 0x00, 0x41, 0x7f, 0x40, 0x00 }, // 6c l
	{ 0x7c, 0x04, 0x18, 0x04, 0x78 }, // 6d m
	{ 0x7c, 0x08, 0x04, 0x04, 0x78 }, // 6e n
	{ 0x38, 0x44, 0x44, 0x44, 0x38 }, // 6f o
	{ 0x7c, 0x14, 0x14, 0x14, 0x08 }, // 70 p
	{ 0x08, 0x14, 0x14, 0x14, 0x7c }, // 71 q
	{ 0x7c, 0x08, 0x04, 0x04, 0x08 }, // 72 r
	{ 0x48, 0x54, 0x54, 0x54, 0x20 }, // 73 s
	{ 0x04, 0x3f, 0x44, 0x40, 0x20 }, // 74 t
	{ 0x3c, 0x40, 0x40, 0x20, 0x7c }, // 75 u
	{ 0x1c, 0x20, 0x40, 0x20, 0x1c }, // 76 v
	{ 0x3c, 0x40, 0x30, 0x40, 0x3c }, // 77 w
	{ 0x44, 0x28, 0x10, 0x28, 0x44 }, // 78 x
	{ 0x0c, 0x50, 0x50, 0x50, 0x3c }, // 79 y
	{ 0x44, 0x64, 0x54, 0x4c, 0x44 }, // 7a z
	{ 0x00, 0x08, 0x36, 0x41, 0x00 }, // 7b {
	{ 0x00, 0x00, 0x7f, 0x00, 0x00 }, // 7c |
	{ 0x00, 0x41, 0x36, 0x08, 0x00 }, // 7d }
	{ 0x10, 0x08, 0x08, 0x10, 0x08 }, // 7e ~
	{ 0x00, 0x00, 0x00, 0x00, 0x00 }  // 7f
};

uint16_t iScrollStart;
uint16_t yStart = TOP_FIXED_AREA; // The initial y coordinate of the top of the scrolling area
uint16_t yArea = 320 - TOP_FIXED_AREA-BOT_FIXED_AREA; // yArea must be a integral multiple of TEXT_HEIGHT
uint16_t yDraw = 320 - BOT_FIXED_AREA - TEXT_HEIGHT; // The initial y coordinate of the top of the bottom text line

void LCD_setupScrollArea(uint16_t TFA, uint16_t BFA) // Setup a portion of the screen for vertical scrolling
{ // We are using a hardware feature of the display, so we can only scroll in portrait orientation
	LCD_Command(VERT_SCROLL_DEFINITION); // Vertical scroll definition
	LCD_Data_16(TFA);
	LCD_Data_16(320-TFA-BFA);
	LCD_Data_16(BFA);
}

void LCD_scrollAddress(uint16_t VSP) // Setup the vertical scrolling start address
{
	LCD_Command(VERT_SCROLL_START_ADDRESS);
	LCD_Data_16(VSP);
}

int LCD_scrollLine() // Call this function to scroll the display one text line
{
	int yTemp = yStart; // Store the old yStart, this is where we draw the next line
	LCD_Rect_Fill(0, yStart, LCD_Width, TEXT_HEIGHT, BLACK); // fill remaining space
	yStart += TEXT_HEIGHT; // Change the top of the scroll area
	if (yStart >= 320 - BOT_FIXED_AREA) yStart = TOP_FIXED_AREA + (yStart - 320 + BOT_FIXED_AREA); // The value must wrap around as the screen memory is a circular buffer
	LCD_scrollAddress(yStart); // Now we can scroll the display
	return yTemp;
}

void LCD_SPI(void)
{ // Output: SCK, MOSI, CS_LD, DC_LD
	LCD_PORT |= (1 << LCD_SCK) | (1 << LCD_MOSI) | (1 << LCD_CS) | (1 << LCD_DC);
	LCD_DDR  |= (1 << LCD_SCK) | (1 << LCD_MOSI) | (1 << LCD_CS) | (1 << LCD_DC);
	SPCR |= (1 << SPE) | (1 << MSTR); // SPE - SPI Enable | MSTR - Master device
	SPSR |= (1 << SPI2X) | (1 << SPR1) | (1 << SPR0);
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

void LCD_Init()
{
	LCD_SPI();
	LCD_Reset();
	LCD_Command(SOFTWARE_RESET);
	LCD_Command(POWER_CONTROL_1);
	LCD_Data_8(0x25);
	LCD_Command(POWER_CONTROL_2);
	LCD_Data_8(0x01);
	LCD_Command(VCOM_CONTROL_1);
	LCD_Data_8(0x2B);
	LCD_Data_8(0x2B);
	LCD_Command(VCOM_CONTROL_2);
	LCD_Data_8(0x06);
	LCD_Command(COLMOD_PIXEL_FORMAT_SET);
	LCD_Data_8(0x05);
	LCD_Command(FRAME_RATE_CONTROL_NORMAL);
	LCD_Data_8(0x00);
	LCD_Data_8(0x18);
	LCD_Command(DISPLAY_FUNCTION_CONTROL);
	LCD_Data_8(0x0A);
	LCD_Data_8(0x82);
	LCD_Data_8(0x27);
	LCD_Command(COLMOD_PIXEL_FORMAT_SET);
	LCD_Data_8(0x55);
	LCD_Command(SLEEP_OUT);
	LCD_Command(DISPLAY_ON);
	LCD_Orientation(DEFAULT_ORIENTATION);
	LCD_Rect_Fill(0, 0, 320, 240, BLACK);
}

void LCD_Orientation(uint8_t orientation)
{
	LCD_Command(MEMORY_ACCESS_CONTROL);
	switch (orientation)
	{
		case 0:
		LCD_Data_8(0x40 | 0x08);
		LCD_Width = LCD_HEIGHT;
		LCD_Height = LCD_WIDTH;
		break;
		case 1:
		LCD_Data_8(0x20 | 0x08);
		LCD_Width  = LCD_WIDTH;
		LCD_Height = LCD_HEIGHT;
		break;
		case 2:
		LCD_Data_8(0x80 | 0x08);
		LCD_Width  = LCD_HEIGHT;
		LCD_Height = LCD_WIDTH;
		break;
		case 3:
		LCD_Data_8(0x40 | 0x80 | 0x20 | 0x08);
		LCD_Width  = LCD_WIDTH;
		LCD_Height = LCD_HEIGHT;
		break;
	}
}
