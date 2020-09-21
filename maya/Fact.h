//
// Created by jwscoggins on 6/20/20.
//

#ifndef MAYA_FACT_H
#define MAYA_FACT_H

typedef struct factBuilder FactBuilder;
typedef struct factModifier FactModifier;
typedef struct factHashEntry FactHashEntry;
struct factPatternNode;

#include "Setup.h"
#include "Network.h"
#include "Entities.h"
#include "Deftemplate.h"
#include "Expression.h"
#include "Evaluation.h"
#include "Scanner.h"
#include "Symbol.h"
#include "Reorder.h"

typedef void ModifyCallFunction(Environment *, Fact *, Fact *, void *);
typedef struct modifyCallFunctionItem ModifyCallFunctionItem;

typedef enum {
    RE_NO_ERROR = 0,
    RE_NULL_POINTER_ERROR,
    RE_COULD_NOT_RETRACT_ERROR,
    RE_RULE_NETWORK_ERROR
} RetractError;

typedef enum {
    AE_NO_ERROR = 0,
    AE_NULL_POINTER_ERROR,
    AE_RETRACTED_ERROR,
    AE_COULD_NOT_ASSERT_ERROR,
    AE_RULE_NETWORK_ERROR
} AssertError;

typedef enum {
    ASE_NO_ERROR = 0,
    ASE_NULL_POINTER_ERROR,
    ASE_PARSING_ERROR,
    ASE_COULD_NOT_ASSERT_ERROR,
    ASE_RULE_NETWORK_ERROR
} AssertStringError;

typedef enum {
    FBE_NO_ERROR = 0,
    FBE_NULL_POINTER_ERROR,
    FBE_DEFTEMPLATE_NOT_FOUND_ERROR,
    FBE_IMPLIED_DEFTEMPLATE_ERROR,
    FBE_COULD_NOT_ASSERT_ERROR,
    FBE_RULE_NETWORK_ERROR
} FactBuilderError;

typedef enum {
    FME_NO_ERROR = 0,
    FME_NULL_POINTER_ERROR,
    FME_RETRACTED_ERROR,
    FME_IMPLIED_DEFTEMPLATE_ERROR,
    FME_COULD_NOT_MODIFY_ERROR,
    FME_RULE_NETWORK_ERROR
} FactModifierError;

struct modifyCallFunctionItem {
    const char *name;
    ModifyCallFunction *func;
    int priority;
    ModifyCallFunctionItem *next;
    void *context;
};

struct fact {
    union {
        struct patternEntity patternHeader;
        TypeHeader header;
    };
    Deftemplate *whichDeftemplate;
    void *list;
    long long factIndex;
    unsigned long hashValue;
    unsigned int garbage: 1;
    Fact *previousFact;
    Fact *nextFact;
    Fact *previousTemplateFact;
    Fact *nextTemplateFact;
    Multifield *basisSlots;
    Multifield theProposition;
};

struct factBuilder {
    Environment *fbEnv;
    Deftemplate *fbDeftemplate;
    CLIPSValue *fbValueArray;
};

struct factModifier {
    Environment *fmEnv;
    Fact *fmOldFact;
    CLIPSValue *fmValueArray;
    char *changeMap;
};

#define FACTS_DATA 3

struct factsData {
    bool ChangeToFactList;
#if DEBUGGING_FUNCTIONS
    bool WatchFacts;
#endif
    Fact DummyFact;
    Fact *GarbageFacts;
    Fact *LastFact;
    Fact *FactList;
    long long NextFactIndex;
    unsigned long NumberOfFacts;
    struct callFunctionItemWithArg *ListOfAssertFunctions;
    struct callFunctionItemWithArg *ListOfRetractFunctions;
    ModifyCallFunctionItem *ListOfModifyFunctions;
    struct patternEntityRecord FactInfo;
    Deftemplate *CurrentDeftemplate;
    struct factHashEntry **FactHashTable;
    unsigned long FactHashTableSize;
    bool FactDuplication;
    Fact *CurrentPatternFact;
    struct multifieldMarker *CurrentPatternMarks;
    long LastModuleIndex;
    RetractError retractError;
    AssertError assertError;
    AssertStringError assertStringError;
    FactModifierError factModifierError;
    FactBuilderError factBuilderError;
};

