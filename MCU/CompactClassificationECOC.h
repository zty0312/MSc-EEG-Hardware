/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: CompactClassificationECOC.h
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 18-Jul-2021 18:36:04
 */

#ifndef COMPACTCLASSIFICATIONECOC_H
#define COMPACTCLASSIFICATIONECOC_H

/* Include Files */
#include "classifyX_internal_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>
#ifdef __cplusplus

extern "C" {

#endif

  /* Function Declarations */
  double c_CompactClassificationECOC_pre(const double obj_ClassNames[4], const
    double obj_Prior[4], const c_classreg_learning_classif_Com
    obj_BinaryLearners[6], const double obj_CodingMatrix[24], const double Xin[6]);

#ifdef __cplusplus

}
#endif
#endif

/*
 * File trailer for CompactClassificationECOC.h
 *
 * [EOF]
 */
