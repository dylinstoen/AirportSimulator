//
// Created by dylin on 4/9/2026.
//

#ifndef AIRPORTSIMULATOR_SEARCHSERVICE_H
#define AIRPORTSIMULATOR_SEARCHSERVICE_H
#include <string>
#include "./Model/Query.h"
#include <nlohmann/json.hpp>
#include <vector>

#include "Model/Response.h"

class RegulationService {
public:
    static std::string ProcessRequest(Query query);
    static std::vector<std::string> ProcessSearchResponse(std::string response);
    static Response ProcessCompareResponse(std::string response);

    static ResponseDif ProcessDiffResponse(Response& response, Response& result_second_date);
};



#endif //AIRPORTSIMULATOR_SEARCHSERVICE_H
