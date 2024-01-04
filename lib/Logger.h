#ifndef CPPL_DIP_LOGGER_H
#define CPPL_DIP_LOGGER_H

#include <iostream>
#include <string>

//! Класс для вывода информации в консоль.
class Logger {
public:
    //! Выводит ошибку.
    static void log_error(const std::string& msg);

    //! Выводит предупреждение.
    static void log_warning(const std::string& msg);

    //! Выводит сообщение.
    static void log_message(const std::string& msg);
};

#endif //CPPL_DIP_LOGGER_H
