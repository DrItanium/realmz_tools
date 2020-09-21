/*******************************************************/
/*      "C" Language Integrated Production System      */
/*                                                     */
/*            CLIPS Version 6.40  11/01/16             */
/*                                                     */
/*                 DEFTEMPLATE MODULE                  */
/*******************************************************/

/*************************************************************/
/* Purpose: Defines basic deftemplate primitive functions    */
/*   such as allocating and deallocating, traversing, and    */
/*   finding deftemplate data structures.                    */
/*                                                           */
/* Principal Programmer(s):                                  */
/*      Gary D. Riley                                        */
/*                                                           */
/* Contributing Programmer(s):                               */
/*      Brian L. Dantes                                      */
/*                                                           */
/* Revision History:                                         */
/*                                                           */
/*      6.23: Added support for templates maintaining their  */
/*            own list of facts.                             */
/*                                                           */
/*      6.24: Renamed BOOLEAN macro type to intBool.         */
/*                                                           */
/*            Corrected code to remove run-time program      */
/*            compiler warnings.                             */
/*                                                           */
/*      6.30: Added code for deftemplate run time            */
/*            initialization of hashed comparisons to        */
/*            constants.                                     */
/*                                                           */
/*            Removed conditional code for unsupported       */
/*            compilers/operating systems (IBM_MCW,          */
/*            MAC_MCW, and IBM_TBC).                         */
/*                                                           */
/*            Support for deftemplate slot facets.           */
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
/*      6.40: Pragma once and other inclusion changes.       */
/*                                                           */
/*            Added support for booleans with <stdbool.h>.   */
/*                                                           */
/*            Removed use of void pointers for specific      */
/*            data structures.                               */
/*                                                           */
/*            ALLOW_ENVIRONMENT_GLOBALS no longer supported. */
/*                                                           */
/*************************************************************/

#include "Setup.h"

#if DEFTEMPLATE_CONSTRUCT

#include <stdio.h>

#include "Construct.h"
#include "ConstraintChecking.h"
#include "Environment.h"
#include "Expression.h"
#include "MemoryAllocation.h"
#include "DefmoduleParser.h"
#include "DefmoduleUtility.h"
#include "Network.h"
#include "Pattern.h"
#include "Router.h"
#include "DeftemplateBasicCommands.h"
#include "DeftemplateFunctions.h"
#include "DeftemplateParser.h"
#include "DeftemplateUtilities.h"

#if BLOAD_AND_BSAVE
#include "BinaryLoad.h"
#include "DeftemplateBinarySaveLoad.h"
#endif

#include "Deftemplate.h"

/***************************************/
/* LOCAL INTERNAL FUNCTION DEFINITIONS */
/***************************************/

static void *AllocateModule(Environment *);
static void ReturnModule(Environment *, void *);
static void ReturnDeftemplate(Environment *, Deftemplate *);
static void InitializeDeftemplateModules(Environment *);
static void DeallocateDeftemplateData(Environment *);
static void DestroyDeftemplateAction(Environment *, ConstructHeader *, void *);
static void DestroyDeftemplate(Environment *, Deftemplate *);

/******************************************************************/
/* InitializeDeftemplates: Initializes the deftemplate construct. */
/******************************************************************/
void InitializeDeftemplates(
        Environment *theEnv) {
    struct entityRecord deftemplatePtrRecord =
            {"DEFTEMPLATE_PTR",
             DEFTEMPLATE_PTR, 1, 0, 0,
             NULL,
             NULL, NULL,
             NULL,
             NULL,
             (EntityBusyCountFunction *) DecrementDeftemplateBusyCount,
             (EntityBusyCountFunction *) IncrementDeftemplateBusyCount,
             NULL, NULL, NULL, NULL, NULL};
    AllocateEnvironmentData(theEnv, DEFTEMPLATE_DATA, sizeof(struct deftemplateData), DeallocateDeftemplateData);

    memcpy(&DeftemplateData(theEnv)->DeftemplatePtrRecord, &deftemplatePtrRecord, sizeof(struct entityRecord));

    InitializeFacts(theEnv);

    InitializeDeftemplateModules(theEnv);

    DeftemplateBasicCommands(theEnv);

    DeftemplateFunctions(theEnv);

    DeftemplateData(theEnv)->DeftemplateConstruct =
            AddConstruct(theEnv, "deftemplate", "deftemplates", ParseDeftemplate,
                         (FindConstructFunction *) FindDeftemplate,
                         GetConstructNamePointer, GetConstructPPForm,
                         GetConstructModuleItem,
                         (GetNextConstructFunction *) GetNextDeftemplate,
                         SetNextConstruct,
                         (IsConstructDeletableFunction *) DeftemplateIsDeletable,
                         (DeleteConstructFunction *) Undeftemplate,
                         (FreeConstructFunction *) ReturnDeftemplate);

    InstallPrimitive(theEnv, (EntityRecord *) &DeftemplateData(theEnv)->DeftemplatePtrRecord, DEFTEMPLATE_PTR);
}

