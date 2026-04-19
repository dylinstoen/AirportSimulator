//
// Created by dylin on 4/13/2026.
//
#include "MarkerDetector.h"

#include <iostream>
#include <optional>
#include <ostream>
#include <vector>

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

bool IsValidRomanNumeral(const std::string& s) {
    if (s.empty()) return false;

    for (char c : s) {
        if (!IsRomanChar(c)) return false;
    }

    int repeatCount = 1;
    char prev = 0;
    int total = 0;
    int lastValue = 0;

    for (int i = static_cast<int>(s.size()) - 1; i >= 0; --i) {
        char c = static_cast<char>(std::tolower(static_cast<unsigned char>(s[i])));
        int value = RomanCharValue(c);
        if (value == 0) return false;

        if (c == prev) {
            ++repeatCount;

            if (c == 'v' || c == 'l' || c == 'd') {
                return false;
            }
            if (repeatCount > 3) {
                return false;
            }
        } else {
            repeatCount = 1;
            prev = c;
        }

        if (value < lastValue) {
            char next = static_cast<char>(std::tolower(static_cast<unsigned char>(s[i + 1])));
            bool validSubtract =
                (c == 'i' && (next == 'v' || next == 'x')) ||
                (c == 'x' && (next == 'l' || next == 'c')) ||
                (c == 'c' && (next == 'd' || next == 'm'));

            if (!validSubtract) {
                return false;
            }
            total -= value;
        } else {
            total += value;
            lastValue = value;
        }
    }

    return total > 0;
}
std::optional<int> MarkerDetector::GetMarkerValue(const std::string& marker, MarkerKind kind) {
    switch (kind) {
        case MarkerKind::Number:
            if (IsAllDigits(marker)) return std::stoi(marker);
            break;

        case MarkerKind::LowerAlpha:
            if (marker.size() == 1 && std::islower(static_cast<unsigned char>(marker[0]))) {
                return (marker[0] - 'a') + 1;
            }
            break;

        case MarkerKind::UpperAlpha:
            if (marker.size() == 1 && std::isupper(static_cast<unsigned char>(marker[0]))) {
                return (marker[0] - 'A') + 1;
            }
            break;

        case MarkerKind::LowerRoman:
            if (IsAllLowerRoman(marker) && IsValidRomanNumeral(marker)) {
                return RomanToInt(marker);
            }
            break;

        case MarkerKind::UpperRoman:
            if (IsAllUpperRoman(marker) && IsValidRomanNumeral(marker)) {
                return RomanToInt(marker);
            }
            break;

        default:
            break;
    }

    return std::nullopt;
}
std::vector<MarkerCandidate> MarkerDetector::GetCandidates(const std::string& body) {
    std::vector<MarkerCandidate> result;

    if (IsAllDigits(body)) {
        result.push_back({ MarkerKind::Number, std::stoi(body) });
    }

    if (IsAllLowerAlpha(body)) {
        // for now only support single-char alpha
        if (body.size() == 1) {
            result.push_back({ MarkerKind::LowerAlpha, (body[0] - 'a') + 1 });
        }
    }

    if (IsAllUpperAlpha(body)) {
        if (body.size() == 1) {
            result.push_back({ MarkerKind::UpperAlpha, (body[0] - 'A') + 1 });
        }
    }

    if (IsAllLowerRoman(body) && IsValidRomanNumeral(body)) {
        result.push_back({ MarkerKind::LowerRoman, RomanToInt(body) });
    }

    if (IsAllUpperRoman(body) && IsValidRomanNumeral(body)) {
        result.push_back({ MarkerKind::UpperRoman, RomanToInt(body) });
    }

    return result;
}
