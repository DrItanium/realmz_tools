/*******************************************************/
/*      "C" Language Integrated Production System      */
/*                                                     */
/*             CLIPS Version 6.40  10/18/16            */
/*                                                     */
/*           CONSTRAINT OPERATIONS HEADER FILE         */
/*******************************************************/

/*************************************************************/
/* Purpose: Provides functions for performing operations on  */
/*   constraint records including computing the intersection */
/*   and union of constraint records.                        */
/*                                                           */
/* Principal Programmer(s):                                  */
/*      Gary D. Riley                                        */
/*                                                           */
/* Contributing Programmer(s):                               */
/*                                                           */
/* Revision History:                                         */
/*                                                           */
/*      6.40: Removed LOCALE definition.                     */
/*                                                           */
/*            Pragma once and other inclusion changes.       */
/*                                                           */
/*            Removed use of void pointers for specific      */
/*            data structures.                               */
/*                                                           */
/*            Eval support for run time and bload only.      */
/*                                                           */
/*************************************************************/

#ifndef _H_cstrnops

#pragma once

#define _H_cstrnops

#include "Evaluation.h"
#include "Constraint.h"

struct constraintRecord *IntersectConstraints(Environment *, struct constraintRecord *, struct constraintRecord *);
struct constraintRecord *UnionConstraints(Environment *, struct constraintRecord *, struct constraintRecord *);
void RemoveConstantFromConstraint(Environment *, int, void *, CONSTRAINT_RECORD *);

#endif /* _H_cstrnops */
