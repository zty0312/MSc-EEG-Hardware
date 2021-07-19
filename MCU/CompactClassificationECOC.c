/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: CompactClassificationECOC.c
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 18-Jul-2021 18:36:04
 */

/* Include Files */
#include "CompactClassificationECOC.h"
#include "Poly.h"
#include "classifyX_internal_types.h"
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const double obj_ClassNames[4]
 *                const double obj_Prior[4]
 *                const c_classreg_learning_classif_Com obj_BinaryLearners[6]
 *                const double obj_CodingMatrix[24]
 *                const double Xin[6]
 * Return Type  : double
 */
double c_CompactClassificationECOC_pre(const double obj_ClassNames[4], const
  double obj_Prior[4], const c_classreg_learning_classif_Com obj_BinaryLearners
  [6], const double obj_CodingMatrix[24], const double Xin[6])
{
  double obj_BinaryLearners_data[252];
  double b_tmp_data[42];
  double M[24];
  double Xnorm[6];
  double d_tmp_data[6];
  double pscore[6];
  double negloss[4];
  double labels;
  double y;
  int obj_BinaryLearners_size[2];
  int tmp_size[2];
  int acoef;
  int bcoef;
  int i;
  int idx;
  int k;
  int tmp_size_idx_1;
  signed char c_tmp_data[6];
  signed char tmp_data[6];
  boolean_T x[6];
  boolean_T b[4];
  boolean_T b_y;
  boolean_T exitg1;
  for (idx = 0; idx < 24; idx++) {
    y = obj_CodingMatrix[idx];
    M[idx] = y;
    if (y == 0.0) {
      M[idx] = rtNaN;
    }
  }

  obj_BinaryLearners_size[0] = 6;
  for (idx = 0; idx < 6; idx++) {
    for (i = 0; i < 6; i++) {
      Xnorm[i] = Xin[i];
      x[i] = (obj_BinaryLearners[idx].Mu[i] == 0.0);
    }

    b_y = true;
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k <= 5)) {
      if (!x[k]) {
        b_y = false;
        exitg1 = true;
      } else {
        k++;
      }
    }

    if (!b_y) {
      for (k = 0; k < 6; k++) {
        Xnorm[k] = Xin[k] - obj_BinaryLearners[idx].Mu[k];
      }
    }

    for (i = 0; i < 6; i++) {
      x[i] = (obj_BinaryLearners[idx].Sigma[i] == 1.0);
    }

    b_y = true;
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k <= 5)) {
      if (!x[k]) {
        b_y = false;
        exitg1 = true;
      } else {
        k++;
      }
    }

    if (!b_y) {
      k = 0;
      acoef = 0;
      for (i = 0; i < 6; i++) {
        if (obj_BinaryLearners[idx].Sigma[i] > 0.0) {
          k++;
          tmp_data[acoef] = (signed char)(i + 1);
          acoef++;
        }
      }

      tmp_size_idx_1 = (signed char)k;
      if ((signed char)k != 0) {
        acoef = (k != 1);
        bcoef = (k != 1);
        i = (signed char)k - 1;
        for (k = 0; k <= i; k++) {
          d_tmp_data[k] = Xnorm[tmp_data[acoef * k] - 1] /
            obj_BinaryLearners[idx].Sigma[tmp_data[bcoef * k] - 1];
        }
      }

      acoef = 0;
      for (i = 0; i < 6; i++) {
        if (obj_BinaryLearners[idx].Sigma[i] > 0.0) {
          c_tmp_data[acoef] = (signed char)(i + 1);
          acoef++;
        }
      }

      for (i = 0; i < tmp_size_idx_1; i++) {
        Xnorm[c_tmp_data[i] - 1] = d_tmp_data[i];
      }
    }

    i = obj_BinaryLearners[idx].SupportVectorsT.size[1];
    obj_BinaryLearners_size[1] = i;
    acoef = obj_BinaryLearners[idx].SupportVectorsT.size[0] * i;
    for (i = 0; i < acoef; i++) {
      obj_BinaryLearners_data[i] = obj_BinaryLearners[idx]
        .SupportVectorsT.data[i] / obj_BinaryLearners[idx].Scale;
    }

    for (i = 0; i < 6; i++) {
      Xnorm[i] /= obj_BinaryLearners[idx].Scale;
    }

    Poly(obj_BinaryLearners_data, obj_BinaryLearners_size, Xnorm, b_tmp_data,
         tmp_size);
    y = 0.0;
    acoef = tmp_size[1];
    for (i = 0; i < acoef; i++) {
      y += b_tmp_data[i] * obj_BinaryLearners[idx].Alpha.data[i];
    }

    pscore[idx] = y + obj_BinaryLearners[idx].Bias;
  }

  for (k = 0; k < 4; k++) {
    y = 0.0;
    acoef = 0;
    for (i = 0; i < 6; i++) {
      y += fmax(0.0, 1.0 - M[k + (i << 2)] * pscore[i]);
      acoef++;
    }

    if (acoef == 0) {
      y = rtNaN;
    } else {
      y /= (double)acoef;
    }

    y = -(y / 2.0);
    negloss[k] = y;
    b[k] = rtIsNaN(y);
  }

  b_y = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k <= 3)) {
    if (!b[k]) {
      b_y = false;
      exitg1 = true;
    } else {
      k++;
    }
  }

  maximum(obj_Prior, &y, &acoef);
  labels = obj_ClassNames[acoef - 1];
  if (!b_y) {
    maximum(negloss, &y, &acoef);
    if (acoef < 0) {
      acoef = 0;
    }

    labels = obj_ClassNames[acoef - 1];
  }

  return labels;
}

/*
 * File trailer for CompactClassificationECOC.c
 *
 * [EOF]
 */
