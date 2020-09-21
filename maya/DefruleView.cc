//
// Created by jwscoggins on 6/21/20.
//

#include "DefruleView.h"
namespace maya {
    Expression *
    DefruleView::getDynamicSalience() noexcept {
        return _raw.dynamicSalience;
    }
    Expression *
    DefruleView::getActions() noexcept {
        return _raw.actions;
    }
    joinNode *
    DefruleView::getLogicalJoin() noexcept {
        return _raw.logicalJoin;
    }
    joinNode *
    DefruleView::getLastJoin() noexcept {
        return _raw.lastJoin;
    }
    std::optional<DefruleView>
    DefruleView::disjunct() noexcept {
        if (_raw.disjunct) {
            return DefruleView(*(_raw.disjunct));
        } else {
            return std::nullopt;
        }
    }
}
