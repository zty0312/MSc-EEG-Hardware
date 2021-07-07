/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: FFTImplementationCallback.c
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 07-Jul-2021 14:39:23
 */

/* Include Files */
#include "FFTImplementationCallback.h"
#include "freq_domain_emxutil.h"
#include "freq_domain_types.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Declarations */
static void c_FFTImplementationCallback_r2b(const emxArray_creal_T *x, int
  n1_unsigned, const double costab_data[], const double sintab_data[],
  emxArray_creal_T *y);
static void d_FFTImplementationCallback_r2b(const emxArray_creal_T *x, int
  n1_unsigned, const double costab_data[], const double sintab_data[],
  emxArray_creal_T *y);

/* Function Definitions */
/*
 * Arguments    : const emxArray_creal_T *x
 *                int n1_unsigned
 *                const double costab_data[]
 *                const double sintab_data[]
 *                emxArray_creal_T *y
 * Return Type  : void
 */
static void c_FFTImplementationCallback_r2b(const emxArray_creal_T *x, int
  n1_unsigned, const double costab_data[], const double sintab_data[],
  emxArray_creal_T *y)
{
  double temp_im;
  double temp_re;
  double twid_im;
  double twid_re;
  int i;
  int iDelta2;
  int iheight;
  int ihi;
  int ix;
  int iy;
  int ju;
  int k;
  int nRowsD2;
  int temp_re_tmp;
  boolean_T tst;
  iy = y->size[0];
  y->size[0] = n1_unsigned;
  emxEnsureCapacity_creal_T(y, iy);
  if (n1_unsigned > x->size[0]) {
    iy = y->size[0];
    y->size[0] = n1_unsigned;
    emxEnsureCapacity_creal_T(y, iy);
    for (iy = 0; iy < n1_unsigned; iy++) {
      y->data[iy].re = 0.0;
      y->data[iy].im = 0.0;
    }
  }

  iDelta2 = x->size[0];
  if (iDelta2 >= n1_unsigned) {
    iDelta2 = n1_unsigned;
  }

  iheight = n1_unsigned - 2;
  nRowsD2 = n1_unsigned / 2;
  k = nRowsD2 / 2;
  ix = 0;
  iy = 0;
  ju = 0;
  for (i = 0; i <= iDelta2 - 2; i++) {
    y->data[iy] = x->data[ix];
    iy = n1_unsigned;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }

    iy = ju;
    ix++;
  }

  y->data[iy] = x->data[ix];
  if (n1_unsigned > 1) {
    for (i = 0; i <= iheight; i += 2) {
      temp_re = y->data[i + 1].re;
      temp_im = y->data[i + 1].im;
      twid_re = y->data[i].re;
      twid_im = y->data[i].im;
      y->data[i + 1].re = y->data[i].re - y->data[i + 1].re;
      y->data[i + 1].im = y->data[i].im - y->data[i + 1].im;
      twid_re += temp_re;
      twid_im += temp_im;
      y->data[i].re = twid_re;
      y->data[i].im = twid_im;
    }
  }

  iy = 2;
  iDelta2 = 4;
  iheight = ((k - 1) << 2) + 1;
  while (k > 0) {
    for (i = 0; i < iheight; i += iDelta2) {
      temp_re_tmp = i + iy;
      temp_re = y->data[temp_re_tmp].re;
      temp_im = y->data[temp_re_tmp].im;
      y->data[temp_re_tmp].re = y->data[i].re - temp_re;
      y->data[temp_re_tmp].im = y->data[i].im - temp_im;
      y->data[i].re += temp_re;
      y->data[i].im += temp_im;
    }

    ix = 1;
    for (ju = k; ju < nRowsD2; ju += k) {
      twid_re = costab_data[ju];
      twid_im = sintab_data[ju];
      i = ix;
      ihi = ix + iheight;
      while (i < ihi) {
        temp_re_tmp = i + iy;
        temp_re = twid_re * y->data[temp_re_tmp].re - twid_im * y->
          data[temp_re_tmp].im;
        temp_im = twid_re * y->data[temp_re_tmp].im + twid_im * y->
          data[temp_re_tmp].re;
        y->data[temp_re_tmp].re = y->data[i].re - temp_re;
        y->data[temp_re_tmp].im = y->data[i].im - temp_im;
        y->data[i].re += temp_re;
        y->data[i].im += temp_im;
        i += iDelta2;
      }

      ix++;
    }

    k /= 2;
    iy = iDelta2;
    iDelta2 += iDelta2;
    iheight -= iy;
  }
}

/*
 * Arguments    : const emxArray_creal_T *x
 *                int n1_unsigned
 *                const double costab_data[]
 *                const double sintab_data[]
 *                emxArray_creal_T *y
 * Return Type  : void
 */