#define FactData(theEnv) ((struct factsData *) GetEnvironmentData(theEnv,FACTS_DATA))

Fact *Assert(Fact *);
AssertStringError GetAssertStringError(Environment *);
Fact *AssertDriver(Fact *, long long, Fact *, Fact *, char *);
Fact *AssertString(Environment *, const char *);
Fact *CreateFact(Deftemplate *);
void ReleaseFact(Fact *);
void DecrementFactCallback(Environment *, Fact *);
long long FactIndex(Fact *);
GetSlotError GetFactSlot(Fact *, const char *, CLIPSValue *);
void PrintFactWithIdentifier(Environment *, const char *, Fact *, const char *);
void PrintFact(Environment *, const char *, Fact *, bool, bool, const char *);
void PrintFactIdentifierInLongForm(Environment *, const char *, Fact *);
RetractError Retract(Fact *);
RetractError RetractDriver(Environment *, Fact *, bool, char *);
RetractError RetractAllFacts(Environment *);
Fact *CreateFactBySize(Environment *, size_t);
void FactInstall(Environment *, Fact *);
void FactDeinstall(Environment *, Fact *);
Fact *GetNextFact(Environment *, Fact *);
Fact *GetNextFactInScope(Environment *, Fact *);
void FactPPForm(Fact *, StringBuilder *, bool);
bool GetFactListChanged(Environment *);
void SetFactListChanged(Environment *, bool);
unsigned long GetNumberOfFacts(Environment *);
void InitializeFacts(Environment *);
Fact *FindIndexedFact(Environment *, long long);
void RetainFact(Fact *);
void IncrementFactCallback(Environment *, Fact *);
void PrintFactIdentifier(Environment *, const char *, Fact *);
void DecrementFactBasisCount(Environment *, Fact *);
void IncrementFactBasisCount(Environment *, Fact *);
bool FactIsDeleted(Environment *, Fact *);
void ReturnFact(Environment *, Fact *);
void MatchFactFunction(Environment *, Fact *);
bool PutFactSlot(Fact *, const char *, CLIPSValue *);
bool AssignFactSlotDefaults(Fact *);
bool CopyFactSlotValues(Environment *, Fact *, Fact *);
bool DeftemplateSlotDefault(Environment *, Deftemplate *,
                            struct templateSlot *, UDFValue *, bool);
bool AddAssertFunction(Environment *, const char *,
                       VoidCallFunctionWithArg *, int, void *);
bool RemoveAssertFunction(Environment *, const char *);
bool AddRetractFunction(Environment *, const char *,
                        VoidCallFunctionWithArg *, int, void *);
bool RemoveRetractFunction(Environment *, const char *);
FactBuilder *CreateFactBuilder(Environment *, const char *);
PutSlotError FBPutSlot(FactBuilder *, const char *, CLIPSValue *);
Fact *FBAssert(FactBuilder *);
void FBDispose(FactBuilder *);
void FBAbort(FactBuilder *);
FactBuilderError FBSetDeftemplate(FactBuilder *, const char *);
PutSlotError FBPutSlotCLIPSInteger(FactBuilder *, const char *, CLIPSInteger *);
PutSlotError FBPutSlotInteger(FactBuilder *, const char *, long long);
PutSlotError FBPutSlotCLIPSFloat(FactBuilder *, const char *, CLIPSFloat *);
PutSlotError FBPutSlotFloat(FactBuilder *, const char *, double);
PutSlotError FBPutSlotCLIPSLexeme(FactBuilder *, const char *, CLIPSLexeme *);
PutSlotError FBPutSlotSymbol(FactBuilder *, const char *, const char *);
PutSlotError FBPutSlotString(FactBuilder *, const char *, const char *);
PutSlotError FBPutSlotInstanceName(FactBuilder *, const char *, const char *);
PutSlotError FBPutSlotFact(FactBuilder *, const char *, Fact *);
PutSlotError FBPutSlotInstance(FactBuilder *, const char *, Instance *);
PutSlotError FBPutSlotCLIPSExternalAddress(FactBuilder *, const char *, CLIPSExternalAddress *);
PutSlotError FBPutSlotMultifield(FactBuilder *, const char *, Multifield *);
FactBuilderError FBError(Environment *);
FactModifier *CreateFactModifier(Environment *, Fact *);
PutSlotError FMPutSlot(FactModifier *, const char *, CLIPSValue *);
Fact *FMModify(FactModifier *);
void FMDispose(FactModifier *);
void FMAbort(FactModifier *);
FactModifierError FMSetFact(FactModifier *, Fact *);
PutSlotError FMPutSlotCLIPSInteger(FactModifier *, const char *, CLIPSInteger *);
PutSlotError FMPutSlotInteger(FactModifier *, const char *, long long);
PutSlotError FMPutSlotCLIPSFloat(FactModifier *, const char *, CLIPSFloat *);
PutSlotError FMPutSlotFloat(FactModifier *, const char *, double);
PutSlotError FMPutSlotCLIPSLexeme(FactModifier *, const char *, CLIPSLexeme *);
PutSlotError FMPutSlotSymbol(FactModifier *, const char *, const char *);
PutSlotError FMPutSlotString(FactModifier *, const char *, const char *);
PutSlotError FMPutSlotInstanceName(FactModifier *, const char *, const char *);
PutSlotError FMPutSlotFact(FactModifier *, const char *, Fact *);
PutSlotError FMPutSlotInstance(FactModifier *, const char *, Instance *);
PutSlotError FMPutSlotExternalAddress(FactModifier *, const char *, CLIPSExternalAddress *);
PutSlotError FMPutSlotMultifield(FactModifier *, const char *, Multifield *);
FactModifierError FMError(Environment *);

