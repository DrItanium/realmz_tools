/*******************************************************/
/*      "C" Language Integrated Production System      */
/*                                                     */
/*             CLIPS Version 6.40  07/30/16            */
/*                                                     */
/*           DEFMODULE BSAVE/BLOAD HEADER FILE         */
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
/*      6.40: Removed LOCALE definition.                     */
/*                                                           */
/*            Pragma once and other inclusion changes.       */
/*                                                           */
/*            Removed use of void pointers for specific      */
/*            data structures.                               */
/*                                                           */
/*************************************************************/

#ifndef _H_modulbin

#pragma once

#define _H_modulbin

#include "Defmodule.h"
#include "DefmoduleBinarySaveLoad.h"
#include "Construct.h"

struct bsaveDefmodule {
    struct bsaveConstructHeader header;
    unsigned long importList;
    unsigned long exportList;
    unsigned long bsaveID;
};

struct bsaveDefmoduleItemHeader {
    unsigned long theModule;
    unsigned long firstItem;
    unsigned long lastItem;
};

struct bsavePortItem {
    unsigned long moduleName;
    unsigned long constructType;
    unsigned long constructName;
    unsigned long next;
};

#define ModulePointer(i) ((Defmodule *) (&DefmoduleData(theEnv)->DefmoduleArray[i]))

void DefmoduleBinarySetup(Environment *);
void UpdateDefmoduleItemHeader
        (Environment *, struct bsaveDefmoduleItemHeader *,
         struct defmoduleItemHeader *, size_t, void *);

#if BLOAD_AND_BSAVE
void AssignBsaveDefmdlItemHdrVals
        (struct bsaveDefmoduleItemHeader *,
         struct defmoduleItemHeader *);
#endif

#endif /* _H_modulbin */



