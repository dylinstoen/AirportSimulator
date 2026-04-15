//
// Created by dylin on 4/14/2026.
//

#ifndef AIRPORTSIMULATOR_RESPONSE_H
#define AIRPORTSIMULATOR_RESPONSE_H
#include <string>
#include <vector>
#include "MarkerKind.h"

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
#endif //AIRPORTSIMULATOR_RESPONSE_H
