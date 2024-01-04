#include "Logger.h"

void Logger::log_error(const std::string& msg) {
    std::cout << "[ошибка]:" << msg << std::endl;
}

void Logger::log_warning(const std::string& msg) {
    std::cout << "[предупреждение]:" << msg << std::endl;
}

void Logger::log_message(const std::string& msg) {
    std::cout << "[информация]:" << msg << std::endl;
}