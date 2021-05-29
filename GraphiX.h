#ifndef GRAPHIX_H
#define GRAPHIX_H   

#include "Colors.h"

//#define DEBUG
//#define COLOR_PALETTE
//#define GREYSCALE

#define WIDTH 120
#define HEIGHT 120
#define TOTALPIXELS 14400
#define START_FRAME 23
#define INCLINE 40

#define FPORCH 0
#define START_BURST 1
#define STOP_BURST 2
#define DRAW_LINE 3

#define TIMING_STOP_HSYNC 15
#define TIMING_START_DRAW_LINE 40

extern volatile unsigned short lineCounter;
extern volatile bool done, vsync, can_draw, enabled;
extern volatile unsigned char line, state;
extern unsigned char frame[HEIGHT][WIDTH];

#define CAN_CALCULATE (!can_draw)

//enables display, disabling display yields display time to calculations
void setEnabled(const bool ena);
//Fills the whole screen with a color.
void fillScreen(const unsigned char color=BLACK);
//Adds a value to each pixel.
void addScreen(const char amount=1);
//Shifts the whole screen to the right by an amount.
void rShiftScreen(const unsigned char amount=1);
//Shifts the whole screen to the left by an amount.
void lShiftScreen(const unsigned char amount=1);
//Shifts the whole screen upwards by an amount.
void uShiftScreen(const unsigned char amount=1);
//Shifts the whole screen downwards by an amount.
void dShiftScreen(const unsigned char amount=1);
//Changes a single pixel
void setPixel(const unsigned char x, const unsigned char y, const unsigned char color=BLACK);
//Draws a horizontal line.
void drawHLine(const unsigned char line, const unsigned char start, const unsigned char end, const unsigned char color=BLACK);
//Draws a vertical line.
void drawVLine(const unsigned char column, const unsigned char start, const unsigned char end, const unsigned char color=BLACK);
//Draw any line.
void drawLine(const unsigned char x1, const unsigned char y1, const unsigned char x2, const unsigned char y2, const unsigned char color=BLACK);
//Draws a hollow rectangle.
void drawRect(const unsigned char xs, const unsigned char ys, const unsigned char xe, const unsigned char ye, const unsigned char color=BLACK);
//Draws a filled rectangle.
void drawBox(const unsigned char xs, const unsigned char ys, const unsigned char xe, const unsigned char ye, const unsigned char color=BLACK);
//Draws a circle
void drawCircle(const unsigned char xc, const unsigned char yc, const unsigned char radius, const unsigned char color=BLACK);
//Draws a sprite
void drawSprite(const unsigned char x, const unsigned char y, const unsigned char spritID, const unsigned char scale=0);

#endif