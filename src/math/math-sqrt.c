#include "math/math-sqrt.h"

float fast_inv_sqrt(float x) {
    const float threehalfs = 1.5F;
    float y = x;
    long i = *(long*)&y;                        // bit-level hacking, float to int
    i = 0x5f3759df - (i >> 1);                  // magic number and bit shift
    y = *(float*)&i;                            // int to float
    y = y * (threehalfs - (x * 0.5F * y * y));  // Newton's method
    return y;
}

float sqrt_optimized(float number) {
    if (number > 0.0f)
    {   
        float res = 1.0f / fast_inv_sqrt(number);
        return res;
    }
    else
        return 0.0f;
}