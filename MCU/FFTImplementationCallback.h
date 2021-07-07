/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: FFTImplementationCallback.h
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 07-Jul-2021 14:39:23
 */

#ifndef FFTIMPLEMENTATIONCALLBACK_H
#define FFTIMPLEMENTATIONCALLBACK_H

/* Include Files */
#include "freq_domain_types.h"
#include "rtwtypes.h"
//#include "omp.h"
#include <stddef.h>
#include <stdlib.h>
#ifdef __cplusplus

extern "C" {

#endif

  /* Function Declarations */
  void c_FFTImplementationCallback_doH(const double x_data[], creal_T y_data[],
    int nfft, const emxArray_creal_T *wwc, const double costab_data[], const int
    costab_size[2], const double sintab_data[], const double costabinv_data[],
    const double sintabinv_data[]);

#ifdef __cplusplus

}
#endif
#endif

/*
 * File trailer for FFTImplementationCallback.h
 *
 * [EOF]
 */
