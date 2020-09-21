/*******************************************************/
/*      "C" Language Integrated Production System      */
/*                                                     */
/*             CLIPS Version 6.40  09/09/19            */
/*                                                     */
/*          EXTENDED MATH FUNCTIONS HEADER FILE        */
/*******************************************************/

/*************************************************************/
/* Purpose: Contains the code for numerous extended math     */
/*   functions including cos, sin, tan, sec, csc, cot, acos, */
/*   asin, atan, atan2, asec, acsc, acot, cosh, sinh, tanh,  */
/*   sech, csch, coth, acosh, asinh, atanh, asech, acsch,    */
/*   acoth, mod, exp, log, log10, sqrt, pi, deg-rad,         */
/*   rad-deg,  deg-grad, grad-deg, **, and round.            */
/*                                                           */
/* Principal Programmer(s):                                  */
/*      Gary D. Riley                                        */
/*                                                           */
/* Contributing Programmer(s):                               */
/*                                                           */
/* Revision History:                                         */
/*                                                           */
/*      6.30: Removed conditional code for unsupported       */
/*            compilers/operating systems (IBM_MCW and       */
/*            MAC_MCW).                                      */
/*                                                           */
/*            Support for long long integers.                */
/*                                                           */
/*            Renamed EX_MATH compiler flag to               */
/*            EXTENDED_MATH_FUNCTIONS.                       */
/*                                                           */
/*            Added const qualifiers to remove C++           */
/*            deprecation warnings.                          */
/*                                                           */
/*      6.40: Removed LOCALE definition.                     */
/*                                                           */
/*            Pragma once and other inclusion changes.       */
/*                                                           */
/*            Removed use of void pointers for specific      */
/*            data structures.                               */
/*                                                           */
/*            UDF redesign.                                  */
/*                                                           */
/*            Added atan2 function.                          */
/*                                                           */
/*************************************************************/

#ifndef _H_emathfun

#pragma once

#define _H_emathfun

void ExtendedMathFunctionDefinitions(Environment *);
#if EXTENDED_MATH_FUNCTIONS
void CosFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void SinFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void TanFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void SecFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void CscFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void CotFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void AcosFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void AsinFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void AtanFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void Atan2Function(Environment *theEnv, UDFContext *context, UDFValue *ret);
void AsecFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void AcscFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void AcotFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void CoshFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void SinhFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void TanhFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void SechFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void CschFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void CothFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void AcoshFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void AsinhFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void AtanhFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void AsechFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void AcschFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void AcothFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void RoundFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void ModFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void ExpFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void LogFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void Log10Function(Environment *theEnv, UDFContext *context, UDFValue *ret);
void SqrtFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void PiFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void DegRadFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void RadDegFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void DegGradFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void GradDegFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void PowFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
#endif

#endif /* _H_emathfun */



