#pragma once

#define DEPLOY_FJET_CORRECT 0

extern float kpy ;
extern float kdy ;
extern float kiy ;

extern float kpx; 
extern float kdx;
extern float kix;

extern float kpa;
extern float kda;

bool calc_rocket_pid_control_2d(
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