/******************************************************/
/* DeallocateDeftemplateData: Deallocates environment */
/*    data for the deftemplate construct.             */
/******************************************************/
static void DeallocateDeftemplateData(
        Environment *theEnv) {
    struct deftemplateModule *theModuleItem;
    Defmodule *theModule;
#if BLOAD_AND_BSAVE
    if (Bloaded(theEnv)) return;
#endif

    DoForAllConstructs(theEnv, DestroyDeftemplateAction, DeftemplateData(theEnv)->DeftemplateModuleIndex, false, NULL);

    for (theModule = GetNextDefmodule(theEnv, NULL);
         theModule != NULL;
         theModule = GetNextDefmodule(theEnv, theModule)) {
        theModuleItem = (struct deftemplateModule *)
                GetModuleItem(theEnv, theModule,
                              DeftemplateData(theEnv)->DeftemplateModuleIndex);
        rtn_struct(theEnv, deftemplateModule, theModuleItem);
    }
}

/*****************************************************/
/* DestroyDeftemplateAction: Action used to remove   */
/*   deftemplates as a result of DestroyEnvironment. */
/*****************************************************/
static void DestroyDeftemplateAction(
        Environment *theEnv,
        ConstructHeader *theConstruct,
        void *buffer) {
#if MAC_XCD
#pragma unused(buffer)
#endif
    Deftemplate *theDeftemplate = (Deftemplate *) theConstruct;

    if (theDeftemplate == NULL) return;

    DestroyDeftemplate(theEnv, theDeftemplate);
}


/*************************************************************/
/* InitializeDeftemplateModules: Initializes the deftemplate */
/*   construct for use with the defmodule construct.         */
/*************************************************************/
static void InitializeDeftemplateModules(
        Environment *theEnv) {
    DeftemplateData(theEnv)->DeftemplateModuleIndex = RegisterModuleItem(theEnv, "deftemplate",
                                                                         AllocateModule,
                                                                         ReturnModule,
#if BLOAD_AND_BSAVE
                                                                         BloadDeftemplateModuleReference,
#else
            NULL,
#endif
                                                                         (FindConstructFunction *) FindDeftemplateInModule);

#if DEFMODULE_CONSTRUCT
    AddPortConstructItem(theEnv, "deftemplate", SYMBOL_TOKEN);
#endif
}

/***************************************************/
/* AllocateModule: Allocates a deftemplate module. */
/***************************************************/
static void *AllocateModule(
        Environment *theEnv) {
    return ((void *) get_struct(theEnv, deftemplateModule));
}

/*************************************************/
/* ReturnModule: Deallocates a deftemplate module. */
/*************************************************/
static void ReturnModule(
        Environment *theEnv,
        void *theItem) {
    FreeConstructHeaderModule(theEnv, (struct defmoduleItemHeader *) theItem, DeftemplateData(theEnv)->DeftemplateConstruct);
    rtn_struct(theEnv, deftemplateModule, theItem);
}

/****************************************************************/
/* GetDeftemplateModuleItem: Returns a pointer to the defmodule */
/*  item for the specified deftemplate or defmodule.            */
/****************************************************************/
struct deftemplateModule *GetDeftemplateModuleItem(
        Environment *theEnv,
        Defmodule *theModule) {
    return ((struct deftemplateModule *) GetConstructModuleItemByIndex(theEnv, theModule, DeftemplateData(theEnv)->DeftemplateModuleIndex));
}

