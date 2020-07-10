#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "adjust_controler.h"
#include "unit_tests.h"
#include "adjust_nn_controler.h"
#include "adjust_pid_controler.h"
#include "control_computer.h"
#include "draw_rocket.h"
#include "graphics.h"
#include "init_conditions.h"
#include "math_model_rocket_2d.h"
#include "rocket_params.h"
#include "screen.h"
#include "target_state.h"

#define ADJUST_PARAMS 0

int main () {
    char onScreenText[100]="";
    srand((unsigned int)time(NULL));
    bool solutionExist = true;

    bool uTestRes = run_unit_test ();
    if (false == uTestRes) {
        printf("\nUnit Test error");
        getchar();
        return 9;
    }

#if ADJUST_PARAMS
    solutionExist = calc_pid_ratio();
    printf("\nReady to play solution. Press enter");
    if (false == solutionExist) {
        return 2;
    }
    getchar();
#endif
    
    initwindow (WIDTH, HEIGHT, "Sky");
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
    while (!kbhit ()) {
        calc_rocket_control_2d (X_TARGET, Y_TARGET, ROCKET_LENGTH, GRAVITATIONAL_ACCELERATION, curX, curY, curAlfaRad,
                                curVx, curVy, curOmega, ROCKET_MASS_KG, &Fjet, &Fcorrect);

        rocket_math_model_2d (ROCKET_LENGTH, GRAVITATIONAL_ACCELERATION, curX, curY, curAlfaRad, curVx, curVy, curOmega,
                              &newCurX, &newCurY, &newAlfaRad, &newCurVx, &newCurVy, &newCurOmega, periodSec,
                              ROCKET_MASS_KG, Fjet, Fcorrect, &newAlfaRadErr);
        draw_roket (curX, curY, curAlfaRad, ROCKET_LENGTH, Fjet, Fcorrect);
        setlinestyle (2, 0, 1);
        draw_axis (WIDTH, HEIGHT);

        //settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        snprintf(onScreenText, sizeof(onScreenText), "T: %3.1f s", curTime);
        outtextxy(30, 0, onScreenText);

        snprintf(onScreenText,  sizeof(onScreenText),"X: %3.2f ", curX );
        outtextxy(30, 20, onScreenText);
        snprintf(onScreenText, sizeof(onScreenText), "Y: %3.2f ", curY);
        outtextxy(30, 40, onScreenText);
        snprintf(onScreenText, sizeof(onScreenText), "Angle: %3.2f deg \n", RADIANSTODEGREES(newAlfaRadErr));
        outtextxy(30, 60, onScreenText);

        snprintf(onScreenText, sizeof(onScreenText), "Vx: %3.2f m/s", curVx);
        outtextxy(30, 80, onScreenText);
        snprintf(onScreenText, sizeof(onScreenText), "Vy: %3.2f m/s", curVy);
        outtextxy(30, 100, onScreenText);
        snprintf(onScreenText, sizeof(onScreenText), "Omega: %3.2f deg/s", RADIANSTODEGREES(curOmega));
        outtextxy(30, 120, onScreenText);
        delay (periodSec * 1000);
        curTime += periodSec;

        curX = newCurX;
        curY = newCurY;
        curAlfaRad = newAlfaRad;
        curVx = newCurVx;
        curVy = newCurVy;
        curOmega = newCurOmega;
        if (curY < ROCKET_LENGTH / 2) {
            if (1.0 < fabs (curVy)) {
                // Crash
                snprintf(onScreenText, sizeof(onScreenText), "Crash");
                outtextxy(100, 100, onScreenText);
                return 1;
            }
        }

        if (fabs(curY - (Y_TARGET + (ROCKET_LENGTH / 2))) < MAX_Y_ERROR) {
            if (fabs(curX - X_TARGET) < 10) {
                if (fabs(RADIANSTODEGREES(newAlfaRadErr)) < MAX_ANGLE_ERROR_DEG) {
                    if ((fabs(curVy) < MAX_Y_SPEED) && (fabs(curVx) < MAX_X_SPEED) && (RADIANSTODEGREES(curOmega)) < 20) {
                        snprintf(onScreenText, sizeof(onScreenText), "Success");
                        outtextxy(100, 100, onScreenText);
                    }
                }
            }
        }

    }
    return 0;
}
