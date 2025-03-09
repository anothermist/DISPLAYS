#ifndef __ST7920_SERIAL_H
#define __ST7920_SERIAL_H


#include "stdint.h"

// A replacement for SPI_TRANSMIT
void SendByteSPI(uint8_t byte);


// Send the command to the LCD
void ST7920_SendCmd (uint8_t cmd);


// send the data to the LCD
void ST7920_SendData (uint8_t data);


/* send the string to the LCD
 * 'row' = starting ROW for the string (from 0 to 3)
 * 'col' = starting COL for the string (from 0 to 7)
 */
void ST7920_SendString(int row, int col, char* string);


/* ENABLE or DISABLE the graphic mode
 * enable =1 --> graphic mode enabled
 */
void ST7920_GraphicMode (int enable);

// clear screen in any mode
void ST7920_Clear();

// Draw bitmap on the display
void ST7920_DrawBitmap(const unsigned char* graphic);


// Update the display with the selected graphics
void ST7920_Update(void);


// Initialize the display
void ST7920_Init (void);


/* Common functions used
 * in other LCDs also
 */


// Set a pixel on the display
void SetPixel(uint8_t x, uint8_t y);


// draw line from (X0, Y0) to (X1, Y1)
void DrawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);


// draw rectangle from (X,Y) w- width, h- height
void DrawRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h);


// draw filled rectangle
void DrawFilledRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h);


// draw circle with centre (X0, Y0) and radius= radius
void DrawCircle(uint8_t x0, uint8_t y0, uint8_t radius);


// Draw Filled Circle with centre (X0, Y0) and radius= r

void DrawFilledCircle(int16_t x0, int16_t y0, int16_t r);

// Draw Traingle with coordimates (x1, y1), (x2, y2), (x3, y3)
void DrawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3);

// Draw Filled Traingle with coordimates (x1, y1), (x2, y2), (x3, y3)
void DrawFilledTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3);

#endif