/***************************************************/
/* FindDeftemplate: Searches for a deftemplate in  */
/*   the list of deftemplates. Returns a pointer   */
/*   to the deftemplate if  found, otherwise NULL. */
/***************************************************/
Deftemplate *FindDeftemplate(
        Environment *theEnv,
        const char *deftemplateName) {
    return (Deftemplate *) FindNamedConstructInModuleOrImports(theEnv, deftemplateName, DeftemplateData(theEnv)->DeftemplateConstruct);
}

/*******************************************************/
/* FindDeftemplateInModule: Searches for a deftemplate */
/*   in the list of deftemplates. Returns a pointer    */
/*   to the deftemplate if  found, otherwise NULL.     */
/*******************************************************/
Deftemplate *FindDeftemplateInModule(
        Environment *theEnv,
        const char *deftemplateName) {
    return (Deftemplate *) FindNamedConstructInModule(theEnv, deftemplateName, DeftemplateData(theEnv)->DeftemplateConstruct);
}

/***********************************************************************/
/* GetNextDeftemplate: If passed a NULL pointer, returns the first     */
/*   deftemplate in the ListOfDeftemplates. Otherwise returns the next */
/*   deftemplate following the deftemplate passed as an argument.      */
/***********************************************************************/
Deftemplate *GetNextDeftemplate(
        Environment *theEnv,
        Deftemplate *deftemplatePtr) {
    return (Deftemplate *) GetNextConstructItem(theEnv, &deftemplatePtr->header, DeftemplateData(theEnv)->DeftemplateModuleIndex);
}

/**********************************************************/
/* DeftemplateIsDeletable: Returns true if a particular   */
/*   deftemplate can be deleted, otherwise returns false. */
/**********************************************************/
bool DeftemplateIsDeletable(
        Deftemplate *theDeftemplate) {
    Environment *theEnv = theDeftemplate->header.env;

    if (!ConstructsDeletable(theEnv)) { return false; }

    if (theDeftemplate->busyCount > 0) return false;
    if (theDeftemplate->patternNetwork != NULL) return false;

    return true;
}

/**************************************************************/
/* ReturnDeftemplate: Returns the data structures associated  */
/*   with a deftemplate construct to the pool of free memory. */
/**************************************************************/
static void ReturnDeftemplate(
        Environment *theEnv,
        Deftemplate *theDeftemplate) {
    struct templateSlot *slotPtr;

    if (theDeftemplate == NULL) return;

        /*====================================================================*/
        /* If a template is redefined, then we want to save its debug status. */
        /*====================================================================*/

#if DEBUGGING_FUNCTIONS
    DeftemplateData(theEnv)->DeletedTemplateDebugFlags = 0;
    if (theDeftemplate->watch) BitwiseSet(DeftemplateData(theEnv)->DeletedTemplateDebugFlags, 0);
#endif

    /*===========================================*/
    /* Free storage used by the templates slots. */
    /*===========================================*/

    slotPtr = theDeftemplate->slotList;
    while (slotPtr != NULL) {
        ReleaseLexeme(theEnv, slotPtr->slotName);
        RemoveHashedExpression(theEnv, slotPtr->defaultList);
        slotPtr->defaultList = NULL;
        RemoveHashedExpression(theEnv, slotPtr->facetList);
        slotPtr->facetList = NULL;
        RemoveConstraint(theEnv, slotPtr->constraints);
        slotPtr->constraints = NULL;
        slotPtr = slotPtr->next;
    }

    ReturnSlots(theEnv, theDeftemplate->slotList);

    /*==================================*/
    /* Free storage used by the header. */
    /*==================================*/

    DeinstallConstructHeader(theEnv, &theDeftemplate->header);

    rtn_struct(theEnv, deftemplate, theDeftemplate);
}

/**************************************************************/
/* DestroyDeftemplate: Returns the data structures associated */
/*   with a deftemplate construct to the pool of free memory. */
/**************************************************************/
static void DestroyDeftemplate(
        Environment *theEnv,
        Deftemplate *theDeftemplate) {
    struct templateSlot *slotPtr, *nextSlot;
    if (theDeftemplate == NULL) return;

    slotPtr = theDeftemplate->slotList;

    while (slotPtr != NULL) {
        nextSlot = slotPtr->next;
        rtn_struct(theEnv, templateSlot, slotPtr);
        slotPtr = nextSlot;
    }

    DestroyFactPatternNetwork(theEnv, theDeftemplate->patternNetwork);

    /*==================================*/
    /* Free storage used by the header. */
    /*==================================*/

    DeinstallConstructHeader(theEnv, &theDeftemplate->header);

    rtn_struct(theEnv, deftemplate, theDeftemplate);
}

