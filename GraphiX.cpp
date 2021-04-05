#include <avr/io.h>
#include "GraphiX.h"

void fillScreen(unsigned char color){
    for(unsigned char l = 0; l < HEIGHT; l++){
        unsigned char *thisLine = frame[l];
        for(unsigned char i = 0; i < WIDTH ; i++){
            thisLine[i] = color;
        }
    }
}

void addScreen(char amount){
    for(unsigned char l = 0; l < HEIGHT; l++){
        unsigned char *thisLine = frame[l];
        for(unsigned char i = 0; i < WIDTH ; i++){
            thisLine[i] += amount;
        }
    }
}

void setPixel(unsigned char x, unsigned char y, unsigned char color){
    frame[y][x] = color;
}

void drawHLine(unsigned char line, unsigned char start, unsigned char end, unsigned char color){
    unsigned char *thisLine = frame[line];
    for(unsigned char i = start ; i < end ; i++) thisLine[i] = color;
}