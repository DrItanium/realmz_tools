/*******************************************************/
/*      "C" Language Integrated Production System      */
/*                                                     */
/*             CLIPS Version 6.40  11/13/17            */
/*                                                     */
/*          INSTANCE PRIMITIVE SUPPORT MODULE          */
/*******************************************************/

/*************************************************************/
/* Purpose:                                                  */
/*                                                           */
/* Principal Programmer(s):                                  */
/*      Brian L. Dantes                                      */
/*                                                           */
/* Contributing Programmer(s):                               */
/*                                                           */
/* Revision History:                                         */
/*                                                           */
/*      6.23: Correction for FalseSymbol/TrueSymbol. DR0859  */
/*                                                           */
/*      6.24: Removed LOGICAL_DEPENDENCIES compilation flag. */
/*                                                           */
/*            Converted INSTANCE_PATTERN_MATCHING to         */
/*            DEFRULE_CONSTRUCT.                             */
/*                                                           */
/*            Renamed BOOLEAN macro type to intBool.         */
/*                                                           */
/*      6.30: Changed integer type/precision.                */
/*                                                           */
/*            Used gensprintf instead of sprintf.            */
/*                                                           */
/*            Changed garbage collection algorithm.          */
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
/*            UDF redesign.                                  */
/*                                                           */
/*************************************************************/

#ifndef _H_insmngr

#pragma once

#define _H_insmngr

#include "Object.h"
#include "InstanceCommand.h"

void InitializeInstanceCommand(Environment *theEnv, UDFContext *context, UDFValue *ret);
void MakeInstanceCommand(Environment *theEnv, UDFContext *context, UDFValue *ret);
CLIPSLexeme *GetFullInstanceName(Environment *, Instance *);
Instance *BuildInstance(Environment *, CLIPSLexeme *, Defclass *, bool);
void InitSlotsCommand(Environment *theEnv, UDFContext *context, UDFValue *ret);
UnmakeInstanceError QuashInstance(Environment *, Instance *);

void InactiveInitializeInstance(Environment *theEnv, UDFContext *context, UDFValue *ret);
void InactiveMakeInstance(Environment *theEnv, UDFContext *context, UDFValue *ret);

InstanceBuilder *CreateInstanceBuilder(Environment *, const char *);
PutSlotError IBPutSlot(InstanceBuilder *, const char *, CLIPSValue *);

Instance *IBMake(InstanceBuilder *, const char *);

void IBDispose(InstanceBuilder *);
void IBAbort(InstanceBuilder *);
InstanceBuilderError IBSetDefclass(InstanceBuilder *, const char *);

PutSlotError IBPutSlotCLIPSInteger(InstanceBuilder *, const char *, CLIPSInteger *);
PutSlotError IBPutSlotInteger(InstanceBuilder *, const char *, long long);

PutSlotError IBPutSlotCLIPSFloat(InstanceBuilder *, const char *, CLIPSFloat *);
PutSlotError IBPutSlotFloat(InstanceBuilder *, const char *, double);

PutSlotError IBPutSlotCLIPSLexeme(InstanceBuilder *, const char *, CLIPSLexeme *);
PutSlotError IBPutSlotSymbol(InstanceBuilder *, const char *, const char *);
PutSlotError IBPutSlotString(InstanceBuilder *, const char *, const char *);
PutSlotError IBPutSlotInstanceName(InstanceBuilder *, const char *, const char *);

PutSlotError IBPutSlotFact(InstanceBuilder *, const char *, Fact *);
PutSlotError IBPutSlotInstance(InstanceBuilder *, const char *, Instance *);
PutSlotError IBPutSlotExternalAddress(InstanceBuilder *, const char *, CLIPSExternalAddress *);
PutSlotError IBPutSlotMultifield(InstanceBuilder *, const char *, Multifield *);
InstanceBuilderError IBError(Environment *);

InstanceModifier *CreateInstanceModifier(Environment *, Instance *);
PutSlotError IMPutSlot(InstanceModifier *, const char *, CLIPSValue *);
void IMDispose(InstanceModifier *);
void IMAbort(InstanceModifier *);
InstanceModifierError IMSetInstance(InstanceModifier *, Instance *);
Instance *IMModify(InstanceModifier *);

PutSlotError IMPutSlotCLIPSInteger(InstanceModifier *, const char *, CLIPSInteger *);
PutSlotError IMPutSlotInteger(InstanceModifier *, const char *, long long);

PutSlotError IMPutSlotCLIPSFloat(InstanceModifier *, const char *, CLIPSFloat *);
PutSlotError IMPutSlotFloat(InstanceModifier *, const char *, double);

PutSlotError IMPutSlotCLIPSLexeme(InstanceModifier *, const char *, CLIPSLexeme *);
PutSlotError IMPutSlotSymbol(InstanceModifier *, const char *, const char *);
PutSlotError IMPutSlotString(InstanceModifier *, const char *, const char *);
PutSlotError IMPutSlotInstanceName(InstanceModifier *, const char *, const char *);

PutSlotError IMPutSlotFact(InstanceModifier *, const char *, Fact *);
PutSlotError IMPutSlotInstance(InstanceModifier *, const char *, Instance *);
PutSlotError IMPutSlotExternalAddress(InstanceModifier *, const char *, CLIPSExternalAddress *);
PutSlotError IMPutSlotMultifield(InstanceModifier *, const char *, Multifield *);
InstanceModifierError IMError(Environment *);

#endif /* _H_insmngr */