bool AddModifyFunction(Environment *, const char *, ModifyCallFunction *, int, void *);
bool RemoveModifyFunction(Environment *, const char *);
ModifyCallFunctionItem *AddModifyFunctionToCallList(Environment *, const char *, int,
                                                    ModifyCallFunction *, ModifyCallFunctionItem *, void *);
ModifyCallFunctionItem *RemoveModifyFunctionFromCallList(Environment *, const char *,
                                                         ModifyCallFunctionItem *, bool *);
void DeallocateModifyCallList(Environment *, ModifyCallFunctionItem *);
// factmanager end
#if FACT_SET_QUERIES

typedef struct query_template {
    Deftemplate *templatePtr;
    struct query_template *chain, *nxt;
} QUERY_TEMPLATE;

typedef struct query_soln {
    Fact **soln;
    struct query_soln *nxt;
} QUERY_SOLN;

typedef struct query_core {
    Fact **solns;
    Expression *query, *action;
    QUERY_SOLN *soln_set, *soln_bottom;
    unsigned soln_size, soln_cnt;
    UDFValue *result;
} QUERY_CORE;

typedef struct query_stack {
    QUERY_CORE *core;
    struct query_stack *nxt;
} QUERY_STACK;

#define FACT_QUERY_DATA 63

struct factQueryData {
    CLIPSLexeme *QUERY_DELIMITER_SYMBOL;
    QUERY_CORE *QueryCore;
    QUERY_STACK *QueryCoreStack;
    bool AbortQuery;
};

#define FactQueryData(theEnv) ((struct factQueryData *) GetEnvironmentData(theEnv,FACT_QUERY_DATA))

#define QUERY_DELIMITER_STRING     "(QDS)"

void SetupFactQuery(Environment *);
void GetQueryFact(Environment *theEnv, UDFContext *context, UDFValue *ret);
void GetQueryFactSlot(Environment *theEnv, UDFContext *context, UDFValue *ret);
void AnyFacts(Environment *theEnv, UDFContext *context, UDFValue *ret);
void QueryFindFact(Environment *theEnv, UDFContext *context, UDFValue *ret);
void QueryFindAllFacts(Environment *theEnv, UDFContext *context, UDFValue *ret);
void QueryDoForFact(Environment *theEnv, UDFContext *context, UDFValue *ret);
void QueryDoForAllFacts(Environment *theEnv, UDFContext *context, UDFValue *ret);
void DelayedQueryDoForAllFacts(Environment *theEnv, UDFContext *context, UDFValue *ret);

Expression *FactParseQueryNoAction(Environment *, Expression *, const char *);
Expression *FactParseQueryAction(Environment *, Expression *, const char *);
#endif /* FACT_SET_QUERIES */

