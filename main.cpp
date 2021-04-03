#include "GraphiX.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

ISR(TIMER0_COMPA_vect){

    DDRC &= ~(1<<1); // disable pixels

    switch(lineCounter){
        case 23:
            CAN_DRAW;
            line = 0;
            cycleTracker = 0;
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
        DDRC &= ~(1<<PINC0);
        _delay_us(HSYNC);
        DDRC |= 1<<PINC0;
    }else{
        DDRC |= 1<<PINC0;
        _delay_us(HSYNC);
        DDRC &= ~(1<<PINC0);
    }
    done = 0;
}

ISR(TIMER0_COMPB_vect){
    unsigned char *thisLine = frame[line];
    for(unsigned char i = 0 ; i<WIDTH ; i++){
        DDRA = thisLine[i];
    }
    DDRA = 7;
}

int main(){
    for(unsigned char l = 0 ; l < HEIGHT ; l++){
        for(unsigned char i = 0 ; i < WIDTH ; i++){
            frame[l][i] = i^~l;
        }
    }

    MCUCR |= (1<<PUD);
    TCCR0A = 0x02;
    TCCR0B = 0x02;
    OCR0A = 159;
    OCR0B = 39;
    TIMSK0 = 0x02;

    PORTC |= 1<<1;
    PORTA = 0xFF;

    sei();
    
    lineIncrementations:
    lineCounter++;
    if(lineCounter > 318) lineCounter = 0;
    
    cycleTracker++;
    if(cycleTracker == 3){
        line++;
        cycleTracker = 0;
    }

    done = 1;

    while(done){}
    goto lineIncrementations;

    return 0;
}