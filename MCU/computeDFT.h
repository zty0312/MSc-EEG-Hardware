/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: computeDFT.h
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 07-Jul-2021 14:39:23
 */

#ifndef COMPUTEDFT_H
#define COMPUTEDFT_H

/* Include Files */
#include "rtwtypes.h"
//#include "omp.h"
#include <stddef.h>
#include <stdlib.h>
#ifdef __cplusplus

extern "C" {

#endif

  /* Function Declarations */
  void computeDFT(const double xin[3000], double varargin_1, creal_T Xx_data[],
                  int Xx_size[1], double f_data[], int f_size[1]);

#ifdef __cplusplus

}
#endif
#endif

/*
 * File trailer for computeDFT.h
 *
 * [EOF]
 */
