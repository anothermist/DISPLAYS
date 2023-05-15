#include "ili9488.h"

extern SPI_HandleTypeDef LCD_SPI;

uint32_t RGB(uint8_t r, uint8_t g, uint8_t b) {
	return ((r & 0xFF) << 16) + ((g & 0xFF) << 8) + (b & 0xFF);
}

inline static void LCD_Command(uint8_t cmd) {
	if (SOFT_CS)
		LCD_U_CS
	LCD_U_DC
	HAL_SPI_Transmit(&LCD_SPI, &cmd, 1, 0);
	if (SOFT_CS)
		LCD_S_CS
}

inline static void LCD_Data_8(uint8_t data) {
	if (SOFT_CS)
		LCD_U_CS
	LCD_S_DC
	HAL_SPI_Transmit(&LCD_SPI, &data, 1, 0);
	if (SOFT_CS)
		LCD_S_CS
}

inline static void LCD_Data_16(uint16_t word) {
	if (SOFT_CS)
		LCD_U_CS
	LCD_S_DC
	LCD_Data_8((word >> 8) & 0x00FF);
	LCD_Data_8(word & 0x00FF);
	if (SOFT_CS)
		LCD_S_CS
}

inline static void LCD_Data_24(uint32_t word) {
	if (SOFT_CS)
		LCD_U_CS
	LCD_S_DC
	LCD_Data_8((word >> 16) & 0x00FFFF);
	LCD_Data_8((word >> 8) & 0x00FFFF);
	LCD_Data_8(word & 0x00FFFF);
	if (SOFT_CS)
		LCD_S_CS
}

inline static void LCD_Window(uint16_t x1, uint16_t y1, uint16_t x2,
		uint16_t y2) {
	LCD_Command(COLUMN_ADDRESS_SET);
	LCD_Data_16(y1);
	LCD_Data_16(y2);
	LCD_Command(PAGE_ADDRESS_SET);
	LCD_Data_16(x1);
	LCD_Data_16(x2);
	LCD_Command(MEMORY_WRITE);
}

void LCD_Pixel(uint16_t x, uint16_t y, uint32_t color24) {
	LCD_Window(x, y, x, y);
	LCD_Data_24(color24);
}

void LCD_Rect_Fill(uint16_t x, uint16_t y, uint16_t w, uint16_t h,
		uint32_t color24) {
	uint32_t i = 0;
	uint32_t j = (uint32_t) w * (uint32_t) h;
	LCD_Window(y, x, y + h - 1, x + w - 1);
	for (i = 0; i < j; i++)
		LCD_Data_24(color24);
}

void LCD_Line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t size,
		uint32_t color24) {
	int deltaX = abs(x2 - x1);
	int deltaY = abs(y2 - y1);
	int signX = x1 < x2 ? 1 : -1;
	int signY = y1 < y2 ? 1 : -1;
	int error = deltaX - deltaY;
	int error2 = 0;
	for (;;) {
		LCD_Rect_Fill(x1, y1, size, size, color24);
		if (x1 == x2 && y1 == y2)
			break;
		error2 = error * 2;
		if (error2 > -deltaY) {
			error -= deltaY;
			x1 += signX;
		}
		if (error2 < deltaX) {
			error += deltaX;
			y1 += signY;
		}
	}
}

void LCD_Rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t size,
		uint32_t color24) {
	LCD_Line(x, y, x + w, y, size, color24);
	LCD_Line(x, y + h, x + w, y + h, size, color24);
	LCD_Line(x, y, x, y + h, size, color24);
	LCD_Line(x + w, y, x + w, y + h, size, color24);
}

void LCD_Triangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
		uint16_t x3, uint16_t y3, uint8_t size, uint32_t color24) {
	LCD_Line(x1, y1, x2, y2, size, color24);
	LCD_Line(x2, y2, x3, y3, size, color24);
	LCD_Line(x3, y3, x1, y1, size, color24);
}

#define ABS(x) ((x) > 0 ? (x) : -(x))

