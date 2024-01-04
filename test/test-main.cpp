#include "catch2/catch_test_macros.hpp"
#include "catch2/catch_session.hpp"

#include "../lib/Strings.h"


TEST_CASE("Strings.h testing", "[Strings.h]") {

    SECTION("Strings::contains for: \">Test string 11!\"") {
        std::string test = ">Test string 11!";
        CHECK(Strings::contains(test, "T"));
        CHECK(!Strings::contains(test, "H"));
        CHECK(Strings::contains(test, "!"));
        CHECK(!Strings::contains(test, "_"));
    }

    SECTION("Strings::starts_with for: \">Test string 11!\"") {
        std::string test = ">Test string 11!";
        CHECK(!Strings::starts_with(test, "<"));
        CHECK(Strings::starts_with(test, ">"));
    }

    SECTION("Strings::ends_with for: \">Test string 11!\"") {
        std::string test = ">Test string 11!";
        CHECK(!Strings::ends_with(test, ">"));
        CHECK(Strings::ends_with(test, "1!"));
    }

    SECTION("Strings::count for: \">Test string 11!\"") {
        std::string test = ">Test string 11!";
        CHECK(Strings::count(test, "T") == 1);
        CHECK(Strings::count(test, " ") == 2);
        CHECK(Strings::count(test, "11") == 1);
        CHECK(Strings::count(test, "i") == 1);
        CHECK(Strings::count(test, "X") == 0);
    }

    SECTION("Strings::trim_left for: \">Test string 11!\"") {
        std::string test = ">Test string 11!";
        CHECK(Strings::trim_left(test, '>') == "Test string 11!");
        CHECK(Strings::trim_left(test, '<') == ">Test string 11!");
    }

    SECTION("Strings::trim_right for: \">Test string 11!\"") {
        std::string test = ">Test string 11!";
        CHECK(Strings::trim_right(test, '*') == ">Test string 11!");
        CHECK(Strings::trim_right(test, '!') == ">Test string 11");
    }

    SECTION("Strings::trim_spaces for: \"  hohoho  \"") {
        std::string test = "  hohoho  ";
        CHECK(Strings::trim_spaces(test) == "hohoho");
    }

    SECTION("Strings::split for: \"ho=hoh=45654=\"") {
        std::string test = "ho=hoh=45654=";
        std::vector<std::string> split = Strings::split(test, "=");

        CHECK(split.size() == 4);
        CHECK(split[0] == "ho");
        CHECK(split[1] == "hoh");
        CHECK(split[2] == "45654");
        CHECK(split[3].empty());

        std::string no_split_str = "no splitter";
        auto nosplitted = Strings::split(no_split_str, "=");
        CHECK(nosplitted.size() == 1);
        CHECK(nosplitted[0] == no_split_str);
    }
}

int main() {
    return Catch::Session().run();
}