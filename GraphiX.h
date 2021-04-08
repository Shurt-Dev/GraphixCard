#ifndef GRAPHIX_H
#define GRAPHIX_H   

#include "Colors.h"

#define F_CPU 20000000UL
#define DEBUG

#define HSYNC 4
#define WIDTH 120
#define HEIGHT 120
#define START_FRAME 23
#define INCLINE 40

#define CAN_DRAW (TIMSK0 |= 1<<OCIE0B)
#define CANT_DRAW (TIMSK0 &= ~(1<<OCIE0B))
#define CAN_CALCULATE !(lineCounter < INCLINE || line >= HEIGHT)

extern volatile unsigned short lineCounter;
extern volatile bool vsync, done, opovf;
extern volatile unsigned char line;
extern unsigned char frame[HEIGHT][WIDTH];

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
void drawLine(unsigned char xs, unsigned char ys, unsigned char xe, unsigned char ye, unsigned char color=BLACK);
//Draws a hollow rectangle.
void drawRect(unsigned char xs, unsigned char ys, unsigned char xe, unsigned char ye, unsigned char color=BLACK);
//Draws a filled rectangle.
void drawBox(unsigned char xs, unsigned char ys, unsigned char xe, unsigned char ye, unsigned char color=BLACK);

#endif