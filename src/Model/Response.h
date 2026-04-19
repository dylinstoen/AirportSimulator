//
// Created by dylin on 4/14/2026.
//

#ifndef AIRPORTSIMULATOR_RESPONSE_H
#define AIRPORTSIMULATOR_RESPONSE_H
#include <string>
#include <vector>
#include "MarkerKind.h"

enum ResponseDifType {
    ADDED,
    CHANGED,
    REMOVED,
    SAME
};
struct ResponseNode {
    std::string marker;
    std::string text;
    MarkerKind kind = MarkerKind::None;
    std::vector<ResponseNode> children;
};

struct Response {
    std::string header;
    ResponseNode body;
};

struct ResponseDifNode {
    std::string marker;
    std::string text;
    ResponseDifType kind = ResponseDifType::SAME;
    std::vector<ResponseDifNode> children;
};

struct ResponseDif {
    std::string header;
    ResponseDifNode body;
};
#endif //AIRPORTSIMULATOR_RESPONSE_H
