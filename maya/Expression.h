/*******************************************************/
/*      "C" Language Integrated Production System      */
/*                                                     */
/*             CLIPS Version 6.40  11/01/16            */
/*                                                     */
/*               EXPRESSION HEADER FILE                */
/*******************************************************/

/*************************************************************/
/* Purpose: Contains routines for creating, deleting,        */
/*   compacting, installing, and hashing expressions.        */
/*                                                           */
/* Principal Programmer(s):                                  */
/*      Gary D. Riley                                        */
/*                                                           */
/* Contributing Programmer(s):                               */
/*      Brian L. Dantes                                      */
/*                                                           */
/* Revision History:                                         */
/*                                                           */
/*      6.24: Renamed BOOLEAN macro type to intBool.         */
/*                                                           */
/*      6.30: Removed conditional code for unsupported       */
/*            compilers/operating systems (IBM_MCW and       */
/*            MAC_MCW).                                      */
/*                                                           */
/*            Changed integer type/precision.                */
/*                                                           */
/*            Changed expression hashing value.              */
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
/*            Eval support for run time and bload only.      */
/*                                                           */
/*************************************************************/

#ifndef _H_expressn

#pragma once

#define _H_expressn

struct exprHashNode;
typedef struct savedContexts SavedContexts;

#include <stdio.h>
#include "Entities.h"
#include "Construct.h"
#include "ExternalFunctions.h"
#include "Scanner.h"

/******************************/
/* Expression Data Structures */
/******************************/

struct expr {
    unsigned short type;
    union {
        void *value;
        CLIPSLexeme *lexemeValue;
        CLIPSFloat *floatValue;
        CLIPSInteger *integerValue;
        CLIPSBitMap *bitMapValue;
        ConstructHeader *constructValue;
        FunctionDefinition *functionValue;
    };
    Expression *argList;
    Expression *nextArg;
};

#define arg_list argList
#define next_arg nextArg

typedef struct exprHashNode {
    unsigned hashval;
    unsigned count;
    Expression *exp;
    struct exprHashNode *next;
    unsigned long bsaveID;
} EXPRESSION_HN;

struct savedContexts {
    bool rtn;
    bool brk;
    struct savedContexts *nxt;
};

#define EXPRESSION_HASH_SIZE 503

/********************/
/* ENVIRONMENT DATA */
/********************/

#define EXPRESSION_DATA 45

struct expressionData {
    FunctionDefinition *PTR_AND;
    FunctionDefinition *PTR_OR;
    FunctionDefinition *PTR_EQ;
    FunctionDefinition *PTR_NEQ;
    FunctionDefinition *PTR_NOT;
    EXPRESSION_HN **ExpressionHashTable;
#if (BLOAD_AND_BSAVE)
    unsigned long NumberOfExpressions;
    Expression *ExpressionArray;
    unsigned long ExpressionCount;
#endif
    SavedContexts *svContexts;
    bool ReturnContext;
    bool BreakContext;
    bool SequenceOpMode;
};

#define ExpressionData(theEnv) ((struct expressionData *) GetEnvironmentData(theEnv,EXPRESSION_DATA))

/********************/
/* Global Functions */
/********************/

void ReturnExpression(Environment *, Expression *);
void ExpressionInstall(Environment *, Expression *);
void ExpressionDeinstall(Environment *, Expression *);
Expression *PackExpression(Environment *, Expression *);
void ReturnPackedExpression(Environment *, Expression *);
void InitExpressionData(Environment *);
void InitExpressionPointers(Environment *);
bool SetSequenceOperatorRecognition(Environment *, bool);
bool GetSequenceOperatorRecognition(Environment *);
Expression *AddHashedExpression(Environment *, Expression *);
void RemoveHashedExpression(Environment *, Expression *);
#if BLOAD_AND_BSAVE
unsigned long HashedExpressionIndex(Environment *, Expression *);
#endif
#define ExpressionPointer(i) ((struct expr *) (((i) == ULONG_MAX) ? NULL : &ExpressionData(theEnv)->ExpressionArray[i]))
#define HashedExpressionPointer(i) ExpressionPointer(i)

void AllocateExpressions(Environment *);
void RefreshExpressions(Environment *);
void ClearBloadedExpressions(Environment *);
void FindHashedExpressions(Environment *);
void BsaveHashedExpressions(Environment *, FILE *);
void BsaveConstructExpressions(Environment *, FILE *);
void BsaveExpression(Environment *, struct expr *, FILE *);

bool ConstantExpression(struct expr *);
void PrintExpression(Environment *, const char *, struct expr *);
unsigned long ExpressionSize(struct expr *);
unsigned short CountArguments(struct expr *);
struct expr *CopyExpression(Environment *, struct expr *);
bool ExpressionContainsVariables(struct expr *, bool);
bool IdenticalExpression(struct expr *, struct expr *);
struct expr *GenConstant(Environment *, unsigned short, void *);
bool CheckArgumentAgainstRestriction(Environment *, struct expr *, unsigned);
bool ConstantType(int);
struct expr *CombineExpressions(Environment *, struct expr *, struct expr *);
struct expr *AppendExpressions(struct expr *, struct expr *);
struct expr *NegateExpression(Environment *, struct expr *);
typedef enum {
    FAE_NO_ERROR = 0,
    FAE_COUNT_ERROR,
    FAE_TYPE_ERROR
} FunctionArgumentsError;

struct expr *Function0Parse(Environment *, const char *);
struct expr *Function1Parse(Environment *, const char *);
struct expr *Function2Parse(Environment *, const char *, const char *);
void PushRtnBrkContexts(Environment *);
void PopRtnBrkContexts(Environment *);
bool ReplaceSequenceExpansionOps(Environment *, struct expr *, struct expr *,
                                 void *, void *);
struct expr *CollectArguments(Environment *, struct expr *, const char *);
struct expr *ArgumentParse(Environment *, const char *, bool *);
struct expr *ParseAtomOrExpression(Environment *, const char *, struct token *);
Expression *ParseConstantArguments(Environment *, const char *, bool *);
struct expr *GroupActions(Environment *, const char *, struct token *,
                          bool, const char *, bool);
struct expr *RemoveUnneededProgn(Environment *, struct expr *);
void PopulateRestriction(Environment *, unsigned *, unsigned, const char *, unsigned int);

FunctionArgumentsError CheckExpressionAgainstRestrictions(Environment *, struct expr *,
                                                          struct functionDefinition *, const char *);

bool RestrictionExists(const char *, int);
#endif




