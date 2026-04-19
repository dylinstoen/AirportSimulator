//
// Created by dylin on 4/9/2026.
//

#include "RegulationService.h"

#include <iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <tinyxml2.h>

#include "CompareResponseMotor.h"
#include "Model/Response.h"

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

Response RegulationService::ProcessCompareResponse(std::string response) {
    tinyxml2::XMLDocument document;
    tinyxml2::XMLError err = document.Parse(response.c_str());
    if (err != tinyxml2::XML_SUCCESS) {
        throw std::runtime_error(document.ErrorStr() ? document.ErrorStr() : "XML parse failed");
    }
    tinyxml2::XMLElement* root = document.FirstChildElement("DIV8");
    if (!root) {
        throw std::runtime_error("DIV8 root not found");
    }
    Response result;
    if (tinyxml2::XMLElement* header = root->FirstChildElement("HEAD")) {
        result.header = header->GetText();
    }
    result.body = CompareResponseMotor::Process(root);
    return result;
}

ResponseDifNode BuildAddedTree(const ResponseNode& node) {
    ResponseDifNode diffNode;
    diffNode.marker = node.marker;
    diffNode.text = node.text;
    diffNode.kind = ResponseDifType::ADDED;

    for (const ResponseNode& child : node.children) {
        diffNode.children.push_back(BuildAddedTree(child));
    }

    return diffNode;
}

ResponseDifNode BuildRemovedTree(const ResponseNode& node) {
    ResponseDifNode diffNode;
    diffNode.marker = node.marker;
    diffNode.text = node.text;
    diffNode.kind = ResponseDifType::REMOVED;

    for (const ResponseNode& child : node.children) {
        diffNode.children.push_back(BuildRemovedTree(child));
    }

    return diffNode;
}

bool AllChildrenSame(const std::vector<ResponseDifNode>& children) {
    for (const ResponseDifNode& child : children) {
        if (child.kind != ResponseDifType::SAME) {
            return false;
        }
    }
    return true;
}
// Build tree of old new child nodes starting at node i,
//
ResponseDifNode BuildDiffNodeRecursion(const ResponseNode* oldNode, const ResponseNode* newNode) {
    // base case
    if (oldNode == nullptr && newNode == nullptr) {
        return {};
    }
    // if there is no old but there is a new node then everything thats a child is added
    if (oldNode == nullptr) {
        return BuildAddedTree(*newNode);
    }

    // if there is a new node node and no old node then everything thats a child is removed
    if (newNode == nullptr) {
        return BuildRemovedTree(*oldNode);
    }

    // Now we are in the changed steps
    // Make output text the new node text
    ResponseDifNode diffNode;
    // Safe guard in case new node dosnt have a marker
    diffNode.marker = newNode->marker.empty() ? oldNode->marker : newNode->marker;
    diffNode.text = newNode->text;

    // Create maps of old and new markers
    std::unordered_map<std::string, const ResponseNode*> oldChildrenByMarker;
    std::unordered_map<std::string, const ResponseNode*> newChildrenByMarker;

    for (const ResponseNode& child : oldNode->children) {
        oldChildrenByMarker[child.marker] = &child;
    }

    for (const ResponseNode& child : newNode->children) {
        newChildrenByMarker[child.marker] = &child;
    }

    // Foreach new child node find its respective old child and if there is one then recurse into that child
    for (const ResponseNode& newChild : newNode->children) {
        const ResponseNode* matchingOld = nullptr;
        auto oldIt = oldChildrenByMarker.find(newChild.marker);
        // if there is a child
        if (oldIt != oldChildrenByMarker.end()) {
            matchingOld = oldIt->second;
        }
        // if there is not nullptr on matching old will ensure everything below gets added as a remove node
        diffNode.children.push_back(BuildDiffNodeRecursion(matchingOld, &newChild));
    }

    // Do the same thing but with old node. Loop through and see if it contains the new child marker. If it dosnt then push back the remove nodes
    for (const ResponseNode& oldChild : oldNode->children) {
        auto newIt = newChildrenByMarker.find(oldChild.marker);
        if (newIt == newChildrenByMarker.end()) {
            diffNode.children.push_back(BuildRemovedTree(oldChild));
        }
    }

    // Assign the actual text as you pop out of this recursive leaf
    bool textSame = (oldNode->text == newNode->text);
    bool markerSame = (oldNode->marker == newNode->marker);
    bool childrenSame = AllChildrenSame(diffNode.children);

    if (textSame && markerSame && childrenSame) {
        diffNode.kind = SAME;
    } else if (!textSame || !markerSame) {
        diffNode.kind = CHANGED;
    } else {
        // parent text same but something below changed
        diffNode.kind = CHANGED;
    }

    return diffNode;
}

ResponseDif RegulationService::ProcessDiffResponse(Response& firstResponse, Response& secondResponse) {
    ResponseDif result;

    if (firstResponse.header == secondResponse.header) {
        result.header = firstResponse.header;
    } else {
        result.header = firstResponse.header + " -> " + secondResponse.header;
    }

    result.body = BuildDiffNodeRecursion(&firstResponse.body, &secondResponse.body);
    return result;
}
