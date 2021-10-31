#pragma once
#include <unordered_map>
#include <filesystem>

#ifndef __CMDLINE_TYPES__
#define __CMDLINE_TYPES__
namespace cmdline {
	enum class Type { STRING, BOOL, NUMBER, DECIMAL, LONGNUMBER, LONGDECIMAL, DATE, TIME, DATETIME, TMS, DIR, DIR_EXISTS, FILE, FILE_EXISTS };
	enum class Source { DEFAULT, ENV, CMDLINE, CODE, AUTO };

	using CMD_STRING      = std::string;
	using CMD_BOOL        = bool;
	using CMD_NUMBER      = long;
	using CMD_LONG        = long;
	using CMD_INT         = int;
	using CMD_DECIMAL     = float;
	using CMD_FLOAT       = float;
	using CMD_DOUBLE      = double;
	using CMD_LONGNUMBER  = long long;
	using CMD_LONGDECIMAL = float;
	using CMD_DATE        = std::tm;
	using CMD_TIME        = std::tm;
	using CMD_DATETIME    = std::tm;
	using CMD_TMS         = char *;
	using CMD_DIR         = std::filesystem::path;
	using CMD_FILE        = std::filesystem::path;

	typedef std::unordered_map<std::string, bool>      Flags;
	typedef std::unordered_map<std::string, std::string>    Options;
}
#endif