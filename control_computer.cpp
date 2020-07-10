#include "control_pid_computer.h"
#include "control_nn_computer.h"
#include "control_computer.h"

#include "utils.h"
#include "pid_params.h"
#include "rocket_params.h"


#include <math.h>


float max_incline = MAX_INCLINE_DEG;




bool calc_rocket_control_2d (
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
    float xError;
    float yError;
    float angleError;
    bool res=false;
    *Fjet = 0;
    *Fcorrect = 0;
    Vector_t desAngleVec={0,1,0};
    Vector_t rocketOrientation={-sin (curAlfaRad), cos (curAlfaRad), 0};
    xError = xTarget - curX;
    yError = yTarget - curY;
    angleError = calc_angle_between_vectors (&desAngleVec, &rocketOrientation);
#if NN_CONTROL
    res = control_neural_network (  xError,   yError, angleError,   curVx, curVy,   curOmega, Fjet, Fcorrect);
#endif
#if PID_CONTROL
    res = calc_rocket_pid_control_2d(
        xTarget,
        yTarget,
        ROCKET_LENGTH,
        GRAVITATIONAL_ACCELERATION,
        curX,
        curY,
        angleError,
        curVx,
        curVy,
        curOmega,
        ROCKET_MASS_KG,
        Fjet,
        Fcorrect);
#endif /*PID_CONTROL*/
    *Fjet = val_limiter(*Fjet, 0, MAX_F_JET);
    *Fcorrect = val_limiter (*Fcorrect, -MAX_F_CORRECT, MAX_F_CORRECT);
    return res;
}
