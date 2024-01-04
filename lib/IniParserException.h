#ifndef CPPL_DIP_INIPARSEREXCEPTION_H
#define CPPL_DIP_INIPARSEREXCEPTION_H

#include <exception>
#include <string>

class IniParserException: public std::exception {
public:
    explicit IniParserException(std::string message);
    const char* what();
private:
    std::string message;
};

#endif //CPPL_DIP_INIPARSEREXCEPTION_H