void LCD_Triangle_Fill(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
		uint16_t x3, uint16_t y3, uint32_t color24) {
	int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0, yinc1 =
			0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0,
			curpixel = 0;

	deltax = ABS(x2 - x1);
	deltay = ABS(y2 - y1);
	x = x1;
	y = y1;

	if (x2 >= x1) {
		xinc1 = 1;
		xinc2 = 1;
	} else {
		xinc1 = -1;
		xinc2 = -1;
	}

	if (y2 >= y1) {
		yinc1 = 1;
		yinc2 = 1;
	} else {
		yinc1 = -1;
		yinc2 = -1;
	}

	if (deltax >= deltay) {
		xinc1 = 0;
		yinc2 = 0;
		den = deltax;
		num = deltax / 2;
		numadd = deltay;
		numpixels = deltax;
	} else {
		xinc2 = 0;
		yinc1 = 0;
		den = deltay;
		num = deltay / 2;
		numadd = deltax;
		numpixels = deltay;
	}

	for (curpixel = 0; curpixel <= numpixels; curpixel++) {
		LCD_Line(x, y, x3, y3, 1, color24);

		num += numadd;
		if (num >= den) {
			num -= den;
			x += xinc1;
			y += yinc1;
		}
		x += xinc2;
		y += yinc2;
	}
}

void LCD_Ellipse(int16_t x0, int16_t y0, int16_t rx, int16_t ry, uint8_t fill,
		uint8_t size, uint32_t color24) {
	int16_t x, y;
	int32_t rx2 = rx * rx;
	int32_t ry2 = ry * ry;
	int32_t fx2 = 4 * rx2;
	int32_t fy2 = 4 * ry2;
	int32_t s;
	if (fill) {
		for (x = 0, y = ry, s = 2 * ry2 + rx2 * (1 - 2 * ry);
				ry2 * x <= rx2 * y; x++) {
			LCD_Line(x0 - x, y0 - y, x0 + x + 1 - size, y0 - y, size, color24);
			LCD_Line(x0 - x, y0 + y, x0 + x + 1 - size, y0 + y, size, color24);
			if (s >= 0) {
				s += fx2 * (1 - y);
				y--;
			}
			s += ry2 * ((4 * x) + 6);
		}
		for (x = rx, y = 0, s = 2 * rx2 + ry2 * (1 - 2 * rx);
				rx2 * y <= ry2 * x; y++) {
			LCD_Line(x0 - x, y0 - y, x0 + x + 1 - size, y0 - y, size, color24);
			LCD_Line(x0 - x, y0 + y, x0 + x + 1 - size, y0 + y, size, color24);
			if (s >= 0) {
				s += fy2 * (1 - x);
				x--;
			}
			s += rx2 * ((4 * y) + 6);
		}
	} else {
		for (x = 0, y = ry, s = 2 * ry2 + rx2 * (1 - 2 * ry);
				ry2 * x <= rx2 * y; x++) {
			LCD_Rect_Fill(x0 + x, y0 + y, size, size, color24);
			LCD_Rect_Fill(x0 - x, y0 + y, size, size, color24);
			LCD_Rect_Fill(x0 + x, y0 - y, size, size, color24);
			LCD_Rect_Fill(x0 - x, y0 - y, size, size, color24);
			if (s >= 0) {
				s += fx2 * (1 - y);
				y--;
			}
			s += ry2 * ((4 * x) + 6);
		}
		for (x = rx, y = 0, s = 2 * rx2 + ry2 * (1 - 2 * rx);
				rx2 * y <= ry2 * x; y++) {
			LCD_Rect_Fill(x0 + x, y0 + y, size, size, color24);
			LCD_Rect_Fill(x0 - x, y0 + y, size, size, color24);
			LCD_Rect_Fill(x0 + x, y0 - y, size, size, color24);
			LCD_Rect_Fill(x0 - x, y0 - y, size, size, color24);
			if (s >= 0) {
				s += fy2 * (1 - x);
				x--;
			}
			s += rx2 * ((4 * y) + 6);
		}
	}
}

