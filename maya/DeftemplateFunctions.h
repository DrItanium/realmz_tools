/*******************************************************/
/*      "C" Language Integrated Production System      */
/*                                                     */
/*             CLIPS Version 6.40  11/01/16            */
/*                                                     */
/*          DEFTEMPLATE FUNCTION HEADER FILE           */
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
/*      6.24: Added deftemplate-slot-names,                  */
/*            deftemplate-slot-default-value,                */
/*            deftemplate-slot-cardinality,                  */
/*            deftemplate-slot-allowed-values,               */
/*            deftemplate-slot-range,                        */
/*            deftemplate-slot-types,                        */
/*            deftemplate-slot-multip,                       */
/*            deftemplate-slot-singlep,                      */
/*            deftemplate-slot-existp, and                   */
/*            deftemplate-slot-defaultp functions.           */
/*                                                           */
/*            Renamed BOOLEAN macro type to intBool.         */
/*                                                           */
/*      6.30: Support for deftemplate slot facets.           */
/*                                                           */
/*            Added deftemplate-slot-facet-existp and        */
/*            deftemplate-slot-facet-value functions.        */
/*                                                           */
/*            Support for long long integers.                */
/*                                                           */
/*            Used gensprintf instead of sprintf.            */
/*                                                           */
/*            Support for modify callback function.          */
/*                                                           */
/*            Added additional argument to function          */
/*            CheckDeftemplateAndSlotArguments to specify    */
/*            the expected number of arguments.              */
/*                                                           */
/*            Added const qualifiers to remove C++           */
/*            deprecation warnings.                          */
/*                                                           */
/*            Converted API macros to function calls.        */
/*                                                           */
/*            Added code to prevent a clear command from     */
/*            being executed during fact assertions via      */
/*            Increment/DecrementClearReadyLocks API.        */
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
/*            Modify command preserves fact id and address.  */
/*                                                           */
/*************************************************************/

#ifndef _H_tmpltfun

#pragma once

#define _H_tmpltfun

#include "Expression.h"
#include "Fact.h"
#include "Symbol.h"
#include "Deftemplate.h"

bool UpdateModifyDuplicate(Environment *, struct expr *, const char *, void *);
struct expr *ModifyParse(Environment *, struct expr *, const char *);
struct expr *DuplicateParse(Environment *, struct expr *, const char *);
void DeftemplateFunctions(Environment *);
void ModifyCommand(Environment *theEnv, UDFContext *context, UDFValue *ret);
void DuplicateCommand(Environment *theEnv, UDFContext *context, UDFValue *ret);
void DeftemplateSlotNamesFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void DeftemplateSlotNames(Deftemplate *, CLIPSValue *);
void DeftemplateSlotDefaultValueFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
bool DeftemplateSlotDefaultValue(Deftemplate *, const char *, CLIPSValue *);
void DeftemplateSlotCardinalityFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
bool DeftemplateSlotCardinality(Deftemplate *, const char *, CLIPSValue *);
void DeftemplateSlotAllowedValuesFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
bool DeftemplateSlotAllowedValues(Deftemplate *, const char *, CLIPSValue *);
void DeftemplateSlotRangeFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
bool DeftemplateSlotRange(Deftemplate *, const char *, CLIPSValue *);
void DeftemplateSlotTypesFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
bool DeftemplateSlotTypes(Deftemplate *, const char *, CLIPSValue *);
void DeftemplateSlotMultiPFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
bool DeftemplateSlotMultiP(Deftemplate *, const char *);
void DeftemplateSlotSinglePFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
bool DeftemplateSlotSingleP(Deftemplate *, const char *);
void DeftemplateSlotExistPFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
bool DeftemplateSlotExistP(Deftemplate *, const char *);
void DeftemplateSlotDefaultPFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
DefaultType DeftemplateSlotDefaultP(Deftemplate *, const char *);
void DeftemplateSlotFacetExistPFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
bool DeftemplateSlotFacetExistP(Environment *, Deftemplate *, const char *, const char *);
void DeftemplateSlotFacetValueFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
bool DeftemplateSlotFacetValue(Environment *, Deftemplate *, const char *, const char *, UDFValue *);
Fact *ReplaceFact(Environment *, Fact *, CLIPSValue *, char *);

#endif /* _H_tmpltfun */




