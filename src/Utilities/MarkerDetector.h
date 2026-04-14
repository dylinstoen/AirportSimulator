//
// Created by dylin on 4/13/2026.
//

#ifndef AIRPORTSIMULATOR_MARKERDETECTOR_H
#define AIRPORTSIMULATOR_MARKERDETECTOR_H
#include <string>
#include "../Model/MarkerKind.h"
class MarkerDetector {
public:
    MarkerKind ClassifyMarker(const std::string& body);
};
#endif //AIRPORTSIMULATOR_MARKERDETECTOR_H
