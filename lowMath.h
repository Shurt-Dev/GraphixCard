#ifndef LOWMATH_H
#define LOWMATH_H

#ifndef SCALE_FACTOR
#define SCALE_FACTOR 9
#endif

#ifndef PI
//For a scale factor of 9 (ie : pi * 512)
#define PIx2 3216
#define PI 1608
#define PIx3d2 2412
#define PId2 804
#endif

#define toInt(x) (x>>SCALE_FACTOR)
//sin function using fixed point and quadratic approximation
int low_sin(const unsigned int x);

//cos function using fixed point and quadratic approximation
#define low_cos(x) low_sin((x) + PId2) 

//tan function using fixed point and quadratic approximation
//#define low_tan(x) 0

#endif