//
// Created by dylin on 4/9/2026.
//

#include "RegulationService.h"

#include <iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <tinyxml2.h>

#include "CompareResponseMotor.h"

std::string RegulationService::ProcessRequest(Query query) {
    cpr::Response r = cpr::Get(cpr::Url{query.url},
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


std::vector<std::string> RegulationService::ProcessSearchResponse(std::string response) {
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

std::string RegulationService::ProcessCompareResponse(std::string response) {
    tinyxml2::XMLDocument document;
    tinyxml2::XMLError err = document.Parse(response.c_str());
    tinyxml2::XMLElement* root = document.FirstChildElement("DIV8");
    CompareResponseMotor c;
    c.Process(root);
    return "";
}


