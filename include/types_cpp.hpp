#pragma once
#include <unordered_map>
#include <filesystem>
#include <vector>

#ifndef __CMDLINE_TYPESCPP__
#define __CMDLINE_TYPESCPP__
namespace cmdline {
	enum class Type {
		STRING, CHAR, BOOL,
		NUMBER, DECIMAL, LONGNUMBER, LONGDECIMAL,
		DATE, TIME, DATETIME, TMS,
		DIR, DIR_EXISTS, FILE, FILE_EXISTS
	};
	enum class Source { DEFAULT, ENV, CMDLINE, CODE, AUTO };

	using TYPE_STRING = std::string;
	using TYPE_BOOL = bool;
	using TYPE_NUMBER = long;
	using TYPE_LONG = long;
	using TYPE_INT = int;
	using TYPE_DECIMAL = float;
	using TYPE_FLOAT = float;
	using TYPE_DOUBLE = double;
	using TYPE_LONGNUMBER = long long;
	using TYPE_LONGDECIMAL = float;
	using TYPE_DATE = std::tm;
	using TYPE_TIME = std::tm;
	using TYPE_DATETIME = std::tm;
	using TYPE_TMS = char*;
	using TYPE_DIR = std::filesystem::path;
	using TYPE_FILE = std::filesystem::path;

	using Flags = std::unordered_map<std::string, bool>;
	using Options = std::unordered_map<std::string, std::string>;

};
#endif