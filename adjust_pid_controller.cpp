#include "adjust_pid_controler.h"

#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>

#include "rocket_simulation_2d.h"
#include "control_pid_computer.h"
#include "rocket_params.h"

bool calc_pid_ratio () {
	FILE* fileOutPtr;
	bool res = false;
	FILE* tempfileOutPtr;
	fileOutPtr = fopen("best_multipliers.txt", "a");
	tempfileOutPtr = fopen("temp_multipliers.txt", "a");
	float maxKoef = MAX_F_JET * 2;
	float sumXError = 0.0;
	float spotBetterSolution = 0.0;
	float kpStep = maxKoef/9;
	float simulationTimeS = 50.0;
	float aError = 100000.0;
	float minTotalError = FLT_MAX;
	float totalError = 100000.0;
	float totalXYError = 100000.0;
	float xError = 100000.0;
	float yError = 100000.0;
	float minXError = 100000;
	float minYError = 100000;
	float minAError = 100000;
	float bestKpx = 100000;
	float bestKdx = 100000;
	float bestKpy = 100000;
	float bestKdy = 100000;
	bool solutionFound = false;
	float bestKpa = 100000;
	float bestKda = 100000;
	float spentFule = 0.0;
	bool spotValues = false;
	bool spotValuesX = false;
	bool spotValuesY = false;
	bool spotValuesA = false;
	float sumAError = 0;
	uint64_t counter = 0;
	for (kpy = 0.0; kpy < maxKoef; kpy += kpStep) {
    	for (kdy = 0.0; kdy < maxKoef; kdy += kpStep) {
			for (kdx = 0.0; kdx < maxKoef; kdx += kpStep) {
				for (kpx = 0.0; kpx < maxKoef; kpx += kpStep) {
	                for (kpa = 0.0; kpa < maxKoef; kpa += kpStep) {
	                    for (kda = 0.0; kda < maxKoef; kda += kpStep) {
						   if (0 == counter % 10000) {
								printf("\n kpy %6.3f %% kdy %6.3f %%", 100 * kpy / (maxKoef), 100 * kdy / (maxKoef));
		                 		//printf("\n kpx %6.3f %% kdx %6.3f %%", 100 * kpx / (maxKoef), 100 * kdx / (maxKoef));
				                //printf("\n kpa %6.3f %% kda %6.3f %%\n ", 100 * kpa / (maxKoef), 100 * kda / (maxKoef));
							}
							counter++;
							bool tempRes;
							tempRes = simulate_rorket (simulationTimeS, &xError, &yError, &aError, &sumXError, &sumAError, &spentFule);
							if (true == tempRes)  {
								solutionFound = true;
							    totalXYError = fabs(xError) + fabs(yError) ;
								totalError = totalXYError + fabs(aError)+ sqrt(fabs(sumXError))+ 10*sqrt(fabs(sumAError))+ spentFule;
								if (totalError < minTotalError) {
									spotBetterSolution = true;
									printf("\nfound better solution!");
									minTotalError = totalError;
									bestKdx = kdx;
									bestKpa = kpa;
				                    bestKda = kda;
									bestKpx = kpx;
									bestKpy = kpy;
									bestKdy = kdy;
									fprintf(tempfileOutPtr, "\nsumXError: %8.1f XYError=%8.1f angleError=%8.1f kpx=%8.1f kdx=%8.1f kpy=%8.1f kdy=%8.1f kpa=%8.1f kda=%8.1f", sumXError,totalXYError, fabs(aError), kpx, kdx, kpy, kdy, kpa, kda);
							  }
							}
						}
					}
				}
			}
	    }
	}

	if ( (true== solutionFound ) &&(true== spotBetterSolution)) {
		kpx = bestKpx;
		kdx = bestKdx;

	    kpy = bestKpy;
    	kdy = bestKdy;
		
		kpa = bestKpa;
		kda = bestKda;
		printf("\n best kpx %8.1f kdx %8.1f kpy %8.1f kdy %8.1f kpa %8.1f kda %8.1f\n", kpx, kdx , kpy, kdy, kpa, kda);
		fprintf(fileOutPtr,"\nkpx=%8.1f; kdx=%8.1f; kpy=%8.1f; kdy=%8.1f; kpa=%8.1f; kda=%8.1f;", kpx, kdx, kpy, kdy, kpa, kda);
		res = true;
		printf("\n\a");
	} else {
		fprintf(fileOutPtr, "solution has not been found!\n" );
		printf("\n solution has not been found!");
		res= false;
	}
	fclose(fileOutPtr);
	return res;

}