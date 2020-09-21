//
// Created by jwscoggins on 6/21/20.
//

#ifndef MAYA_DEFTEMPLATEVIEW_H
#define MAYA_DEFTEMPLATEVIEW_H
extern "C" {
#include "clips.h"
}
#include <optional>
#include <string>
#include "GenericView.h"
#include "FactView.h"
namespace maya {
    class TemplateSlotView : public GenericView<templateSlot> {
    public:
        using Self = TemplateSlotView;
        using Parent = GenericView<templateSlot>;
        using Optional = std::optional<Self>;
        explicit TemplateSlotView(templateSlot& v) : Parent(v) { }
        /// @todo getSlotName
        [[nodiscard]] constexpr bool isMultislot() const noexcept { return _raw.multislot; }
        [[nodiscard]] constexpr bool noDefault() const noexcept { return _raw.noDefault; }
        [[nodiscard]] constexpr bool defaultPresent() const noexcept { return _raw.defaultPresent; }
        [[nodiscard]] constexpr bool defaultDynamic() const noexcept { return _raw.defaultDynamic; }
        /// @todo constraints
        /// @todo get defaultList and facetList
        [[nodiscard]] Optional getNext() noexcept;
    };

    class DeftemplateView : public GenericView<Deftemplate> {
    public:
        using Self = DeftemplateView;
        using Parent = GenericView<deftemplate>;
        using Optional = std::optional<Self>;
        explicit DeftemplateView(Deftemplate& v) : Parent(v) { }
        ConstructHeader& getHeader() noexcept { return _raw.header; }
        [[nodiscard]] TemplateSlotView::Optional getSlotList() const noexcept;
        [[nodiscard]] constexpr bool isImplied() const noexcept { return _raw.implied; }
        [[nodiscard]] constexpr bool watch() const noexcept { return _raw.watch; }
        [[nodiscard]] constexpr bool inScope() const noexcept { return _raw.inScope; }
        [[nodiscard]] constexpr auto numberOfSlots() const noexcept { return _raw.numberOfSlots; }
        [[nodiscard]] constexpr auto busyCount() const noexcept { return _raw.busyCount; }
        FactView::Optional getFactList() noexcept;
        FactView::Optional getLastFact() noexcept;
        /// @todo patternNetwork needs to be accessible

    };
} // end namespace maya
#endif //MAYA_DEFTEMPLATEVIEW_H
