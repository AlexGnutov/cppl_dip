#include <string>
#include <iostream>

#include "IniParser.h"

#ifdef  _WIN32
#include <windows.h>
#endif

int main() {

#ifdef _WIN32
    SetConsoleOutputCP(65001);
#else
    setlocale(LC_ALL, "rus");
#endif

	iniparser::IniParser p("test.INI");

    std::cout << "Section1.var1=" << p.get_value<double>("Section1.var1") << std::endl;
    std::cout << "Section1.var2=" << p.get_value<std::string>("Section1.var2") << std::endl;
    std::cout << "Section1.var3=" << p.get_value<std::string>("Section1.var3") << std::endl;

    std::cout << "Section2.var1=" << p.get_value<int>("Section2.var1") << std::endl;
    std::cout << "Section2.var2=" << p.get_value<std::string>("Section2.var2") << std::endl;

    std::cout << "Section4.Mode=" <<  p.get_value<std::string>("Section4.Mode") << std::endl;
    std::cout << "Section4.Vid=" <<  p.get_value<std::string>("Section4.Vid") << std::endl;

	return 0;
}