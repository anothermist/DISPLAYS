#include "ssd1306.h"

extern I2C_HandleTypeDef SSD1306_I2C;

#define SSD1306_WRITEDATA(data)       I2C_Write(SSD1306_I2C_ADDR, 0x40, (data))
#define SSD1306_WRITECOMMAND(command) I2C_Write(SSD1306_I2C_ADDR, 0x00, (command))

static uint8_t SSD1306_Buffer[(SSD1306_WIDTH + 1) * SSD1306_HEIGHT / 8];

typedef struct {
	uint16_t CurrentX;
	uint16_t CurrentY;
	uint8_t Inverted;
	uint8_t Initialized;
} SSD1306_t;

static SSD1306_t SSD1306;

void I2C_Write(uint8_t address, uint8_t reg, uint8_t data) 
{
	uint8_t dt[2];
	dt[0] = reg;
	dt[1] = data;
	HAL_I2C_Master_Transmit(&SSD1306_I2C, address, dt, 2, 10);
}

void I2C_WriteMulti(uint8_t address, uint8_t reg, uint8_t* data, uint16_t count)
{
	uint8_t dt[count + 1];
	dt[0] = reg;
	uint8_t i;
	for(i = 1; i <= count; i++)
		dt[i] = data[i-1];
	HAL_I2C_Master_Transmit(&SSD1306_I2C, address, dt, count, 10);
}

uint8_t SSD1306_Init(void)
{
	HAL_Delay(100);
	if (HAL_I2C_IsDeviceReady(&SSD1306_I2C, SSD1306_I2C_ADDR, 1, 20000) != HAL_OK) return 0;

	SSD1306_WRITECOMMAND(SSD1306_DISPLAYOFF);
	SSD1306_WRITECOMMAND(SSD1306_SETDISPLAYCLOCKDIV);
	SSD1306_WRITECOMMAND(0x80);
	SSD1306_WRITECOMMAND(SSD1306_SETMULTIPLEX);
	if (SSD1306_HEIGHT == 32) SSD1306_WRITECOMMAND(0x1F);
	else SSD1306_WRITECOMMAND(0x3F);
	SSD1306_WRITECOMMAND(SSD1306_SETDISPLAYOFFSET);
	SSD1306_WRITECOMMAND(0x00);
	SSD1306_WRITECOMMAND(SSD1306_SETSTARTLINE | 0x00);
	SSD1306_WRITECOMMAND(SSD1306_CHARGEPUMP);
	SSD1306_WRITECOMMAND(0x14);
	SSD1306_WRITECOMMAND(SSD1306_MEMORYMODE);
	SSD1306_WRITECOMMAND(0x00);
	SSD1306_WRITECOMMAND(SSD1306_SEGREMAP | 0x1);
	SSD1306_WRITECOMMAND(SSD1306_COMSCANDEC);
	SSD1306_WRITECOMMAND(SSD1306_SETCOMPINS);
	if (SSD1306_HEIGHT == 32) SSD1306_WRITECOMMAND(0x02);
	else SSD1306_WRITECOMMAND(0x12);
	SSD1306_WRITECOMMAND(SSD1306_SETCONTRAST);
	SSD1306_WRITECOMMAND(0xCF);
	SSD1306_WRITECOMMAND(SSD1306_SETPRECHARGE);
	SSD1306_WRITECOMMAND(0xF1);
	SSD1306_WRITECOMMAND(SSD1306_SETVCOMDETECT);
	SSD1306_WRITECOMMAND(0x40);	
	SSD1306_WRITECOMMAND(SSD1306_DISPLAYALLON_RESUME);
	SSD1306_WRITECOMMAND(SSD1306_DISPLAYON);
	LCD_Fill(SSD1306_COLOR_BLACK);
	LCD_UpdateScreen();

	SSD1306.CurrentX = 0;
	SSD1306.CurrentY = 0;
	
	SSD1306.Initialized = 1;
	return 1;
}

void LCD_ON(void)
{
	SSD1306_WRITECOMMAND(0x8D);  
	SSD1306_WRITECOMMAND(0x14);  
	SSD1306_WRITECOMMAND(0xAF);  
}

void LCD_OFF(void)
{
	SSD1306_WRITECOMMAND(0x8D);  
	SSD1306_WRITECOMMAND(0x10);
	SSD1306_WRITECOMMAND(0xAE);  
}

