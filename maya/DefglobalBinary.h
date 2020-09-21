/*******************************************************/
/*      "C" Language Integrated Production System      */
/*                                                     */
/*             CLIPS Version 6.40  07/30/16            */
/*                                                     */
/*             DEFGLOBAL BINARY HEADER FILE            */
/*******************************************************/

/*************************************************************/
/* Purpose:                                                  */
/*                                                           */
/* Principal Programmer(s):                                  */
/*      Gary D. Riley                                        */
/*                                                           */
/* Contributing Programmer(s):                               */
/*      Brian L. Dantes                                      */
/*                                                           */
/* Revision History:                                         */
/*                                                           */
/*      6.30: Changed integer type/precision.                */
/*                                                           */
/*            Moved WatchGlobals global to defglobalData.    */
/*                                                           */
/*      6.40: Removed LOCALE definition.                     */
/*                                                           */
/*            Pragma once and other inclusion changes.       */
/*                                                           */
/*************************************************************/

#ifndef _H_globlbin

#pragma once

#define _H_globlbin

#include "DefmoduleBinarySaveLoad.h"
#include "Construct.h"
#include "Defglobal.h"

struct bsaveDefglobal {
    struct bsaveConstructHeader header;
    unsigned long initial;
};

struct bsaveDefglobalModule {
    struct bsaveDefmoduleItemHeader header;
};

#define GLOBLBIN_DATA 60

struct defglobalBinaryData {
    Defglobal *DefglobalArray;
    unsigned long NumberOfDefglobals;
    struct defglobalModule *ModuleArray;
    unsigned long NumberOfDefglobalModules;
};

#define DefglobalBinaryData(theEnv) ((struct defglobalBinaryData *) GetEnvironmentData(theEnv,GLOBLBIN_DATA))

#define DefglobalPointer(i) (&DefglobalBinaryData(theEnv)->DefglobalArray[i])

void DefglobalBinarySetup(Environment *);
void *BloadDefglobalModuleReference(Environment *, unsigned long);

#endif /* _H_globlbin */



