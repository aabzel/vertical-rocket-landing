import math  

def rocket_math_model_2d (rocketLength, GravitationalAcceleration, curX, curY, curAlfa, curVx, curVy, curOmega, periodSec, massKg, Fjet, Fcorrect):
    if ((0.0 < massKg) and  (0.0<rocketLength)):
        rodMomentOfInertia = massKg * rocketLength * rocketLength / 12.0;
        newVx = (-Fjet * math.sin (curAlfa) * periodSec / massKg) + curVx;
        newVy = (-GravitationalAcceleration * massKg + Fjet * math.cos (curAlfa)) * periodSec / massKg + curVy;
        newOmega = -(((rocketLength) * Fcorrect * periodSec) / (2*rodMomentOfInertia)) + curOmega;
        newX = newVx * periodSec + curX;
        newY = newVy * periodSec + curY;
        newAlfa = newOmega * periodSec + curAlfa;
    return [newX, newY, newAlfa, newVx, newVy, newOmega];
