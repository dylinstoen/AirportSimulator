//
// Created by dylin on 4/18/2026.
//

#ifndef AIRPORTSIMULATOR_MARKERCANDIDATE_H
#define AIRPORTSIMULATOR_MARKERCANDIDATE_H
#include "MarkerKind.h"

struct MarkerCandidate {
    MarkerKind kind = MarkerKind::None;
    int value = -1;
};
#endif //AIRPORTSIMULATOR_MARKERCANDIDATE_H
