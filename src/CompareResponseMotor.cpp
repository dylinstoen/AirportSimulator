//
// Created by dylin on 4/13/2026.
//

#include "CompareResponseMotor.h"

#include <algorithm>
#include <iostream>
#include <optional>
#include <ostream>
#include <regex>
#include <string>
#include <vector>

#include "Model/MarkerKind.h"
#include "Utilities/MarkerCycle.h"
#include "Utilities/MarkerDetector.h"


struct ParsedMarker {
    std::string raw;       // "(a)"
    std::string body;      // "a"
    std::string remainder; // text after marker
};

std::optional<int> FindIndexInCycle(MarkerKind kind) {
    const auto& cycle = MarkerCycle::DefaultMarkerCycle();
    for (int i = 0; i < static_cast<int>(cycle.size()); ++i) {
        if (cycle[i] == kind) {
            return i;
        }
    }
    return std::nullopt;
}

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
// TODO: If its at a roman numeral and current levels sibiling dosn't expect c or d then its a lower alpha
// TODO:
ResponseNode CompareResponseMotor::Process(tinyxml2::XMLElement* root) {
    ResponseNode rootNode;
    rootNode.kind = MarkerKind::None;
    std::vector<ResponseNode*> stack;
    stack.push_back(&rootNode);
    for (tinyxml2::XMLElement* elem = root->FirstChildElement(); elem != nullptr; elem = elem->NextSiblingElement()) {

        if (strcmp(elem->Name(), "P") != 0) {
            continue;
        }
        const char* rawText = elem->GetText();
        if (!rawText) {
            continue;
        }
        auto parsed = TryParseLeadingMarker(rawText);
        if (!parsed) {
            continue;
        }
        MarkerKind incomingKind;
        if (!stack.empty() && !stack.back()->children.empty()) {
            incomingKind = MarkerDetector::ClassifyMarker(parsed.value().body, stack.back()->children.back().marker);
        } else {
            incomingKind = MarkerDetector::ClassifyMarker(parsed.value().body);
        }

        if (incomingKind == MarkerKind::None) {
            continue;
        }
        auto incomingIndex = FindIndexInCycle(incomingKind);
        if (!incomingIndex) {
            continue;
        }
        while (!stack.empty()) {
            ResponseNode* current = stack.back();
            if (current->kind == MarkerKind::None) {
                break;
            }
            auto currentIndex = FindIndexInCycle(current->kind);
            if (!currentIndex) {
                break;
            }
            if (*incomingIndex == *currentIndex + 1) {
                // Go 1 level deeper
                break;
            }
            if (*incomingIndex == *currentIndex) {
                // it's the same level so add to parents child
                stack.pop_back();
                break;
            }
            if (*incomingIndex < *currentIndex) {
                // Pop back up until a valid parent is found
                stack.pop_back();
                continue;
            }
            // just pop upwards if deeper level is not in cycle
            stack.pop_back();
        }
        if (stack.empty()) {
            stack.push_back(&rootNode);
        }
        ResponseNode newNode;
        newNode.marker = parsed.value().body;
        newNode.text = parsed->remainder;
        newNode.kind = incomingKind;

        stack.back()->children.push_back(std::move(newNode));
        ResponseNode* inserted = &stack.back()->children.back();
        stack.push_back(inserted);
    }
    return rootNode;
}


