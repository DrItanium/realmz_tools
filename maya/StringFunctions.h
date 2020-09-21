/*******************************************************/
/*      "C" Language Integrated Production System      */
/*                                                     */
/*             CLIPS Version 6.40  08/27/19            */
/*                                                     */
/*          STRING_TYPE FUNCTIONS HEADER FILE          */
/*******************************************************/

/*************************************************************/
/* Purpose:                                                  */
/*                                                           */
/* Principal Programmer(s):                                  */
/*      Gary D. Riley                                        */
/*                                                           */
/* Contributing Programmer(s):                               */
/*                                                           */
/* Revision History:                                         */
/*                                                           */
/*      6.23: Correction for FalseSymbol/TrueSymbol. DR0859  */
/*                                                           */
/*      6.30: Support for long long integers.                */
/*                                                           */
/*            Removed conditional code for unsupported       */
/*            compilers/operating systems (IBM_MCW and       */
/*            MAC_MCW).                                      */
/*                                                           */
/*            Used gensprintf instead of sprintf.            */
/*                                                           */
/*            Changed integer type/precision.                */
/*                                                           */
/*            Changed garbage collection algorithm.          */
/*                                                           */
/*            Added support for UTF-8 strings to str-length, */
/*            str-index, and sub-string functions.           */
/*                                                           */
/*            Added const qualifiers to remove C++           */
/*            deprecation warnings.                          */
/*                                                           */
/*      6.40: Removed LOCALE definition.                     */
/*                                                           */
/*            Pragma once and other inclusion changes.       */
/*                                                           */
/*            Added support for booleans with <stdbool.h>.   */
/*                                                           */
/*            Removed use of void pointers for specific      */
/*            data structures.                               */
/*                                                           */
/*            ALLOW_ENVIRONMENT_GLOBALS no longer supported. */
/*                                                           */
/*            UDF redesign.                                  */
/*                                                           */
/*            Added str-replace function.                    */
/*                                                           */
/*************************************************************/

#ifndef _H_strngfun

#pragma once

#define _H_strngfun

#include "Entities.h"

typedef enum {
    EE_NO_ERROR = 0,
    EE_PARSING_ERROR,
    EE_PROCESSING_ERROR
} EvalError;

typedef enum {
    BE_NO_ERROR = 0,
    BE_COULD_NOT_BUILD_ERROR,
    BE_CONSTRUCT_NOT_FOUND_ERROR,
    BE_PARSING_ERROR,
} BuildError;

BuildError Build(Environment *, const char *);
EvalError Eval(Environment *, const char *, CLIPSValue *);
void StringFunctionDefinitions(Environment *);
void StrCatFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void SymCatFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void StrLengthFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void UpcaseFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void LowcaseFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void StrCompareFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void SubStringFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void StrIndexFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void EvalFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void BuildFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void StringToFieldFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void StringToField(Environment *, const char *, UDFValue *);
void StrReplaceFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);

#endif /* _H_strngfun */
