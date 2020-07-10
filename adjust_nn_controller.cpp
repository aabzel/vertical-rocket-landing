#include "adjust_nn_controler.h"

#include <conio.h>
#include <float.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>

#include "rocket_simulation_2d.h"
#include "control_computer.h"
#include "rocket_params.h"
#include "utils.h"
#include "float_utils.h"

bool calc_nn_ratio () {
    FILE* fileOutPtr;

    float origWeightVal = 0;
    float newWeightVal = 0;
    int changedIndexI = 1000;
    int changedIndexJ = 1000;

    bool res = false;
    FILE* tempfileOutPtr;
    fileOutPtr = fopen ("best_nn_multipliers.txt", "a");
    tempfileOutPtr = fopen ("temp_nn_multipliers.txt", "a");

    float sumXError = 0.0;
    float spotBetterSolution = 0.0;
    float simulationTimeS = 30.0;
    bool oneWeightChanged = false;
    float aError = FLT_MAX;
    float minTotalError = FLT_MAX;
    float curTotalError = FLT_MAX;
    float minTotalNotSolError = FLT_MAX;
    float prevTolatError = FLT_MAX;
    float totalXYError = FLT_MAX;
    float xError = FLT_MAX;
    float yError = FLT_MAX;
    float minXError = 100000;
    float minYError = 100000;
    float minAError = 100000;
    bool solutionFound = false;
    uint32_t restoreWeightCounter = 0;
    uint32_t approximation—ounter = 0;
    uint32_t betterError—ounter = 0;
    uint32_t changeWeightCnt = 0;
    uint32_t betterSolCnt = 0;
    uint32_t approved—hange = 0;
    uint32_t improvement—ounter = 0;
    float spentFule = 0.0;
    float sumAError = 0;
    uint64_t counter = 0;
    bool loop = true;
    while (true == loop) {
        bool trySolution;
        trySolution = simulate_rorket (simulationTimeS, &xError, &yError, &aError, &sumXError, &sumAError, &spentFule);
        totalXYError = fabs (xError) + fabs (yError);
        curTotalError = totalXYError + fabs (aError) + sqrt (fabs (sumXError)) + 10 * sqrt (fabs (sumAError)) + spentFule;
        counter++;
        curTotalError = val_limiter (curTotalError, FLT_MIN / 2, FLT_MAX / 2);
#if DEBUG_ERROR
        printf("\ncurTotalError %f xErr %f yErr %f", curTotalError, xError, yError);
#endif
        if (true == trySolution) {
            approved—hange++;
            oneWeightChanged = false;
            solutionFound = true;
            //save_weights_to_file (fileOutPtr);
            if (curTotalError < minTotalError) {
                betterSolCnt++;
                spotBetterSolution = true;
                printf ("\nfound better solution!");
                minTotalError = curTotalError;

                fprintf (fileOutPtr, "\n better solution weights %6.1f \n", minTotalError);
                save_weights_to_file (fileOutPtr);
                //loop = false;
            } else {
                //printf ("\nfound  solution!");
            }
        }

        if (true == oneWeightChanged) {
            if ((changedIndexI < WEIGHT_MATRIX_DIM) && (changedIndexJ < WEIGHT_MATRIX_DIM)) {
                if (false == is_float_equal_absolute (origWeightVal, neuralNetworkWeights [changedIndexI] [changedIndexJ], F_EPSILON)) {
                    if (true == is_float_equal_absolute (newWeightVal, neuralNetworkWeights [changedIndexI] [changedIndexJ], F_EPSILON)) {
                        neuralNetworkWeights [changedIndexI] [changedIndexJ] = origWeightVal;
                        restoreWeightCounter++;
                        oneWeightChanged = false;
                    } else {
                        save_weights_to_file(tempfileOutPtr);
                        //printf ("\n i %u j %u\n", changedIndexI, changedIndexJ);
                        printf ("\n newWeightVal %f real val %f\n", newWeightVal, neuralNetworkWeights [changedIndexI] [changedIndexJ]);
                        getchar ();
                        exit (4);
                    }
                } else {
                    save_weights_to_file(tempfileOutPtr);
                    printf ("\n i %u j %u\n", changedIndexI, changedIndexJ);
                    printf ("\n origWeightVal %f real val %f\n", origWeightVal, neuralNetworkWeights [changedIndexI] [changedIndexJ]);
                    getchar ();
                    exit (2);
                }
            }
        } else {
            if (false == oneWeightChanged) {
                origWeightVal = 0.0;
                newWeightVal = 0.0;
                changeWeightCnt += change_one_rand_nn_weights (&changedIndexI, &changedIndexJ, &origWeightVal, &newWeightVal);
                oneWeightChanged = true;
            }
        }

        if (curTotalError < prevTolatError) {
            //printf("\nless error cur %9.2f < prev %9.2f", curTotalError, prevTolatError);
            betterError—ounter++;

        }

        if (curTotalError < minTotalNotSolError) {
            minTotalNotSolError = curTotalError;
            approximation—ounter++;
            printf ("\n min Total Not Sol Error %f\n", minTotalNotSolError);
            fprintf (tempfileOutPtr, "\n min Total Not Sol Error %f\n", minTotalNotSolError);
            //printf("\nless abs none sol error cur %9.2f < prev %9.2f", curTotalError, minTotalNotSolError);
            if (0 == (approximation—ounter % 100)) {
                save_weights_to_file (tempfileOutPtr);
            }
        }

        if (0 == counter % 8000) {
            printf("\n a: %u + r:%u ?= c:%u", approved—hange, restoreWeightCounter, changeWeightCnt);
            printf ("\n min Total Not Sol Error %f  ", minTotalNotSolError);
            //printf("  curTotalError: %6.2f", curTotalError);
            if (0<betterSolCnt) {
                printf("  betterSolCnt: %u", betterSolCnt);
            }
            if (0 < approved—hange) {
                printf ("  approved change cnt: %u", approved—hange);
            }
            //printf ("\n last change i:%u j:%u orig %6.2f", changedIndexI, changedIndexJ, origWeightVal);
            //printf("\n+8k iteration done betterErrorCounter %6d changeWeightCnt %6u approximationCounter %6u restoreWeightCounter %6u curTotalError %12.2f", betterError—ounter, changeWeightCnt, approximation—ounter, restoreWeightCounter,curTotalError);
        }
        if (100 < betterSolCnt) {
            loop = false;
        }

        //if (0 == stabilisationCounter % 400000) {
        //    printf("\n Mutation" );
        //    change_rand_nn_weights();
        //}

        prevTolatError = curTotalError;

        if (1e6 < counter) {
            loop = false;
        }
        if (curTotalError < 1) {
            //solutionFound = true;
            //spotBetterSolution = true;
            //loop = false;
        }
        char c = 0;
        if (kbhit ()) {
            c = fgetc (stdin);
            printf ("Char: %c\n", c);
        }

        if ('q' == c) {
            fprintf (tempfileOutPtr, "\n dump weights\n");
            save_weights_to_file (tempfileOutPtr);
            solutionFound = true;
            spotBetterSolution = true;
            loop = false;
        }
    }

    if ((true == solutionFound) && (true == spotBetterSolution)) {
        res = true;
        printf ("\n\a");
    } else {
        fprintf (fileOutPtr, "solution has not been found!\n");
        printf ("\n solution has not been found!");
        res = false;
    }
    fclose (fileOutPtr);
    return res;

}

