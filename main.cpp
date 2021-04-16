#include "GraphiX.h"
#include "Colors.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>

volatile unsigned short lineCounter = 0;
volatile bool done = 0, vsync = 0, can_draw = 0;
volatile unsigned char line = 0, state = HSYNC;
unsigned char frame[HEIGHT][WIDTH] = {0};

void setupTimer0(){
    TCCR0A = 0x02; // CTC
    TCCR0B = 0x02; // prescaler = 8
    OCR0A = 159;   // f = 15625 Hz
    OCR0B = START_DRAW_LINE;    // begin drawing 15 uS after int
    TIMSK0 = 0x06; // compA interrupt
}

ISR(TIMER0_COMPA_vect){

    #ifdef DEBUG
    PORTC = 1;
    #endif

    lineCounter++;
    if(lineCounter > 318) lineCounter = 0;
    if(lineCounter>INCLINE) line += lineCounter&1;
    if(line >= HEIGHT) can_draw = 0;

    switch(lineCounter){
        case 23:
            line=0;
            break;

        case INCLINE:
            can_draw = 1;
            break;

        case 312:
            vsync = 1;
            break;

        case 316:
            vsync = 0;
            break;
    }

    if(vsync){
        DDRD &= 127;
    }else{
        DDRD |= 128;
    }
    OCR0B = STOP_HSYNC;
    state = FPORCH;
    done = 0;

    #ifdef DEBUG
    PORTC = 1;
    #endif
}

ISR(TIMER0_COMPB_vect){
    #ifdef DEBUG
    PORTC = 1;
    #endif

    switch(state){
        case FPORCH:
            if(vsync){
                DDRD |= 128;
            }else{
                DDRD &= 127;
            }
            OCR0B = START_DRAW_LINE;
            state = DRAW;
            DDRA = BLACK;
            break;

        case BURST:
            break;

        case DRAW:
            if(can_draw){
                unsigned char *thisLine = frame[line];
                for(unsigned char i = 0 ; i < WIDTH ; i++){
                    DDRA = thisLine[i];
                }
            }else{
                DDRA = WHITE;
            }
            DDRA = BLACK;
            state = HSYNC;
            break;
    }

    #ifdef DEBUG
    PORTC = 0;
    #endif
}

int main(){
    for(unsigned char l = 0 ; l < HEIGHT ; l++){
        for(unsigned char i = 0 ; i < WIDTH ; i++){
            frame[l][i] = l+i;
        }
    }

    MCUCR |= (1<<PUD); //Disable pullup resistors

    setupTimer0();

    PORTA = 0xFF;

    #ifdef DEBUG
    DDRC = 1;
    PORTC = 1;
    PORTC = 0;
    #endif
    drawBox(0,0,10,10,WHITE);

    sei();

    processShit:

    if(CAN_CALCULATE){
        dShiftScreen();
    }

    done = 1;
    while(done){}
    goto processShit;

    return 0;
}