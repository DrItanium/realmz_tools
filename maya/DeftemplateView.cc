//
// Created by jwscoggins on 6/21/20.
//

#include "DeftemplateView.h"
namespace maya {
    FactView::Optional
    DeftemplateView::getFactList() noexcept {
        if (_raw.factList) {
            return FactView(*_raw.factList);
        } else {
            return std::nullopt;
        }
    }
    FactView::Optional
    DeftemplateView::getLastFact() noexcept {
        if (_raw.lastFact) {
            return FactView(*_raw.lastFact);
        } else {
            return std::nullopt;
        }
    }
    TemplateSlotView::Optional
    DeftemplateView::getSlotList() const noexcept {
        if (_raw.slotList) {
            return TemplateSlotView(*_raw.slotList);
        } else {
            return std::nullopt;
        }
    }
    TemplateSlotView::Optional
    TemplateSlotView::getNext() noexcept {
        if (_raw.next) {
            return TemplateSlotView(*_raw.next);
        } else {
            return std::nullopt;
        }
    }
}
