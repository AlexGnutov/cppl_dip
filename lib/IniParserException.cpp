#include "IniParserException.h"

IniParserException::IniParserException(std::string message)
: message(std::move(message)) {}

const char* IniParserException::what() {
    return message.c_str();
}
