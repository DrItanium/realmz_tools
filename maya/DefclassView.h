//
// Created by jwscoggins on 7/8/20.
//

#ifndef MAYA_DEFCLASSVIEW_H
#define MAYA_DEFCLASSVIEW_H
extern "C" {
#include "clips.h"
}
#include <optional>
#include <string>
#include "GenericView.h"
namespace maya {
    class DefclassView : public GenericView<defclass> {
    public:
        using Parent = GenericView<defclass>;
    public:
        using Parent::Parent;
        std::string getName() const noexcept { return DefclassName(&_raw); }
        std::string getPPForm() const noexcept { return DefclassPPForm(&_raw); }
        std::string getModuleName() const noexcept { return DefclassModule(&_raw); };
        CLIPSLexeme* getNamePointer() const noexcept { return GetDefclassNamePointer(&_raw); }
        [[nodiscard]] bool isAbstract() const noexcept { return ClassAbstractP(&_raw); }
        [[nodiscard]] bool isReactive() const noexcept { return ClassReactiveP(&_raw); }
        bool isSubclassOf(const DefclassView& other) const noexcept;
        bool isSuperclassOf(const DefclassView& other) const noexcept;
        bool slotExists(const std::string& slotName, bool) const noexcept;
        bool slotWritable(const std::string& slotName) const noexcept;
        bool slotInitable(const std::string& slotName) const noexcept;
        bool slotPublic(const std::string& slotName) const noexcept;
        bool slotDirectAccess(const std::string& slotName) const noexcept;
    };
}

#endif //MAYA_DEFCLASSVIEW_H
