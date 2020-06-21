import math  
from utils import *
from controle_system import *
import numpy

def run_unit_tests():
    outVal=limiter (5, -10, 10)
    if outVal != 5:
        print ('limit error real {} exp {}'.format(outVal,5))
        return False;
        
    outVal=limiter (0, -10, 10)
    if outVal != 0:
        print ('limit error real {} exp {}'.format(outVal,0))
        return False;
    outVal=limiter (100, -10, 10)
    if outVal != 10:
        print ('limit error real {} exp {}'.format(outVal,10))
        return False;
        
    outVal=limiter (-100, -10, 10)
    if outVal != -10:
        print ('limit error real {} exp {}'.format(outVal,-10))
        return False;
        
    crosProd = numpy.cross([0, 1, 0],[1, 1, 0])
    print (crosProd)
    if False==is_similar_abs(crosProd[2],-1,0.01):
        print ('4 real {} exp {}'.format(crosProd[2],0))
        return False;
    angleRad = math.radians(90)
    angleErr = calcAngleError (angleRad)
    if False==is_similar_abs(angleErr,math.radians(90),0.01):
        print ('1 real {} exp {}'.format(angleErr,math.radians(90)))
        return False;
    angleRad = math.radians(3*90)
    angleErr = calcAngleError (angleRad)
    if False==is_similar_abs(math.radians(-90),angleErr,0.01):
        print ('2 real {} exp {}'.format(angleErr,math.radians(-90)))
        return False;
    angleRad = math.radians(-3*90)
    angleErr = calcAngleError (angleRad)
    if False==is_similar_abs(math.radians(90),angleErr,0.01):
        print ('3 real {} exp {}'.format(angleErr,math.radians(90)))
        return False;
    return True