/*******************************************************/
/*      "C" Language Integrated Production System      */
/*                                                     */
/*             CLIPS Version 6.40  08/25/16            */
/*                                                     */
/*                 DEVELOPER HEADER FILE               */
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
/*      6.24: Converted INSTANCE_PATTERN_MATCHING to         */
/*            DEFRULE_CONSTRUCT.                             */
/*                                                           */
/*      6.30: Added support for hashed alpha memories.       */
/*                                                           */
/*            Changed garbage collection algorithm.          */
/*            Functions enable-gc-heuristics and             */
/*            disable-gc-heuristics are no longer supported. */
/*                                                           */
/*            Changed integer type/precision.                */
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
/*            UDF redesign.                                  */
/*                                                           */
/*************************************************************/

#ifndef _H_developr

#pragma once

#define _H_developr

void DeveloperCommands(Environment *);
void PrimitiveTablesInfoCommand(Environment *theEnv, UDFContext *context, UDFValue *ret);
void PrimitiveTablesUsageCommand(Environment *theEnv, UDFContext *context, UDFValue *ret);

#if DEFTEMPLATE_CONSTRUCT
void ShowFactPatternNetworkCommand(Environment *theEnv, UDFContext *context, UDFValue *ret);
void ValidateFactIntegrityCommand(Environment *theEnv, UDFContext *context, UDFValue *ret);
#endif
void PrintObjectPatternNetworkCommand(Environment *theEnv, UDFContext *context, UDFValue *ret);
void InstanceTableUsageCommand(Environment *theEnv, UDFContext *context, UDFValue *ret);
void ValidateBetaMemoriesCommand(Environment *theEnv, UDFContext *context, UDFValue *ret);

#endif /* _H_developr */


