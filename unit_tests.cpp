#include "unit_tests.h"
#include "utils.h"
#include "float_utils.h"
#include "control_nn_computer.h"

#include <stdio.h>
#include <float.h>

bool run_unit_test () {
    bool res = false;
    int val = amount_of_weights ();
    if (48 != val) {
        printf ("\n val %u", val);
        return false;

    }

    int changeWeightCnt;
    int changedIndexI = 100;
    int changedIndexJ = 100;
    float origWeightVal = FLT_MAX, newWeightVal = FLT_MAX;
    changeWeightCnt = change_one_rand_nn_weights (&changedIndexI, &changedIndexJ, &origWeightVal, &newWeightVal);
    if (1 != changeWeightCnt) {
        printf ("\n changeWeightCnt %u", changeWeightCnt);
        return false;
    }
    if (!(0 <= changedIndexI && changedIndexI <= 13)) {
        printf ("\n changedIndexI %u", changedIndexI);
        return false;
    }

    if (!(0 <= changedIndexJ && changedIndexJ <= 13)) {
        printf ("\n changedIndexI %u", changedIndexJ);
        return false;
    }

    if (true == is_float_equal_absolute(origWeightVal, newWeightVal, 0.01)) {
    }
    return true;
}
