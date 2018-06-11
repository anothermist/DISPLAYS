#ifndef _SSD1331_H_
#define _SSD1331_H_

#include "main.h"

#define LCD_HEIGHT 64
#define LCD_WIDTH  96

#define LCD_PORT PORTB
#define LCD_DDR  DDRB
#define LCD_DC	 PB1 // PB1 | PB3
#define LCD_CS	 PB2 // PB2 | PB4
#define LCD_MOSI PB5 // PB3 | PB5
#define LCD_SCK	 PB7 // PB5 | PB7

#define LCD_S_DC	LCD_PORT |= (1 << LCD_DC);
#define LCD_U_DC	LCD_PORT &= ~(1 << LCD_DC);
#define LCD_S_CS	LCD_PORT |= (1 << LCD_CS);
#define LCD_U_CS	LCD_PORT &= ~(1 << LCD_CS);

#define RGB_OLED_WIDTH                      96
#define RGB_OLED_HEIGHT                     64

#define CMD_DRAW_LINE                       0x21
#define CMD_DRAW_RECTANGLE                  0x22
#define CMD_COPY_WINDOW                     0x23
#define CMD_DIM_WINDOW                      0x24
#define CMD_CLEAR_WINDOW                    0x25
#define CMD_FILL_WINDOW                     0x26
#define DISABLE_FILL    0x00
#define ENABLE_FILL     0x01
#define CMD_CONTINUOUS_SCROLLING_SETUP      0x27
#define CMD_DEACTIVE_SCROLLING              0x2E
#define CMD_ACTIVE_SCROLLING                0x2F

#define CMD_SET_COLUMN_ADDRESS              0x15
#define CMD_SET_ROW_ADDRESS                 0x75
#define CMD_SET_CONTRAST_A                  0x81
#define CMD_SET_CONTRAST_B                  0x82
#define CMD_SET_CONTRAST_C                  0x83
#define CMD_MASTER_CURRENT_CONTROL          0x87
#define CMD_SET_PRECHARGE_SPEED_A           0x8A
#define CMD_SET_PRECHARGE_SPEED_B           0x8B
#define CMD_SET_PRECHARGE_SPEED_C           0x8C
#define CMD_SET_REMAP                       0xA0
#define CMD_SET_DISPLAY_START_LINE          0xA1
#define CMD_SET_DISPLAY_OFFSET              0xA2
#define CMD_NORMAL_DISPLAY                  0xA4
#define CMD_ENTIRE_DISPLAY_ON               0xA5
#define CMD_ENTIRE_DISPLAY_OFF              0xA6
#define CMD_INVERSE_DISPLAY                 0xA7
#define CMD_SET_MULTIPLEX_RATIO             0xA8
#define CMD_DIM_MODE_SETTING                0xAB
#define CMD_SET_MASTER_CONFIGURE            0xAD
#define CMD_DIM_MODE_DISPLAY_ON             0xAC
#define CMD_DISPLAY_OFF                     0xAE
#define CMD_NORMAL_BRIGHTNESS_DISPLAY_ON    0xAF
#define CMD_POWER_SAVE_MODE                 0xB0
#define CMD_PHASE_PERIOD_ADJUSTMENT         0xB1
#define CMD_DISPLAY_CLOCK_DIV               0xB3
#define CMD_SET_GRAy_SCALE_TABLE            0xB8
#define CMD_ENABLE_LINEAR_GRAY_SCALE_TABLE  0xB9
#define CMD_SET_PRECHARGE_VOLTAGE           0xBB
#define CMD_SET_V_VOLTAGE                   0xBE

typedef enum {
	//reset the above effect and turn the data to ON at the corresponding gray level.
	NormalDisplay   = 0xA4,
	//forces the entire display to be at "GS63"
	DisplayOn       = 0xA5,
	//forces the entire display to be at gray level "GS0"
	DisplayOff      = 0xA6,
	//swap the gray level of display data
	InverseDisplay  = 0xA7
}DisplayMode;

typedef enum {
	DimMode         = 0xAC,
	SleepMode       = 0xAE,
	NormalMode      = 0xAF
}DisplayPower;

