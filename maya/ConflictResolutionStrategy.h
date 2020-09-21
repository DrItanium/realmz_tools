/*******************************************************/
/*      "C" Language Integrated Production System      */
/*                                                     */
/*             CLIPS Version 6.40  11/01/16            */
/*                                                     */
/*      CONFLICT RESOLUTION STRATEGY HEADER MODULE     */
/*******************************************************/

/*************************************************************/
/* Purpose: Used to determine where a new activation is      */
/*   placed on the agenda based on the current conflict      */
/*   resolution strategy (depth, breadth, mea, lex,          */
/*   simplicity, or complexity). Also provides the           */
/*   set-strategy and get-strategy commands.                 */
/*                                                           */
/* Principal Programmer(s):                                  */
/*      Gary D. Riley                                        */
/*                                                           */
/* Contributing Programmer(s):                               */
/*                                                           */
/* Revision History:                                         */
/*                                                           */
/*      6.23: Corrected compilation errors for files         */
/*            generated by constructs-to-c. DR0861           */
/*                                                           */
/*      6.24: Removed CONFLICT_RESOLUTION_STRATEGIES         */
/*            compilation flag.                              */
/*                                                           */
/*      6.30: Added salience groups to improve performance   */
/*            with large numbers of activations of different */
/*            saliences.                                     */
/*                                                           */
/*            Removed pseudo-facts used for not CEs.         */
/*                                                           */
/*            Changed integer type/precision.                */
/*                                                           */
/*            Added const qualifiers to remove C++           */
/*            deprecation warnings.                          */
/*                                                           */
/*            Converted API macros to function calls.        */
/*                                                           */
/*      6.40: Removed LOCALE definition.                     */
/*                                                           */
/*            Pragma once and other inclusion changes.       */
/*                                                           */
/*            Removed use of void pointers for specific      */
/*            data structures.                               */
/*                                                           */
/*            ALLOW_ENVIRONMENT_GLOBALS no longer supported. */
/*                                                           */
/*            UDF redesign.                                  */
/*                                                           */
/*************************************************************/

#ifndef _H_crstrtgy

#pragma once

#define _H_crstrtgy

typedef enum {
    DEPTH_STRATEGY,
    BREADTH_STRATEGY,
    LEX_STRATEGY,
    MEA_STRATEGY,
    COMPLEXITY_STRATEGY,
    SIMPLICITY_STRATEGY,
    RANDOM_STRATEGY
} StrategyType;

#include "Agenda.h"
#include "Entities.h"

#define DEFAULT_STRATEGY DEPTH_STRATEGY

void PlaceActivation(Environment *, Activation **, Activation *, struct salienceGroup *);
StrategyType SetStrategy(Environment *, StrategyType);
StrategyType GetStrategy(Environment *);
void SetStrategyCommand(Environment *theEnv, UDFContext *context, UDFValue *ret);
void GetStrategyCommand(Environment *theEnv, UDFContext *context, UDFValue *ret);

#endif /* _H_crstrtgy */

