//
// Created by dylin on 4/13/2026.
//
#include "MarkerDetector.h"

#include <iostream>
#include <ostream>

int RomanCharValue(char c) {
    switch (std::tolower(static_cast<unsigned char>(c))) {
        case 'i': return 1;
        case 'v': return 5;
        case 'x': return 10;
        case 'l': return 50;
        case 'c': return 100;
        case 'd': return 500;
        case 'm': return 1000;
        default: return 0;
    }
}

int RomanToInt(const std::string& s) {
    int total = 0;
    int prev = 0;

    for (int i = static_cast<int>(s.size()) - 1; i >= 0; --i) {
        int value = RomanCharValue(s[i]);
        if (value == 0) {
            return -1;
        }

        if (value < prev) {
            total -= value;
        } else {
            total += value;
            prev = value;
        }
    }

    return total;
}
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
// TODO: Does this have a sibiling or will this be a first child?
// TODO: Does this MarkerKind make sense for the sibiling?
MarkerKind MarkerDetector::ClassifyMarker(const std::string& body, const std::string& sibilingBody) {
    if (IsAllDigits(body)) return MarkerKind::Number;
    std::cout << sibilingBody << std::endl;
    if (IsAllLowerRoman(body) && RomanToInt(body) == RomanToInt(sibilingBody) + 1) {
        return MarkerKind::LowerRoman;
    }

    if (IsAllUpperRoman(body)) return MarkerKind::UpperRoman;
    if (IsAllLowerAlpha(body)) return MarkerKind::LowerAlpha;
    if (IsAllUpperAlpha(body)) return MarkerKind::UpperAlpha;
    return MarkerKind::None;
}
MarkerKind MarkerDetector::ClassifyMarker(const std::string& body) {
    if (IsAllDigits(body)) return MarkerKind::Number;
    if (IsAllLowerRoman(body) && RomanToInt(body) == 1) {
        return MarkerKind::LowerRoman;
    }
    if (IsAllUpperRoman(body)) return MarkerKind::UpperRoman;
    if (IsAllLowerAlpha(body)) return MarkerKind::LowerAlpha;
    if (IsAllUpperAlpha(body)) return MarkerKind::UpperAlpha;
    return MarkerKind::None;
}