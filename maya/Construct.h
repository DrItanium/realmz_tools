/*******************************************************/
/*      "C" Language Integrated Production System      */
/*                                                     */
/*             CLIPS Version 6.40  10/01/16            */
/*                                                     */
/*                  CONSTRUCT MODULE                   */
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
/*      6.24: Added environment parameter to GenClose.       */
/*            Added environment parameter to GenOpen.        */
/*                                                           */
/*            Renamed BOOLEAN macro type to intBool.         */
/*                                                           */
/*      6.30: Changed garbage collection algorithm.          */
/*                                                           */
/*            Removed conditional code for unsupported       */
/*            compilers/operating systems (IBM_MCW and       */
/*            MAC_MCW).                                      */
/*                                                           */
/*            Added code for capturing errors/warnings       */
/*            (EnvSetParserErrorCallback).                   */
/*                                                           */
/*            Fixed issue with save function when multiple   */
/*            defmodules exist.                              */
/*                                                           */
/*            Added const qualifiers to remove C++           */
/*            deprecation warnings.                          */
/*                                                           */
/*            Converted API macros to function calls.        */
/*                                                           */
/*            Fixed linkage issue when BLOAD_ONLY compiler   */
/*            flag is set to 1.                              */
/*                                                           */
/*            Added code to prevent a clear command from     */
/*            being executed during fact assertions via      */
/*            Increment/DecrementClearReadyLocks API.        */
/*                                                           */
/*            Added code to keep track of pointers to        */
/*            constructs that are contained externally to    */
/*            to constructs, DanglingConstructs.             */
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
/*            Modified EnvClear to return completion status. */
/*                                                           */
/*            File name/line count displayed for errors      */
/*            and warnings during load command.              */
/*                                                           */
/*************************************************************/

#ifndef _H_constrct

#pragma once

#define _H_constrct

typedef struct construct Construct;

#include "Entities.h"
#include "UserData.h"
#include "Defmodule.h"
#include "Utility.h"
#include "StringFunctions.h"

typedef void SaveCallFunction(Environment *, Defmodule *, const char *, void *);
typedef struct saveCallFunctionItem SaveCallFunctionItem;

typedef void ParserErrorFunction(Environment *, const char *, const char *, const char *, long, void *);
typedef bool BeforeResetFunction(Environment *);

#define CHS (ConstructHeader *)

struct saveCallFunctionItem {
    const char *name;
    SaveCallFunction *func;
    int priority;
    SaveCallFunctionItem *next;
    void *context;
};
typedef bool ConstructParseFunction(Environment*, const char*);
typedef CLIPSLexeme* ConstructGetConstructNameFunction(ConstructHeader*);
typedef const char* ConstructGetPPFormFunction(ConstructHeader*);
typedef struct defmoduleItemHeader* ConstructGetModuleItemFunction(ConstructHeader*);
typedef void ConstructSetNextItemFunction(ConstructHeader*, ConstructHeader*);
struct construct {
    const char *constructName;
    const char *pluralName;
    ConstructParseFunction* parseFunction;
    FindConstructFunction *findFunction;
    ConstructGetConstructNameFunction* getConstructNameFunction;
    ConstructGetPPFormFunction* getPPFormFunction;
    ConstructGetModuleItemFunction* getModuleItemFunction;
    GetNextConstructFunction *getNextItemFunction;
    ConstructSetNextItemFunction* setNextItemFunction;
    IsConstructDeletableFunction *isConstructDeletableFunction;
    DeleteConstructFunction *deleteFunction;
    FreeConstructFunction *freeFunction;
    Construct *next;
};

#define CONSTRUCT_DATA 42

