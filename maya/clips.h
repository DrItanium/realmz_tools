/*******************************************************/
/*      "C" Language Integrated Production System      */
/*                                                     */
/*            CLIPS Version 6.40  11/17/19             */
/*                                                     */
/*                   API HEADER FILE                   */
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
/*      6.24: Added filertr.h and tmpltfun.h to include      */
/*            list.                                          */
/*                                                           */
/*      6.30: Added classpsr.h, iofun.h, and strngrtr.h to   */
/*            include list.                                  */
/*                                                           */
/*      6.40: Pragma once and other inclusion changes.       */
/*                                                           */
/*************************************************************/

#ifndef _H_CLIPS_API

#pragma once

#define _H_CLIPS_API

#include <stdio.h>

#include "Setup.h"
#include "ArgumentAccess.h"
#include "Constants.h"
#include "MemoryAllocation.h"
#include "Construct.h"
#include "StringFunctions.h"
#include "Environment.h"
#include "CommandLine.h"
#include "Symbol.h"

#include "PrintUtility.h"
#include "Router.h"
#include "File.h"
#include "StringRouter.h"

#include "IOFunctions.h"

#include "SystemDependency.h"
#include "BasicMathFunctions.h"
#include "Expression.h"
#include "Expression.h"
#include "Evaluation.h"
#include "MiscFunctions.h"
#include "Construct.h"
#include "Utility.h"
#include "Watch.h"
#include "DefModuleBasicCommands.h"

#if BLOAD_AND_BSAVE
#include "BinaryLoad.h"
#endif

#if BLOAD_AND_BSAVE
#include "BinarySave.h"
#endif

#include "Defrule.h"
#include "BasicRuleCommands.h"
#include "Engine.h"
#include "Drive.h"
#include "IncrementalReset.h"
#include "RuleCommands.h"
#include "ConflictResolutionStrategy.h"

#if DEFFACTS_CONSTRUCT
#include "Deffacts.h"
#include "DeffactsBasicCommands.h"
#endif

#if DEFTEMPLATE_CONSTRUCT
#include "Deftemplate.h"
#include "DeftemplateBasicCommands.h"
#include "DeftemplateFunctions.h"
#include "Fact.h"
#endif

#if DEFGLOBAL_CONSTRUCT
#include "Defglobal.h"
#include "DefglobalBasicCommands.h"
#include "DefglobalCommands.h"
#endif

#if DEFFUNCTION_CONSTRUCT
#include "Deffunction.h"
#endif

#if DEFGENERIC_CONSTRUCT
#include "GenericFunctionCommands.h"
#include "GenericFunction.h"
#endif

#include "ClassCommands.h"
#include "ClassExamination.h"
#include "ClassFunctions.h"
#include "ClassInfo.h"
#include "ClassInitialization.h"
#include "ClassParser.h"
#include "Definstances.h"
#include "InstanceCommand.h"
#include "InstanceSaveLoadCommands.h"
#include "InstanceFunctions.h"
#include "InstanceManager.h"
#include "DefmessageHandlerCommands.h"
#include "DefmessageHandlerDispatch.h"
#include "ObjectReteMatch.h"

#endif /* _H_CLIPS_API */
