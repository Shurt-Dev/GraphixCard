#ifndef LOWMATH_H
#define LOWMATH_H

namespace lowMath{

    #ifndef SCALE_FACTOR
    #define SCALE_FACTOR 9
    #endif

    #ifndef PI
    //For a scale factor of 9 (ie : pi * 512)
    #define PIx2 3216
    #define PI 1608
    #define PIx3d2 2412
    #endif

    #define toInt(x) (x>>SCALE_FACTOR)
    //sin function using fixed point and quadratic approximation
    short sin(unsigned short x);
    //cos function using fixed point and quadratic approximation
    #define cos(x) lowMath::sin(x + PIx3d2) 

}

#endif