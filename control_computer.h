#pragma once



#define NN_CONTROL 0
#define PID_CONTROL 1
extern float max_incline;

bool calc_rocket_control_2d(
    float xTarget,
    float yTarget,
    float rocketLength,
    float GravitationalAcceleration,
    float curX,
    float curY,
    float curAlfaRad,
    float curVx,
    float curVy,
    float curOmega,
    float roketMassKg,
    float* Fjet,
    float* Fcorrect);