#printlog=False
printlog=True


maxIncline = 10
rocketLength = 10
GravitationalAcceleration = 9.8
tubeMass = 23000
fuleMass = 50000
roketMassKg = tubeMass + fuleMass

maxFjet = roketMassKg*GravitationalAcceleration*2
maxFcorrect = roketMassKg*GravitationalAcceleration*0.5

fSupp =  roketMassKg*GravitationalAcceleration