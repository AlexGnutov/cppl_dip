#ifndef CPPL_DIP_STRINGS_H
#define CPPL_DIP_STRINGS_H

#include <string>
#include <vector>

class Strings {
public:
    static std::string trim_left(const std::string& str, char ch);

    static std::string trim_right(const std::string& str, char ch);

    static std::string trim_spaces(const std::string& str);

    static std::vector<std::string> split(const std::string& str, const std::string& sep);

    static int count(const std::string& str, const std::string& key);

    static bool contains(const std::string& str, const std::string& key);

    static bool starts_with(const std::string& str, const std::string& key);

    static bool ends_with(const std::string& str, const std::string& key);
};

#endif //CPPL_DIP_STRINGS_H