/***********************************************/
/* ReturnSlots: Returns the slot structures of */
/*   a deftemplate to free memory.             */
/***********************************************/
void ReturnSlots(
        Environment *theEnv,
        struct templateSlot *slotPtr) {
    struct templateSlot *nextSlot;

    while (slotPtr != NULL) {
        nextSlot = slotPtr->next;
        ReturnExpression(theEnv, slotPtr->defaultList);
        ReturnExpression(theEnv, slotPtr->facetList);
        RemoveConstraint(theEnv, slotPtr->constraints);
        rtn_struct(theEnv, templateSlot, slotPtr);
        slotPtr = nextSlot;
    }
}

/*************************************************/
/* DecrementDeftemplateBusyCount: Decrements the */
/*   busy count of a deftemplate data structure. */
/*************************************************/
void DecrementDeftemplateBusyCount(
        Environment *theEnv,
        Deftemplate *theTemplate) {
    if (!ConstructData(theEnv)->ClearInProgress) theTemplate->busyCount--;
}

/*************************************************/
/* IncrementDeftemplateBusyCount: Increments the */
/*   busy count of a deftemplate data structure. */
/*************************************************/
void IncrementDeftemplateBusyCount(
        Environment *theEnv,
        Deftemplate *theTemplate) {
#if MAC_XCD
#pragma unused(theEnv)
#endif

    theTemplate->busyCount++;
}

/*******************************************************************/
/* GetNextFactInTemplate: If passed a NULL pointer, returns the    */
/*   first fact in the template's fact-list. Otherwise returns the */
/*   next template fact following the fact passed as an argument.  */
/*******************************************************************/
Fact *GetNextFactInTemplate(
        Deftemplate *theTemplate,
        Fact *factPtr) {
    if (factPtr == NULL) { return (theTemplate->factList); }

    if (factPtr->garbage) return NULL;

    return (factPtr->nextTemplateFact);
}


/******************************/
/* CreateDeftemplateScopeMap: */
/******************************/
void *CreateDeftemplateScopeMap(
        Environment *theEnv,
        Deftemplate *theDeftemplate) {
    unsigned short scopeMapSize;
    char *scopeMap;
    const char *templateName;
    Defmodule *matchModule, *theModule;
    unsigned long moduleID;
    unsigned int count;
    void *theBitMap;

    templateName = theDeftemplate->header.name->contents;
    matchModule = theDeftemplate->header.whichModule->theModule;

    scopeMapSize = (sizeof(char) * ((GetNumberOfDefmodules(theEnv) / BITS_PER_BYTE) + 1));
    scopeMap = (char *) gm2(theEnv, scopeMapSize);

    ClearBitString((void *) scopeMap, scopeMapSize);
    SaveCurrentModule(theEnv);
    for (theModule = GetNextDefmodule(theEnv, NULL);
         theModule != NULL;
         theModule = GetNextDefmodule(theEnv, theModule)) {
        SetCurrentModule(theEnv, theModule);
        moduleID = theModule->header.bsaveID;
        if (FindImportedConstruct(theEnv, "deftemplate", matchModule,
                                  templateName, &count, true, NULL) != NULL)
            SetBitMap(scopeMap, moduleID);
    }
    RestoreCurrentModule(theEnv);
    theBitMap = AddBitMap(theEnv, scopeMap, scopeMapSize);
    IncrementBitMapCount(theBitMap);
    rm(theEnv, scopeMap, scopeMapSize);
    return (theBitMap);
}


/*##################################*/
/* Additional Environment Functions */
/*##################################*/

const char *DeftemplateModule(
        Deftemplate *theDeftemplate) {
    return GetConstructModuleName(&theDeftemplate->header);
}

const char *DeftemplateName(
        Deftemplate *theDeftemplate) {
    return GetConstructNameString(&theDeftemplate->header);
}

const char *DeftemplatePPForm(
        Deftemplate *theDeftemplate) {
    return GetConstructPPForm(&theDeftemplate->header);
}

#endif /* DEFTEMPLATE_CONSTRUCT */