void LCD_Circle(uint16_t x, uint16_t y, uint8_t radius, uint8_t fill,
		uint8_t size, uint32_t color24) {
	int a_, b_, P;
	a_ = 0;
	b_ = radius;
	P = 1 - radius;
	while (a_ <= b_) {
		if (fill == 1) {
			LCD_Rect_Fill(x - a_, y - b_, 2 * a_ + 1, 2 * b_ + 1, color24);
			LCD_Rect_Fill(x - b_, y - a_, 2 * b_ + 1, 2 * a_ + 1, color24);
		} else {
			LCD_Rect_Fill(a_ + x, b_ + y, size, size, color24);
			LCD_Rect_Fill(b_ + x, a_ + y, size, size, color24);
			LCD_Rect_Fill(x - a_, b_ + y, size, size, color24);
			LCD_Rect_Fill(x - b_, a_ + y, size, size, color24);
			LCD_Rect_Fill(b_ + x, y - a_, size, size, color24);
			LCD_Rect_Fill(a_ + x, y - b_, size, size, color24);
			LCD_Rect_Fill(x - a_, y - b_, size, size, color24);
			LCD_Rect_Fill(x - b_, y - a_, size, size, color24);
		}
		if (P < 0) {
			P = (P + 3) + (2 * a_);
			a_++;
		} else {
			P = (P + 5) + (2 * (a_ - b_));
			a_++;
			b_--;
		}
	}
}

void LCD_Circle_Helper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername,
		uint8_t size, uint32_t color24) {
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

void LCD_Rect_Round(uint16_t x, uint16_t y, uint16_t length, uint16_t width,
		uint16_t r, uint8_t size, uint32_t color24) {
	LCD_Line(x + (r + 2), y, x + length + size - (r + 2), y, size, color24);
	LCD_Line(x + (r + 2), y + width - 1, x + length + size - (r + 2),
			y + width - 1, size, color24);
	LCD_Line(x, y + (r + 2), x, y + width - size - (r + 2), size, color24);
	LCD_Line(x + length - 1, y + (r + 2), x + length - 1,
			y + width - size - (r + 2), size, color24);

	LCD_Circle_Helper(x + (r + 2), y + (r + 2), (r + 2), 1, size, color24);
	LCD_Circle_Helper(x + length - (r + 2) - 1, y + (r + 2), (r + 2), 2, size,
			color24);
	LCD_Circle_Helper(x + length - (r + 2) - 1, y + width - (r + 2) - 1,
			(r + 2), 4, size, color24);
	LCD_Circle_Helper(x + (r + 2), y + width - (r + 2) - 1, (r + 2), 8, size,
			color24);
}

void LCD_Circle_Fill_Helper(int16_t x0, int16_t y0, int16_t r,
		uint8_t cornername, int16_t delta, uint32_t color24) {
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
			LCD_Line(x0 + x, y0 - y, x0 + x, y0 - y + 2 * y + delta, 1,
					color24);
			LCD_Line(x0 + y, y0 - x, x0 + y, y0 - x + 2 * x + delta, 1,
					color24);
		}
		if (cornername & 0x2) {
			LCD_Line(x0 - x, y0 - y, x0 - x, y0 - y + 2 * y + delta, 1,
					color24);
			LCD_Line(x0 - y, y0 - x, x0 - y, y0 - x + 2 * x + delta, 1,
					color24);
		}
	}
}

void LCD_Rect_Round_Fill(uint16_t x, uint16_t y, uint16_t length,
		uint16_t width, uint16_t r, uint32_t color24) {
	LCD_Rect_Fill(x + r, y, length - 2 * r, width, color24);
	LCD_Circle_Fill_Helper(x + length - r - 1, y + r, r, 1, width - 2 * r - 1,
			color24);
	LCD_Circle_Fill_Helper(x + r, y + r, r, 2, width - 2 * r - 1, color24);
}

static void LCD_Char(int16_t x, int16_t y, const GFXglyph *glyph,
		const GFXfont *font, uint8_t size, uint32_t color24) {
	uint8_t *bitmap = font->bitmap;
	uint16_t bo = glyph->bitmapOffset;
	uint8_t bits = 0, bit = 0;
	uint16_t set_pixels = 0;
	uint8_t cur_x, cur_y;
	for (cur_y = 0; cur_y < glyph->height; cur_y++) {
		for (cur_x = 0; cur_x < glyph->width; cur_x++) {
			if (bit == 0) {
				bits = (*(const unsigned char*) (&bitmap[bo++]));
				bit = 0x80;
			}
			if (bits & bit)
				set_pixels++;
			else if (set_pixels > 0) {
				LCD_Rect_Fill(x + (glyph->xOffset + cur_x - set_pixels) * size,
						y + (glyph->yOffset + cur_y) * size, size * set_pixels,
						size, color24);
				set_pixels = 0;
			}
			bit >>= 1;
		}
		if (set_pixels > 0) {
			LCD_Rect_Fill(x + (glyph->xOffset + cur_x - set_pixels) * size,
					y + (glyph->yOffset + cur_y) * size, size * set_pixels,
					size, color24);
			set_pixels = 0;
		}
	}
}

