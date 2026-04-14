//
// Created by dylin on 4/13/2026.
//

#include "CompareResponseMotor.h"

#include <iostream>
#include <optional>
#include <ostream>
#include <regex>
#include <string>
#include <vector>

#include "Model/MarkerKind.h"


struct RegulationNode {
    std::string marker;                 // "(a)", "(1)", "(i)"
    std::string text;                   // full paragraph text
    std::vector<RegulationNode> children;
};
struct RegulationSection {
    std::string head;
    std::vector<RegulationNode> nodes;
    std::string citation;
};

struct ParsedMarker {
    std::string raw;       // "(a)"
    std::string body;      // "a"
    std::string remainder; // text after marker
};
std::optional<ParsedMarker> TryParseLeadingMarker(const std::string& text) {
    static const std::regex pattern(R"(^\s*(\(([A-Za-z0-9ivxlcdmIVXLCDM]+)\))\s*(.*)$)");
    std::smatch match;
    if (!std::regex_match(text, match, pattern)) {
        return std::nullopt;
    }
    ParsedMarker result;
    result.raw = match[1];
    result.body = match[2];
    result.remainder = match[3];
    return result;
}

RegulationNode* AppendChild(std::vector<std::unique_ptr<RegulationNode>>& list, std::string marker, MarkerKind kind, std::string text) {

}

void CompareResponseMotor::Process(tinyxml2::XMLElement* root) {
    for (tinyxml2::XMLElement* elem = root->FirstChildElement(); elem != nullptr; elem = elem->NextSiblingElement()) {
        auto parsed = TryParseLeadingMarker(elem->GetText());
        if (!parsed) {


        }
    }
}


