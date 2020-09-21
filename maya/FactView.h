//
// Created by jwscoggins on 6/21/20.
//

#ifndef MAYA_FACTVIEW_H
#define MAYA_FACTVIEW_H
extern "C" {
#include "clips.h"
}
#include <optional>
#include <string>
#include "GenericView.h"
namespace maya {
    class FactView : public GenericView<fact> {
    public:
        using Self = FactView;
        using Parent = GenericView<fact>;
        using Optional = std::optional<Self>;
        using Parent::Parent;
        [[nodiscard]] constexpr auto getFactIndex() const noexcept { return _raw.factIndex; }
        [[nodiscard]] constexpr auto getHashValue() const noexcept { return _raw.hashValue; }
        [[nodiscard]] constexpr bool isGarbage() const noexcept { return _raw.garbage; }
        std::optional<FactView> getPreviousFact() noexcept;
        std::optional<FactView> getNextFact() noexcept;
        std::optional<FactView> getPreviousTemplateFact() noexcept;
        std::optional<FactView> getNextTemplateFact() noexcept;
        /// @todo implement basis slots after implementing MultifieldView
        /// @todo implement whichDeftemplate support
        Multifield &getTheProposition() noexcept { return _raw.theProposition; }
    };
} // end namespace maya
#endif //MAYA_FACTVIEW_H