bool FactPNGetVar1(Environment *, void *, UDFValue *);
bool FactPNGetVar2(Environment *, void *, UDFValue *);
bool FactPNGetVar3(Environment *, void *, UDFValue *);
bool FactJNGetVar1(Environment *, void *, UDFValue *);
bool FactJNGetVar2(Environment *, void *, UDFValue *);
bool FactJNGetVar3(Environment *, void *, UDFValue *);
bool FactSlotLength(Environment *, void *, UDFValue *);
bool FactJNCompVars1(Environment *, void *, UDFValue *);
bool FactJNCompVars2(Environment *, void *, UDFValue *);
bool FactPNCompVars1(Environment *, void *, UDFValue *);
bool FactPNConstant1(Environment *, void *, UDFValue *);
bool FactPNConstant2(Environment *, void *, UDFValue *);
bool FactStoreMultifield(Environment *, void *, UDFValue *);
size_t AdjustFieldPosition(Environment *, struct multifieldMarker *,
                           unsigned short, unsigned short, size_t *);
struct expr *BuildRHSAssert(Environment *, const char *, struct token *, bool *, bool, bool, const char *);
struct expr *GetAssertArgument(Environment *, const char *, struct token *, bool *, TokenType, bool, bool *);
struct expr *GetRHSPattern(Environment *, const char *, struct token *, bool *, bool,
                           bool, bool, TokenType);
Fact *StringToFact(Environment *, const char *);

void PrintFactJNCompVars1(Environment *, const char *, void *);
void PrintFactJNCompVars2(Environment *, const char *, void *);
void PrintFactPNCompVars1(Environment *, const char *, void *);
void PrintFactJNGetVar1(Environment *, const char *, void *);
void PrintFactJNGetVar2(Environment *, const char *, void *);
void PrintFactJNGetVar3(Environment *, const char *, void *);
void PrintFactPNGetVar1(Environment *, const char *, void *);
void PrintFactPNGetVar2(Environment *, const char *, void *);
void PrintFactPNGetVar3(Environment *, const char *, void *);
void PrintFactSlotLength(Environment *, const char *, void *);
void PrintFactPNConstant1(Environment *, const char *, void *);
void PrintFactPNConstant2(Environment *, const char *, void *);

void FactPatternMatch(Environment *, Fact *,
                      struct factPatternNode *, size_t, size_t,
                      struct multifieldMarker *,
                      struct multifieldMarker *);
void MarkFactPatternForIncrementalReset(Environment *, struct patternNodeHeader *, bool);
void FactsIncrementalReset(Environment *);

#define FACTBIN_DATA 62

struct factBinaryData {
    struct factPatternNode *FactPatternArray;
    unsigned long NumberOfPatterns;
};

#define FactBinaryData(theEnv) ((struct factBinaryData *) GetEnvironmentData(theEnv,FACTBIN_DATA))

void FactBinarySetup(Environment *);

#define BsaveFactPatternIndex(patPtr) ((patPtr == NULL) ? ULONG_MAX : ((struct factPatternNode *) patPtr)->bsaveID)
#define BloadFactPatternPointer(i) ((struct factPatternNode *) ((i == ULONG_MAX) ? NULL : &FactBinaryData(theEnv)->FactPatternArray[i]))

struct factPatternNode {
    struct patternNodeHeader header;
    unsigned long bsaveID;
    unsigned short whichField; // TBD seems to be 1 based rather than 0 based
    unsigned short whichSlot;
    unsigned short leaveFields;
    struct expr *networkTest;
    struct factPatternNode *nextLevel;
    struct factPatternNode *lastLevel;
    struct factPatternNode *leftNode;
    struct factPatternNode *rightNode;
};

void InitializeFactPatterns(Environment *);
void DestroyFactPatternNetwork(Environment *, struct factPatternNode *);
#if DEFTEMPLATE_CONSTRUCT

void FactCommandDefinitions(Environment *);
void AssertCommand(Environment *theEnv, UDFContext *context, UDFValue *ret);
void RetractCommand(Environment *theEnv, UDFContext *context, UDFValue *ret);
void AssertStringFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void FactsCommand(Environment *theEnv, UDFContext *context, UDFValue *ret);
void Facts(Environment *, const char *, Defmodule *, long long, long long, long long);
void SetFactDuplicationCommand(Environment *theEnv, UDFContext *context, UDFValue *ret);
void GetFactDuplicationCommand(Environment *theEnv, UDFContext *context, UDFValue *ret);
void FactIndexFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);

