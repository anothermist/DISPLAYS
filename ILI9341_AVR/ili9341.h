#ifndef _ILI9341_H_
#define _ILI9341_H_

#include "main.h"

#define LCD_HEIGHT 240
#define LCD_WIDTH  320

#define DEFAULT_ORIENTATION 3

#define LCD_PORT PORTB
#define LCD_DDR  DDRB
#define LCD_DC	 PB3 // PB1 | PB3
#define LCD_CS	 PB4 // PB2 | PB4
#define LCD_MOSI PB5 // PB3 | PB5
#define LCD_SCK	 PB7 // PB5 | PB7
#define LCD_RST	 0

#define LCD_DC_S	LCD_PORT |= (1 << LCD_DC);
#define LCD_DC_U	LCD_PORT &= ~(1 << LCD_DC);
#define LCD_CS_S	LCD_PORT |= (1 << LCD_CS);
#define LCD_CS_U	LCD_PORT &= ~(1 << LCD_CS);
#define LCD_RST_S	LCD_PORT |= (1 << LCD_RST);
#define LCD_RST_U	LCD_PORT &= ~(1 << LCD_RST);

#define BLACK   0x000000
#define WHITE   0xFFFFFF
#define RED     HUE_17
#define BLUE    HUE_01
#define BLUE_D  0x0000A0 /*   0,   0, 160 */
#define CYAN    HUE_05
#define YELLOW  HUE_13 /* 255, 255,   0 */
#define MAGENTA HUE_21 /* 255,   0, 255 */
#define GREEN   HUE_09 /*   0, 255,   0 */
#define GREEN_D 0x007F00 /*   0, 128,   0 */
#define PURPLE  0x7F007F /* 128,   0, 128 */
#define TEAL    0x007F7F /*   0, 128, 128 */
#define NAVY    0x00007F /*   0,   0, 128 */
#define SILVER  0xBFBFBF /* 191, 191, 191 */
#define GRAY    0x7F7F7F /* 128, 128, 128 */
#define ORANGE  0xFFA500 /* 255, 165,   0 */
#define BROWN   0xA52A2A /* 165, 255,  42 */
#define MAROON  0x7F0000 /* 128,   0,   0 */
#define OLIVE   0x7F7F00 /* 128, 128,   0 */
#define LIME    HUE_12

#define HUE_01 0x0000FF // 000, 000, 255 - BLUE
#define HUE_02 0x003FFF // 000, 063, 255 - 
#define HUE_03 0x007FFF // 000, 127, 255 - 
#define HUE_04 0x00BFFF // 000, 191, 255 - 
#define HUE_05 0x00FFFF // 000, 255, 255 - CYAN
#define HUE_06 0x00FFBF // 000, 255, 191 - 
#define HUE_07 0x00FF7F // 000, 255, 127 - 
#define HUE_08 0x00FF00 // 000, 255, 063 - 
#define HUE_09 0x00FF00 // 000, 255, 000 - GREEN
#define HUE_10 0x3FFF00 // 063, 255, 000 - 
#define HUE_11 0x7FFF7F // 127, 255, 000 - 
#define HUE_12 0xBFFF00 // 191, 255, 000 - LIME
#define HUE_13 0xFFFF00 // 255, 255, 000 - YELLOW
#define HUE_14 0xFFBF00 // 255, 191, 000 - 
#define HUE_15 0xFF7F00 // 255, 127, 000 - 
#define HUE_16 0xFF3F00 // 255, 063, 000 - 
#define HUE_17 0xFF0000 // 255, 000, 000 - RED
#define HUE_18 0xFF003F // 255, 000, 063 - 
#define HUE_19 0xFF007F // 255, 000, 127 - 
#define HUE_20 0xFF00BF // 255, 000, 191 - 
#define HUE_21 0xFF00FF // 255, 000, 255 - MAGENTA
#define HUE_22 0xBF00FF // 191, 000, 255 - 
#define HUE_23 0x7F00FF // 127, 000, 255 - 
#define HUE_24 0x3F00FF // 063, 000, 255 - 

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

uint32_t RGB(uint8_t r, uint8_t g, uint8_t b);

void LCD_SPI(void);
void LCD_Init(void);
void LCD_Orientation(uint8_t orientation);
void LCD_Pixel(uint16_t x, uint16_t y, uint32_t color24);
void LCD_Rect_Fill(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint32_t color24);
void LCD_Line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t size, uint32_t color24);
void LCD_Rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t size, uint32_t color24);
void LCD_Triangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint8_t size, uint32_t color24);
void LCD_Triangle_Fill(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint32_t color24);
void LCD_Ellipse(int16_t x0, int16_t y0, int16_t rx, int16_t ry, uint8_t fill, uint8_t size, uint32_t color24);
void LCD_Circle(uint16_t x, uint16_t y, uint8_t radius, uint8_t fill, uint8_t size, uint32_t color24);
void LCD_Rect_Round(uint16_t x, uint16_t y, uint16_t length, uint16_t width, uint16_t r, uint8_t size, uint32_t color24);
void LCD_Rect_Round_Fill(uint16_t x, uint16_t y, uint16_t length, uint16_t width, uint16_t r, uint32_t color24);
void LCD_Font(uint16_t x, uint16_t y, const char *text, const GFXfont *p_font, uint8_t size, uint32_t color24);
void LCD_Bitmap(uint16_t x, uint16_t y, PGM_P bitmap);
void LCD_Bitmap_Mono(uint16_t x, uint16_t y, PGM_P bitmap, uint32_t color24_set, uint32_t color24_unset);

void LCD_setupScrollArea(uint16_t TFA, uint16_t BFA) ;
void LCD_scrollAddress(uint16_t VSP);
int LCD_scrollLine(void);

