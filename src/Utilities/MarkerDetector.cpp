//
// Created by dylin on 4/13/2026.
//
#include "MarkerDetector.h"

bool IsRomanChar(char c) {
    c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    return c == 'i' || c == 'v' || c == 'x' || c == 'l' || c == 'c' || c == 'd' || c == 'm';
}
bool IsAllDigits(const std::string& s) {
    if (s.empty()) return false;
    for (const char c : s) {
        if (!std::isdigit(static_cast<unsigned char>(c))) return false;
    }
    return true;
}

bool IsAllLowerAlpha(const std::string& s) {
    if (s.empty()) return false;
    for (const char c : s) {
        if (!std::islower(static_cast<unsigned char>(c))) return false;
    }
    return true;
}

bool IsAllUpperAlpha(const std::string& s) {
    if (s.empty()) return false;
    for (const char c : s) {
        if (!std::isupper(static_cast<unsigned char>(c))) return false;
    }
    return true;
}

bool IsAllLowerRoman(const std::string& s) {
    if (s.empty()) return false;
    for (const char c : s) {
        if (!std::islower(static_cast<unsigned char>(c)) || !IsRomanChar(c)) return false;
    }
    return true;
}

bool IsAllUpperRoman(const std::string& s) {
    if (s.empty()) return false;
    for (char c : s) {
        if (!std::isupper(static_cast<unsigned char>(c)) || !IsRomanChar(c)) return false;
    }
    return true;
}

MarkerKind MarkerDetector::ClassifyMarker(const std::string& body) {
    if (IsAllDigits(body)) return MarkerKind::Number;
    if (IsAllLowerRoman(body)) return MarkerKind::LowerRoman;
    if (IsAllUpperRoman(body)) return MarkerKind::UpperRoman;
    if (IsAllLowerAlpha(body)) return MarkerKind::LowerAlpha;
    if (IsAllUpperAlpha(body)) return MarkerKind::UpperAlpha;
    return MarkerKind::None;
}