#endif /* DEFTEMPLATE_CONSTRUCT */

void FactFileCommandDefinitions(Environment *);
void SaveFactsCommand(Environment *theEnv, UDFContext *context, UDFValue *ret);
void LoadFactsCommand(Environment *theEnv, UDFContext *context, UDFValue *ret);
long SaveFacts(Environment *, const char *, SaveScope);
long SaveFactsDriver(Environment *, const char *, SaveScope, struct expr *);
long LoadFacts(Environment *, const char *);
long LoadFactsFromString(Environment *, const char *, size_t);
void BinarySaveFactsCommand(Environment *theEnv, UDFContext *context, UDFValue *ret);
void BinaryLoadFactsCommand(Environment *theEnv, UDFContext *context, UDFValue *ret);
long BinarySaveFacts(Environment *, const char *, SaveScope);
long BinarySaveFactsDriver(Environment *, const char *, SaveScope, Expression *);
long BinaryLoadFacts(Environment *, const char *);

void FactFunctionDefinitions(Environment *);
/**********************************************************/
/* factGetVarPN1Call: This structure is used to store the */
/*   arguments to the most general extraction routine for */
/*   retrieving a variable from the fact pattern network. */
/**********************************************************/
struct factGetVarPN1Call {
    unsigned int factAddress: 1;
    unsigned int allFields: 1;
    unsigned short whichField;
    unsigned short whichSlot;
};

/***********************************************************/
/* factGetVarPN2Call: This structure is used to store the  */
/*   arguments to the most specific extraction routine for */
/*   retrieving a variable from the fact pattern network.  */
/*   It is used for retrieving the single value stored in  */
/*   a single field slot (the slot index can be used to    */
/*   directly to retrieve the value from the fact array).  */
/***********************************************************/
struct factGetVarPN2Call {
    unsigned short whichSlot;
};

/**********************************************************/
/* factGetVarPN3Call:  */
/**********************************************************/
struct factGetVarPN3Call {
    unsigned int fromBeginning: 1;
    unsigned int fromEnd: 1;
    unsigned short beginOffset;
    unsigned short endOffset;
    unsigned short whichSlot;
};

/**************************************************************/
/* factConstantPN1Call: Used for testing for a constant value */
/*   in the fact pattern network. Compare the value of a      */
/*   single field slot to a constant.                         */
/**************************************************************/
struct factConstantPN1Call {
    unsigned int testForEquality: 1;
    unsigned short whichSlot;
};

/******************************************************************/
/* factConstantPN2Call: Used for testing for a constant value in  */
/*   the fact pattern network. Compare the value of a multifield  */
/*   slot to a constant (where the value retrieved for comparison */
/*   from the slot contains no multifields before or only one     */
/*   multifield before and none after).                           */
/******************************************************************/
struct factConstantPN2Call {
    unsigned int testForEquality: 1;
    unsigned int fromBeginning: 1;
    unsigned short offset;
    unsigned short whichSlot;
};

/**********************************************************/
/* factGetVarJN1Call: This structure is used to store the */
/*   arguments to the most general extraction routine for */
/*   retrieving a fact variable from the join network.    */
/**********************************************************/
struct factGetVarJN1Call {
    unsigned int factAddress: 1;
    unsigned int allFields: 1;
    unsigned int lhs: 1;
    unsigned int rhs: 1;
    unsigned short whichPattern;
    unsigned short whichSlot;
    unsigned short whichField;
};

/**********************************************************/
/* factGetVarJN2Call:  */
/**********************************************************/
struct factGetVarJN2Call {
    unsigned int lhs: 1;
    unsigned int rhs: 1;
    unsigned short whichPattern;
    unsigned short whichSlot;
};

/**********************************************************/
/* factGetVarJN3Call:  */
/**********************************************************/
struct factGetVarJN3Call {
    unsigned int fromBeginning: 1;
    unsigned int fromEnd: 1;
    unsigned int lhs: 1;
    unsigned int rhs: 1;
    unsigned short beginOffset;
    unsigned short endOffset;
    unsigned short whichPattern;
    unsigned short whichSlot;
};

