// maya
// Copyright (c) 2012-2018, Joshua Scoggins
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
// ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#include "clips.h"
#include "MiscFunctions.h"
#include "ExternalFunctions.h"
#include "MayaExtensions.h"
#include "MayaSetup.h"

#if BOOST_EXTENSIONS
#include "BoostExtensions.h"
#endif

#if FUNCTIONAL_EXTENSIONS
#include "FunctionalExtensions.h"
#endif

#if !MAYA_EXTENSIONS
void InstallMayaExtensions(void* environment) { }
#else
static void EmptyFunction(Environment *theEnv, UDFContext *context, UDFValue *ret);
static void Functionp(Environment *theEnv, UDFContext *context, UDFValue *ret);
//static void NextToken(Environment*, UDFContext* context, UDFValue* ret);
static void LastFunction(Environment *, UDFContext *context, UDFValue *ret);

void InstallMayaExtensions(Environment *theEnv) {
    AddUDF(theEnv, "empty$", "b", 1, 1, "m", EmptyFunction, NULL);
    AddUDF(theEnv, "functionp", "b", 1, 1, "y", Functionp, NULL);
    AddUDF(theEnv, "quit", "v", 0, 1, "l", ExitCommand, NULL);
    AddUDF(theEnv, "bye", "v", 0, 1, "l", ExitCommand, NULL);
    AddUDF(theEnv, "last$", "m", 1, 1, "m", LastFunction, NULL);
#if BOOST_EXTENSIONS
    InstallBoostExtensions(theEnv);
#endif
#if FUNCTIONAL_EXTENSIONS
    InstallFunctionalExtensions(theEnv);
#endif
}

void
LastFunction(Environment *theEnv, UDFContext *context, UDFValue *ret) {
    UDFValue theArg;
    Multifield *theList;

    /*===================================*/
    /* Get the segment to be subdivided. */
    /*===================================*/
    if (!UDFFirstArgument(context, MULTIFIELD_BIT, &theArg)) {
        return;
    }

    theList = theArg.multifieldValue;

    ret->value = theList;
    if (theArg.range >= 1) {
        ret->begin = (theArg.begin + theArg.range) - 1;
        ret->range = 1;
    } else {
        ret->begin = theArg.begin;
        ret->range = theArg.range;
    }
}

void
Functionp(Environment *theEnv, UDFContext *context, UDFValue *ret) {
    Expression theRef;
    UDFValue theArg;
    ret->lexemeValue = CreateBoolean(theEnv, (UDFFirstArgument(context, LEXEME_BITS, &theArg) &&
                                           GetFunctionReference(theEnv, theArg.lexemeValue->contents, &theRef)));
}
void
EmptyFunction(Environment *theEnv, UDFContext *context, UDFValue *ret) {
    UDFValue theArg;
    if (!UDFFirstArgument(context, MULTIFIELD_BIT, &theArg)) {
        return;
    }
    ret->lexemeValue = CreateBoolean(theEnv, theArg.range > 0);
}

#endif // end MAYA_EXTENSIONS
