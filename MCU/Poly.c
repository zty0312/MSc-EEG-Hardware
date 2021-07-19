/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: Poly.c
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 18-Jul-2021 18:36:04
 */

/* Include Files */
#include "Poly.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const double svT_data[]
 *                const int svT_size[2]
 *                const double x[6]
 *                double kernelProduct_data[]
 *                int kernelProduct_size[2]
 * Return Type  : void
 */
void Poly(const double svT_data[], const int svT_size[2], const double x[6],
          double kernelProduct_data[], int kernelProduct_size[2])
{
  double temp_data[42];
  double s;
  int boffset;
  int j;
  int k;
  int n;
  n = svT_size[1];
  kernelProduct_size[1] = svT_size[1];
  for (j = 0; j < n; j++) {
    boffset = j * 6;
    s = 0.0;
    for (k = 0; k < 6; k++) {
      s += x[k] * svT_data[boffset + k];
    }

    kernelProduct_data[j] = s;
  }

  n = svT_size[1] - 1;
  for (boffset = 0; boffset <= n; boffset++) {
    kernelProduct_data[boffset]++;
  }

  n = svT_size[1];
  if (0 <= n - 1) {
    memcpy(&temp_data[0], &kernelProduct_data[0], n * sizeof(double));
  }

  kernelProduct_size[0] = 1;
  n = svT_size[1] - 1;
  for (boffset = 0; boffset <= n; boffset++) {
    kernelProduct_data[boffset] *= temp_data[boffset];
  }
}

/*
 * File trailer for Poly.c
 *
 * [EOF]
 */