void LCD_UpdateScreen(void)
{
	uint8_t m;	
	for (m = 0; m < 8; m++)
	{
		SSD1306_WRITECOMMAND(0xB0 + m);
		SSD1306_WRITECOMMAND(0x00);
		SSD1306_WRITECOMMAND(0x10);
		I2C_WriteMulti(SSD1306_I2C_ADDR, 0x40, &SSD1306_Buffer[(SSD1306_WIDTH + 1) * m], (SSD1306_WIDTH + 1));
	}
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

void LCD_GotoXY(uint16_t x, uint16_t y)
{
	SSD1306.CurrentX = x;
	SSD1306.CurrentY = y;
}

void LCD_Pixel(uint16_t x, uint16_t y, SSD1306_COLOR_t color)
{
	if (x >= (SSD1306_WIDTH + 1) || y >= SSD1306_HEIGHT) return;
	if (SSD1306.Inverted) color = (SSD1306_COLOR_t)!color;	
	if (color == SSD1306_COLOR_WHITE) SSD1306_Buffer[x + (y / 8) * (SSD1306_WIDTH + 1)] |= 1 << (y % 8);
	else SSD1306_Buffer[x + (y / 8) * (SSD1306_WIDTH + 1)] &= ~(1 << (y % 8));
}

char LCD_Char(char ch, FontDef_t* Font, SSD1306_COLOR_t color)
{
	uint32_t i, b, j;
	
	if ((SSD1306_WIDTH + 1) <= (SSD1306.CurrentX + Font -> FontWidth) || SSD1306_HEIGHT <= (SSD1306.CurrentY + Font -> FontHeight)) return 0;
	
	for (i = 0; i < Font -> FontHeight; i++)
	{
		b = Font -> data[(ch - 32) * Font -> FontHeight + i];
		for (j = 0; j < Font -> FontWidth; j++) {
			if ((b << j) & 0x8000)
			{
				LCD_Pixel(SSD1306.CurrentX + j, (SSD1306.CurrentY + i), (SSD1306_COLOR_t) color);
			} 
			else
			{
				LCD_Pixel(SSD1306.CurrentX + j, (SSD1306.CurrentY + i), (SSD1306_COLOR_t)!color);
			}
		}
	}
	SSD1306.CurrentX += Font->FontWidth;
	return ch;
}

char LCD_String(uint16_t x, uint16_t y, char* str, FontDef_t* Font, SSD1306_COLOR_t color)
{
	LCD_GotoXY(x, y);
	while (*str)
	{
		if (LCD_Char(*str, Font, color) != *str) return *str;
		str++;
	}
	return *str;
}

void LCD_Line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, SSD1306_COLOR_t c)
{
	int16_t dx, dy, sx, sy, err, e2, i, tmp; 

	if (x0 >= (SSD1306_WIDTH + 1)) x0 = (SSD1306_WIDTH + 1) - 1;
	if (x1 >= (SSD1306_WIDTH + 1)) x1 = (SSD1306_WIDTH + 1) - 1;
	if (y0 >= SSD1306_HEIGHT) y0 = SSD1306_HEIGHT - 1;
	if (y1 >= SSD1306_HEIGHT) y1 = SSD1306_HEIGHT - 1;
	
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

		for (i = y0; i <= y1; i++) LCD_Pixel(x0, i, c);	
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
		
		for (i = x0; i <= x1; i++) LCD_Pixel(i, y0, c);
		return;
	}
	
	while (1)
	{
		LCD_Pixel(x0, y0, c);
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

void LCD_Rectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, SSD1306_COLOR_t c)
{
	if (x >= (SSD1306_WIDTH + 1) || y >= SSD1306_HEIGHT) return;
	if ((x + w) >= (SSD1306_WIDTH + 1)) w = (SSD1306_WIDTH + 1) - x;
	if ((y + h) >= SSD1306_HEIGHT) h = SSD1306_HEIGHT - y;
	
	LCD_Line(x, y, x + w, y, c);         /* Top line */
	LCD_Line(x, y + h, x + w, y + h, c); /* Bottom line */
	LCD_Line(x, y, x, y + h, c);         /* Left line */
	LCD_Line(x + w, y, x + w, y + h, c); /* Right line */
}

void LCD_Rectangle_Fill(uint16_t x, uint16_t y, uint16_t w, uint16_t h, SSD1306_COLOR_t c)
{
	uint8_t i;	
	if (x >= (SSD1306_WIDTH + 1) || y >= SSD1306_HEIGHT) return;
	if ((x + w) >= (SSD1306_WIDTH + 1)) w = (SSD1306_WIDTH + 1) - x;
	if ((y + h) >= SSD1306_HEIGHT) h = SSD1306_HEIGHT - y;
	for (i = 0; i <= h; i++) LCD_Line(x, y + i, x + w, y + i, c);

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

void LCD_Circle(int16_t x0, int16_t y0, int16_t r, SSD1306_COLOR_t c)
{
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

    LCD_Pixel(x0, y0 + r, c);
    LCD_Pixel(x0, y0 - r, c);
    LCD_Pixel(x0 + r, y0, c);
    LCD_Pixel(x0 - r, y0, c);

    while (x < y)
			{
        if (f >= 0)
				{
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        LCD_Pixel(x0 + x, y0 + y, c);
        LCD_Pixel(x0 - x, y0 + y, c);
        LCD_Pixel(x0 + x, y0 - y, c);
        LCD_Pixel(x0 - x, y0 - y, c);

        LCD_Pixel(x0 + y, y0 + x, c);
        LCD_Pixel(x0 - y, y0 + x, c);
        LCD_Pixel(x0 + y, y0 - x, c);
        LCD_Pixel(x0 - y, y0 - x, c);
    }
}

void LCD_Circle_Fill(int16_t x0, int16_t y0, int16_t r, SSD1306_COLOR_t c)
{
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

    LCD_Pixel(x0, y0 + r, c);
    LCD_Pixel(x0, y0 - r, c);
    LCD_Pixel(x0 + r, y0, c);
    LCD_Pixel(x0 - r, y0, c);
    LCD_Line(x0 - r, y0, x0 + r, y0, c);

    while (x < y)
		{
        if (f >= 0)
				{
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        LCD_Line(x0 - x, y0 + y, x0 + x, y0 + y, c);
        LCD_Line(x0 + x, y0 - y, x0 - x, y0 - y, c);

        LCD_Line(x0 + y, y0 + x, x0 - y, y0 + x, c);
        LCD_Line(x0 + y, y0 - x, x0 - y, y0 - x, c);
    }
}