typedef enum {
	Horizontal      = 0x00,
	Vertical        = 0x01,
	Diagonal        = 0x02
}ScollingDirection;

typedef struct { // Data stored PER GLYPH
	uint16_t bitmapOffset;     // Pointer into GFXfont->bitmap
	uint8_t  width, height;    // Bitmap dimensions in pixels
	uint8_t  xAdvance;         // Distance to advance cursor (x axis)
	int8_t   xOffset, yOffset; // Dist from cursor position to UL corner
} GFXglyph;

typedef struct { // Data stored for FONT AS A WHOLE:
	uint8_t  *bitmap;      // Glyph bitmaps, concatenated
	GFXglyph *glyph;       // Glyph array
	uint8_t   first, last; // ASCII extents
	uint8_t   yAdvance;    // Newline distance (y axis)
} GFXfont;

#define BLACK   0x000000 /*   0,   0,   0 */
#define WHITE   0xFFFFFF /* 255, 255, 255 */
#define RED     0xFF0000 /* 255,   0,   0 */
#define BLUE    0x0000FF /*   0,   0, 255 */
#define BLUE_D  0x0000A0 /*   0,   0, 160 */
#define CYAN    0x00FFFF /*   0, 255, 255 */
#define CYAN_D  0x008080 /*   0, 128, 128 */
#define YELLOW  0xFFFF00 /* 255, 255,   0 */
#define MAGENTA 0xFF00FF /* 255,   0, 255 */
#define GREEN   0x00FF00 /*   0, 255,   0 */
#define GREEN_D 0x008000 /*   0, 128,   0 */
#define PURPLE  0x800080 /* 128,   0, 128 */
#define TEAL    0x008080 /*   0, 128, 128 */
#define NAVY    0x000080 /*   0,   0, 128 */
#define SILVER  0xC0C0C0 /* 192, 192, 192 */
#define GRAY    0x808080 /* 128, 128, 128 */
#define ORANGE  0xFFA500 /* 255, 165,   0 */
#define BROWN   0xA52A2A /* 165, 255,  42 */
#define MAROON  0x800000 /* 128,   0,   0 */
#define OLIVE   0x808000 /* 128, 128,   0 */
#define LIME    0xBFFF00 /* 191, 255,   0 */

void SSD1331_Frame(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint32_t outColor, uint32_t fillColor);
void LCD_Rect_Fill(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint32_t color24);
void LCD_Line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t size, uint32_t color24);
void LCD_Rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t size, uint32_t color24);
void LCD_Triangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint8_t size, uint32_t color24);
void LCD_Triangle_Fill(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint32_t color24);
void LCD_Ellipse(int16_t x0, int16_t y0, int16_t rx, int16_t ry, uint8_t fill, uint8_t size, uint32_t color24);
void LCD_Circle(uint16_t x, uint16_t y, uint8_t radius, uint8_t fill, uint8_t size, uint32_t color24);
void LCD_Rect_Round(uint16_t x, uint16_t y, uint16_t length, uint16_t width, uint16_t r, uint8_t size, uint32_t color24);
void LCD_Rect_Round_Fill(uint16_t x, uint16_t y, uint16_t length, uint16_t width, uint16_t r, uint32_t color24);
void LCD_Font(uint16_t x, uint16_t y, char *text, const GFXfont *p_font, uint8_t size, uint32_t color24);

void SSD1331_IMG(const unsigned char *img, uint16_t x, uint16_t y, uint16_t width, uint16_t height);
void SSD1331_copyWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1,uint16_t x2, uint16_t y2);
void SSD1331_dimWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
void SSD1331_clearWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
void SSD1331_setScrolling(ScollingDirection direction, uint8_t rowAddr, uint8_t rowNum, uint8_t timeInterval);
void SSD1331_enableScrolling(uint8_t enable);
void SSD1331_setDisplayMode(DisplayMode mode);
void SSD1331_setDisplayPower(DisplayPower power);
void SSD1331_Init(void);

#endif /* _SSD1331_H_ */
