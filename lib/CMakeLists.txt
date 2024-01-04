set(HEADERS
        Logger.h
        Strings.h
        ParserTools.h
        IniParser.h
        IniParserException.h
)

set(SOURCES
        Logger.cpp
        Strings.cpp
        ParserTools.cpp
        IniParser.cpp
        IniParserException.cpp
)

add_library(ini_lib SHARED ${HEADERS} ${SOURCES})
target_include_directories(ini_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
