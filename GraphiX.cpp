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
        for(unsigned char loops = 0 ; loops < amount ; loops++){
            unsigned char *thisLine = frame[l];
            unsigned char bufferPixel = thisLine[WIDTH-1];
            for(unsigned char i = WIDTH-1 ; i > 0 ; i--){
                thisLine[i] = thisLine[i-1];
            }
            thisLine[0] = bufferPixel;
        }
    }
}

void lShiftScreen(unsigned char amount){
    for(unsigned char l = 0; l < HEIGHT; l++){
        for(unsigned char loops = 0 ; loops < amount ; loops++){
            unsigned char *thisLine = frame[l];
            unsigned char bufferPixel = thisLine[0];
            for(unsigned char i = 0 ; i < WIDTH-1 ; i++){
                thisLine[i] = thisLine[i+1];
            }
            thisLine[WIDTH-1] = bufferPixel;
        }
    }
}

void uShiftScreen(unsigned char amount){
    for(unsigned char i = 0; i < WIDTH; i++){
        for(unsigned char loops = 0 ; loops < amount ; loops++){
            unsigned char bufferPixel = frame[0][i];
            for(unsigned char l = 0 ; l < HEIGHT-1 ; l++){
                frame[l][i] = frame[l+1][i];
            }
            frame[HEIGHT-1][i] = bufferPixel;
        }
    }
}

void dShiftScreen(unsigned char amount){
    for(unsigned char i = 0; i < WIDTH; i++){
        for(unsigned char loops = 0 ; loops < amount ; loops++){
            unsigned char bufferPixel = frame[HEIGHT-1][i];
            for(unsigned char l = HEIGHT-1 ; l > 0 ; l--){
                frame[l][i] = frame[l-1][i];
            }
            frame[0][i] = bufferPixel;
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

void drawLine(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char color){
    float dx = x2>x1 ? x2-x1 : x1-x2;
    float dy = y2>y1 ? y2-y1 : y1-y2;

    if(dx > dy){
        if(x2 > x1){
            dy = (y2-y1)/dx;
            float yPos = y1;
            for(unsigned char i = x1 ; i < x2 ; i++){
                frame[(unsigned char) yPos][i] = color;
                yPos += dy;
            }
        }else{
            dy = (y2-y1)/dx;
            float yPos = y1;
            for(unsigned char i = x1 ; i > x2 ; i--){
                frame[(unsigned char) yPos][i] = color;
                yPos += dy;
            }
        }
    }else{
        if(y2 > y1){
            dx = (x2-x1)/dy;
            float xPos = x1;
            for(unsigned char i = y1 ; i < y2 ; i++){
                frame[i][(unsigned char)xPos] = color;
                xPos += dx;
            }
        }else{
            dx = (x2-x1)/dy;
            float xPos = x1;
            for(unsigned char i = y1 ; i > y2 ; i--){
                frame[i][(unsigned char)xPos] = color;
                xPos += dx;
            }
        }
    }
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