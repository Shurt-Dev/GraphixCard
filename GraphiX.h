#define F_CPU 20000000UL

#define HSYNC 5   

#define WIDTH 123
#define HEIGHT 95

#define CAN_DRAW TIMSK0 |= 1<<OCIE0B
#define CANT_DRAW TIMSK0 &= ~(1<<OCIE0B)

volatile unsigned short lineCounter = 0;
volatile bool vsync = 0, done = 0;
volatile unsigned char line = 0, cycleTracker=0;
unsigned char frame[HEIGHT][WIDTH] = {0};
