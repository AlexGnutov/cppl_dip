#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>


typedef std::unordered_map<std::string, std::string> Section;
typedef std::unordered_map<std::string, Section> IniData;


class Logger {
public:
	static void log_error(const std::string& msg) {
		std::cout << "[ошибка]:" << msg << std::endl;
	}

	static void log_warning(const std::string& msg) {
		std::cout << "[предупреждение]:" << msg << std::endl;
	}

	static void log_message(const std::string& msg) {
		std::cout << "[информация]:" << msg << std::endl;
	}
};

class Strings {
public:
	static std::string trim_left(const std::string& str, char ch) {
		if (str.empty()) return "";

		int cut = 0;
		for (auto i = str.cbegin(); i != str.cend(); ++i) {
			if (*i == ch) {
				cut += 1;
			}
			else {
				break;
			}
		}
		return str.substr(cut);
	};

	static std::string trim_right(const std::string& str, char ch) {
		if (str.empty()) return "";

		int cut = 0;
		for (auto i = str.crbegin(); i != str.crend(); ++i) {
			if (*i == ch) {
				cut += 1;
			}
			else {
				break;
			}
		}
		return str.substr(0, str.length() - cut);
	};

	static std::string trim_spaces(const std::string& str) {
		auto tl = trim_left(str, ' ');
		return trim_right(tl, ' ');
	};

