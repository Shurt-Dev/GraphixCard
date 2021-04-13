#include "GraphiX.h"
#include "Colors.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>

volatile unsigned short lineCounter = 0;
volatile bool vsync = 0, done = 0, opovf = 0;
volatile unsigned char line = 0;
unsigned char frame[HEIGHT][WIDTH] = {0};

void setupTimer0(){
    TCCR0A = 0x02; // CTC
    TCCR0B = 0x02; // prescaler = 8
    OCR0A = 159;   // f = 15625
    OCR0B = 43;    // begin drawing 15 uS after int
    TIMSK0 = 0x02; // compA interrupt
}

ISR(TIMER0_COMPA_vect){

    lineCounter++;
    if(lineCounter > 318) lineCounter = 0;
    if(lineCounter>INCLINE) line += lineCounter&1;

    switch(lineCounter){
        case START_FRAME:
            CAN_DRAW;
            line=0;
            break;

        case 310:
            CANT_DRAW;
            break;

        case 313:
            vsync = 1;
            break;

        case 316:
            vsync = 0;
            break;
    }

    if(vsync){
        DDRD &= 127;
        _delay_us(HSYNC);
        DDRD |= 128;
    }else{
        DDRD |= 128;
        _delay_us(HSYNC);
        DDRD &= 127;
    }
    done = 0;
}

ISR(TIMER0_COMPB_vect){
    if(lineCounter < INCLINE || line >= HEIGHT){
        DDRA = 0;
    }else{
        unsigned char *thisLine = frame[line];
        for(unsigned char i = 0 ; i < WIDTH ; i++){
            DDRA = thisLine[i];
        }
    }
    DDRA = BLACK;
}

int main(){
    for(unsigned char l = 0 ; l < HEIGHT ; l++){
        for(unsigned char i = 0 ; i < WIDTH ; i++){
            frame[l][i] = BLACK;
        }
    }

    MCUCR |= (1<<PUD); //Disable pullup resistors

    setupTimer0();

    PORTA = 0xFF;

    #ifdef DEBUG
    DDRC = 1;
    PORTC = 1;
    drawBox(0,0,10,10,WHITE);
    PORTC = 0;
    #endif

    sei();

    processShit:

    if(CAN_CALCULATE){
    }

    done = 1;
    while(done){}
    goto processShit;

    return 0;
}