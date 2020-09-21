//
// Created by jwscoggins on 6/21/20.
//

#ifndef MAYA_NANDFRAMEVIEW_H
#define MAYA_NANDFRAMEVIEW_H
extern "C" {
#include "Analysis.h"
}
#include <optional>
#include <string>
#include "GenericView.h"
namespace maya {
    class NandFrameView : public GenericView<::nandFrame> {
    public:
        using Self = NandFrameView;
        using Parent = GenericView<nandFrame>;
        using Optional = std::optional<Self>;
        using Parent::Parent;
        [[nodiscard]] constexpr auto getDepth() const noexcept { return _raw.depth; }
        [[nodiscard]] inline Optional getNext() noexcept;
        ///@todo implement LHSParseNodeView
        //[[nodiscard]] std::optional<LHSParseNodeView> getNandCE() noexcept;

    };
} // end namespace maya


#endif //MAYA_NANDFRAMEVIEW_H
