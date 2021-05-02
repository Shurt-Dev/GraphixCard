#include "lowMath.h"

short lowMath::sin(unsigned short x){

    int res = ((x<<SCALE_FACTOR) / PI) & 0x03FF;
    if(res > (1<<SCALE_FACTOR)-1){
        res &= ~(1<<SCALE_FACTOR);
        short res2 = (res*res)>>SCALE_FACTOR;
        res = (res - res2) << 2;
        res = ~res + 1;
    }else{
        short res2 = (res*res)>>SCALE_FACTOR;
        res = (res - res2) << 2;
    }

    return (short)res;
}