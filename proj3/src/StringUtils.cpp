#include "StringUtils.h"
#include <algorithm>
#include <cctype>

// Capitalizes the first letter of the string
std::string StringUtils::Capitalize(const std::string &str) noexcept {
    if (str.empty()) return str;
    std::string result = str;
    result[0] = std::toupper(result[0]);
    for (std::size_t i = 1; i < result.size(); i++) { // Use std::size_t for iteration
        result[i] = std::tolower(result[i]);
    }
    return result;
}

// Converts all characters to uppercase
std::string StringUtils::Upper(const std::string &str) noexcept {
    std::string result = str;
    for (std::size_t i = 0; i < result.size(); i++) {
        result[i] = std::toupper(result[i]);
    }
    return result;
}

// Converts all characters to lowercase
std::string StringUtils::Lower(const std::string &str) noexcept {
    std::string result = str;
    for (std::size_t i = 0; i < result.size(); i++) {
        result[i] = std::tolower(result[i]);
    }
    return result;
}

// Centers the string with padding
std::string StringUtils::Center(const std::string &str, int width, char fill) noexcept {
    if (str.empty() || static_cast<std::size_t>(width) <= str.size()) { // Cast width
        return str;
    }
    int padding = width - str.size();
    int leftPad = padding / 2;
    int rightPad = padding - leftPad;
    return std::string(leftPad, fill) + str + std::string(rightPad, fill);
}

// Left justifies the string
std::string StringUtils::LJust(const std::string &str, int width, char fill) noexcept {
    if (str.empty() || static_cast<std::size_t>(width) <= str.size()) {
        return str;
    }
    return str + std::string(width - str.size(), fill);
}

// Right justifies the string
std::string StringUtils::RJust(const std::string &str, int width, char fill) noexcept {
    if (str.empty() || static_cast<std::size_t>(width) <= str.size()) {
        return str;
    }
    return std::string(width - str.size(), fill) + str;
}

