// Basic geometry 2D

#include <math.h>

float pytogoras_l(float x, float y){
    float l = (x > y) ? x : y;
    float s = (x > y) ? y : x;
    return sqrtf(powf(l, 2) - powf(s, 2));
}

float pytogoras_h(float x, float y){
    return sqrtf(powf(x, 2) + powf(y, 2));
}

float triangle_area(float a, float b, float c_angle){
    float A = (1/2)*(a*b*sin(c_angle));
}

float triangle_area_s(float a, float b, float c){
    float R = (a*b*c)/(sqrtf((a+b+c)*(b+c-a)*(c+a-b)*(a+b-c)));
    float A = (a*b*c)/(4*R);
    return A;
}

float circle_circumfrance(float r, float pi = 3.14159265f){
    return 2*pi*r;
}

float circle_area(float r, float pi = 3.14159265f){
    return pi*pow(r, 2);
}