struct constructData {
    bool ClearReadyInProgress;
    bool ClearInProgress;
    bool ResetReadyInProgress;
    bool ResetInProgress;
    short ClearReadyLocks;
    int DanglingConstructs;
    SaveCallFunctionItem *ListOfSaveFunctions;
    bool PrintWhileLoading;
    bool LoadInProgress;
    bool WatchCompilations;
    bool CheckSyntaxMode;
    bool ParsingConstruct;
    char *ErrorString;
    char *WarningString;
    char *ParsingFileName;
    char *ErrorFileName;
    char *WarningFileName;
    long ErrLineNumber;
    long WrnLineNumber;
    int errorCaptureRouterCount;
    size_t MaxErrChars;
    size_t CurErrPos;
    size_t MaxWrnChars;
    size_t CurWrnPos;
    ParserErrorFunction *ParserErrorCallback;
    void *ParserErrorContext;
    Construct *ListOfConstructs;
    struct voidCallFunctionItem *ListOfResetFunctions;
    struct voidCallFunctionItem *ListOfClearFunctions;
    struct boolCallFunctionItem *ListOfClearReadyFunctions;
    bool Executing;
    BeforeResetFunction *BeforeResetCallback;
};

#define ConstructData(theEnv) ((struct constructData *) GetEnvironmentData(theEnv,CONSTRUCT_DATA))

bool Clear(Environment *);
void Reset(Environment *);
bool Save(Environment *, const char *);

void InitializeConstructData(Environment *);
bool AddResetFunction(Environment *, const char *, VoidCallFunction *, int, void *);
bool RemoveResetFunction(Environment *, const char *);
bool AddClearReadyFunction(Environment *, const char *, BoolCallFunction *, int, void *);
bool RemoveClearReadyFunction(Environment *, const char *);
bool AddClearFunction(Environment *, const char *, VoidCallFunction *, int, void *);
bool RemoveClearFunction(Environment *, const char *);
void IncrementClearReadyLocks(Environment *);
void DecrementClearReadyLocks(Environment *);
Construct *AddConstruct(Environment *, const char *, const char *,
                        ConstructParseFunction*,
                        FindConstructFunction *,
                        ConstructGetConstructNameFunction*,
                        ConstructGetPPFormFunction*,
                        ConstructGetModuleItemFunction*,
                        GetNextConstructFunction *,
                        ConstructSetNextItemFunction*,
                        IsConstructDeletableFunction *,
                        DeleteConstructFunction *,
                        FreeConstructFunction *);
bool RemoveConstruct(Environment *, const char *);
void SetCompilationsWatch(Environment *, bool);
bool GetCompilationsWatch(Environment *);
void SetPrintWhileLoading(Environment *, bool);
bool GetPrintWhileLoading(Environment *);
void SetLoadInProgress(Environment *, bool);
bool GetLoadInProgress(Environment *);
bool ExecutingConstruct(Environment *);
void SetExecutingConstruct(Environment *, bool);
void InitializeConstructs(Environment *);
BeforeResetFunction *SetBeforeResetFunction(Environment *, BeforeResetFunction *);
void ResetCommand(Environment *theEnv, UDFContext *context, UDFValue *ret);
void ClearCommand(Environment *theEnv, UDFContext *context, UDFValue *ret);
bool ClearReady(Environment *);
Construct *FindConstruct(Environment *, const char *);
void DeinstallConstructHeader(Environment *, ConstructHeader *);
void DestroyConstructHeader(Environment *, ConstructHeader *);
ParserErrorFunction *SetParserErrorCallback(Environment *, ParserErrorFunction *, void *);

bool AddSaveFunction(Environment *, const char *, SaveCallFunction *, int, void *);
bool RemoveSaveFunction(Environment *, const char *);
SaveCallFunctionItem *AddSaveFunctionToCallList(Environment *, const char *, int,
                                                SaveCallFunction *, SaveCallFunctionItem *, void *);
SaveCallFunctionItem *RemoveSaveFunctionFromCallList(Environment *, const char *,
                                                     SaveCallFunctionItem *, bool *);
void DeallocateSaveCallList(Environment *, SaveCallFunctionItem *);

#if BLOAD_AND_BSAVE

struct bsaveConstructHeader {
    unsigned long name;
    unsigned long whichModule;
    unsigned long next;
};

void MarkConstructHeaderNeededItems(ConstructHeader *, unsigned long);
void AssignBsaveConstructHeaderVals(struct bsaveConstructHeader *,
                                    ConstructHeader *);

void UpdateConstructHeader(Environment *, struct bsaveConstructHeader *,
                           ConstructHeader *, ConstructType, size_t, void *, size_t, void *);
void UnmarkConstructHeader(Environment *, ConstructHeader *);

