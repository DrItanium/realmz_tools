//
// Created by jwscoggins on 6/21/20.
//

#ifndef MAYA_FACTEXTENSIONS_H
#define MAYA_FACTEXTENSIONS_H

extern "C" {
#include "Environment.h"
#include "Fact.h"
}
#include <string>
#include <tuple>
#include "FunctionalExtensions.h"

namespace maya {

        class FactBuilder {
            public:
            FactBuilder(Environment& env, const std::string& name) : _env(env), _contents(CreateFactBuilder(&env, name.c_str())) { }
            ~FactBuilder() noexcept { ::FBDispose(_contents); }
            Fact* assert() noexcept { return FBAssert(_contents); }
            void abort() noexcept { FBAbort(_contents); }
            inline FactBuilderError error() noexcept { return FBError(&_env); }
            FactBuilderError setDeftemplate(const std::string& templateName) noexcept { return FBSetDeftemplate(_contents, templateName.c_str()); }
            PutSlotError putSlot(const std::string& slotName, CLIPSValue* value) noexcept { return FBPutSlot(_contents, slotName.c_str(), value); }
#define X(kind, type) PutSlotError putSlot(const std::string& slotName, type value) noexcept { return FBPutSlot ## kind (_contents, slotName.c_str(), value); }
            X(CLIPSInteger, CLIPSInteger*);
            X(CLIPSFloat, CLIPSFloat*);
            X(CLIPSLexeme, CLIPSLexeme*);
            X(CLIPSExternalAddress, CLIPSExternalAddress*);
            X(Integer, int64_t);
            X(Float, double);
            X(Fact, Fact*);
            X(Instance, Instance*);
            X(Multifield, Multifield*);
#undef X
#define X(kind) \
    inline PutSlotError putSlot(const std::string& slotName, const std::string& value, TreatLexemeAs ## kind ) noexcept {  \
        return FBPutSlot ## kind (_contents, slotName.c_str(), value.c_str()); \
    }
            X(Symbol);
            X(String);
            X(InstanceName);
#undef X
            private:
            ::Environment& _env;
            ::FactBuilder* _contents = nullptr;
        };
        class FactModifier {
            public:
            FactModifier(Environment& env, Fact* targetFact) : _env(env), _contents(CreateFactModifier(&_env, targetFact)) {}
            ~FactModifier() noexcept { ::FMDispose(_contents); }
            FactModifierError error() noexcept { return ::FMError(&_env); }
            void abort() noexcept { ::FMAbort(_contents); }
            FactModifierError setFact(Fact* fact) noexcept { return ::FMSetFact(_contents, fact); }
            Fact* modify() noexcept { return ::FMModify(_contents); }
#define X(kind, type) PutSlotError putSlot(const std::string& slotName, type value) noexcept { return FMPutSlot ## kind (_contents, slotName.c_str(), value); }
            X(CLIPSInteger, CLIPSInteger*);
            X(CLIPSFloat, CLIPSFloat*);
            X(CLIPSLexeme, CLIPSLexeme*);
            X(ExternalAddress, CLIPSExternalAddress *);
            X(Integer, int64_t);
            X(Float, double);
            X(Fact, Fact*);
            X(Instance, Instance*);
            X(Multifield, Multifield*);
#undef X
#define X(kind) \
    inline PutSlotError putSlot(const std::string& slotName, const std::string& value, TreatLexemeAs ## kind ) noexcept {  \
        return FMPutSlot ## kind (_contents, slotName.c_str(), value.c_str()); \
    }
            X(Symbol);
            X(String);
            X(InstanceName);
#undef X
            private:
            ::Environment& _env;
            ::FactModifier* _contents = nullptr;

        };

} // end namespace maya


#endif //MAYA_FACTEXTENSIONS_H
