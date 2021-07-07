/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: bandpower.h
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 07-Jul-2021 14:39:23
 */

#ifndef BANDPOWER_H
#define BANDPOWER_H

/* Include Files */
#include "rtwtypes.h"
//#include "omp.h"
#include <stddef.h>
#include <stdlib.h>
#ifdef __cplusplus

extern "C" {

#endif

  /* Function Declarations */
  void timedomainbandpower(const double x[3000], double fs, const double
    freqrange[2], double pwr_data[], int pwr_size[2]);

#ifdef __cplusplus

}
#endif
#endif

/*
 * File trailer for bandpower.h
 *
 * [EOF]
 */