#endif
typedef enum {
    LE_NO_ERROR = 0,
    LE_OPEN_FILE_ERROR,
    LE_PARSING_ERROR,
} LoadError;

LoadError Load(Environment *, const char *);
bool LoadConstructsFromLogicalName(Environment *, const char *);
bool LoadFromString(Environment *, const char *, size_t);
BuildError ParseConstruct(Environment *, const char *, const char *);
void ImportExportConflictMessage(Environment *, const char *, const char *,
                                 const char *, const char *);
void FlushParsingMessages(Environment *);
char *GetParsingFileName(Environment *);
void SetParsingFileName(Environment *, const char *);
char *GetErrorFileName(Environment *);
void SetErrorFileName(Environment *, const char *);
char *GetWarningFileName(Environment *);
void SetWarningFileName(Environment *, const char *);
void CreateErrorCaptureRouter(Environment *);
void DeleteErrorCaptureRouter(Environment *);

typedef bool ConstructGetWatchFunction(void *);
typedef void ConstructSetWatchFunction(void *, bool);
typedef void ConstructActionFunction(Environment *, ConstructHeader *, void *);

void AddConstructToModule(ConstructHeader *);
bool DeleteNamedConstruct(Environment *, const char *, Construct *);
ConstructHeader *FindNamedConstructInModule(Environment *, const char *, Construct *);
ConstructHeader *FindNamedConstructInModuleOrImports(Environment *, const char *, Construct *);
void UndefconstructCommand(UDFContext *, const char *, Construct *);
bool PPConstruct(Environment *, const char *, const char *, Construct *);
const char *PPConstructNil(Environment *, const char *, Construct *);
CLIPSLexeme *GetConstructModuleCommand(UDFContext *, const char *, Construct *);
Defmodule *GetConstructModule(Environment *, const char *, Construct *);
bool Undefconstruct(Environment *, ConstructHeader *, Construct *);
bool UndefconstructAll(Environment *, Construct *);
void SaveConstruct(Environment *, Defmodule *, const char *, Construct *);
const char *GetConstructNameString(ConstructHeader *);
const char *GetConstructModuleName(ConstructHeader *);
CLIPSLexeme *GetConstructNamePointer(ConstructHeader *);
void GetConstructListFunction(UDFContext *, UDFValue *, Construct *);
void GetConstructList(Environment *, UDFValue *, Construct *,
                      Defmodule *);
void ListConstructCommand(UDFContext *, Construct *);
void ListConstruct(Environment *, Construct *, const char *, Defmodule *);
void SetNextConstruct(ConstructHeader *, ConstructHeader *);
struct defmoduleItemHeader *GetConstructModuleItem(ConstructHeader *);
const char *GetConstructPPForm(ConstructHeader *);
void PPConstructCommand(UDFContext *, const char *, Construct *, UDFValue *);
ConstructHeader *GetNextConstructItem(Environment *, ConstructHeader *, unsigned);
struct defmoduleItemHeader *GetConstructModuleItemByIndex(Environment *, Defmodule *, unsigned);
void FreeConstructHeaderModule(Environment *, struct defmoduleItemHeader *,
                               Construct *);
void DoForAllConstructs(Environment *,
                        ConstructActionFunction *,
                        unsigned, bool, void *);
void DoForAllConstructsInModule(Environment *, Defmodule *,
                                ConstructActionFunction *,
                                unsigned, bool, void *);
void InitializeConstructHeader(Environment *, const char *, ConstructType,
                               ConstructHeader *, CLIPSLexeme *);
void SetConstructPPForm(Environment *, ConstructHeader *, const char *);
ConstructHeader *LookupConstruct(Environment *, Construct *, const char *, bool);
#if DEBUGGING_FUNCTIONS
bool ConstructPrintWatchAccess(Environment *, Construct *, const char *,
                               Expression *,
                               ConstructGetWatchFunction *,
                               ConstructSetWatchFunction *);
bool ConstructSetWatchAccess(Environment *, Construct *, bool,
                             Expression *,
                             ConstructGetWatchFunction *,
                             ConstructSetWatchFunction *);
#endif
bool ConstructsDeletable(Environment *);

#endif /* _H_constrct */




