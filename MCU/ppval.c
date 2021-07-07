/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: ppval.c
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 07-Jul-2021 14:39:23
 */

/* Include Files */
#include "ppval.h"
#include "freq_domain_internal_types.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const struct_T *pp
 *                const double x[3000]
 *                double v[3000]
 * Return Type  : void
 */
void ppval(const struct_T *pp, const double x[3000], double v[3000])
{
  double xloc;
  int high_i;
  int ix;
  int low_i;
  int low_ip1;
  int mid_i;

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(xloc,low_i,low_ip1,high_i,mid_i)

  for (ix = 0; ix < 3000; ix++) {
    xloc = x[ix];
    if (!rtIsNaN(xloc)) {
      low_i = 0;
      low_ip1 = 2;
      high_i = 3000;
      while (high_i > low_ip1) {
        mid_i = ((low_i + high_i) + 1) >> 1;
        if (x[ix] >= pp->breaks[mid_i - 1]) {
          low_i = mid_i - 1;
          low_ip1 = mid_i + 1;
        } else {
          high_i = mid_i;
        }
      }

      xloc = x[ix] - pp->breaks[low_i];
      xloc = xloc * (xloc * pp->coefs[low_i] + pp->coefs[low_i + 2999]) +
        pp->coefs[low_i + 5998];
    }

    v[ix] = xloc;
  }
}

/*
 * File trailer for ppval.c
 *
 * [EOF]
 */
