//
// Created by alex on 04.01.24.
//

#include "ParserTools.h"

bool ParserTools::is_commentary(const std::string &line) {
    return Strings::starts_with(line, ";");
};

bool ParserTools::includes_commentary(const std::string &line) {
    return !Strings::starts_with(line, ";") && Strings::contains(line, ";");
}

bool ParserTools::is_key_value(const std::string &line) {
    return Strings::contains(line, "=") && Strings::count(line, "=") == 1;
};

bool ParserTools::is_section(const std::string &line) {
    return Strings::starts_with(line, "[") && Strings::ends_with(line, "]");
};

std::tuple<bool, std::string> ParserTools::get_commentary(const std::string &line) {
    return {true, ""};
};

std::tuple<bool, std::string> ParserTools::get_section(const std::string &line) {
    auto tl = Strings::trim_left(line, '[');
    auto out = Strings::trim_right(tl, ']');
    if (!out.empty()) {
        return {true, out};
    }
    return {false, "не удалось получить имя секции, т.к. имя нулевой длины"};
};

std::tuple<bool, std::string, std::string> ParserTools::get_key_value(const std::string &line) {
    auto split = Strings::split(line, "=");
    if (split.size() == 2 && !split[0].empty()) {
        return {true, split[0], split[1]};
    }
    return {false, "", ""};
};
