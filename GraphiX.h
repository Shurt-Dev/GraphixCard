#define F_CPU 20000000UL

#define BACK_PORCH 2
#define FRONT_PORCH 5      //us
#define HSYNC 5   

#define width 114
#define height 100

#define CAN_DRAW TIMSK0 |= 1<<OCIE0B
#define CANT_DRAW TIMSK0 &= ~(1<<OCIE0B)

volatile unsigned short lineCounter = 0;  // 0b DVXXXXXX XXXXXXXX
volatile bool vsync = 0;

unsigned char frame[height][width] = {0};