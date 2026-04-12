//
// Created by dylin on 4/9/2026.
//

#ifndef AIRPORTSIMULATOR_SEARCHSERVICE_H
#define AIRPORTSIMULATOR_SEARCHSERVICE_H
#include <string>
#include "./Model/Query.h"
#include <nlohmann/json.hpp>
#include <vector>

class RegulationService {
public:
    static std::string ProcessRequest(Query query);
    static std::vector<std::string> ProcessResponse(std::string response);
};



#endif //AIRPORTSIMULATOR_SEARCHSERVICE_H
