//
// Created by jwscoggins on 6/21/20.
//

#ifndef MAYA_DEFRULEVIEW_H
#define MAYA_DEFRULEVIEW_H
extern "C" {
#include "clips.h"
}
#include <optional>
#include "GenericView.h"
namespace maya {
    class DefruleView : public GenericView<defrule> {
    public:
        using Parent = GenericView<defrule>;
    public:
        using Parent::Parent;
        [[nodiscard]] constexpr auto getSalience() const noexcept { return _raw.salience; }
        [[nodiscard]] constexpr auto getLocalVariableCount() const noexcept { return _raw.localVarCnt; }
        [[nodiscard]] constexpr auto getComplexity() const noexcept { return _raw.complexity; }
        [[nodiscard]] constexpr bool isAfterBreakpoint() const noexcept { return _raw.afterBreakpoint; }
        [[nodiscard]] constexpr bool watchActivations() const noexcept { return _raw.watchActivation; }
        [[nodiscard]] constexpr bool watchFirings() const noexcept { return _raw.watchFiring; }
        [[nodiscard]] constexpr bool autoFocus() const noexcept { return _raw.autoFocus; }
        [[nodiscard]] constexpr bool executing() const noexcept { return _raw.executing; }
        Expression* getDynamicSalience() noexcept;
        Expression* getActions() noexcept;
        joinNode* getLogicalJoin() noexcept;
        joinNode* getLastJoin() noexcept;
        std::optional<DefruleView> disjunct() noexcept;
    };
} // end namespace maya
#endif //MAYA_DEFRULEVIEW_H
