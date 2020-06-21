import matplotlib.pyplot as plt
import numpy as np
import keyboard  # using module keyboard
import math
from rocket_params import *
from init_conditions import *

from math_model_rocket_2d import rocket_math_model_2d
from controle_system import calc_rocket_control
from unit_tests import run_unit_tests

periodSec = 0.02
xTarget = 0
yTarget = rocketLength * 0.5

# use ggplot style for more sophisticated visuals
plt.style.use('ggplot')


def draw_rocket(cX, cY, alfaRag, len):
    #plt.xlim(-50, 50)
    #plt.ylim(-50, 50)
    #plt.axis('equal')
    TopY = cY + math.cos(alfaRag) * len / 2
    TopX = cX - math.sin(alfaRag) * len / 2
    bottomX = cX + math.sin(alfaRag) * len / 2
    bottomY = cY - math.cos(alfaRag) * len / 2
    pointTop = [TopX, TopY]
    pointBottom = [bottomX, bottomY]
    x_values = [pointTop[0], pointBottom[0]]
    y_values = [pointTop[1], pointBottom[1]]
    plt.plot(x_values, y_values)
    plt.plot(bottomX, bottomY, 'bo')
    #plt.show()


plt.xlabel('X ')
plt.ylabel('Y ')

loop = True
utRes = run_unit_tests()
if (False == utRes):
    print('unit test error')
    loop = False

controlSys = 1
simulation_time = 60
scale = 100
curTime = 0

Fsupport = roketMassKg * GravitationalAcceleration
FcorrectForse = roketMassKg * GravitationalAcceleration * 0.0001
while loop:
    plt.clf()  # Clear figure
    Fjet = 0
    Fcorrect = 0
    if keyboard.is_pressed('q'):
        loop = false
    if controlSys == 1:
        controlList = calc_rocket_control(xTarget, yTarget, rocketLength,
                                          GravitationalAcceleration, curX,
                                          curY, curAlfaRad, curVx, curVy,
                                          curOmega, roketMassKg)
        Fjet = controlList[0]
        Fcorrect = controlList[1]

    retList = rocket_math_model_2d(rocketLength, GravitationalAcceleration,
                                   curX, curY, curAlfaRad, curVx, curVy,
                                   curOmega, periodSec, roketMassKg, Fjet,
                                   Fcorrect)
    curX = retList[0]
    curY = retList[1]
    curAlfaRad = retList[2]
    curVx = retList[3]
    curVy = retList[4]
    curOmega = retList[5]
    draw_rocket(curX, curY, curAlfaRad, 10)
    if True == printlog:
        print(
            'x {:6.2f} y {:6.2f} alfa {:6.2f} deg vX {:6.2f} vY {:6.2f} Fjet: {:6.2f}% Fcor: {:6.2f}%'
            .format(curX, curY, math.degrees(curAlfaRad), curVx, curVy,
                    100 * Fjet / maxFjet, 100 * Fcorrect / maxFcorrect))
    plt.axis('equal')
    plt.axis([-scale, scale, -scale, scale])
    plt.pause(periodSec)
    curTime = curTime + periodSec
    if (simulation_time < curTime):
        loop = False
