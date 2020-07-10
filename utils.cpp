#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"

float val_limiter (float val, float min, float max) {
    float outVal = val;
    if (val < min) {
        outVal = min;
    }
    if (max < val) {
        outVal = max;
    }
    return outVal;
}

float rand_float (float minVal, float maxVal) {
    float outVal = NAN;
    if (minVal < maxVal) {
        outVal = ((maxVal - minVal)*(float)rand()/ RAND_MAX )+ minVal;
    }
    return outVal;
}

float dot_product (Vector_t* v1, Vector_t* v2) {
    float dot = 0.0;
    dot = (v1->x) * (v2->x) + (v1->y) * (v2->y) + (v1->z) * (v2->z);
    return dot;
}

Vector_t cross_product (Vector_t* a, Vector_t* b) {
    Vector_t v;
    v.x = a->y * b->z - a->z * b->y;
    v.y = -(a->x * b->z - a->z * b->x);
    v.z = a->x * b->y - a->y * b->x;
    return v;
}

float deg2radians (float degrees) {
    const float pi_on_180 = 4.0 * atan (1.0) / 180.0;
    return degrees * pi_on_180;
}

float radians2deg (float radians) {
    return radians * (180.0 / M_PI);
}

float norm (Vector_t* v) {
    float norm;
    norm = sqrt ((v->x) * (v->x) + (v->y) * (v->y));
    return norm;
}

float calc_angle_between_vectors (Vector_t* v1, Vector_t* v2) {
    //  betta rad  0.....3.14159
    float betta = 0.0, norm1, norm2, absBetta;
    float dotPr;
    Vector_t v3;
    norm1 = norm (v1);
    norm2 = norm (v2);
    if (0.0 == norm1 || 0.0 == norm2) {
        return 0.0;
    } else {
        dotPr = dot_product (v1, v2);
        absBetta = acos (dotPr / (norm1 * norm2));
        //scalar multiplication gives just module of  the angle.
        //vector multiplication gives the sign of the angle.
        v3 = cross_product (v1, v2);
        if ((0.0 == v3.x) && (0.0 == v3.y) && (0.0 == v3.z)) {
            betta = absBetta;
        } else {
            betta = sign (v3.z) * absBetta;
        }
        return betta;
    }
}

float sign (float inVal) {
    float outVal = 0;
    if (0.0 < inVal) {
        outVal = 1.0;
    }
    if (inVal < 0.0) {
        outVal = -1.0;
    }
    return outVal;
}
