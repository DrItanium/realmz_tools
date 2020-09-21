/*******************************************************/
/*      "C" Language Integrated Production System      */
/*                                                     */
/*             CLIPS Version 6.40  02/19/20            */
/*                                                     */
/*                 DEFRULE HEADER FILE                 */
/*******************************************************/

/*************************************************************/
/* Purpose: Defines basic defrule primitive functions such   */
/*   as allocating and deallocating, traversing, and finding */
/*   defrule data structures.                                */
/*                                                           */
/* Principal Programmer(s):                                  */
/*      Gary D. Riley                                        */
/*                                                           */
/* Contributing Programmer(s):                               */
/*      Brian L. Dantes                                      */
/*                                                           */
/* Revision History:                                         */
/*                                                           */
/*      6.24: Removed DYNAMIC_SALIENCE and                   */
/*            LOGICAL_DEPENDENCIES compilation flags.        */
/*                                                           */
/*            Removed CONFLICT_RESOLUTION_STRATEGIES         */
/*            compilation flag.                              */
/*                                                           */
/*            Renamed BOOLEAN macro type to intBool.         */
/*                                                           */
/*            Corrected code to remove run-time program      */
/*            compiler warnings.                             */
/*                                                           */
/*      6.30: Removed conditional code for unsupported       */
/*            compilers/operating systems (IBM_MCW,          */
/*            MAC_MCW, and IBM_TBC).                         */
/*                                                           */
/*            Added support for hashed memories.             */
/*                                                           */
/*            Added additional developer statistics to help  */
/*            analyze join network performance.              */
/*                                                           */
/*            Added salience groups to improve performance   */
/*            with large numbers of activations of different */
/*            saliences.                                     */
/*                                                           */
/*            Added EnvGetDisjunctCount and                  */
/*            EnvGetNthDisjunct functions.                   */
/*                                                           */
/*            Added const qualifiers to remove C++           */
/*            deprecation warnings.                          */
/*                                                           */
/*            Converted API macros to function calls.        */
/*                                                           */
/*            Changed find construct functionality so that   */
/*            imported modules are search when locating a    */
/*            named construct.                               */
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
/*************************************************************/

#ifndef _H_ruledef

#pragma once

#define _H_ruledef

#define GetDisjunctIndex(r) (r->header.bsaveID)

typedef struct defrule Defrule;
struct defruleModule;

#include "Construct.h"
#include "Expression.h"
#include "Network.h"
#include "Defrule.h"
#include "Symbol.h"
#include "Agenda.h"
#include "Constraint.h"
#include "Construct.h"
#include "Evaluation.h"
#include "Defmodule.h"

struct defrule {
    ConstructHeader header;
    int salience;
    unsigned short localVarCnt;
    unsigned int complexity: 11;
    unsigned int afterBreakpoint: 1;
    unsigned int watchActivation: 1;
    unsigned int watchFiring: 1;
    unsigned int autoFocus: 1;
    unsigned int executing: 1;
    struct expr *dynamicSalience;
    struct expr *actions;
    struct joinNode *logicalJoin;
    struct joinNode *lastJoin;
    Defrule *disjunct;
};



struct defruleModule {
    struct defmoduleItemHeader header;
    struct salienceGroup *groupings;
    struct activation *agenda;
};

#ifndef ALPHA_MEMORY_HASH_SIZE
#define ALPHA_MEMORY_HASH_SIZE       63559L
#endif

#define DEFRULE_DATA 16

struct defruleData {
    Construct *DefruleConstruct;
    unsigned DefruleModuleIndex;
    unsigned long long CurrentEntityTimeTag;
    struct alphaMemoryHash **AlphaMemoryTable;
    bool BetaMemoryResizingFlag;
    struct joinLink *RightPrimeJoins;
    struct joinLink *LeftPrimeJoins;

#if DEBUGGING_FUNCTIONS
    bool WatchRules;
    int DeletedRuleDebugFlags;
#endif
#if DEVELOPER
    bool WatchRuleAnalysis;
#endif
};

#define DefruleData(theEnv) ((struct defruleData *) GetEnvironmentData(theEnv,DEFRULE_DATA))

#define GetPreviousJoin(theJoin) \
   (((theJoin)->joinFromTheRight) ? \
    ((struct joinNode *) (theJoin)->rightSideEntryStructure) : \
    ((theJoin)->lastLevel))
#define GetPatternForJoin(theJoin) \
   (((theJoin)->joinFromTheRight) ? \
    NULL : \
    ((theJoin)->rightSideEntryStructure))

void InitializeDefrules(Environment *);
Defrule *FindDefrule(Environment *, const char *);
Defrule *FindDefruleInModule(Environment *, const char *);
Defrule *GetNextDefrule(Environment *, Defrule *);
struct defruleModule *GetDefruleModuleItem(Environment *, Defmodule *);
bool DefruleIsDeletable(Defrule *);
#if BLOAD_AND_BSAVE
void AddBetaMemoriesToJoin(Environment *, struct joinNode *);
#endif
long GetDisjunctCount(Environment *, Defrule *);
Defrule *GetNthDisjunct(Environment *, Defrule *, long);
const char *DefruleModule(Defrule *);
const char *DefruleName(Defrule *);
const char *DefrulePPForm(Defrule *);

#endif /* _H_ruledef */


