#include "GraphiX.h"
#include "Colors.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>

volatile unsigned short lineCounter = 0;
volatile bool done = 0, vsync = 0, can_draw = 0;
volatile unsigned char line = 0, state = FPORCH;
unsigned char frame[HEIGHT][WIDTH] = {0};

void setupTimer0(){
    TCCR0A = 0x02; // CTC
    TCCR0B = 0x02; // prescaler = 8
    OCR0A = 159;   // f = 15625 Hz
    OCR0B = TIMING_START_DRAW_LINE;    // begin drawing 15 uS after int
    TIMSK0 = 0x06; // compA interrupt
}

ISR(TIMER0_COMPA_vect){

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

    OCR0B = TIMING_STOP_HSYNC;
    state = FPORCH;
    done = 0;
}

ISR(TIMER0_COMPB_vect){

    switch(state){
        case FPORCH:
            if(vsync){
                DDRD |= 128;
            }else{
                DDRD &= 127;
            }
            #ifndef GREYSCALE
            if(can_draw){
                OCR0B = TIMING_START_BURST;
                state = START_BURST;
            }else{
                OCR0B = TIMING_START_DRAW_LINE;
                state = DRAW_LINE;
            }
            #endif
            #ifdef GREYSCALE
            OCR0B = TIMING_START_DRAW_LINE;
            state = DRAW_LINE;
            #endif
            break;

        case START_BURST:
            DDRA = BURST;
            OCR0B = TIMING_STOP_BURST;
            state = STOP_BURST;
            break;

        case STOP_BURST:
            DDRA = BLACK;
            OCR0B = TIMING_START_DRAW_LINE;
            state = DRAW_LINE;
            break;

        case DRAW_LINE:
            if(can_draw){
                unsigned char *thisLine = frame[line];
                for(unsigned char i = 0 ; i < WIDTH ; i++){
                    DDRA = thisLine[i];
                }
            }else{
                DDRA = WHITE;
            }
            DDRA = BLACK;
            break;
    }
}

int main(){
    for(unsigned char l = 0 ; l < HEIGHT ; l++){
        for(unsigned char i = 0 ; i < WIDTH ; i++){
            //frame[l][i] = (unsigned char)((16.0/120) * i) |  (unsigned char)((16.0/120) * l)<<4;
            frame[l][i] = BLACK;
        }
    }

    MCUCR |= (1<<PUD); //Disable pullup resistors

    setupTimer0();

    PORTA = 0xFF;

    #ifdef DEBUG
    DDRC = 1;
    PORTC = 1;
    drawLine(59,59,99,89,WHITE);
    PORTC = 0;
    #endif

    sei();
    float bob=0;
    int bab=0;
    processShit:

    if(CAN_CALCULATE){
        if(bab&1){
        drawLine(59,59,20*cos(bob)+59,20*sin(bob)+59,BLACK);
        }else{
        bob += 0.01;
        drawLine(59,59,20*cos(bob)+59,20*sin(bob)+59,WHITE);}bab++;
    }

    done = 1;
    while(done){}
    goto processShit;

    return 0;
}