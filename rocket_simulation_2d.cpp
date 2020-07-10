#include "rocket_simulation_2d.h"

#include <float.h>
#include <math.h>

#include "init_conditions.h"
#include "math_model_rocket_2d.h"
#include "control_computer.h"
#include "rocket_params.h"
#include "target_state.h"

#define MAX_Y_ERROR 1.0


bool simulate_rorket (float max_time, 
    float* xError, float* yError,       float* aError, 
    float* sumXError, float* sumAError, float* spentFule){
    *xError = FLT_MAX;
    *yError = FLT_MAX;
    *aError = FLT_MAX;
    *sumXError = 0.0f;
    *sumAError = 0.0f;
    *spentFule = 0.0;
    float angleError;
    float curTime = 0.0f;
    float Fjet = 0.0f;
    float Fcorrect = 0.0f;
    float curX = X0;
    float curY = Y0;
    float curVx = VX0;
    float curVy = VY0;
    float curOmega = OMEGA0;
    float curAlfaRad = ALFA_RAD_0;

    float newCurX = 0.0f;
    float newCurY = 0.0f;
    float newCurVx = 0.0f;
    float newCurVy = 0.0f;
    float newCurOmega = 0.0f;
    float newAlfaRad = 0.0f;
    float newAlfaRadErr = 0.0f;

    float periodSec = 0.05f;
    while (curTime < max_time) {
        calc_rocket_control_2d (
            X_TARGET,
            Y_TARGET,
            ROCKET_LENGTH,
            GRAVITATIONAL_ACCELERATION,
            curX,
            curY,
            curAlfaRad,
            curVx,
            curVy,
            curOmega,
            ROCKET_MASS_KG,
            &Fjet,
            &Fcorrect);

        rocket_math_model_2d(ROCKET_LENGTH, GRAVITATIONAL_ACCELERATION,
            curX, curY, curAlfaRad, curVx, curVy, curOmega,
            &newCurX, &newCurY, &newAlfaRad, &newCurVx, &newCurVy, &newCurOmega,
            periodSec, ROCKET_MASS_KG, Fjet, Fcorrect, &newAlfaRadErr);
        curTime += periodSec;

        curX = newCurX;
        curY = newCurY;
        curAlfaRad = newAlfaRad;
        curVx = newCurVx;
        curVy = newCurVy;
        curOmega = newCurOmega;

        *spentFule += (fabs(Fjet) + fabs(Fcorrect))*periodSec;
        *sumXError += fabs(curX - X_TARGET)* periodSec;
        *sumAError += fabs(newAlfaRadErr) * periodSec;

        if (fabs(curY - (Y_TARGET + (ROCKET_LENGTH / 2))) < MAX_Y_ERROR) {
            if (MAX_Y_SPEED <fabs(curVy)) {
                //Crash
                *xError = fabs(curX - X_TARGET);
                *yError = fabs(curY - Y_TARGET);
                *aError = fabs(newAlfaRadErr);
                return false;
            }
        } 

        if ( fabs (curY-  (Y_TARGET+(ROCKET_LENGTH / 2))) < MAX_Y_ERROR) {
            if (fabs(curX- X_TARGET)<10) {
               if (fabs(RADIANSTODEGREES(newAlfaRadErr))< MAX_ANGLE_ERROR_DEG) {
                    if ((fabs(curVy) < MAX_Y_SPEED) && (fabs(curVx) < MAX_X_SPEED) && (RADIANSTODEGREES(curOmega))<20) {
                        *xError = fabs(curX - X_TARGET);
                        *yError = fabs(curY - Y_TARGET);
                        *aError = fabs(newAlfaRadErr);
                        return true;
                    }
                }
            }
        }
    }
    *xError = fabs(curX - X_TARGET);
    *yError = fabs(curY - Y_TARGET);
    *aError = fabs(newAlfaRadErr);

    return false;
}