static void d_FFTImplementationCallback_r2b(const emxArray_creal_T *x, int
  n1_unsigned, const double costab_data[], const double sintab_data[],
  emxArray_creal_T *y)
{
  double temp_im;
  double temp_re;
  double twid_im;
  double twid_re;
  int i;
  int iDelta2;
  int iheight;
  int istart;
  int ix;
  int iy;
  int ju;
  int k;
  int nRowsD2;
  int temp_re_tmp;
  boolean_T tst;
  iDelta2 = y->size[0];
  y->size[0] = n1_unsigned;
  emxEnsureCapacity_creal_T(y, iDelta2);
  if (n1_unsigned > x->size[0]) {
    iDelta2 = y->size[0];
    y->size[0] = n1_unsigned;
    emxEnsureCapacity_creal_T(y, iDelta2);
    for (iDelta2 = 0; iDelta2 < n1_unsigned; iDelta2++) {
      y->data[iDelta2].re = 0.0;
      y->data[iDelta2].im = 0.0;
    }
  }

  iheight = x->size[0];
  if (iheight >= n1_unsigned) {
    iheight = n1_unsigned;
  }

  istart = n1_unsigned - 2;
  nRowsD2 = n1_unsigned / 2;
  k = nRowsD2 / 2;
  ix = 0;
  iy = 0;
  ju = 0;
  for (i = 0; i <= iheight - 2; i++) {
    y->data[iy] = x->data[ix];
    iDelta2 = n1_unsigned;
    tst = true;
    while (tst) {
      iDelta2 >>= 1;
      ju ^= iDelta2;
      tst = ((ju & iDelta2) == 0);
    }

    iy = ju;
    ix++;
  }

  y->data[iy] = x->data[ix];
  if (n1_unsigned > 1) {
    for (i = 0; i <= istart; i += 2) {
      temp_re = y->data[i + 1].re;
      temp_im = y->data[i + 1].im;
      twid_re = y->data[i].re;
      twid_im = y->data[i].im;
      y->data[i + 1].re = y->data[i].re - y->data[i + 1].re;
      y->data[i + 1].im = y->data[i].im - y->data[i + 1].im;
      twid_re += temp_re;
      twid_im += temp_im;
      y->data[i].re = twid_re;
      y->data[i].im = twid_im;
    }
  }

  iy = 2;
  iDelta2 = 4;
  iheight = ((k - 1) << 2) + 1;
  while (k > 0) {
    for (i = 0; i < iheight; i += iDelta2) {
      temp_re_tmp = i + iy;
      temp_re = y->data[temp_re_tmp].re;
      temp_im = y->data[temp_re_tmp].im;
      y->data[temp_re_tmp].re = y->data[i].re - temp_re;
      y->data[temp_re_tmp].im = y->data[i].im - temp_im;
      y->data[i].re += temp_re;
      y->data[i].im += temp_im;
    }

    istart = 1;
    for (ix = k; ix < nRowsD2; ix += k) {
      twid_re = costab_data[ix];
      twid_im = sintab_data[ix];
      i = istart;
      ju = istart + iheight;
      while (i < ju) {
        temp_re_tmp = i + iy;
        temp_re = twid_re * y->data[temp_re_tmp].re - twid_im * y->
          data[temp_re_tmp].im;
        temp_im = twid_re * y->data[temp_re_tmp].im + twid_im * y->
          data[temp_re_tmp].re;
        y->data[temp_re_tmp].re = y->data[i].re - temp_re;
        y->data[temp_re_tmp].im = y->data[i].im - temp_im;
        y->data[i].re += temp_re;
        y->data[i].im += temp_im;
        i += iDelta2;
      }

      istart++;
    }

    k /= 2;
    iy = iDelta2;
    iDelta2 += iDelta2;
    iheight -= iy;
  }

  if (y->size[0] > 1) {
    twid_re = 1.0 / (double)y->size[0];
    iy = y->size[0];
    for (iDelta2 = 0; iDelta2 < iy; iDelta2++) {
      y->data[iDelta2].re *= twid_re;
      y->data[iDelta2].im *= twid_re;
    }
  }
}

/*
 * Arguments    : const double x_data[]
 *                creal_T y_data[]
 *                int nfft
 *                const emxArray_creal_T *wwc
 *                const double costab_data[]
 *                const int costab_size[2]
 *                const double sintab_data[]
 *                const double costabinv_data[]
 *                const double sintabinv_data[]
 * Return Type  : void
 */
