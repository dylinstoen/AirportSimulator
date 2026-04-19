//
// Created by dylin on 4/13/2026.
//

#ifndef AIRPORTSIMULATOR_MARKERDETECTOR_H
#define AIRPORTSIMULATOR_MARKERDETECTOR_H
#include <optional>
#include <string>
#include <vector>

#include "../Model/MarkerKind.h"
#include "../Model/MarkerCandidate.h"
class MarkerDetector {
public:
    static std::vector<MarkerCandidate> GetCandidates(const std::string& body);
    static std::optional<int> GetMarkerValue(const std::string& marker, MarkerKind kind);
};
#endif //AIRPORTSIMULATOR_MARKERDETECTOR_H
