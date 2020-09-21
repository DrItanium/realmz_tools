/*******************************************************/
/*      "C" Language Integrated Production System      */
/*                                                     */
/*             CLIPS Version 6.40  07/30/16            */
/*                                                     */
/*         DEFTEMPLATE BSAVE/BLOAD HEADER FILE         */
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
/*      6.23: Added support for templates maintaining their  */
/*            own list of facts.                             */
/*                                                           */
/*      6.30: Changed integer type/precision.                */
/*                                                           */
/*            Support for deftemplate slot facets.           */
/*                                                           */
/*      6.40: Removed LOCALE definition.                     */
/*                                                           */
/*            Pragma once and other inclusion changes.       */
/*                                                           */
/*            Removed use of void pointers for specific      */
/*            data structures.                               */
/*                                                           */
/*************************************************************/

#ifndef _H_tmpltbin

#pragma once

#define _H_tmpltbin

struct bsaveTemplateSlot {
    unsigned long slotName;
    unsigned int multislot: 1;
    unsigned int noDefault: 1;
    unsigned int defaultPresent: 1;
    unsigned int defaultDynamic: 1;
    unsigned long constraints;
    unsigned long defaultList;
    unsigned long facetList;
    unsigned long next;
};

struct bsaveDeftemplate;
struct bsaveDeftemplateModule;

#include "Construct.h"

struct bsaveDeftemplate {
    struct bsaveConstructHeader header;
    unsigned long slotList;
    unsigned int implied: 1;
    unsigned int numberOfSlots: 15;
    unsigned long patternNetwork;
};

#include "DefmoduleBinarySaveLoad.h"

struct bsaveDeftemplateModule {
    struct bsaveDefmoduleItemHeader header;
};

#define TMPLTBIN_DATA 61

#include "Deftemplate.h"

struct deftemplateBinaryData {
    Deftemplate *DeftemplateArray;
    unsigned long NumberOfDeftemplates;
    unsigned long NumberOfTemplateSlots;
    unsigned long NumberOfTemplateModules;
    struct templateSlot *SlotArray;
    struct deftemplateModule *ModuleArray;
};

#define DeftemplateBinaryData(theEnv) ((struct deftemplateBinaryData *) GetEnvironmentData(theEnv,TMPLTBIN_DATA))

#define DeftemplatePointer(i) ((Deftemplate *) (&DeftemplateBinaryData(theEnv)->DeftemplateArray[i]))

#ifndef _H_tmpltdef
#include "tmpltdef.h"
#endif

void DeftemplateBinarySetup(Environment *);
void *BloadDeftemplateModuleReference(Environment *, unsigned long);

#endif /* _H_tmpltbin */



