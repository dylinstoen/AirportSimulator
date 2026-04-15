//
// Created by dylin on 4/13/2026.
//

#include "MarkerCycle.h"

const std::vector<MarkerKind> &MarkerCycle::DefaultMarkerCycle() {
    static const std::vector<MarkerKind> cycle = {
        MarkerKind::LowerAlpha,
        MarkerKind::Number,
        MarkerKind::LowerRoman,
        MarkerKind::UpperAlpha,
        MarkerKind::Number,
        MarkerKind::LowerRoman,
        MarkerKind::UpperAlpha
    };
    return cycle;
}



