//
// Created by jwscoggins on 6/21/20.
//

#ifndef MAYA_INSTANCEEXTENSIONS_H
#define MAYA_INSTANCEEXTENSIONS_H
extern "C" {
#include "Environment.h"
#include "InstanceCommand.h"
#include "InstanceManager.h"
}
#include <string>
#include "FunctionalExtensions.h"

namespace maya {
class InstanceBuilder {
public:
    InstanceBuilder(Environment& env, const std::string& className) : _env(env), _contents(CreateInstanceBuilder(&_env, className.c_str())) { }
    ~InstanceBuilder() noexcept { IBDispose(_contents); }
    void abort() noexcept { IBAbort(_contents); }
    Instance* make(const std::string& name) noexcept { return IBMake(_contents, name.c_str()); }
    auto error() noexcept { return IBError(&_env); }
    PutSlotError putSlot(const std::string& slotName, CLIPSValue* value) noexcept { return IBPutSlot(_contents, slotName.c_str(), value) ; }
#define X(kind, type) PutSlotError putSlot(const std::string& slotName, type value) noexcept { return IBPutSlot ## kind (_contents, slotName.c_str(), value); }
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
        return IBPutSlot ## kind (_contents, slotName.c_str(), value.c_str()); \
    }
        X(Symbol);
        X(String);
        X(InstanceName);
#undef X
private:
    ::Environment& _env;
    ::InstanceBuilder* _contents = nullptr;
};

class InstanceModifier {
    InstanceModifier(Environment& env, Instance* inst) : _env(env), _contents(CreateInstanceModifier(&_env, inst)) { }
    ~InstanceModifier() noexcept { IMDispose(_contents); }
    void abort() noexcept { IMAbort(_contents); }
    Instance* make(const std::string& name) noexcept { return IMModify(_contents); }
    auto error() noexcept { return IMError(&_env); }
    auto setInstance(Instance* inst) noexcept { return IMSetInstance(_contents, inst); }
    PutSlotError putSlot(const std::string& slotName, CLIPSValue* value) noexcept { return IMPutSlot(_contents, slotName.c_str(), value) ; }
#define X(kind, type) PutSlotError putSlot(const std::string& slotName, type value) noexcept { return IMPutSlot ## kind (_contents, slotName.c_str(), value); }
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
        return IMPutSlot ## kind (_contents, slotName.c_str(), value.c_str()); \
    }
        X(Symbol);
        X(String);
        X(InstanceName);
#undef X
private:
    ::Environment& _env;
    ::InstanceModifier* _contents = nullptr;

};
} // end namespace maya

#endif //MAYA_INSTANCEEXTENSIONS_H
