//
// Created by dylin on 4/13/2026.
//
#include "MarkerDetector.h"

bool IsRomanChar(char c) {
    c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    return c == 'i' || c == 'v' || c == 'x' || c == 'l' || c == 'c' || c == 'd' || c == 'm';
}
bool IsAllDigits(std::string& s) {
    if (s.empty()) return false;
    for (const char c : s) {
        if (!std::isdigit(static_cast<unsigned char>(c))) return false;
    }
    return true;
}

MarkerKind MarkerDetector::ClassifyMarker(const std::string& body) {

}
