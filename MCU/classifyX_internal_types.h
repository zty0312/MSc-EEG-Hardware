/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: classifyX_internal_types.h
 *
 * MATLAB Coder version            : 5.1
 * C/C++ source code generated on  : 18-Jul-2021 18:36:04
 */

#ifndef CLASSIFYX_INTERNAL_TYPES_H
#define CLASSIFYX_INTERNAL_TYPES_H

/* Include Files */
#include "classifyX_types.h"
#include "rtwtypes.h"

/* Type Definitions */
#ifndef enum_c_classreg_learning_coderutils_
#define enum_c_classreg_learning_coderutils_

enum c_classreg_learning_coderutils_
{
  Logit = 0,                           /* Default value */
  Doublelogit,
  Invlogit,
  Ismax,
  Sign,
  Symmetric,
  Symmetricismax,
  Symmetriclogit,
  Identity
};

#endif                                 /*enum_c_classreg_learning_coderutils_*/

#ifndef typedef_c_classreg_learning_coderutils_
#define typedef_c_classreg_learning_coderutils_

typedef enum c_classreg_learning_coderutils_ c_classreg_learning_coderutils_;

#endif                                 /*typedef_c_classreg_learning_coderutils_*/

#ifndef enum_d_classreg_learning_coderutils_
#define enum_d_classreg_learning_coderutils_

enum d_classreg_learning_coderutils_
{
  linear = 1,                          /* Default value */
  gaussian = 2,
  rbf = 2,
  polynomial = 3
};

#endif                                 /*enum_d_classreg_learning_coderutils_*/

#ifndef typedef_d_classreg_learning_coderutils_
#define typedef_d_classreg_learning_coderutils_

typedef enum d_classreg_learning_coderutils_ d_classreg_learning_coderutils_;

#endif                                 /*typedef_d_classreg_learning_coderutils_*/

#ifndef struct_emxArray_real_T_42
#define struct_emxArray_real_T_42

struct emxArray_real_T_42
{
  double data[42];
  int size[1];
};

#endif                                 /*struct_emxArray_real_T_42*/

#ifndef typedef_emxArray_real_T_42
#define typedef_emxArray_real_T_42

typedef struct emxArray_real_T_42 emxArray_real_T_42;

#endif                                 /*typedef_emxArray_real_T_42*/

#ifndef struct_emxArray_real_T_6x42
#define struct_emxArray_real_T_6x42

struct emxArray_real_T_6x42
{
  double data[252];
  int size[2];
};

#endif                                 /*struct_emxArray_real_T_6x42*/

#ifndef typedef_emxArray_real_T_6x42
#define typedef_emxArray_real_T_6x42

typedef struct emxArray_real_T_6x42 emxArray_real_T_6x42;

#endif                                 /*typedef_emxArray_real_T_6x42*/

#ifndef typedef_c_classreg_learning_classif_Com
#define typedef_c_classreg_learning_classif_Com

typedef struct {
  emxArray_real_T_42 Alpha;
  double Bias;
  emxArray_real_T_6x42 SupportVectorsT;
  double Scale;
  double Order;
  double Mu[6];
  double Sigma[6];
  d_classreg_learning_coderutils_ KernelFunction;
  double ClassNames[2];
  int ClassNamesLength[2];
  c_classreg_learning_coderutils_ ScoreTransform;
  double Prior[2];
  boolean_T ClassLogicalIndices[2];
  double Cost[4];
} c_classreg_learning_classif_Com;

#endif                                 /*typedef_c_classreg_learning_classif_Com*/
#endif

/*
 * File trailer for classifyX_internal_types.h
 *
 * [EOF]
 */
