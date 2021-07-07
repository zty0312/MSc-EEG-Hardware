/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: computeperiodogram.h
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 07-Jul-2021 14:39:23
 */

#ifndef COMPUTEPERIODOGRAM_H
#define COMPUTEPERIODOGRAM_H

/* Include Files */
#include "rtwtypes.h"
//#include "omp.h"
#include <stddef.h>
#include <stdlib.h>
#ifdef __cplusplus

extern "C" {

#endif

  /* Function Declarations */
  void computeperiodogram(const double x[3000], const double win[3000], double
    Fs, const char options_range[8], boolean_T options_reassign, double
    Pxx_data[], int Pxx_size[1], double F_data[], int F_size[1], creal_T
    RPxx_data[], int RPxx_size[1], double Fc_data[], int Fc_size[2]);

#ifdef __cplusplus

}
#endif
#endif

/*
 * File trailer for computeperiodogram.h
 *
 * [EOF]
 */
