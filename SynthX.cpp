#include <avr/io.h>
#include "SynthX.h"

void setupVoice2(){
    TCCR2A = 0x12;
    TCCR2B = 0x07;
    OCR0A = 255;
    DDRD |= 1<<PD6;
}