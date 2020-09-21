/*******************************************************/
/*      "C" Language Integrated Production System      */
/*                                                     */
/*             CLIPS Version 6.40  07/30/16            */
/*                                                     */
/*                                                     */
/*******************************************************/

/*************************************************************/
/* Purpose:                                                  */
/*                                                           */
/* Principal Programmer(s):                                  */
/*      Brian L. Dantes                                      */
/*                                                           */
/* Contributing Programmer(s):                               */
/*                                                           */
/* Revision History:                                         */
/*                                                           */
/*      6.24: Converted INSTANCE_PATTERN_MATCHING to         */
/*            DEFRULE_CONSTRUCT.                             */
/*                                                           */
/*      6.30: Added support for hashed memories and other    */
/*            join network changes.                          */
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
/*************************************************************/

#ifndef _H_objrtgen

#pragma once

#define _H_objrtgen


#include "Expression.h"
#include "Reorder.h"

void ReplaceGetJNObjectValue(Environment *, Expression *, struct lhsParseNode *, int);
Expression *GenGetJNObjectValue(Environment *, struct lhsParseNode *, int);
Expression *ObjectJNVariableComparison(Environment *, struct lhsParseNode *, struct lhsParseNode *, bool);
Expression *GenObjectPNConstantCompare(Environment *, struct lhsParseNode *);
void ReplaceGetPNObjectValue(Environment *, Expression *, struct lhsParseNode *);
Expression *GenGetPNObjectValue(Environment *, struct lhsParseNode *);
Expression *ObjectPNVariableComparison(Environment *, struct lhsParseNode *, struct lhsParseNode *);
void GenObjectLengthTest(Environment *, struct lhsParseNode *);
void GenObjectZeroLengthTest(Environment *, struct lhsParseNode *);


#endif /* _H_objrtgen */




