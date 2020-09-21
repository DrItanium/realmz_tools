/*******************************************************/
/*      "C" Language Integrated Production System      */
/*                                                     */
/*             CLIPS Version 6.40  04/04/19            */
/*                                                     */
/*              FILE COMMANDS HEADER FILE              */
/*******************************************************/

/*************************************************************/
/* Purpose: Contains the code for file commands including    */
/*   batch, dribble-on, dribble-off, save, load, bsave, and  */
/*   bload.                                                  */
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
/*      6.30: Removed conditional code for unsupported       */
/*            compilers/operating systems (IBM_MCW,          */
/*            MAC_MCW, and IBM_TBC).                         */
/*                                                           */
/*            Added code for capturing errors/warnings.      */
/*                                                           */
/*            Added AwaitingInput flag.                      */
/*                                                           */
/*            Added const qualifiers to remove C++           */
/*            deprecation warnings.                          */
/*                                                           */
/*            Converted API macros to function calls.        */
/*                                                           */
/*            Fixed linkage issue when BLOAD_ONLY compiler   */
/*            flag is set to 1.                              */
/*                                                           */
/*      6.31: Fixed error in AppendDribble for older         */
/*            compilers not allowing variable definition     */
/*            within for statement.                          */
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
/*************************************************************/

#ifndef _H_filecom

#pragma once

#define _H_filecom

#include <stdio.h>
#include <stdlib.h>

#include "Entities.h"

typedef struct batchEntry BatchEntry;

/***************/
/* STRUCTURES  */
/***************/

struct batchEntry {
    int batchType;
    FILE *fileSource;
    const char *logicalSource;
    const char *theString;
    const char *fileName;
    long lineNumber;
    BatchEntry *next;
};

/***************/
/* DEFINITIONS */
/***************/

#define FILE_BATCH      0
#define STRING_BATCH    1

#define BUFFER_SIZE   120

#define FILECOM_DATA 14

struct fileCommandData {
#if DEBUGGING_FUNCTIONS
    FILE *DribbleFP;
    char *DribbleBuffer;
    size_t DribbleCurrentPosition;
    size_t DribbleMaximumPosition;
    int (*DribbleStatusFunction)(Environment *, bool);
#endif
    int BatchType;
    FILE *BatchFileSource;
    const char *BatchLogicalSource;
    char *BatchBuffer;
    size_t BatchCurrentPosition;
    size_t BatchMaximumPosition;
    BatchEntry *TopOfBatchList;
    BatchEntry *BottomOfBatchList;
    char *batchPriorParsingFile;
};

#define FileCommandData(theEnv) ((struct fileCommandData *) GetEnvironmentData(theEnv,FILECOM_DATA))

void FileCommandDefinitions(Environment *);
void BatchCommand(Environment *theEnv, UDFContext *context, UDFValue *ret);
void BatchStarCommand(Environment *theEnv, UDFContext *context, UDFValue *ret);
void LoadCommand(Environment *theEnv, UDFContext *context, UDFValue *ret);
void LoadStarCommand(Environment *theEnv, UDFContext *context, UDFValue *ret);
void SaveCommand(Environment *theEnv, UDFContext *context, UDFValue *ret);
void DribbleOnCommand(Environment *theEnv, UDFContext *context, UDFValue *ret);
void DribbleOffCommand(Environment *theEnv, UDFContext *context, UDFValue *ret);

#define FILE_ROUTER_DATA 47

struct fileRouter {
    const char *logicalName;
    FILE *stream;
    struct fileRouter *next;
};

struct fileRouterData {
    struct fileRouter *ListOfFileRouters;
};

#define FileRouterData(theEnv) ((struct fileRouterData *) GetEnvironmentData(theEnv,FILE_ROUTER_DATA))

void InitializeFileRouter(Environment *);
FILE *FindFptr(Environment *, const char *);
bool OpenAFile(Environment *, const char *, const char *, const char *);
bool CloseAllFiles(Environment *);
bool CloseFile(Environment *, const char *);
bool FindFile(Environment *, const char *, void *);
bool FlushAllFiles(Environment *);
bool FlushFile(Environment *, const char *);
bool RewindFile(Environment *, const char *);
long long TellFile(Environment *, const char *);
bool SeekFile(Environment *, const char *, long, int);

bool DribbleOn(Environment *, const char *);
bool DribbleActive(Environment *);
bool DribbleOff(Environment *);
void AppendDribble(Environment *, const char *);
int LLGetcBatch(Environment *, const char *, bool);
bool Batch(Environment *, const char *);
bool OpenBatch(Environment *, const char *, bool);
bool OpenStringBatch(Environment *, const char *, const char *, bool);
bool RemoveBatch(Environment *);
bool BatchActive(Environment *);
void CloseAllBatchSources(Environment *);
bool BatchStar(Environment *, const char *);
#endif /* _H_filecom */






