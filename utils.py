import numpy
import math  

def is_similar_abs(valA,valB,alloError):
    result  = False
    diff = abs(valA-valB)
    print (alloError)
    print (diff)
    if diff<alloError:
        result = True
    return result


def limiter (val, downLimin, upLimit):
    outVal = val
    if upLimit < val:
        outVal = upLimit
    if val < downLimin:
        outVal = downLimin
    return outVal

def calc_angle_between_vectors(vectorA, vectorB):
    normA = numpy.linalg.norm(vectorA)
    normB = numpy.linalg.norm(vectorB)
    #print ('normB {} normB {} '.format(normA,normB))
    #print ('vertical {} rocketOrientation {} '.format(vectorA,vectorB))
    dotPrd = abs( numpy.dot( vectorA, vectorB))
    #print ('dotPrd {}  '.format(dotPrd))
    AngleAbsRad = math.acos(dotPrd/(normA*normB));
    #print ('AngleAbs {} rad {} deg'.format(AngleAbsRad,math.degrees(AngleAbsRad)))
    crossProd = numpy.cross(vectorA,vectorB)
    effectiveAngleRad = AngleAbsRad*numpy.sign(crossProd[2])
    #print ('effectiveAngleRad {} {} deg  '.format(effectiveAngleRad, math.degrees(effectiveAngleRad)))
    return effectiveAngleRad
