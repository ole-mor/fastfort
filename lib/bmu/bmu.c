// Basic math utilitis

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

// Basic geometry
// returns missing leg
float pytogorasL(float x, float y){
    float l = (x > y) ? x : y;
    float s = (x > y) ? y : x;
    return sqrtf(powf(l, 2) - powf(s, 2));
}

// returns hypotenus
float pytogorasH(float x, float y){
    return sqrtf(powf(x, 2) + powf(y, 2));
}