/**********************************************************/
/* factCompVarsPN1Call:  */
/**********************************************************/
struct factCompVarsPN1Call {
    unsigned int pass: 1;
    unsigned int fail: 1;
    unsigned short field1;
    unsigned short field2;
};

/**********************************************************/
/* factCompVarsJN1Call:  */
/**********************************************************/
struct factCompVarsJN1Call {
    unsigned int pass: 1;
    unsigned int fail: 1;
    unsigned int p1lhs: 1;
    unsigned int p1rhs: 1;
    unsigned int p2lhs: 1;
    unsigned int p2rhs: 1;
    unsigned short pattern1;
    unsigned short pattern2;
    unsigned short slot1;
    unsigned short slot2;
};

/**********************************************************/
/* factCompVarsJN2Call:  */
/**********************************************************/
struct factCompVarsJN2Call {
    unsigned int pass: 1;
    unsigned int fail: 1;
    unsigned int p1lhs: 1;
    unsigned int p1rhs: 1;
    unsigned int p2lhs: 1;
    unsigned int p2rhs: 1;
    unsigned int fromBeginning1: 1;
    unsigned int fromBeginning2: 1;
    unsigned short offset1;
    unsigned short offset2;
    unsigned short pattern1;
    unsigned short pattern2;
    unsigned short slot1;
    unsigned short slot2;
};

/**********************************************************/
/* factCheckLengthPNCall: This structure is used to store */
/*   the  arguments to the routine for determining if the */
/*   length of a multifield slot is equal or greater than */
/*   a specified value.                                   */
/**********************************************************/

struct factCheckLengthPNCall {
    unsigned int exactly: 1;
    unsigned short minLength;
    unsigned short whichSlot;
};

/****************************************/
/* GLOBAL EXTERNAL FUNCTION DEFINITIONS */
/****************************************/

void InitializeFactReteFunctions(Environment *);
struct expr *FactPNVariableComparison(Environment *, struct lhsParseNode *,
                                      struct lhsParseNode *);
struct expr *FactJNVariableComparison(Environment *, struct lhsParseNode *,
                                      struct lhsParseNode *, bool);
void FactReplaceGetvar(Environment *, struct expr *, struct lhsParseNode *, int);
void FactReplaceGetfield(Environment *, struct expr *, struct lhsParseNode *);
struct expr *FactGenPNConstant(Environment *, struct lhsParseNode *);
struct expr *FactGenGetfield(Environment *, struct lhsParseNode *);
struct expr *FactGenGetvar(Environment *, struct lhsParseNode *, int);
struct expr *FactGenCheckLength(Environment *, struct lhsParseNode *);
struct expr *FactGenCheckZeroLength(Environment *, unsigned short);
void FactRelationFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
CLIPSLexeme *FactRelation(Fact *);
Deftemplate *FactDeftemplate(Fact *);
void FactExistpFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
bool FactExistp(Fact *);
void FactSlotValueFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void FactSlotValue(Environment *, Fact *, const char *, CLIPSValue *);
void FactSlotNamesFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void FactSlotNames(Fact *, CLIPSValue *);
void GetFactListFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void GetFactList(Environment *, CLIPSValue *, Defmodule *);
void PPFactFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
void PPFact(Fact *, const char *, bool);
Fact *GetFactAddressOrIndexArgument(UDFContext *, bool);
void FactAddresspFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);

struct factHashEntry {
    Fact *theFact;
    FactHashEntry *next;
};

#define SIZE_FACT_HASH 16231

void AddHashedFact(Environment *, Fact *, size_t);
bool RemoveHashedFact(Environment *, Fact *);
size_t HandleFactDuplication(Environment *, Fact *, Fact **, long long);
bool GetFactDuplication(Environment *);
bool SetFactDuplication(Environment *, bool);
void InitializeFactHashTable(Environment *);
void ShowFactHashTableCommand(Environment *theEnv, UDFContext *context, UDFValue *ret);
size_t HashFact(Fact *);
bool FactWillBeAsserted(Environment *, Fact *);

bool FactPatternParserFind(CLIPSLexeme *);
struct lhsParseNode *FactPatternParse(Environment *, const char *, struct token *);
struct lhsParseNode *SequenceRestrictionParse(Environment *, const char *, struct token *);

#endif //MAYA_FACT_H
