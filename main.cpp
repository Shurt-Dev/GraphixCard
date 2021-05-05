#include "GraphiX.h"
#include "Colors.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "lowMath.h"

volatile unsigned short lineCounter = 0;
volatile bool done = 0, vsync = 0, can_draw = 0, enabled = 1;
volatile unsigned char line = 0, state = FPORCH;
unsigned char frame[HEIGHT][WIDTH] = {0};
unsigned char testMatrix[16][16];

void setupTimer3(){
    TCCR3B = 0x0A; // CTC + prescaler = 8
    OCR3AL = 159;   // f = 15625 Hz
    OCR3BL = TIMING_START_DRAW_LINE;    // begin drawing 15 uS after int
    TIMSK3 = 0x06; // compA + compB interrupt
}

ISR(TIMER3_COMPA_vect){

    lineCounter++;
    if(lineCounter > 318) lineCounter = 0;
    if(lineCounter>INCLINE) line += lineCounter&1;
    if(line >= HEIGHT) can_draw = 0;

    switch(lineCounter){
        case 23:
            line=0;
            break;

        case INCLINE:
            can_draw = enabled;
            break;

        case 312:
            vsync = 1;
            break;

        case 316:
            vsync = 0;
            done = 0;
            break;
    }

    if(!vsync){
        DDRD |= 0x01;
    }else{
        DDRD &= 0xFE;
    }

    OCR3BL = TIMING_STOP_HSYNC;
    state = FPORCH;
}

ISR(TIMER3_COMPB_vect){
    //PORTC = 1;
    switch(state){
        case FPORCH:
            if(!vsync){
                DDRD &= 0xFE;
            }else{
                DDRD |= 0x01;
            }
            #ifndef GREYSCALE
            if(can_draw){
                OCR3BL = TIMING_START_BURST;
                state = START_BURST;
            }else{
                OCR3BL = TIMING_START_DRAW_LINE;
                state = DRAW_LINE;
            }
            #endif
            #ifdef GREYSCALE
            OCR3BL = TIMING_START_DRAW_LINE;
            state = DRAW_LINE;
            #endif
            break;

        case START_BURST:
            DDRA = BURST;
            OCR3BL = TIMING_STOP_BURST;
            state = STOP_BURST;
            break;

        case STOP_BURST:
            DDRA = BLACK;
            OCR3BL = TIMING_START_DRAW_LINE;
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
    //PORTC = 0;
}

int main(){
    unsigned char bob = 0;
    for(unsigned char l = 0 ; l < 16 ; l++){
        for(unsigned char i = 0 ; i < 16 ; i++){
            testMatrix[l][i] = bob;
            bob++;
        }
    }
    for(unsigned char l = 0 ; l < HEIGHT ; l++){
        for(unsigned char i = 0 ; i < WIDTH ; i++){
            frame[l][i] = testMatrix[(unsigned char)(l / 7.5)][(unsigned char)(i / 7.5)];
            //frame[l][i] = l+i;
        }
    }

    MCUCR |= (1<<PUD); //Disable pullup resistors

    setupTimer3();

    PORTA = 0xFF;

    #ifdef DEBUG
    DDRC = 1;
    PORTC = 1;
    drawLine(59,59,99,89,WHITE);
    PORTC = 0;
    #endif

    sei();

    processShit:

    if(CAN_CALCULATE){
        setEnabled(!enabled);
    }

    done = 1;
    while(done){}
    goto processShit;

    return 0;
}