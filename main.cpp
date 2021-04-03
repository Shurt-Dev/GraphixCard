#include "GraphiX.h"

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>


ISR(TIMER0_COMPA_vect){

    DDRC &= ~(1<<1); // disable pixels

    lineCounter++;
    if(lineCounter > 318) lineCounter = 0;

    switch(lineCounter){
        case 23:
            CAN_DRAW;
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
}

ISR(TIMER0_COMPB_vect){
    for(unsigned char i = 0 ; i<width ; i++){
        DDRA = frame[0][i];
    }
    DDRA = 7;
}

int main(){

    for(unsigned char i = 0 ; i<width ; i++) frame[0][i] = 7*(i&1);

    MCUCR |= (1<<PUD);
    TCCR0A = 0x02;
    TCCR0B = 0x02;
    OCR0A = 159;
    OCR0B = 39;
    TIMSK0 = 0x02;

    PORTC |= 1<<1;
    PORTA = 0xFF;

    sei();
    
    while(1){

    }

    return 0;
}