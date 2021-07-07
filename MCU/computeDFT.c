/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: computeDFT.c
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 07-Jul-2021 14:39:23
 */

/* Include Files */
#include "computeDFT.h"
#include "FFTImplementationCallback.h"
#include "freq_domain_emxutil.h"
#include "freq_domain_types.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const double xin[3000]
 *                double varargin_1
 *                creal_T Xx_data[]
 *                int Xx_size[1]
 *                double f_data[]
 *                int f_size[1]
 * Return Type  : void
 */
void computeDFT(const double xin[3000], double varargin_1, creal_T Xx_data[],
                int Xx_size[1], double f_data[], int f_size[1])
{
  static creal_T y_data[3000];
  static double costab_data[6001];
  static double sintab_data[6001];
  static double sintabinv_data[6001];
  static double costab1q_data[3001];
  static double w1_data[3000];
  emxArray_creal_T *wwc;
  double nt_im;
  double nt_re;
  int costab_size[2];
  int N2blue;
  int costab1q_size_idx_1;
  int k;
  int pmax;
  int pmin;
  int pow2p;
  boolean_T exitg1;
  pmax = 31;
  pmin = 0;
  exitg1 = false;
  while ((!exitg1) && (pmax - pmin > 1)) {
    k = (pmin + pmax) >> 1;
    pow2p = 1 << k;
    if (pow2p == 5999) {
      pmax = k;
      exitg1 = true;
    } else if (pow2p > 5999) {
      pmax = k;
    } else {
      pmin = k;
    }
  }

  N2blue = 1 << pmax;
  nt_re = 6.2831853071795862 / (double)N2blue;
  pow2p = N2blue / 2 / 2;
  costab1q_size_idx_1 = pow2p + 1;
  costab1q_data[0] = 1.0;
  pmax = pow2p / 2 - 1;
  for (k = 0; k <= pmax; k++) {
    costab1q_data[k + 1] = cos(nt_re * ((double)k + 1.0));
  }

  pmin = pmax + 2;
  pmax = pow2p - 1;
  for (k = pmin; k <= pmax; k++) {
    costab1q_data[k] = sin(nt_re * (double)(pow2p - k));
  }

  costab1q_data[pow2p] = 0.0;
  pmin = pow2p << 1;
  costab_size[0] = 1;
  costab_size[1] = (short)(pmin + 1);
  costab_data[0] = 1.0;
  sintab_data[0] = 0.0;
  for (k = 0; k < pow2p; k++) {
    sintabinv_data[k + 1] = costab1q_data[(pow2p - k) - 1];
  }

  for (k = costab1q_size_idx_1; k <= pmin; k++) {
    sintabinv_data[k] = costab1q_data[k - pow2p];
  }

  for (k = 0; k < pow2p; k++) {
    costab_data[k + 1] = costab1q_data[k + 1];
    sintab_data[k + 1] = -costab1q_data[(pow2p - k) - 1];
  }

  for (k = costab1q_size_idx_1; k <= pmin; k++) {
    costab_data[k] = -costab1q_data[pmin - k];
    sintab_data[k] = -costab1q_data[k - pow2p];
  }

  emxInit_creal_T(&wwc, 1);
  pmin = wwc->size[0];
  wwc->size[0] = 2999;
  emxEnsureCapacity_creal_T(wwc, pmin);
  pmax = 1498;
  pmin = 0;
  wwc->data[1499].re = 1.0;
  wwc->data[1499].im = 0.0;
  for (k = 0; k < 1499; k++) {
    pow2p = ((k + 1) << 1) - 1;
    if (3000 - pmin <= pow2p) {
      pmin = (pow2p + pmin) - 3000;
    } else {
      pmin += pow2p;
    }

    nt_im = -3.1415926535897931 * (double)pmin / 1500.0;
    if (nt_im == 0.0) {
      nt_re = 1.0;
      nt_im = 0.0;
    } else {
      nt_re = cos(nt_im);
      nt_im = sin(nt_im);
    }

    wwc->data[pmax].re = nt_re;
    wwc->data[pmax].im = -nt_im;
    pmax--;
  }

  pmax = 0;
  for (k = 1498; k >= 0; k--) {
    wwc->data[k + 1500] = wwc->data[pmax];
    pmax++;
  }

  Xx_size[0] = 3000;
  memcpy(&Xx_data[0], &y_data[0], 3000U * sizeof(creal_T));
  if (N2blue != 1) {
    c_FFTImplementationCallback_doH(xin, Xx_data, N2blue, wwc, costab_data,
      costab_size, sintab_data, costab_data, sintabinv_data);
  } else {
    pmax = 0;
    Xx_size[0] = 3000;
    for (k = 0; k < 3000; k++) {
      Xx_data[k].re = wwc->data[k + 2999].re * xin[pmax];
      Xx_data[k].im = wwc->data[k + 2999].im * -xin[pmax];
      pmax++;
    }
  }

  emxFree_creal_T(&wwc);
  if (rtIsNaN(varargin_1)) {
    nt_re = 6.2831853071795862;
  } else {
    nt_re = varargin_1;
  }

  nt_im = nt_re / 3000.0;
  for (pmin = 0; pmin < 3000; pmin++) {
    w1_data[pmin] = nt_im * (double)pmin;
  }

  w1_data[1500] = nt_re / 2.0;
  w1_data[2999] = nt_re - nt_im;
  f_size[0] = 3000;
  memcpy(&f_data[0], &w1_data[0], 3000U * sizeof(double));
}

/*
 * File trailer for computeDFT.c
 *
 * [EOF]
 */
