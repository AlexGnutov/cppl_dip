#ifndef CPPL_DIP_INIPARSER_H
#define CPPL_DIP_INIPARSER_H

#include <string>
#include <unordered_map>
#include <tuple>

#include "Strings.h"
#include "ParserTools.h"
#include "IniParserException.h"

typedef std::unordered_map<std::string, std::string> Section;
typedef std::unordered_map<std::string, Section> IniData;

namespace iniparser {

class IniParser {
public:

    explicit IniParser(const std::string& path);

    template<typename T>
    T get_value(const std::string& address) {
        T value;
        get_value(address, value);
        return value;
    }

    std::string path;
    IniData data;
    ParserTools pt;

private:
    //! Добавляет секцию с указанным именем.
    bool add_section(const std::string& section_key);

    //! Проверяет, есть ли секция с указанным именем.
    bool has_section(const std::string& section_key) const;

    //! Добавляет в указанную секцию пару ключ-значение.
    bool add_key_value(const std::string& section_key, const std::string& key, const std::string& value);

    //! Считывает данные INI файла.
    std::tuple<bool, std::string> read_file_data(const std::string& filepath);

    //! Возвращает значение из выбранной секции section.key.
    std::tuple<bool, std::string> get_ini_value(const std::string& address);

    /*
    //! Возвращает значение пары в заданной секции.
    template<typename TL>
    void get_value(const std::string& address, TL& value) {
        bool ok;
        std::string msg;
        std::tie(ok, msg) = get_ini_value(address);
        if (!ok) throw IniParserException(msg);
        value = static_cast<TL>(msg);
    }
     */

    void get_value(const std::string& address, std::string& value) {
        bool ok;
        std::string msg;
        std::tie(ok, msg) = get_ini_value(address);
        if (!ok) throw IniParserException(msg);
        value = msg;
    }

    void get_value(const std::string& address, int& value) {
        bool ok;
        std::string msg;
        std::tie(ok, msg) = get_ini_value(address);
        if (!ok) throw IniParserException(msg);
        value = std::stoi(msg);
    }

    void get_value(const std::string& address, double& value) {
        bool ok;
        std::string msg;
        std::tie(ok, msg) = get_ini_value(address);
        if (!ok) throw IniParserException(msg);
        value = std::stod(msg);
    }

};

} // iniparser

#endif //CPPL_DIP_INIPARSER_H
