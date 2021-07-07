/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: computeperiodogram.c
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 07-Jul-2021 14:39:23
 */

/* Include Files */
#include "computeperiodogram.h"
#include "computeDFT.h"
#include "freq_domain_emxutil.h"
#include "freq_domain_internal_types.h"
#include "freq_domain_types.h"
#include "mod.h"
#include "ppval.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Declarations */
static double rt_roundd_snf(double u);

/* Function Definitions */
/*
 * Arguments    : double u
 * Return Type  : double
 */
static double rt_roundd_snf(double u)
{
  double y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/*
 * Arguments    : const double x[3000]
 *                const double win[3000]
 *                double Fs
 *                const char options_range[8]
 *                boolean_T options_reassign
 *                double Pxx_data[]
 *                int Pxx_size[1]
 *                double F_data[]
 *                int F_size[1]
 *                creal_T RPxx_data[]
 *                int RPxx_size[1]
 *                double Fc_data[]
 *                int Fc_size[2]
 * Return Type  : void
 */
void computeperiodogram(const double x[3000], const double win[3000], double Fs,
  const char options_range[8], boolean_T options_reassign, double Pxx_data[],
  int Pxx_size[1], double F_data[], int F_size[1], creal_T RPxx_data[], int
  RPxx_size[1], double Fc_data[], int Fc_size[2])
{
  static struct_T expl_temp;
  static creal_T Xx_data[3000];
  static creal_T Xxc_data[3000];
  static double pp_coefs[11996];
  static double b_Fc_data[3000];
  static double md[3000];
  static double rowIdx_data[3000];
  static double xw[3000];
  static double dvdf[2999];
  static const char b[8] = { 't', 'w', 'o', 's', 'i', 'd', 'e', 'd' };

  emxArray_real_T *p1;
  emxArray_real_T *rowIdx1;
  double ai;
  double bi;
  double br;
  double dzzdx;
  double pidx;
  double r;
  int Xx_size[1];
  int unusedU1_size[1];
  int acoef;
  int b_i;
  int i;
  int k;
  int ret;
  unsigned int tempIdx;
  short ppd_breaks[3000];
  boolean_T b_b_data[3000];
  boolean_T b_data[3000];
  boolean_T exitg1;
  boolean_T y;
  if (rtIsNaN(Fs)) {
    Fs = 6.2831853071795862;
  }

  for (k = 0; k < 3000; k++) {
    xw[k] = x[k] * win[k];
  }

  computeDFT(xw, Fs, Xx_data, Xx_size, F_data, F_size);
  if (options_reassign) {
    for (k = 0; k < 2999; k++) {
      dvdf[k] = win[k + 1] - win[k];
    }

    xw[0] = (5.0 * dvdf[0] + dvdf[1]) / 2.0;
    xw[2999] = (5.0 * dvdf[2998] + dvdf[2997]) / 2.0;
    md[0] = 1.0;
    md[2999] = 1.0;
    for (k = 0; k < 2998; k++) {
      xw[k + 1] = 3.0 * (dvdf[k] + dvdf[k + 1]);
      md[k + 1] = 4.0;
    }

    r = 1.0 / md[0];
    md[1] -= r * 2.0;
    xw[1] -= r * xw[0];
    for (k = 0; k < 2997; k++) {
      r = 1.0 / md[k + 1];
      md[k + 2] -= r;
      xw[k + 2] -= r * xw[k + 1];
    }

    r = 2.0 / md[2998];
    md[2999] -= r;
    xw[2999] -= r * xw[2998];
    xw[2999] /= md[2999];
    for (k = 2997; k >= 0; k--) {
      xw[k + 1] = (xw[k + 1] - xw[k + 2]) / md[k + 1];
    }

    xw[0] = (xw[0] - 2.0 * xw[1]) / md[0];
    for (ret = 0; ret < 2999; ret++) {
      ai = dvdf[ret];
      pidx = xw[ret];
      dzzdx = ai - pidx;
      r = xw[ret + 1] - ai;
      pp_coefs[ret] = r - dzzdx;
      pp_coefs[ret + 2999] = 2.0 * dzzdx - r;
      pp_coefs[ret + 5998] = pidx;
      pp_coefs[ret + 8997] = win[ret];
    }

    for (i = 0; i < 3000; i++) {
      ppd_breaks[i] = (short)(i + 1);
    }

    memset(&expl_temp.coefs[0], 0, 8997U * sizeof(double));
    for (ret = 0; ret < 2999; ret++) {
      expl_temp.coefs[ret] = pp_coefs[ret] * 3.0;
      expl_temp.coefs[ret + 2999] = pp_coefs[ret + 2999] * 2.0;
      expl_temp.coefs[ret + 5998] = pp_coefs[ret + 5998];
    }

    for (i = 0; i < 3000; i++) {
      expl_temp.breaks[i] = ppd_breaks[i];
      b_Fc_data[i] = (double)i + 1.0;
    }

    ppval(&expl_temp, b_Fc_data, xw);
    r = Fs / 6.2831853071795862;
    for (k = 0; k < 3000; k++) {
      ai = xw[k] * r;
      xw[k] = ai;
      md[k] = x[k] * ai;
    }

    computeDFT(md, Fs, Xxc_data, Xx_size, b_Fc_data, unusedU1_size);
    for (b_i = 0; b_i < 3000; b_i++) {
      for (i = 0; i < 3000; i++) {
        ai = b_Fc_data[i];
        b_data[i] = rtIsInf(ai);
        b_b_data[i] = rtIsNaN(ai);
      }

      y = true;
      k = 0;
      exitg1 = false;
      while ((!exitg1) && (k < 3000)) {
        if ((!b_data[k]) && (!b_b_data[k])) {
          y = false;
          exitg1 = true;
        } else {
          k++;
        }
      }

      if (y) {
        b_Fc_data[b_i] = 0.0;
      } else {
        dzzdx = Xxc_data[b_i].re;
        ai = Xxc_data[b_i].im;
        br = Xx_data[b_i].re;
        bi = Xx_data[b_i].im;
        if (bi == 0.0) {
          if (ai == 0.0) {
            r = 0.0;
          } else {
            r = ai / br;
          }
        } else if (br == 0.0) {
          if (dzzdx == 0.0) {
            r = 0.0;
          } else {
            r = -(dzzdx / bi);
          }
        } else {
          r = fabs(br);
          pidx = fabs(bi);
          if (r > pidx) {
            r = bi / br;
            r = (ai - r * dzzdx) / (br + r * bi);
          } else if (pidx == r) {
            if (br > 0.0) {
              br = 0.5;
            } else {
              br = -0.5;
            }

            if (bi > 0.0) {
              bi = 0.5;
            } else {
              bi = -0.5;
            }

            r = (ai * br - dzzdx * bi) / r;
          } else {
            r = br / bi;
            r = (r * ai - dzzdx) / (bi + r * br);
          }
        }

        b_Fc_data[b_i] = -r;
      }
    }

    if (F_size[0] == 1) {
      ret = 3000;
    } else if (F_size[0] == 3000) {
      ret = 3000;
    } else {
      ret = (short)F_size[0];
    }

    acoef = (F_size[0] != 1);
    i = ret - 1;
    for (k = 0; k <= i; k++) {
      xw[k] = F_data[acoef * k] + b_Fc_data[k];
    }

    Fc_size[0] = ret;
    Fc_size[1] = 1;
    if (0 <= ret - 1) {
      memcpy(&Fc_data[0], &xw[0], ret * sizeof(double));
    }
  } else {
    Fc_size[0] = 0;
    Fc_size[1] = 0;
  }

  r = 0.0;
  for (i = 0; i < 3000; i++) {
    ai = win[i];
    r += ai * ai;
  }

  Pxx_size[0] = 3000;
  for (i = 0; i < 3000; i++) {
    dzzdx = Xx_data[i].re;
    ai = Xx_data[i].im;
    pidx = dzzdx * dzzdx - ai * -ai;
    if (dzzdx * -ai + ai * dzzdx == 0.0) {
      pidx /= r;
    } else if (pidx == 0.0) {
      pidx = 0.0;
    } else {
      pidx /= r;
    }

    Pxx_data[i] = pidx;
  }

  if (options_reassign) {
    acoef = F_size[0];
    ret = memcmp(&options_range[0], &b[0], 8);
    if (ret == 0) {
      r = F_data[F_size[0] - 1] - F_data[0];
      ret = Fc_size[0] * Fc_size[1];
      for (i = 0; i < ret; i++) {
        b_Fc_data[i] = (Fc_data[i] - F_data[0]) * ((double)F_size[0] - 1.0) / r;
      }

      for (k = 0; k < ret; k++) {
        b_Fc_data[k] = rt_roundd_snf(b_Fc_data[k]);
      }

      for (k = 0; k < ret; k++) {
        rowIdx_data[k] = b_mod(b_Fc_data[k], acoef);
      }

      for (i = 0; i < ret; i++) {
        rowIdx_data[i]++;
      }
    } else {
      r = F_data[F_size[0] - 1] - F_data[0];
      ret = Fc_size[0] * Fc_size[1];
      for (i = 0; i < ret; i++) {
        rowIdx_data[i] = (Fc_data[i] - F_data[0]) * ((double)F_size[0] - 1.0) /
          r;
      }

      for (k = 0; k < ret; k++) {
        rowIdx_data[k] = rt_roundd_snf(rowIdx_data[k]);
      }

      for (i = 0; i < ret; i++) {
        rowIdx_data[i]++;
      }
    }

    r = 0.0;
    for (b_i = 0; b_i < ret; b_i++) {
      ai = rowIdx_data[b_i];
      if ((ai >= 1.0) && (ai <= acoef)) {
        r++;
      }
    }

    emxInit_real_T(&rowIdx1, 1);
    emxInit_real_T(&p1, 1);
    i = rowIdx1->size[0];
    rowIdx1->size[0] = (int)r;
    emxEnsureCapacity_real_T(rowIdx1, i);
    i = p1->size[0];
    p1->size[0] = (int)r;
    emxEnsureCapacity_real_T(p1, i);
    tempIdx = 1U;
    pidx = 1.0;
    for (b_i = 0; b_i < ret; b_i++) {
      ai = rowIdx_data[b_i];
      if ((ai >= 1.0) && (ai <= acoef)) {
        rowIdx1->data[(int)tempIdx - 1] = ai;
        p1->data[(int)tempIdx - 1] = Pxx_data[(int)pidx - 1];
        tempIdx++;
      }

      pidx++;
      if (b_mod((double)b_i + 1.0, 3000.0) == 0.0) {
        pidx = 1.0;
      }
    }

    RPxx_size[0] = F_size[0];
    ret = F_size[0];
    if (0 <= ret - 1) {
      memset(&RPxx_data[0], 0, ret * sizeof(creal_T));
    }

    i = (int)r;
    for (b_i = 0; b_i < i; b_i++) {
      ret = (int)rowIdx1->data[b_i] - 1;
      RPxx_data[ret].re += p1->data[b_i];
    }

    emxFree_real_T(&p1);
    emxFree_real_T(&rowIdx1);
  } else {
    RPxx_size[0] = 0;
    Fc_size[0] = 0;
    Fc_size[1] = 0;
  }
}

/*
 * File trailer for computeperiodogram.c
 *
 * [EOF]
 */
