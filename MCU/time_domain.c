/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: time_domain.c
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 05-Jun-2021 08:41:31
 */

/* Include Files */
#include "time_domain.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <stdio.h>


#define proc_frame 6000
#define fea_vec_frame 6
/* Function Definitions */
/*
 * %% Time Domain
 * standard statistics  (2 features)
 * Arguments    : const double input[proc_frame]
 *                double epochLength
 *                double feature_time_dom[7]
 * Return Type  : void
 */
double* time_domain(const double input[proc_frame],  double
                 feature_time_dom[fea_vec_frame])
{
	  double x0[proc_frame];
	  double Activity;
	  double Mobility_tmp;
	  double m4;
	  double s2;
	  double t;
	  double xbar;
	  double y;
	  int c;
	  int i;
	  int k;
	  int num = 0;



	  /* Kurtosis */
	  t = 0.0;
	  c = 0;
	  for (k = 0; k < proc_frame; k++) {
	    y = input[k];
	    if (!rtIsNaN(y)) {
	      t += y;
	      c++;
	    }
	  }
	  if (c == 0) {
	    xbar = rtNaN;
	  } else {
	    xbar = t / (double)c;
	  }

	  s2 = 0.0;
	  c = 0;
	  for (k = 0; k < proc_frame; k++) {
	    y = input[k] - xbar;
	    y *= y;
	    x0[k] = y;
	    if (!rtIsNaN(y)) {
	      s2 += y;
	      c++;
	    }
	  }

	  if (c == 0) {
	    s2 = rtNaN;
	  } else {
	    s2 /= (double)c;
	  }

	  m4 = 0.0;
	  c = 0;
	  for (k = 0; k < proc_frame; k++) {
	    y = x0[k];
	    y *= y;
	    x0[k] = y;
	    if (!rtIsNaN(y)) {
	      m4 += y;
	      c++;
	    }
	  }

	  if (c == 0) {
	    m4 = rtNaN;
	  } else {
	    m4 /= (double)c;
	  }

	  feature_time_dom[0] = m4 / (s2 * s2); //K


	  /* Hjorth parameters (3 features) */
	  xbar = input[0];
	  for (k = 0; k < proc_frame - 1; k++) {
		  xbar += input[k + 1];
	  }

	  xbar /= proc_frame;
	  Activity = 0.0;
	  for (k = 0; k < proc_frame; k++) {
		  t = input[k] - xbar;
		  Activity += t * t;
	  }

	  Activity /= (proc_frame - 1);
	  x0[0] = input[1] - input[0];
	  for (c = 0; c < (proc_frame - 2); c++) {
		  x0[c + 1] = (input[c + 2] - input[c]) / 2.0;
	  }

	  x0[proc_frame - 1] = input[proc_frame - 1] - input[proc_frame - 2];
	  xbar = x0[0];
	  for (k = 0; k < (proc_frame - 1); k++) {
		  xbar += x0[k + 1];
	  }

	  xbar /= proc_frame;
	  Mobility_tmp = 0.0;
	  for (k = 0; k < proc_frame; k++) {
		  t = x0[k] - xbar;
		  Mobility_tmp += t * t;
	  }

	  Mobility_tmp /= (proc_frame - 1);
	  feature_time_dom[1] = sqrt(Mobility_tmp / Activity); //mobility



	  /* numZerocross */

	  for (i = 0; i <proc_frame - 1; i++) {
		  if (input[i] * input[i + 1] < 0 || input[i] == 0)
			  num++;
	  }
	  feature_time_dom[2] = num;

  return feature_time_dom;
}

/*
 * File trailer for time_domain.c
 *
 * [EOF]
 */
