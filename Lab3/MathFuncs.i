%module MathFuncsDll
%{
/* Includes the header in the wrapper code */
#include "MathFuncsDll.h"
%}
/* Parse the header file to generate wrappers */
%include "MathFuncsDll.h"