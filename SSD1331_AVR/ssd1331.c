#include "ssd1331.h"

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
//	LCD_U_DC
	SPDR = cmd;
	while(!(SPSR & (1 << SPIF)));
	LCD_S_CS
}

inline static void LCD_Data_8(uint8_t data)
{
	LCD_U_CS
//	LCD_S_DC
	SPDR = data;
	while(!(SPSR & (1 << SPIF)));
	LCD_S_CS
}

void SSD1331_Frame(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint32_t outColor, uint32_t fillColor)
{
	LCD_Command(CMD_FILL_WINDOW);//fill window
	LCD_Command(ENABLE_FILL);
	LCD_Command(CMD_DRAW_RECTANGLE);//draw rectangle
	LCD_Command(x0);//start column
	LCD_Command(y0);//start row
	LCD_Command(x1);//end column
	LCD_Command(y1);//end row
	
	outColor = H24_RGB565(1, outColor);
	fillColor = H24_RGB565(1, fillColor);
	
	LCD_Command((uint8_t)((outColor>>11)&0x1F));//R
	LCD_Command((uint8_t)((outColor>>5)&0x3F));//G
	LCD_Command((uint8_t)(outColor&0x1F));//B
	LCD_Command((uint8_t)((fillColor>>11)&0x1F));//R
	LCD_Command((uint8_t)((fillColor>>5)&0x3F));//G
	LCD_Command((uint8_t)(fillColor&0x1F));//B
}

void LCD_Rect_Fill(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint32_t color24)
{
	SSD1331_Frame(x, y, x + w, y + h, color24, color24);
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

void SSD1331_IMG(const unsigned char *img, uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
	uint16_t xx, yy;

	if ( (x + width > LCD_WIDTH) | (y+height > LCD_HEIGHT) ){
		return;
	}

	for (yy=0; yy<height; yy++) {
		//set column point
		LCD_Command(CMD_SET_COLUMN_ADDRESS);
		LCD_Command(x);
		LCD_Command(LCD_WIDTH-1);
		//set row point
		LCD_Command(CMD_SET_ROW_ADDRESS);
		LCD_Command(y + yy);
		LCD_Command(LCD_HEIGHT-1);
		LCD_S_DC	//GPIO_SetBits(GPIOB, GPIO_Pin_0); //dc
		LCD_U_CS	//GPIO_ResetBits(GPIOB, GPIO_Pin_1); //cs

		for (xx=0; xx<width*2; xx++) {
			LCD_Data_8(img[yy*width*2 + xx]);
		}
	}
}

void SSD1331_copyWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1,uint16_t x2, uint16_t y2)
{
	LCD_Command(CMD_COPY_WINDOW);//copy window
	LCD_Command(x0);//start column
	LCD_Command(y0);//start row
	LCD_Command(x1);//end column
	LCD_Command(y1);//end row
	LCD_Command(x2);//new column
	LCD_Command(y2);//new row
}

void SSD1331_dimWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
	LCD_Command(CMD_DIM_WINDOW);//copy area
	LCD_Command(x0);//start column
	LCD_Command(y0);//start row
	LCD_Command(x1);//end column
	LCD_Command(y1);//end row
}

void SSD1331_clearWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
	LCD_Command(CMD_CLEAR_WINDOW);//clear window
	LCD_Command(x0);//start column
	LCD_Command(y0);//start row
	LCD_Command(x1);//end column
	LCD_Command(y1);//end row
}

void SSD1331_setScrolling(ScollingDirection direction, uint8_t rowAddr, uint8_t rowNum, uint8_t timeInterval)
{
	uint8_t scolling_horizontal = 0x0;
	uint8_t scolling_vertical = 0x0;
	switch(direction){
		case Horizontal:
		scolling_horizontal = 0x01;
		scolling_vertical = 0x00;
		break;
		case Vertical:
		scolling_horizontal = 0x00;
		scolling_vertical = 0x01;
		break;
		case Diagonal:
		scolling_horizontal = 0x01;
		scolling_vertical = 0x01;
		break;
		default:
		break;
	}
	LCD_Command(CMD_CONTINUOUS_SCROLLING_SETUP);
	LCD_Command(scolling_horizontal);
	LCD_Command(rowAddr);
	LCD_Command(rowNum);
	LCD_Command(scolling_vertical);
	LCD_Command(timeInterval);
	LCD_Command(CMD_ACTIVE_SCROLLING);
}

