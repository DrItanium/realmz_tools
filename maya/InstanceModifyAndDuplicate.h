/*******************************************************/
/*      "C" Language Integrated Production System      */
/*                                                     */
/*             CLIPS Version 6.40  10/18/16            */
/*                                                     */
/*           INSTANCE MODIFY AND DUPLICATE MODULE      */
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
/*            Changed name of variable exp to theExp         */
/*            because of Unix compiler warnings of shadowed  */
/*            definitions.                                   */
/*                                                           */
/*      6.24: Converted INSTANCE_PATTERN_MATCHING to         */
/*            DEFRULE_CONSTRUCT.                             */
/*                                                           */
/*      6.30: Added DATA_OBJECT_ARRAY primitive type.        */
/*                                                           */
/*            Changed integer type/precision.                */
/*                                                           */
/*            The return value of DirectMessage indicates    */
/*            whether an execution error has occurred.       */
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
/*            Removed DATA_OBJECT_ARRAY primitive type.      */
/*                                                           */
/*            Eval support for run time and bload only.      */
/*                                                           */
/*************************************************************/

#ifndef _H_insmoddp

#pragma once

#define _H_insmoddp

#define DIRECT_MODIFY_STRING    "direct-modify"
#define MSG_MODIFY_STRING       "message-modify"
#define DIRECT_DUPLICATE_STRING "direct-duplicate"
#define MSG_DUPLICATE_STRING    "message-duplicate"

#include "Evaluation.h"

void SetupInstanceModDupCommands(Environment *);

void ModifyInstance(Environment *theEnv, UDFContext *context, UDFValue *ret);
void MsgModifyInstance(Environment *theEnv, UDFContext *context, UDFValue *ret);
void DuplicateInstance(Environment *theEnv, UDFContext *context, UDFValue *ret);
void MsgDuplicateInstance(Environment *theEnv, UDFContext *context, UDFValue *ret);

void InactiveModifyInstance(Environment *theEnv, UDFContext *context, UDFValue *ret);
void InactiveMsgModifyInstance(Environment *theEnv, UDFContext *context, UDFValue *ret);
void InactiveDuplicateInstance(Environment *theEnv, UDFContext *context, UDFValue *ret);
void InactiveMsgDuplicateInstance(Environment *theEnv, UDFContext *context, UDFValue *ret);

void DirectModifyMsgHandler(Environment *theEnv, UDFContext *context, UDFValue *ret);
void MsgModifyMsgHandler(Environment *theEnv, UDFContext *context, UDFValue *ret);
void DirectDuplicateMsgHandler(Environment *theEnv, UDFContext *context, UDFValue *ret);
void MsgDuplicateMsgHandler(Environment *theEnv, UDFContext *context, UDFValue *ret);

#endif /* _H_insmoddp */