// The scrolling area must be a integral multiple of TEXT_HEIGHT
#define TEXT_HEIGHT 16 // Height of text to be printed and scrolled
#define BOT_FIXED_AREA 0 // Number of lines in bottom fixed area (lines counted from bottom of screen)
#define TOP_FIXED_AREA 16 // Number of lines in top fixed area (lines counted from top of screen)

// The scrolling area must be a integral multiple of TEXT_HEIGHT
#define TEXT_HEIGHT 16 // Height of text to be printed and scrolled
#define BOT_FIXED_AREA 0 // Number of lines in bottom fixed area (lines counted from bottom of screen)
#define TOP_FIXED_AREA 16 // Number of lines in top fixed area (lines counted from top of screen)

/* Level 1 Commands (from the display Datasheet) */
#define NOP                             0x00
#define SOFTWARE_RESET                  0x01
#define READ_DISP_ID                    0x04
#define READ_DISP_STATUS                0x09
#define READ_DISP_MADCTRL               0x0B
#define READ_DISP_PIXEL_FORMAT          0x0C
#define READ_DISP_IMAGE_FORMAT          0x0D
#define READ_DISP_SIGNAL_MODE           0x0E
#define READ_DISP_SELF_DIAGNOSTIC       0x0F
#define ENTER_SLEEP_MODE                0x10
#define SLEEP_OUT                       0x11
#define PARTIAL_MODE_ON                 0x12
#define NORMAL_DISP_MODE_ON             0x13
#define DISP_INVERSION_OFF              0x20
#define DISP_INVERSION_ON               0x21
#define GAMMA_SET                       0x26
#define DISPLAY_OFF                     0x28
#define DISPLAY_ON                      0x29
#define COLUMN_ADDRESS_SET              0x2A
#define PAGE_ADDRESS_SET                0x2B
#define MEMORY_WRITE                    0x2C
#define COLOR_SET                       0x2D
#define MEMORY_READ                     0x2E
#define PARTIAL_AREA                    0x30
#define VERT_SCROLL_DEFINITION          0x33
#define TEARING_EFFECT_LINE_OFF         0x34
#define TEARING_EFFECT_LINE_ON          0x35
#define MEMORY_ACCESS_CONTROL           0x36
#define VERT_SCROLL_START_ADDRESS       0x37
#define IDLE_MODE_OFF                   0x38
#define IDLE_MODE_ON                    0x39
#define COLMOD_PIXEL_FORMAT_SET         0x3A
#define WRITE_MEMORY_CONTINUE           0x3C
#define READ_MEMORY_CONTINUE            0x3E
#define SET_TEAR_SCANLINE               0x44
#define GET_SCANLINE                    0x45
#define WRITE_DISPLAY_BRIGHTNESS        0x51
#define READ_DISPLAY_BRIGHTNESS         0x52
#define WRITE_CTRL_DISPLAY              0x53
#define READ_CTRL_DISPLAY               0x54
#define WRITE_CONTENT_ADAPT_BRIGHTNESS  0x55
#define READ_CONTENT_ADAPT_BRIGHTNESS   0x56
#define WRITE_MIN_CAB_LEVEL             0x5E
#define READ_MIN_CAB_LEVEL              0x5F
#define READ_ID1                        0xDA
#define READ_ID2                        0xDB
#define READ_ID3                        0xDC
/* Level 2 Commands (from the display Datasheet) */
#define RGB_SIGNAL_CONTROL              0xB0
#define FRAME_RATE_CONTROL_NORMAL       0xB1
#define FRAME_RATE_CONTROL_IDLE_8COLOR  0xB2
#define FRAME_RATE_CONTROL_PARTIAL      0xB3
#define DISPLAY_INVERSION_CONTROL       0xB4
#define BLANKING_PORCH_CONTROL          0xB5
#define DISPLAY_FUNCTION_CONTROL        0xB6
#define ENTRY_MODE_SET                  0xB7
#define BACKLIGHT_CONTROL_1             0xB8
#define BACKLIGHT_CONTROL_2             0xB9
#define BACKLIGHT_CONTROL_3             0xBA
#define BACKLIGHT_CONTROL_4             0xBB
#define BACKLIGHT_CONTROL_5             0xBC
#define BACKLIGHT_CONTROL_6             0xBD
#define BACKLIGHT_CONTROL_7             0xBE
#define BACKLIGHT_CONTROL_8             0xBF
#define POWER_CONTROL_1                 0xC0
#define POWER_CONTROL_2                 0xC1
#define VCOM_CONTROL_1                  0xC5
#define VCOM_CONTROL_2                  0xC7
#define POWER_ON_SEQ_CONTROL            0xCB
#define POWER_CONTROL_A                 0xCD
#define POWER_CONTROL_B                 0xCF
#define NVMEM_WRITE                     0xD0
#define NVMEM_PROTECTION_KEY            0xD1
#define NVMEM_STATUS_READ               0xD2
#define READ_ID4                        0xD3
#define POSITIVE_GAMMA_CORRECTION       0xE0
#define NEGATIVE_GAMMA_CORRECTION       0xE1
#define DIGITAL_GAMMA_CONTROL_1         0xE2
#define DIGITAL_GAMMA_CONTROL_2         0xE3
#define DRIVER_TIMING_CONTROL_A         0xE8
#define DRIVER_TIMING_CONTROL_B         0xEA
#define POWER_ON_SEQUENCE				0xED
#define ENABLE_3_GAMMA_CONTROL          0xF2
#define INTERFACE_CONTROL               0xF6
#define PUMP_RATIO_CONTROL              0xF7

#endif /* _ILI9341_H_ */
