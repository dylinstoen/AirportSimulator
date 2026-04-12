//
// Created by dylin on 4/9/2026.
//

#include "RegulationService.h"

#include <iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

std::string RegulationService::ProcessRequest(Query query) {
    // /api/versioner/v1/versions/title-{title}.json
    // https://www.ecfr.gov/api/versioner/v1/full/
    cpr::Response r = cpr::Get(cpr::Url{
        "https://www.ecfr.gov/api/versioner/v1/versions/title-" + query.title + ".json"},
        cpr::Parameters {
            {"chapter", query.chapter},
            {"part", query.part},
            {"section", query.section}
        });
    if (r.error.code != cpr::ErrorCode::OK) {
        throw std::runtime_error("Network error: " + r.error.message);
    }
    if (r.status_code != 200) {
        throw std::runtime_error("HTTP error: " + std::to_string(r.status_code));
    }
    return r.text;
}

std::vector<std::string> RegulationService::ProcessResponse(std::string response) {
    nlohmann::json j = nlohmann::json::parse(response);
    std::vector<std::string> result;
    std::unordered_set<std::string> seen;
    for (const auto& item : j["content_versions"]) {
        if (!item.contains("date")) continue;
        std::string date = item["date"];
        if (seen.insert(date).second) { // true if inserted (not duplicate)
            result.push_back(date);
        }
    }
    return result;
}
