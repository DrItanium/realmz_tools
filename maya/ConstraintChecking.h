/*******************************************************/
/*      "C" Language Integrated Production System      */
/*                                                     */
/*             CLIPS Version 6.40  10/03/19            */
/*                                                     */
/*            CONSTRAINT CHECKING HEADER FILE          */
/*******************************************************/

/*************************************************************/
/* Purpose: Provides functions for constraint checking of    */
/*   data types.                                             */
/*                                                           */
/* Principal Programmer(s):                                  */
/*      Gary D. Riley                                        */
/*                                                           */
/* Contributing Programmer(s):                               */
/*                                                           */
/* Revision History:                                         */
/*                                                           */
/*      6.24: Added allowed-classes slot facet.              */
/*                                                           */
/*            Renamed BOOLEAN macro type to intBool.         */
/*                                                           */
/*      6.30: Removed conditional code for unsupported       */
/*            compilers/operating systems (IBM_MCW and       */
/*            MAC_MCW).                                      */
/*                                                           */
/*            Support for long long integers.                */
/*                                                           */
/*            Added const qualifiers to remove C++           */
/*            deprecation warnings.                          */
/*                                                           */
/*            Dynamic constraint checking for the            */
/*            allowed-classes constraint now searches        */
/*            imported modules.                              */
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
/*            UDF redesign.                                  */
/*                                                           */
/*            Eval support for run time and bload only.      */
/*                                                           */
/*************************************************************/

#ifndef _H_cstrnchk

#pragma once

#define _H_cstrnchk

#include "Constraint.h"
#include "Evaluation.h"

typedef enum {
    NO_VIOLATION,
    TYPE_VIOLATION,
    RANGE_VIOLATION,
    ALLOWED_VALUES_VIOLATION,
    FUNCTION_RETURN_TYPE_VIOLATION,
    CARDINALITY_VIOLATION,
    ALLOWED_CLASSES_VIOLATION
} ConstraintViolationType;

bool CheckCardinalityConstraint(Environment *, size_t, CONSTRAINT_RECORD *);
bool CheckAllowedValuesConstraint(int, void *, CONSTRAINT_RECORD *);
bool CheckAllowedClassesConstraint(Environment *, int, void *, CONSTRAINT_RECORD *);
ConstraintViolationType ConstraintCheckExpressionChain(Environment *, struct expr *,
                                                       CONSTRAINT_RECORD *);
void ConstraintViolationErrorMessage(Environment *, const char *, const char *, bool,
                                     unsigned short, CLIPSLexeme *, unsigned short,
                                     ConstraintViolationType, CONSTRAINT_RECORD *, bool);
ConstraintViolationType ConstraintCheckValue(Environment *, int, void *, CONSTRAINT_RECORD *);
ConstraintViolationType ConstraintCheckDataObject(Environment *, UDFValue *, CONSTRAINT_RECORD *);
ConstraintViolationType ConstraintCheckExpression(Environment *, struct expr *,
                                                  CONSTRAINT_RECORD *);
bool UnmatchableConstraint(struct constraintRecord *);

#endif /* _H_cstrnchk */



