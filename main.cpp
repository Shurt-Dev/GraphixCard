#include "GraphiX.h"
#include "Colors.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned short lineCounter = 0;
volatile bool vsync = 0, done = 0, opovf = 0;
volatile unsigned char line = 0;
unsigned char frame[HEIGHT][WIDTH] = {0};

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
        DDRC = 0;
    }else{
        unsigned char *thisLine = frame[line];
        for(unsigned char i = 0 ; i < WIDTH ; i++){
            DDRC = thisLine[i];
        }
    }
    DDRC = BLACK;
}

int main(){
    for(unsigned char l = 0 ; l < HEIGHT ; l++){
        for(unsigned char i = 0 ; i < WIDTH ; i++){
            frame[l][i] = BLACK;
        }
    }

    MCUCR |= (1<<PUD);
    TCCR0A = 0x02;
    TCCR0B = 0x02;
    OCR0A = 159;
    OCR0B = 43;
    TIMSK0 = 0x02;

    PORTC = 0xFF;

    #ifdef DEBUG
    DDRA = 0xFF;
    PORTA = 128;
    drawBox(30,30,90,90,WHITE);
    PORTA = 0;
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