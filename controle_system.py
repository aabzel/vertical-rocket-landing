import math
import numpy
from pid_params import *
from utils import *
from rocket_params import *


def diod(x):
    out = 0
    if 0 < x:
        out = x
    return out


def calcAngleError(angleRad):
    #calc angle betveen vectors
    vertical = [0, 1, 0]
    rocketOrientation = [-math.sin(angleRad), math.cos(angleRad), 0]
    effectiveAngle = calc_angle_between_vectors(vertical, rocketOrientation)
    return effectiveAngle


def calc_rocket_control(xTarget, yTarget, rocketLength,
                        GravitationalAcceleration, curX, curY, curAlfaRad,
                        curVx, curVy, curOmega, roketMassKg):
    fSupp = roketMassKg * GravitationalAcceleration
    xError = xTarget - curX
    kdy = kdyFar
    desAngle = -xError * kpx + curVx * pdx
    desAngleLim = limiter(desAngle, -math.radians(maxIncline),
                          math.radians(maxIncline))
    desAngleVec = [-math.sin(desAngleLim), math.cos(desAngleLim), 0]
    rocketOrientation = [-math.sin(curAlfaRad), math.cos(curAlfaRad), 0]
    angleError = calc_angle_between_vectors(desAngleVec, rocketOrientation)
    if True == printlog:
        print('des angle {:5.2f} deg angleError  {:5.2f} deg'.format(
            math.degrees(desAngleLim), math.degrees(angleError)))
    Fcorrect = angleError * kpA + curOmega * kdA
    yError = yTarget - curY

    if (yError < ((rocketLength / 2) + 3)):
        kdy = kdyNear

    calc_rocket_control.yErrorAcc = calc_rocket_control.yErrorAcc + yError
    Fjet = (yError) * kpy - (curVy) * kdy + calc_rocket_control.yErrorAcc * kiy
    #if (False==is_similar_abs(0, angleError, math.radians(90))):
    #    Fjet = 0
    Fjet = limiter(Fjet, 0, maxFjet)
    Fcorrect = limiter(Fcorrect, -maxFcorrect, maxFcorrect)
    return [Fjet, Fcorrect]


calc_rocket_control.yErrorAcc = 0
