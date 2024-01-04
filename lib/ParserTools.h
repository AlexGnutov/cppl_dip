#ifndef CPPL_DIP_PARSERTOOLS_H
#define CPPL_DIP_PARSERTOOLS_H

#include <string>
#include <tuple>

#include "Strings.h"

//! Функции для парсинга строк INI файлов.
class ParserTools {
public:
    //! Проверяет, является ли строка комментарием.
    bool is_commentary(const std::string& line);

    //! Проверяет, включает ли строка комментарий.
    bool includes_commentary(const std::string& line);

    //! Проверяет, содержит ли строка пару ключ - значение.
    bool is_key_value(const std::string& line);

    //! Проверяет, содержит ли строка имя секции.
    bool is_section(const std::string& line);

    //! Возвращает комментарий из строки.
    std::tuple<bool, std::string> get_commentary(const std::string& line);

    //! Возвращает имя секции из строки с именем секции.
    std::tuple<bool, std::string> get_section(const std::string& line);

    //! Возвращает ключ и значение из строки с парой ключ-значение.
    std::tuple<bool, std::string, std::string> get_key_value(const std::string& line);
};

#endif //CPPL_DIP_PARSERTOOLS_H
