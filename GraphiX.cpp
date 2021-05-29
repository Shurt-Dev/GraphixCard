#include <avr/io.h>
#include <avr/pgmspace.h>
#include "GraphiX.h"
#include "lowMath.h"
#include "assets/sprites.h"

void setEnabled(const bool ena){
    enabled = ena;
}

void fillScreen(const unsigned char color){
    for(unsigned char l = 0; l < HEIGHT; l++){
        unsigned char *thisLine = frame[l];
        for(unsigned char i = 0; i < WIDTH ; i++){
            thisLine[i] = color;
        }
    }
}

void addScreen(const char amount){
    for(unsigned char l = 0; l < HEIGHT; l++){
        unsigned char *thisLine = frame[l];
        for(unsigned char i = 0; i < WIDTH ; i++){
            thisLine[i] += amount;
        }
    }
}

void rShiftScreen(const unsigned char amount){
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

void lShiftScreen(const unsigned char amount){
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

void uShiftScreen(const unsigned char amount){
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

void dShiftScreen(const unsigned char amount){
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

void setPixel(const unsigned char x, const unsigned char y, const unsigned char color){
    frame[y][x] = color;
}

void drawHLine(const unsigned char line, const unsigned char start, const unsigned char end, const unsigned char color){
    unsigned char *thisLine = frame[line];
    for(unsigned char i = start ; i < end ; i++) thisLine[i] = color;
}

void drawVLine(const unsigned char column, const unsigned char start, const unsigned char end, const unsigned char color){
    for(unsigned char i = start ; i < end ; i++) frame[i][column] = color;
}

void drawLine(const unsigned char x1, const unsigned char y1, const unsigned char x2, const unsigned char y2, const unsigned char color){
    int16_t dx = x2-x1;
    int16_t dy = y2-y1;
    #define abs(x) (x<0 ? -x : x)

    if(abs(dx) > abs(dy)){
        if(x2 > x1){
            dy = (dy << SCALE_FACTOR) / abs(dx);
            uint16_t yPos = y1 << SCALE_FACTOR;
            for(unsigned char i = x1 ; i < x2 ; i++){
                frame[yPos >> SCALE_FACTOR][i] = color;
                yPos += dy;
            }
        }else{
            dy = (dy << SCALE_FACTOR) / abs(dx);
            uint16_t yPos = y1 << SCALE_FACTOR;
            for(unsigned char i = x1 ; i > x2 ; i--){
                frame[yPos >> SCALE_FACTOR][i] = color;
                yPos += dy;
            }
        }
    }else{
        if(y2 > y1){
            dx = (dx << SCALE_FACTOR) / abs(dy);
            uint16_t xPos = x1 << SCALE_FACTOR;
            for(unsigned char i = y1 ; i < y2 ; i++){
                frame[i][xPos >> SCALE_FACTOR] = color;
                xPos += dx;
            }
        }else{
            dx = (dx << SCALE_FACTOR) / abs(dy);
            uint16_t xPos = x1 << SCALE_FACTOR;
            for(unsigned char i = y1 ; i > y2 ; i--){
                frame[i][xPos >> SCALE_FACTOR] = color;
                xPos += dx;
            }
        }
    }
}

void drawRect(const unsigned char xs, const unsigned char ys, const unsigned char xe, const unsigned char ye, const unsigned char color){
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

void drawBox(const unsigned char xs, const unsigned char ys, const unsigned char xe, const unsigned char ye, const unsigned char color){
    for(unsigned char l = ys ; l < ye ; l++){
        unsigned char *thisLine = frame[l];
        for(unsigned char i = xs ; i < xe ; i++){
            thisLine[i] = color;
        }
    }
}

void drawCircle(const unsigned char xc, const unsigned char yc, const unsigned char radius, const unsigned char color){
    #define GON 12
    unsigned char points[GON][2] = {0};    
    for(unsigned char i = 0 ; i < GON ; i++){
        points[i][0] = xc + (((long)(radius << SCALE_FACTOR) * (long)low_cos((PIx2/GON) * i))>>(SCALE_FACTOR<<1));
        points[i][1] = yc + (((long)(radius << SCALE_FACTOR) * (long)low_sin((PIx2/GON) * i))>>(SCALE_FACTOR<<1));
    }
    for(unsigned char i = 1 ; i < GON ; i++){
        drawLine(points[i-1][0],points[i-1][1],points[i][0],points[i][1],color);
    }
    drawLine(points[GON-1][0],points[GON-1][1],points[0][0],points[0][1],color);
}

void drawSprite(const unsigned char x, const unsigned char y, const unsigned char spritID, const unsigned char scale){
    if(!scale){
        for(unsigned char i = 0 ; i < 8 ; i++){
            for(unsigned char l = 0 ; l < 8 ; l++){
                unsigned char pixel = pgm_read_byte(&archer[i][l]);
                if(pixel){
                    frame[x+i][y+l] = pixel;
                }
            }
        }
    }else{
        for(unsigned char i = 0 ; i < 8 ; i++){
            for(unsigned char l = 0 ; l < 8 ; l++){
                unsigned char pixel = pgm_read_byte(&archer[i][l]);
                if(pixel){
                    frame[x+2*i][y+2*l] = pixel;
                    frame[x+2*i+1][y+2*l] = pixel;
                    frame[x+2*i][y+2*l+1] = pixel;
                    frame[x+2*i+1][y+2*l+1] = pixel;
                }
            }
        }
    }
}