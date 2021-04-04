#ifndef GRAPHIX_H
#define GRAPHIX_H   

#pragma region global_variables
#define F_CPU 20000000UL

#define HSYNC 5   

#define WIDTH 123
#define HEIGHT 95

#define CAN_DRAW (TIMSK0 |= 1<<OCIE0B)
#define DRAW_CAN (TIMSK0 & 1<<OCIE0B)
#define CANT_DRAW (TIMSK0 &= ~(1<<OCIE0B))

extern volatile unsigned short lineCounter;
extern volatile bool vsync, done, opovf;
extern volatile unsigned char line, cycleTracker;
extern unsigned char frame[HEIGHT][WIDTH];
#pragma endregion

void fillScreen(unsigned char color=7);
void addScreen(char amount=1);
#endif