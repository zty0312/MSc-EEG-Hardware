/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: freq_domain.c
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 29-Jun-2021 20:14:30
 */

/* Include Files */
#include "freq_domain.h"
#include "bandpower.h"
#include "freq_domain_data.h"
#include "freq_domain_initialize.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
/*
 * Spectral Power in Frequency Bands (3 features)
 * Arguments    : const double input[3000]
 *                double fs
 *                double feature_freq_dom[6]
 * Return Type  : void
 */
double* freq_domain(const double input[3000], double fs, double feature_freq_dom[6])
{
  double dv[2];
  double pband_alpha_data[1];
  double pband_gamma_data[1];
  double pband_theta_data[1];
  double ptot_data[1];
  double Y;
  double b_Y;
  double c_Y;
  int pband_alpha_size[2];
  int pband_gamma_size[2];
  int pband_theta_size[2];
  int ptot_size[2];

  dv[0] = 0.0;
  dv[1] = fs / 2.0;
  timedomainbandpower(input, fs, dv, ptot_data, ptot_size);
  dv[0] = 4.0;
  dv[1] = 8.0;
  timedomainbandpower(input, fs, dv, pband_theta_data, pband_theta_size);
  dv[0] = 8.0;
  dv[1] = 12.0;
  timedomainbandpower(input, fs, dv, pband_alpha_data, pband_alpha_size);
  dv[0] = 30.0;
  dv[1] = 100.0;
  timedomainbandpower(input, fs, dv, pband_gamma_data, pband_gamma_size);
  if ((pband_theta_size[1] == 0) || (ptot_size[1] == 0)) {
    Y = 0.0;
  } else {
    Y = pband_theta_data[0] / ptot_data[0];
  }

  if ((pband_alpha_size[1] == 0) || (ptot_size[1] == 0)) {
    b_Y = 0.0;
  } else {
    b_Y = pband_alpha_data[0] / ptot_data[0];
  }

  if ((pband_gamma_size[1] == 0) || (ptot_size[1] == 0)) {
    c_Y = 0.0;
  } else {
    c_Y = pband_gamma_data[0] / ptot_data[0];
  }

  feature_freq_dom[3] = 100.0 * Y;
  feature_freq_dom[4] = 100.0 * b_Y;
  feature_freq_dom[5] = 100.0 * c_Y;
  return feature_freq_dom;
}

/*
 * File trailer for freq_domain.c
 *
 * [EOF]
 */