void SSD1331_enableScrolling(uint8_t enable)
{
	if(enable)
	LCD_Command(CMD_ACTIVE_SCROLLING);
	else
	LCD_Command(CMD_DEACTIVE_SCROLLING);
}

void SSD1331_setDisplayMode(DisplayMode mode)
{
	LCD_Command(mode);
}

void SSD1331_setDisplayPower(DisplayPower power)
{
	LCD_Command(power);
}

void SPI_Init(void)
{
	LCD_PORT |= (1 << LCD_SCK) | (1 << LCD_MOSI) | (1 << LCD_CS) | (1 << LCD_DC);
	LCD_DDR  |= (1 << LCD_SCK) | (1 << LCD_MOSI) | (1 << LCD_CS) | (1 << LCD_DC);
	SPCR |= (1 << SPE) | (1 << MSTR);
	SPSR |= (1 << SPI2X) | (0 << SPR1) | (0 << SPR0);
}

void SSD1331_Init(void)
{
	SPI_Init();
	_delay_ms(1);
	LCD_Command(CMD_DISPLAY_OFF);          //Display Off
	LCD_Command(CMD_SET_CONTRAST_A);       //Set contrast for color A
	LCD_Command(0x91);                     //145 (0x91)
	LCD_Command(CMD_SET_CONTRAST_B);       //Set contrast for color B
	LCD_Command(0x50);                     //80 (0x50)
	LCD_Command(CMD_SET_CONTRAST_C);       //Set contrast for color C
	LCD_Command(0x7D);                     //125 (0x7D)
	LCD_Command(CMD_MASTER_CURRENT_CONTROL);//master current control
	LCD_Command(0x06);                     //6
	LCD_Command(CMD_SET_PRECHARGE_SPEED_A);//Set Second Pre-change Speed For ColorA
	LCD_Command(0x64);                     //100
	LCD_Command(CMD_SET_PRECHARGE_SPEED_B);//Set Second Pre-change Speed For ColorB
	LCD_Command(0x78);                     //120
	LCD_Command(CMD_SET_PRECHARGE_SPEED_C);//Set Second Pre-change Speed For ColorC
	LCD_Command(0x64);                     //100
	LCD_Command(CMD_SET_REMAP);            //set remap & data format
	LCD_Command(0x72);                     //0x72
	LCD_Command(CMD_SET_DISPLAY_START_LINE);//Set display Start Line
	LCD_Command(0x0);
	LCD_Command(CMD_SET_DISPLAY_OFFSET);   //Set display offset
	LCD_Command(0x0);
	LCD_Command(CMD_NORMAL_DISPLAY);       //Set display mode
	LCD_Command(CMD_SET_MULTIPLEX_RATIO);  //Set multiplex ratio
	LCD_Command(0x3F);
	LCD_Command(CMD_SET_MASTER_CONFIGURE); //Set master configuration
	LCD_Command(0x8E);
	LCD_Command(CMD_POWER_SAVE_MODE);      //Set Power Save Mode
	LCD_Command(0x00);                     //0x00
	LCD_Command(CMD_PHASE_PERIOD_ADJUSTMENT);//phase 1 and 2 period adjustment
	LCD_Command(0x31);                     //0x31
	LCD_Command(CMD_DISPLAY_CLOCK_DIV);    //display clock divider/oscillator frequency
	LCD_Command(0xF0);
	LCD_Command(CMD_SET_PRECHARGE_VOLTAGE);//Set Pre-Change Level
	LCD_Command(0x3A);
	LCD_Command(CMD_SET_V_VOLTAGE);        //Set vcomH
	LCD_Command(0x3E);
	LCD_Command(CMD_DEACTIVE_SCROLLING);   //disable scrolling
	LCD_Command(CMD_NORMAL_BRIGHTNESS_DISPLAY_ON);//set display on
	_delay_ms(1);
	SSD1331_clearWindow(0, 0, 95, 63);
	_delay_ms(1);
}
