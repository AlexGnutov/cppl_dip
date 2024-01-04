#include "Strings.h"

std::string Strings::trim_left(const std::string &str, char ch) {
    if (str.empty()) return "";

    int cut = 0;
    for (auto i = str.cbegin(); i != str.cend(); ++i) {
        if (*i == ch) {
            cut += 1;
        } else {
            break;
        }
    }
    return str.substr(cut);
};

std::string Strings::trim_right(const std::string &str, char ch) {
    if (str.empty()) return "";

    int cut = 0;
    for (auto i = str.crbegin(); i != str.crend(); ++i) {
        if (*i == ch) {
            cut += 1;
        } else {
            break;
        }
    }
    return str.substr(0, str.length() - cut);
};

std::string Strings::trim_spaces(const std::string &str) {
    auto tl = trim_left(str, ' ');
    return trim_right(tl, ' ');
};

std::vector<std::string> Strings::split(const std::string &str, const std::string &sep) {
    std::vector<std::string> strs = {};
    std::string::size_type pos = 0;
    std::string::size_type nxt_pos = 0;

    while (true) {
        nxt_pos = str.find(sep, pos);
        if (nxt_pos == std::string::npos) break;
        strs.push_back(str.substr(pos, nxt_pos - pos));
        pos = nxt_pos + sep.size();
    }
    strs.push_back(str.substr(pos));
    return strs;
};

int Strings::count(const std::string &str, const std::string &key) {
    if (str.empty() || key.empty()) return 0;

    int c = 0;
    std::string::size_type pos = 0;
    std::string::size_type n;

    while (true) {
        n = str.find(key, pos);
        if (n == std::string::npos) {
            break;
        }
        c += 1;
        pos = n + 1;
    }
    return c;
};

bool Strings::contains(const std::string &str, const std::string &key) {
    if (str.empty() || key.empty()) return false;
    std::string::size_type n;
    n = str.find(key);
    return n != std::string::npos;
};

bool Strings::starts_with(const std::string &str, const std::string &key) {
    if (str.empty() || key.empty()) return false;
    std::string::size_type n;
    n = str.find(key);
    return n == 0;
};

bool Strings::ends_with(const std::string &str, const std::string &key) {
    if (str.empty() || key.empty()) return false;
    std::string::size_type end_pos = str.length() - key.length();
    if (end_pos < 0) {
        return false;
    }
    std::string::size_type n;
    n = str.find(key);
    return n == end_pos;
};