void c_FFTImplementationCallback_doH(const double x_data[], creal_T y_data[],
  int nfft, const emxArray_creal_T *wwc, const double costab_data[], const int
  costab_size[2], const double sintab_data[], const double costabinv_data[],
  const double sintabinv_data[])
{
  static double b_costab_data[6001];
  static double b_sintab_data[6001];
  static double costab1q_data[3001];
  emxArray_creal_T *fy;
  emxArray_creal_T *r;
  emxArray_creal_T *y;
  creal_T reconVar1_data[1500];
  creal_T reconVar2_data[1500];
  creal_T ytmp_data[1500];
  double hcostabinv_data[3001];
  double hsintab_data[3001];
  double hsintabinv_data[3001];
  double d;
  double temp_im;
  double temp_re;
  double twid_im;
  double twid_re;
  double z;
  int wrapIndex_data[1500];
  int hszCostab;
  int i;
  int idx;
  int ihi;
  int ix;
  int j;
  int ju;
  int k;
  int nRowsD2;
  int temp_re_tmp;
  boolean_T tst;
  costab1q_data[0] = 1.0;
  for (k = 0; k < 750; k++) {
    costab1q_data[k + 1] = cos(0.0010471975511965976 * ((double)k + 1.0));
  }

  for (k = 0; k < 749; k++) {
    costab1q_data[k + 751] = sin(0.0010471975511965976 * (1500.0 - ((double)k +
      751.0)));
  }

  costab1q_data[1500] = 0.0;
  b_costab_data[0] = 1.0;
  b_sintab_data[0] = 0.0;
  for (k = 0; k < 1500; k++) {
    b_costab_data[k + 1] = costab1q_data[k + 1];
    b_sintab_data[k + 1] = -costab1q_data[1499 - k];
  }

  for (k = 1501; k < 3001; k++) {
    b_costab_data[k] = -costab1q_data[3000 - k];
    b_sintab_data[k] = -costab1q_data[k - 1500];
  }

  hszCostab = costab_size[1] / 2;
  for (i = 0; i < hszCostab; i++) {
    idx = ((i + 1) << 1) - 2;
    costab1q_data[i] = costab_data[idx];
    hsintab_data[i] = sintab_data[idx];
    hcostabinv_data[i] = costabinv_data[idx];
    hsintabinv_data[i] = sintabinv_data[idx];
  }

  idx = 0;
  hszCostab = 1;
  for (i = 0; i < 1500; i++) {
    reconVar1_data[i].re = b_sintab_data[idx] + 1.0;
    reconVar1_data[i].im = -b_costab_data[idx];
    reconVar2_data[i].re = 1.0 - b_sintab_data[idx];
    reconVar2_data[i].im = b_costab_data[idx];
    idx += 2;
    if (i + 1 != 1) {
      wrapIndex_data[i] = 1501 - i;
    } else {
      wrapIndex_data[0] = 1;
    }

    temp_re = x_data[hszCostab - 1];
    temp_im = x_data[hszCostab];
    ytmp_data[i].re = wwc->data[i + 1499].re * temp_re + wwc->data[i + 1499].im *
      temp_im;
    ytmp_data[i].im = wwc->data[i + 1499].re * temp_im - wwc->data[i + 1499].im *
      temp_re;
    hszCostab += 2;
  }

  emxInit_creal_T(&y, 1);
  z = (double)nfft / 2.0;
  ix = y->size[0];
  y->size[0] = (int)z;
  emxEnsureCapacity_creal_T(y, ix);
  if ((int)z > 1500) {
    hszCostab = (int)z;
    ix = y->size[0];
    y->size[0] = (int)z;
    emxEnsureCapacity_creal_T(y, ix);
    for (ix = 0; ix < hszCostab; ix++) {
      y->data[ix].re = 0.0;
      y->data[ix].im = 0.0;
    }
  }

  emxInit_creal_T(&fy, 1);
  ix = fy->size[0];
  fy->size[0] = y->size[0];
  emxEnsureCapacity_creal_T(fy, ix);
  hszCostab = y->size[0];
  for (ix = 0; ix < hszCostab; ix++) {
    fy->data[ix] = y->data[ix];
  }

  if (1500 < (int)z) {
    idx = 1498;
  } else {
    idx = (int)z - 2;
  }

  j = (int)z - 2;
  nRowsD2 = (int)z / 2;
  k = nRowsD2 / 2;
  ix = 0;
  hszCostab = 0;
  ju = 0;
  for (i = 0; i <= idx; i++) {
    fy->data[hszCostab] = ytmp_data[ix];
    hszCostab = (int)z;
    tst = true;
    while (tst) {
      hszCostab >>= 1;
      ju ^= hszCostab;
      tst = ((ju & hszCostab) == 0);
    }

    hszCostab = ju;
    ix++;
  }

  fy->data[hszCostab] = ytmp_data[ix];
  ix = y->size[0];
  y->size[0] = fy->size[0];
  emxEnsureCapacity_creal_T(y, ix);
  hszCostab = fy->size[0];
  for (ix = 0; ix < hszCostab; ix++) {
    y->data[ix] = fy->data[ix];
  }

  if ((int)z > 1) {
    for (i = 0; i <= j; i += 2) {
      temp_re = y->data[i + 1].re;
      temp_im = y->data[i + 1].im;
      twid_re = y->data[i].re;
      twid_im = y->data[i].im;
      y->data[i + 1].re = y->data[i].re - y->data[i + 1].re;
      y->data[i + 1].im = y->data[i].im - y->data[i + 1].im;
      twid_re += temp_re;
      twid_im += temp_im;
      y->data[i].re = twid_re;
      y->data[i].im = twid_im;
    }
  }

  hszCostab = 2;
  idx = 4;
  ix = ((k - 1) << 2) + 1;
  while (k > 0) {
    for (i = 0; i < ix; i += idx) {
      temp_re_tmp = i + hszCostab;
      temp_re = y->data[temp_re_tmp].re;
      temp_im = y->data[temp_re_tmp].im;
      y->data[temp_re_tmp].re = y->data[i].re - temp_re;
      y->data[temp_re_tmp].im = y->data[i].im - temp_im;
      y->data[i].re += temp_re;
      y->data[i].im += temp_im;
    }

    ju = 1;
    for (j = k; j < nRowsD2; j += k) {
      twid_re = costab1q_data[j];
      twid_im = hsintab_data[j];
      i = ju;
      ihi = ju + ix;
      while (i < ihi) {
        temp_re_tmp = i + hszCostab;
        temp_re = twid_re * y->data[temp_re_tmp].re - twid_im * y->
          data[temp_re_tmp].im;
        temp_im = twid_re * y->data[temp_re_tmp].im + twid_im * y->
          data[temp_re_tmp].re;
        y->data[temp_re_tmp].re = y->data[i].re - temp_re;
        y->data[temp_re_tmp].im = y->data[i].im - temp_im;
        y->data[i].re += temp_re;
        y->data[i].im += temp_im;
        i += idx;
      }

      ju++;
    }

    k /= 2;
    hszCostab = idx;
    idx += idx;
    ix -= hszCostab;
  }

  emxInit_creal_T(&r, 1);
  c_FFTImplementationCallback_r2b(wwc, (int)((double)nfft / 2.0), costab1q_data,
    hsintab_data, r);
  ix = fy->size[0];
  fy->size[0] = y->size[0];
  emxEnsureCapacity_creal_T(fy, ix);
  hszCostab = y->size[0];
  for (ix = 0; ix < hszCostab; ix++) {
    fy->data[ix].re = y->data[ix].re * r->data[ix].re - y->data[ix].im * r->
      data[ix].im;
    fy->data[ix].im = y->data[ix].re * r->data[ix].im + y->data[ix].im * r->
      data[ix].re;
  }

  emxFree_creal_T(&y);
  d_FFTImplementationCallback_r2b(fy, (int)z, hcostabinv_data, hsintabinv_data,
    r);
  ix = fy->size[0];
  fy->size[0] = r->size[0];
  emxEnsureCapacity_creal_T(fy, ix);
  hszCostab = r->size[0];
  for (ix = 0; ix < hszCostab; ix++) {
    fy->data[ix] = r->data[ix];
  }

  emxFree_creal_T(&r);
  idx = 0;
  ix = wwc->size[0];
  for (k = 1500; k <= ix; k++) {
    ytmp_data[idx].re = wwc->data[k - 1].re * fy->data[k - 1].re + wwc->data[k -
      1].im * fy->data[k - 1].im;
    ytmp_data[idx].im = wwc->data[k - 1].re * fy->data[k - 1].im - wwc->data[k -
      1].im * fy->data[k - 1].re;
    idx++;
  }

  emxFree_creal_T(&fy);
  for (i = 0; i < 1500; i++) {
    ix = wrapIndex_data[i];
    twid_re = ytmp_data[ix - 1].re;
    twid_im = -ytmp_data[ix - 1].im;
    temp_re = reconVar1_data[i].re;
    temp_im = reconVar1_data[i].im;
    z = reconVar2_data[i].re;
    d = reconVar2_data[i].im;
    y_data[i].re = 0.5 * ((ytmp_data[i].re * temp_re - ytmp_data[i].im * temp_im)
                          + (twid_re * z - twid_im * d));
    y_data[i].im = 0.5 * ((ytmp_data[i].re * temp_im + ytmp_data[i].im * temp_re)
                          + (twid_re * d + twid_im * z));
    y_data[i + 1500].re = 0.5 * ((ytmp_data[i].re * z - ytmp_data[i].im * d) +
      (twid_re * temp_re - twid_im * temp_im));
    y_data[i + 1500].im = 0.5 * ((ytmp_data[i].re * d + ytmp_data[i].im * z) +
      (twid_re * temp_im + twid_im * temp_re));
  }
}

/*
 * File trailer for FFTImplementationCallback.c
 *
 * [EOF]
 */
