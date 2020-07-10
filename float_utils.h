#ifndef RX_FLOAT_H
#define RX_FLOAT_H

#include <math.h>
#include <stdint.h>


#ifndef FLOAT_T_DEFINED
#if defined(__STRICT_ANSI__) || defined (MATLAB_MEX_FILE)
#define FLOAT_T_DEFINED
typedef float float_t;
typedef double double_t;
#else
#define FLOAT_T_DEFINED
#endif
#endif /* FLOAT_T_DEFINED */

#define F_EPSILON 1E-10f
#define D_EPSILON 1E-10

#ifdef __cplusplus
extern "C" {
#endif

bool is_floats_equal (float_t valA, float_t valB);
bool is_float_equal_relative(float_t a__fife, float_t b__fife, float_t relative_epsilon__fife);
bool is_double_equal_relative(double_t a__fide, double_t b__fide, double_t relative_epsilon__fide);
bool is_float_equal_absolute(float_t a__fife, float_t b__fife, float_t absolute_epsilon__fife);
bool is_double_equal_absolute(double_t a__fide, double_t b__fide, double_t absolute_epsilon__fide);

#ifdef __cplusplus
}
#endif

#endif /* RX_FLOAT_H */
