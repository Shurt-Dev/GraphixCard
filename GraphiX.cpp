#include <avr/io.h>
#include "GraphiX.h"
#include <math.h>

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

void rShiftScreen(unsigned char amount){
    for(unsigned char l = 0; l < HEIGHT; l++){
        unsigned char *thisLine = frame[l];
        for(unsigned char i = WIDTH; i > 0 ; i--){
            if(i - amount < 0){
                thisLine[i] = thisLine[WIDTH-amount+i];
            }else{
                thisLine[i] = thisLine[i-amount];
            }
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

void drawVLine(unsigned char column, unsigned char start, unsigned char end, unsigned char color){
    for(unsigned char i = start ; i < end ; i++) frame[i][column] = color;
}

void drawLine(unsigned char xs, unsigned char ys, unsigned char xe, unsigned char ye, unsigned char color){

}

void drawRect(unsigned char xs, unsigned char ys, unsigned char xe, unsigned char ye, unsigned char color){
    unsigned char *firstLine = frame[ys];
    unsigned char *secondline = frame[ye];
    for(unsigned char i = xs ; i < xe ; i++){
        firstLine[i] = color;
        secondline[i] = color;
    }
    for(unsigned char i = ys+1 ; i < ye ; i++){
        frame[i][xs] = color;
        frame[i][xe] = color;
    }
}

void drawBox(unsigned char xs, unsigned char ys, unsigned char xe, unsigned char ye, unsigned char color){
    for(unsigned char l = ys ; l < ye ; l++){
        unsigned char *thisLine = frame[l];
        for(unsigned char i = xs ; i < xe ; i++){
            thisLine[i] = color;
        }
    }
}