void LCD_Font(uint16_t x, uint16_t y, const char *text, const GFXfont *p_font,
		uint8_t size, uint32_t color24) {
	int16_t cursor_x = x;
	int16_t cursor_y = y;
	GFXfont font;
	memcpy(&font, p_font, sizeof(GFXfont));
	for (uint16_t text_pos = 0; text_pos < strlen(text); text_pos++) {
		char c = text[text_pos];
		if (c == '\n') {
			cursor_x = x;
			cursor_y += font.yAdvance * size;
		} else if (c >= font.first && c <= font.last && c != '\r') {
			GFXglyph glyph;
			memcpy(&glyph, &font.glyph[c - font.first], sizeof(GFXglyph));
			LCD_Char(cursor_x, cursor_y, &glyph, &font, size, color24);
			cursor_x += glyph.xAdvance * size;
		}
	}
}

void LCD_Bitmap(uint16_t x, uint16_t y, const char *bitmap) {
	uint8_t w = (*(const unsigned short*) (bitmap));
	bitmap += 2;
	uint8_t h = (*(const unsigned short*) (bitmap));
	bitmap += 2;
	LCD_Window(x, y, x + w - 1, y + h - 1);
	for (uint16_t i = 0; i < h; i++) {
		for (uint16_t j = 0; j < w; j++) {
			uint16_t color = (*(const unsigned short*) (bitmap));
			LCD_Data_16(color);
			bitmap += 2;
		}
	}
}

void LCD_Bitmap_Mono(uint16_t x, uint16_t y, const char *bitmap,
		uint32_t color24_set, uint32_t color24_unset) {
	uint8_t w = (*(const unsigned char*) (bitmap++));
	uint8_t h = (*(const unsigned char*) (bitmap++));
	LCD_Window(x, y, x + w - 1, y + h - 1);
	uint16_t bit_pos = 0;
	uint16_t byte = 0;
	for (uint16_t i = 0; i < h; i++) {
		for (uint16_t j = 0; j < w; j++) {
			if (bit_pos % 8 == 0)
				byte = (*(const unsigned char*) (bitmap++));
			if (byte & (1 << (bit_pos % 8)))
				LCD_Data_24(color24_set);
			else
				LCD_Data_24(color24_unset);
			bit_pos++;
		}
	}
}

uint16_t LCD_Width = 0;
uint16_t LCD_Height = 0;
uint16_t iScrollStart;
uint16_t yStart = TOP_FIXED_AREA; // The initial y coordinate of the top of the scrolling area
uint16_t yArea = 320 - TOP_FIXED_AREA - BOT_FIXED_AREA; // yArea must be a integral multiple of TEXT_HEIGHT
uint16_t yDraw = 320 - BOT_FIXED_AREA - TEXT_HEIGHT; // The initial y coordinate of the top of the bottom text line

void LCD_setupScrollArea(uint16_t TFA, uint16_t BFA) { // Setup a portion of the screen for vertical scrolling. Using a hardware feature of the display, so we can only scroll in portrait orientation
	LCD_Command(VERT_SCROLL_DEFINITION); // Vertical scroll definition
	LCD_Data_16(TFA);
	LCD_Data_16(320 - TFA - BFA);
	LCD_Data_16(BFA);
}

void LCD_scrollAddress(uint16_t VSP) { // Setup the vertical scrolling start address
	LCD_Command(VERT_SCROLL_START_ADDRESS);
	LCD_Data_16(VSP);
}

int LCD_scrollLine(void) { // Call this function to scroll the display one text line
	int yTemp = yStart; // Store the old yStart, this is where we draw the next line
	LCD_Rect_Fill(0, yStart, LCD_Width, TEXT_HEIGHT, BLACK); // fill remaining space
	yStart += TEXT_HEIGHT; // Change the top of the scroll area
	if (yStart >= LCD_WIDTH - BOT_FIXED_AREA)
		yStart = TOP_FIXED_AREA + (yStart - LCD_WIDTH + BOT_FIXED_AREA); // The value must wrap around as the screen memory is a circular buffer
	LCD_scrollAddress(yStart); // Now we can scroll the display
	return yTemp;
}

