#ifndef GRAPHIX_H
#define GRAPHIX_H   

#include "Colors.h"

#define F_CPU 20000000UL
//#define DEBUG

#define WIDTH 120
#define HEIGHT 120
#define TOTALPIXELS 14400
#define START_FRAME 23
#define INCLINE 40

#define HSYNC 0
#define FPORCH 1
#define BURST 2
#define REST 3
#define DRAW 4

#define STOP_HSYNC 12
#define START_DRAW_LINE 43

extern volatile unsigned short lineCounter;
extern volatile bool done, vsync, can_draw;
extern volatile unsigned char line, state;
extern unsigned char frame[HEIGHT][WIDTH];

#define CAN_CALCULATE !(lineCounter < INCLINE || line >= HEIGHT)

//Fills the whole screen with a color.
void fillScreen(unsigned char color=BLACK);
//Adds a value to each pixel.
void addScreen(char amount=1);
//Shifts the whole screen to the right by an amount.
void rShiftScreen(unsigned char amount=1);
//Shifts the whole screen to the left by an amount.
void lShiftScreen(unsigned char amount=1);
//Shifts the whole screen upwards by an amount.
void uShiftScreen(unsigned char amount=1);
//Shifts the whole screen downwards by an amount.
void dShiftScreen(unsigned char amount=1);
//Changes a single pixel
void setPixel(unsigned char x, unsigned char y, unsigned char color=BLACK);
//Draws a horizontal line.
void drawHLine(unsigned char line, unsigned char start, unsigned char end, unsigned char color=BLACK);
//Draws a vertical line.
void drawVLine(unsigned char column, unsigned char start, unsigned char end, unsigned char color=BLACK);
//Draw any line.
void drawLine(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char color=BLACK);
//Draws a hollow rectangle.
void drawRect(unsigned char xs, unsigned char ys, unsigned char xe, unsigned char ye, unsigned char color=BLACK);
//Draws a filled rectangle.
void drawBox(unsigned char xs, unsigned char ys, unsigned char xe, unsigned char ye, unsigned char color=BLACK);

#endif