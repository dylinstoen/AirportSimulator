//
// Created by dylin on 4/13/2026.
//

#include "CompareResponseMotor.h"

#include <algorithm>
#include <iostream>
#include <optional>
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
bool IsMarkerChild(MarkerKind parent, MarkerKind child) {
    const auto& cycle = MarkerCycle::DefaultMarkerCycle();

    for (size_t i = 0; i + 1 < cycle.size(); ++i) {
        if (cycle[i] == parent && cycle[i + 1] == child) {
            return true;
        }
    }
    return false;
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
struct ParentMatch {
    ResponseNode* parent = nullptr;
    MarkerKind kind = MarkerKind::None;
    int score = -1000000;
};
int ScoreCandidateParent(ResponseNode* parent, const MarkerCandidate& incoming) {
    if (!parent) return -1000000;

    // No previous child and the incoming value is a starting value. Insert it here
    if (parent->children.empty() && incoming.value == 1) {
        return 1000;
    }
    // No previous child and its not a child then it must be a parent
    if (parent->children.empty() && incoming.value != 1) {
        return -1000;
    }

    const ResponseNode& prev = parent->children.back();

    if (!IsMarkerChild(parent->kind, incoming.kind)) {
        return -1000;
    }

    auto prevValue = MarkerDetector::GetMarkerValue(prev.marker, prev.kind);
    // if there is no previous value and we already determined above that the incoming kind isnt starting so this is clearly not the child
    if (!prevValue.has_value()) {
        return -1000;
    }
    // if its the next value in the sequence
    if (incoming.value == *prevValue + 1) {
        return 100;
    }
    // Rare but if its the same value in the sequence thats okay
    if (incoming.value == *prevValue) {
        return 20;
    }
    // Also rare but if its just greater maybe typo then thats fine
    if (incoming.value > *prevValue) {
        return 5;
    }

    // If its strictly less than the prev child then its not this
    return -100;
}
ParentMatch FindBestParent(const std::vector<ResponseNode*>& stack, const std::vector<MarkerCandidate>& candidates) {
    ParentMatch best;
    for (int i = static_cast<int>(stack.size()) - 1; i >= 0; --i) {
        ResponseNode* parent = stack[i];
        if (!parent) {
            continue;
        }

        for (const auto& candidate : candidates) {
            int score = ScoreCandidateParent(parent, candidate);

            // Prefer deeper parents when score ties
            score += i;

            if (score > best.score) {
                best.parent = parent;
                best.kind = candidate.kind;
                best.score = score;
            }
        }
    }

    return best;
}
void TrimStackToParent(std::vector<ResponseNode*>& stack, ResponseNode* parent) {
    while (!stack.empty() && stack.back() != parent) {
        stack.pop_back();
    }
}
ResponseNode CompareResponseMotor::Process(tinyxml2::XMLElement* root) {
    ResponseNode rootNode;
    rootNode.kind = MarkerKind::None;

    std::vector<ResponseNode*> stack;
    stack.push_back(&rootNode);


    for (tinyxml2::XMLElement* elem = root->FirstChildElement();
        elem != nullptr;
        elem = elem->NextSiblingElement()) {

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

            const std::string& markerText = parsed->body;
            const std::string& remainder = parsed->remainder;
            // 1. Get all possible interpretations
            std::vector<MarkerCandidate> candidates = MarkerDetector::GetCandidates(markerText);
            if (candidates.empty()) {
                continue;
            }

            // 2. Find best parent + best kind
            ParentMatch match = FindBestParent(stack, candidates);
            if (!match.parent || match.kind == MarkerKind::None) {
                continue;
            }

            // 3. Move stack back to chosen parent
            TrimStackToParent(stack, match.parent);
            if (stack.empty()) {
                stack.push_back(&rootNode);
                match.parent = &rootNode;
            }

            // 4. Insert
            ResponseNode newNode;
            newNode.marker = markerText;
            newNode.text = remainder;
            newNode.kind = match.kind;

            match.parent->children.push_back(std::move(newNode));
            ResponseNode* inserted = &match.parent->children.back();

            // 5. Push inserted node as current path leaf
            stack.push_back(inserted);
    }
    return rootNode;
}


