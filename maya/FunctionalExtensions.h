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
#ifndef __MAYA_FUNCTIONAL_H__
#define __MAYA_FUNCTIONAL_H__
#ifdef __cplusplus
#include <string>
#include <cstdint>

extern "C" {
#endif
#include "clips.h"
void InstallFunctionalExtensions(Environment *theEnv);

#ifdef __cplusplus
}
namespace maya {
    class TreatLexemeAsSymbol final { };
    class TreatLexemeAsString final { };
    class TreatLexemeAsInstanceName final { };
// class definition for the FunctionBuilder
    class FunctionCallBuilder {
    public:
        using FCB = ::FunctionCallBuilder;
        using ErrorKind = ::FunctionCallBuilderError;
        using String = const std::string &;
    public:
        FunctionCallBuilder(Environment *theEnv, size_t size = 0);
        ~FunctionCallBuilder();
        ErrorKind call(String functionName, CLIPSValue *ret) noexcept;
        void reset() noexcept { FCBReset(_builder); }
        void append(UDFValue *value) noexcept;
        void append(CLIPSValue *value) noexcept;
        void append(CLIPSInteger *value) noexcept;
        void append(int64_t value) noexcept;
        void append(CLIPSFloat *value) noexcept;
        void append(double value) noexcept;
        void append(CLIPSLexeme *value) noexcept;
        void append(String sym, TreatLexemeAsSymbol) noexcept;
        void append(String sym, TreatLexemeAsString) noexcept;
        void append(String sym, TreatLexemeAsInstanceName) noexcept;
        void append(CLIPSExternalAddress *value) noexcept;
        void append(Fact *value) noexcept;
        void append(Instance *value) noexcept;
        void append(Multifield *value) noexcept;
    private:
        FCB *_builder;
    };

    class MultifieldBuilder {
    public:
        using MB = ::MultifieldBuilder;
        using String = const std::string &;
    public:
        MultifieldBuilder(Environment *theEnv, size_t size = 0);
        ~MultifieldBuilder();
        Multifield *create() noexcept { return MBCreate(_builder); }
        void reset() noexcept { MBReset(_builder); }
        void append(UDFValue *) noexcept;
        void append(CLIPSValue *) noexcept;
        void append(CLIPSInteger *value) noexcept;
        void append(int64_t) noexcept;
        void append(CLIPSFloat *) noexcept;
        void append(double) noexcept;
        void append(CLIPSLexeme *) noexcept;
        void append(CLIPSExternalAddress *) noexcept;
        void append(Fact *) noexcept;
        void append(Instance *) noexcept;
        void append(Multifield *) noexcept;
        void append(String, TreatLexemeAsSymbol) noexcept;
        void append(String, TreatLexemeAsString) noexcept;
        void append(String, TreatLexemeAsInstanceName) noexcept;
    private:
        MB *_builder;
    };
}
#endif // end __cplusplus
#endif // end __MAYA_FUNCTIONAL_H__
