#include <fstream>

#include "Logger.h"
#include "IniParser.h"
#include "IniParserException.h"

using namespace iniparser;

IniParser::IniParser(const std::string& path) : path(path), data({}), pt(ParserTools()) {
    bool ok;
    std::string msg;
    std::tie(ok, msg) = read_file_data(path);
    if (!ok) {
        throw IniParserException(msg);
    }
}

bool IniParser::add_section(const std::string& section_key) {
    if (this->data.count(section_key) > 0) {
        return false;
    }
    Section new_section = {};
    this->data[section_key] = new_section;
    return true;
};

bool IniParser::has_section(const std::string &section_key) const {
    return this->data.count(section_key) > 0;
}

bool IniParser::add_key_value(const std::string& section_key, const std::string& key, const std::string& value) {
    if (this->data.count(section_key) == 0) {
        return false;
    }
    this->data[section_key][key] = value;
    return true;
};

std::tuple<bool, std::string> IniParser::read_file_data(const std::string& filepath) {

    std::ifstream file;
    file.open(filepath);
    if (!file.is_open()) {
        return {false, "не удалось открыть файл"};
    }

    std::string current_section_name;

    for (std::string line; std::getline(file, line);) {

        std::string trimmed = Strings::trim_spaces(line);
        if (trimmed.length() == 0) continue;

        if (pt.is_commentary(trimmed)) {
            Logger::log_message("пропускаю комментарий: " + trimmed);
            continue;
        }

        std::string value_str;
        if (pt.includes_commentary(trimmed)) {
            auto splitted = Strings::split(trimmed, ";");
            value_str = splitted[0];
            Logger::log_message("отбрасываю комментарий: " + splitted[1]);
        } else {
            value_str = trimmed;
        }

        value_str = Strings::trim_spaces(value_str);

        if (pt.is_section(value_str)) {
            bool ok;
            std::string msg;

            std::tie(ok, msg) = pt.get_section(value_str);
            if (!ok) {
                Logger::log_error(msg);
                continue;
            }

            ok = add_section(msg);
            if (!ok) {
                Logger::log_warning("такая секция уже существует: " + msg);
            } else {
                Logger::log_message("добавлена секция: " + msg);
            }

            current_section_name = msg;
            continue;
        }

        if (pt.is_key_value(value_str)) {
            bool ok;
            std::string key;
            std::string value;

            std::tie(ok, key, value) = pt.get_key_value(value_str);
            if (!ok) {
                // log here
                continue;
            }

            if (current_section_name.length() > 0) {
                std::string msg;
                msg += "inside [";
                msg += current_section_name;
                msg += "]: ";
                msg += key;
                msg += "=";
                msg += value;
                Logger::log_message(msg);

                ok = add_key_value(current_section_name, key, value);
                if (!ok) {
                    std::string err;
                    err += "не удалось добавить значение ";
                    err += value;
                    err += "=";
                    err += key;
                    Logger::log_error(err);
                }
            }
            continue;
        }

        Logger::log_error("не удалось разобрать строку: " + line);
    }

    return {true, ""};
}

std::tuple<bool, std::string> IniParser::get_ini_value(const std::string& address) {
    if (!Strings::contains(address, ".")) {
        return {false, "передайте адрес значения в виде section.key"};
    }

    auto split = Strings::split(address, ".");
    if (split.size() != 2) {
        return {false, "некорректный формат адреса, ожидаемый формат: section.key"};
    }

    if (split[0].empty() || split[1].empty()) {
        return {false, "пустое значение секции или ключа"};
    }

    if (!has_section(split[0])) {
        return {false, "секции " + split[0] + " не в структуре данных"};
    }

    if (data[split[0]].count(split[1]) != 1) {
        return {false, "в секции " + split[0] + " нет значения для " + split[1]};
    }

    return {true, data[split[0]][split[1]]};
};
