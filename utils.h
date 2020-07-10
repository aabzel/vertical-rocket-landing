#pragma once

#define M_PI 3.14159

#define DEGREESTORADIANS(angleDegrees) ((angleDegrees) * M_PI / 180.0)
#define RADIANSTODEGREES(angleRadians) ((angleRadians) * 180.0 / M_PI)

typedef struct xVector_t {
    float x;
    float y;
    float z;
} Vector_t;

float sign(float inVal);
float val_limiter(float val, float min, float max);
float calc_angle_between_vectors (Vector_t* v1, Vector_t* v2) ;
float rand_float(float minVal, float maxVal);
