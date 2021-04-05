#ifndef GRAPHIX_H
#define GRAPHIX_H   

#pragma region global_variables
#define F_CPU 20000000UL

//#define DEBUG

#define HSYNC 4
#define WIDTH 123
#define HEIGHT 123
#define START_FRAME 23
#define INCLINE 40

#define CAN_DRAW (TIMSK0 |= 1<<OCIE0B)
#define CANT_DRAW (TIMSK0 &= ~(1<<OCIE0B))
#define CAN_CALCULATE !(lineCounter < INCLINE || line >= HEIGHT)

extern volatile unsigned short lineCounter;
extern volatile bool vsync, done, opovf;
extern volatile unsigned char line;
extern unsigned char frame[HEIGHT][WIDTH];
#pragma endregion

void fillScreen(unsigned char color=7);
void addScreen(char amount=1);
void setPixel(unsigned char x, unsigned char y, unsigned char color=7);

#endif