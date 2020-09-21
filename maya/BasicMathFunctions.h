/*******************************************************/
/*      "C" Language Integrated Production System      */
/*                                                     */
/*             CLIPS Version 6.40  08/25/16            */
/*                                                     */
/*             BASIC MATH FUNCTIONS MODULE             */
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
/*      6.24: Renamed BOOLEAN macro type to intBool.         */
/*                                                           */
/*      6.30: Support for long long integers.                */
/*                                                           */
/*            Converted API macros to function calls.        */
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
/*            Auto-float-dividend always enabled.            */
/*                                                           */
/*************************************************************/

#ifndef _H_bmathfun

#pragma once

#define _H_bmathfun

#include "Evaluation.h"

void BasicMathFunctionDefinitions(Environment *);
void AdditionFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void MultiplicationFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void SubtractionFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void DivisionFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void DivFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void IntegerFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void FloatFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void AbsFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void MinFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void MaxFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);

#endif




