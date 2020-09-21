//
// Created by jwscoggins on 6/21/20.
//

#include "FactView.h"
namespace maya {
    std::optional<FactView> FactView::getPreviousFact() noexcept {
        if (_raw.previousFact) {
            return FactView(*_raw.previousFact);
        } else {
            return std::nullopt;
        }
    }
    std::optional<FactView> FactView::getNextFact() noexcept {
        if (_raw.nextFact) {
            return FactView(*_raw.nextFact);
        } else {
            return std::nullopt;
        }
    }
    std::optional<FactView> FactView::getPreviousTemplateFact() noexcept {
        if (_raw.previousTemplateFact) {
            return FactView(*_raw.previousTemplateFact);
        } else {
            return std::nullopt;
        }
    }
    std::optional<FactView> FactView::getNextTemplateFact() noexcept {
        if (_raw.nextTemplateFact) {
            return FactView(*_raw.nextTemplateFact);
        } else {
            return std::nullopt;
        }
    }
} // end namespace maya