void LCD_Reset(void) {
	LCD_U_CS
	LCD_S_RST
	HAL_Delay(150);
	LCD_U_RST
	HAL_Delay(150);
	LCD_S_RST
}

void LCD_Orientation(uint8_t orientation) {
	LCD_Command(MEMORY_ACCESS_CONTROL);
	switch (orientation) {
	case 0:
		LCD_Data_8(0x40 | 0x08);
		LCD_Width = LCD_HEIGHT;
		LCD_Height = LCD_WIDTH;
		break;
	case 1:
		LCD_Data_8(0x20 | 0x08);
		LCD_Width = LCD_WIDTH;
		LCD_Height = LCD_HEIGHT;
		break;
	case 2:
		LCD_Data_8(0x80 | 0x08);
		LCD_Width = LCD_HEIGHT;
		LCD_Height = LCD_WIDTH;
		break;
	case 3:
		LCD_Data_8(0x40 | 0x80 | 0x20 | 0x08);
		LCD_Width = LCD_WIDTH;
		LCD_Height = LCD_HEIGHT;
		break;
	}
}

void LCD_Init(void) {
	LCD_Reset();
	LCD_Command(SOFTWARE_RESET);

	LCD_Command(POWER_CONTROL_1);
	LCD_Data_8(0x17);    //Vreg1out
	LCD_Data_8(0x15);    //Verg2out

	LCD_Command(POWER_CONTROL_2);
	LCD_Data_8(0x41);    //VGH,VGL

	LCD_Command(VCOM_CONTROL_1);
	LCD_Data_8(0x00);
	LCD_Data_8(0x12);    //Vcom
	LCD_Data_8(0x80);

	LCD_Command(MEMORY_ACCESS_CONTROL);
	LCD_Data_8(0x48);

	LCD_Command(COLMOD_PIXEL_FORMAT_SET);
	LCD_Data_8(0x66); 	  //18 bit

	LCD_Command(RGB_SIGNAL_CONTROL);
	LCD_Data_8(0x80);    //SDO NOT USE

	LCD_Command(FRAME_RATE_CONTROL_NORMAL);
	LCD_Data_8(0xA0);    //60Hz

	LCD_Command(DISPLAY_INVERSION_CONTROL);
	LCD_Data_8(0x02);    //2-dot

	LCD_Command(DISPLAY_FUNCTION_CONTROL);
	LCD_Data_8(0x02);    //MCU
	LCD_Data_8(0x02);    //Source,Gate scan dieection

	LCD_Command(0XE9);   // Set Image Functio
	LCD_Data_8(0x00);    // Disable 24 bit data

	LCD_Command(PUMP_RATIO_CONTROL);
	LCD_Data_8(0xA9);
	LCD_Data_8(0x51);
	LCD_Data_8(0x2C);
	LCD_Data_8(0x82);    // D7 stream, loose

//	LCD_Command(SOFTWARE_RESET);
//	LCD_Command(POWER_CONTROL_1);
//	LCD_Data_8(0x25);
//	LCD_Command(POWER_CONTROL_2);
//	LCD_Data_8(0x01);
//	LCD_Command(VCOM_CONTROL_1);
//	LCD_Data_8(0x2B);
//	LCD_Data_8(0x2B);
//	LCD_Command(VCOM_CONTROL_2);
//	LCD_Data_8(0x06);
//	LCD_Command(COLMOD_PIXEL_FORMAT_SET);
//	LCD_Data_8(0x05);
//	LCD_Command(FRAME_RATE_CONTROL_NORMAL);
//	LCD_Data_8(0x00);
//	LCD_Data_8(0x18);
//	LCD_Command(DISPLAY_FUNCTION_CONTROL);
//	LCD_Data_8(0x0A);
//	LCD_Data_8(0x82);
//	LCD_Data_8(0x27);
//	LCD_Command(COLMOD_PIXEL_FORMAT_SET);
//	LCD_Data_8(0x55);
	LCD_Command(SLEEP_OUT);
	LCD_Command(DISPLAY_ON);
	LCD_Orientation(DEFAULT_ORIENTATION);
	LCD_Rect_Fill(0, 0, LCD_WIDTH, LCD_HEIGHT, BLACK);
}
