#include "control_computer.h"

#include "control_pid_computer.h"

#include "utils.h"
#include "pid_params.h"
#include "rocket_params.h"

#include <math.h>



#if 0
float kpa = (FSUPP * 0.5);
float kda = (FSUPP * 4);


float kpy = (FSUPP * 0.5);
float kdy = (FSUPP * 4);
float kiy = (FSUPP * 0.0);

float kpx = (FSUPP * 0.5);
float kdx = (FSUPP * 4);
float kix = (FSUPP * 0.0);
#endif 

float kpx = 43555.6;
float kdx = 348444.5;
float kpy = 43555.6;
float kdy = 0.0;
float kpa = 87111.1;
float kda = 174222.2;
//kpx=  43555.6; kdx = 348444.5; kpy=  43555.6; kdy=  0.0; kpa = 87111.1; kda=174222.2;
//kpx = 43555.6; kdx = 348444.5; kpy = 43555.6; kdy = 0.0; kpa = 130666.7; kda = 261333.3;
//kpx = 32666.7; kdx=392000.0; kpy= 32666.7; kdy=     0.0; kpa= 98000.0; kda=294000.0;


bool calc_rocket_pid_control_2d (
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
    float *Fjet,
    float *Fcorrect) {
    bool res=false;
    float yError;
    float fSupp = roketMassKg * GravitationalAcceleration;
    float xError = xTarget - curX;
    float desAngle = -xError * kpx + curVx * kdx;
    max_incline = val_limiter(fabs(xError),0, MAX_INCLINE_DEG);
    float desAngleLim = val_limiter (desAngle, -DEGREESTORADIANS(max_incline), DEGREESTORADIANS(max_incline));
    Vector_t desAngleVec, rocketOrientation;
    float angleError, kdy;
    desAngleVec.x = -sin (desAngleLim);
    desAngleVec.y = cos (desAngleLim);
    desAngleVec.z = 0;
    kdy = KDYFAR;
    rocketOrientation.x = -sin (curAlfaRad);
    rocketOrientation.y = cos (curAlfaRad);
    rocketOrientation.z = 0;
    angleError = calc_angle_between_vectors (&desAngleVec, &rocketOrientation);
    *Fcorrect = angleError * kpa + curOmega * kda;
    yError = yTarget - curY;
    if (yError < ((rocketLength / 2) + 3)) {
        kdy = KDYNEAR;
    }
    float xCorrectFjet = 0.0;
    *Fjet = (yError) * kpy - (curVy) *kdy ;
    *Fjet = val_limiter (*Fjet, 0, MAX_F_JET);
    *Fjet += xCorrectFjet;
    *Fjet = val_limiter(*Fjet, 0, MAX_F_JET);
    *Fcorrect = val_limiter (*Fcorrect, -MAX_F_CORRECT, MAX_F_CORRECT);
    return res;
}
