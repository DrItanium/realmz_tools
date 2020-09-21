//
// Created by jwscoggins on 6/21/20.
//

#include "NandFrameView.h"

namespace maya {

    NandFrameView::Optional NandFrameView::getNext() noexcept {
        if (_raw.next) {
            return NandFrameView(*_raw.next);
        } else {
            return std::nullopt;
        }
    }
} // end namespace maya