	static std::vector<std::string> split(const std::string& str, const std::string& sep) {
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

	static int count(const std::string& str, const std::string& key) {
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

	static bool contains(const std::string& str, const std::string& key) {
		if (str.empty() || key.empty()) return false;
		std::string::size_type n;
		n = str.find(key);
		return n != std::string::npos;
	};

	static bool starts_with(const std::string& str, const std::string& key) {
		if (str.empty() || key.empty()) return false;
		std::string::size_type n;
		n = str.find(key);
		return n == 0;
	};

	static bool ends_with(const std::string& str, const std::string& key) {
		if (str.empty() || key.empty()) return false;
		std::string::size_type end_pos = str.length() - key.length();
		if (end_pos < 0) {
			return false;
		}
		std::string::size_type n;
		n = str.find(key);
		return n == end_pos;
	};
};

class ParserTools {
public:
	bool is_commentary(const std::string& line) {
		return Strings::starts_with(line, ";");
	};

	bool includes_commentary(const std::string& line) {
		return !Strings::starts_with(line, ";") && Strings::contains(line, ";");
	}

	bool is_key_value(const std::string& line) {
		return Strings::contains(line, "=") && Strings::count(line, "=") == 1;
	};

	bool is_section(const std::string& line) {
		return Strings::starts_with(line, "[") && Strings::ends_with(line, "]");
	};

	std::tuple<bool, std::string> get_commentary(const std::string& line) {

	};

	std::tuple<bool, std::string> get_section(const std::string& line) {
		auto tl = Strings::trim_left(line, '[');
		auto out = Strings::trim_right(tl, ']');
		if (out.size() > 0) {
			return { true, out };
		}
		return { false, "не удалось получить имя секции, т.к. имя нулевой длины" };
	};

	std::tuple<bool, std::string, std::string> get_key_value(const std::string& line) {
		auto split = Strings::split(line, "=");
		if (split.size() == 2 && split[0].size() > 0) {
			return { true, split[0], split[1] };
		}
		return { false, "", "" };
	};

};

class IniParser {
public:

	IniParser(std::string path) :path(path), data({}), pt(ParserTools()) {
		bool ok;
		std::string msg;

		std::tie(ok, msg) = read_file_data(path);
	}

	std::string path;
	IniData data;
	ParserTools pt;

private:
	bool add_section(std::string section_key) {
		if (this->data.count(section_key) > 0) {
			return false;
		}
		Section new_section = {};
		this->data[section_key] = new_section;
		return true;
	};

	bool has_section(std::string section_key) {
		return this->data.count(section_key) > 0;
	}

	bool add_key_value(std::string section_key, std::string key, std::string value) {
		if (this->data.count(section_key) == 0) {
			return false;
		}
		this->data[section_key][key] = value;
		return true;
	};

	std::tuple<bool, std::string> read_file_data(std::string path) {

		std::ifstream file;
		file.open(path);
		if (!file.is_open()) {
			return { false, "не удалось открыть файл" };
		}

		std::string current_section_name = "";

		for (std::string line; std::getline(file, line);) {

			std::string trimmed = Strings::trim_spaces(line);
			if (trimmed.length() == 0) continue;

			if (pt.is_commentary(trimmed)) {
				Logger::log_message("пропускаю комментарий: " + trimmed);
				continue;
			}

			std::string value_str;
			if (pt.includes_commentary(trimmed)) {
				auto splitted = Strings::split(trimmed, ";");
				value_str = splitted[0];
				Logger::log_message("отбрасываю комментарий: " + splitted[1]);
			}
			else {
				value_str = trimmed;
			}

			value_str = Strings::trim_spaces(value_str);

			if (pt.is_section(value_str)) {
				bool ok;
				std::string msg;

				std::tie(ok, msg) = pt.get_section(value_str);
				if (!ok) {
					Logger::log_error(msg);
					continue;
				}

				ok = add_section(msg);
				if (!ok) {
					Logger::log_warning("такая секция уже существует: " + msg);
				}
				else {
					Logger::log_message("добавлена секция: " + msg);
				}

				current_section_name = msg;
				continue;
			}

			if (pt.is_key_value(value_str)) {
				bool ok;
				std::string key;
				std::string value;

				std::tie(ok, key, value) = pt.get_key_value(value_str);
				if (!ok) {
					// log here
					continue;
				}

				if (current_section_name.length() > 0) {
					std::cout << "inside [" << current_section_name << "]: " << key << "=" << value << std::endl;
				}
				continue;
			}

			std::cout << "не удалось разобрать строку: " << line << std::endl;
		}

		return { true, "" };
	}
};


int main() {

	setlocale(LC_ALL, "rus");


	std::string test = ">Test string 11!";

	std::cout << "Testing Strings:contains for string: " << test << std::endl;
	std::cout << "contains T: " << Strings::contains(test, "T") << std::endl;
	std::cout << "contains H: " << Strings::contains(test, "H") << std::endl;
	std::cout << "contains !: " << Strings::contains(test, "!") << std::endl;
	std::cout << "contains \" \": " << Strings::contains(test, "_") << std::endl;
	std::cout << std::endl;

	std::cout << "Testing Strings::starts_with for string: " << test << std::endl;
	std::cout << "starts_with : <" << Strings::starts_with(test, "<") << std::endl;
	std::cout << "starts_with : >" << Strings::starts_with(test, ">") << std::endl;

	std::cout << "Testing Strings::ends_with for string: " << test << std::endl;
	std::cout << "ends_with >: " << Strings::ends_with(test, ">") << std::endl;
	std::cout << "ends_with 1!: " << Strings::ends_with(test, "1!") << std::endl;

	std::cout << "Testing Strings::count for string: " << test << std::endl;
	std::cout << "count T: " << Strings::count(test, "T") << std::endl;
	std::cout << "count \" \": " << Strings::count(test, " ") << std::endl;
	std::cout << "count 11: " << Strings::count(test, "11") << std::endl;
	std::cout << "count i: " << Strings::count(test, "i") << std::endl;
	std::cout << "count X: " << Strings::count(test, "X") << std::endl;

	std::cout << "Testing Strings::trim_left for string: " << test << std::endl;
	std::cout << "trim_left for >: " << Strings::trim_left(test, '>') << std::endl;
	std::cout << "trim_left for <" << Strings::trim_left(test, '<') << std::endl;

	std::cout << "Testing Strings::trim_right for string: " << test << std::endl;
	std::cout << "trim_left for *: " << Strings::trim_right(test, '*') << std::endl;
	std::cout << "trim_left for !" << Strings::trim_right(test, '!') << std::endl;

	std::cout << "Testing Strings::trim_spaces for string: " << "  hohoho  " << std::endl;
	std::cout << "trim_spaces: " << Strings::trim_spaces("  hohoho  ") << std::endl;

	std::string split_str = "ho=hoh=45654=";
	std::cout << "Testing Strings::split for string: " << split_str << std::endl;
	auto splitted = Strings::split(split_str, "=");
	std::cout << splitted.size() << std::endl;

	for (const auto& v : splitted) {
		std::cout << v << " ";
	}
	std::cout << std::endl;

	std::string no_split_str = "no splitter";
	std::cout << "Testing Strings::split for string: " << no_split_str << std::endl;
	auto nosplitted = Strings::split(no_split_str, "=");
	for (const auto& v : nosplitted) {
		std::cout << v << " ";
	}
	std::cout << std::endl;


	IniParser p("test.INI");



	return 0;
}