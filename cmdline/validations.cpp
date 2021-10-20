#define _VALIDATIONS_CODE_

#include <iostream>
#include <vector>
#include <locale>
#include <iomanip>
#include <sstream>
#include <iterator>

#include "validations.h"
#include "cmdline_exceptions.hpp"

namespace cmdline {

	void        validateEntry(char* parm, char* prev) {
		if (strlen(parm) == 1) throw CmdLineException("Invalid Option", parm);
		if (prev != nullptr) throw CmdLineException("Missing value", prev);
	}
	inline void validateNumber(char* value) {
		char* p;
		long converted = strtol(value, &p, 10);
		if (*p) throw CmdLineValueException(value, "expected number");
	}
	inline void validateDecimal(char* value) {
		std::string::size_type sz;
		try {
			float f = std::stof(value, &sz);
		}
		catch (std::exception ex) {
			throw (char*)(value, "expected decimal");
		}
	}
	inline void validateTime(char* value) {
		std::tm t = {};
		const std::string& ss = std::string(value);
		std::istringstream str(ss);
		str >> std::get_time(&t, "%H:%M:%S");
		if (str.fail()) throw CmdLineValueException(value, "expected time");
	}
	inline void validateDate(char* value) {
		//	try_get_time(string(value));
		const std::string& ss = std::string(value);
		std::istringstream str(ss);
		std::ios_base::iostate err = std::ios_base::goodbit;

		std::tm t;
		std::istreambuf_iterator<char> ret =
			std::use_facet<std::time_get<char>>(str.getloc()).get_time(
				{ str }, {}, str, err, &t
			);
		str.setstate(err);
		if (!str) throw CmdLineValueException(value, "expected date");

	}
	inline void validateDir(char* value) {

	}
	inline void validateFile(char* value) {
	}
	inline void validateDirExist(char* value) {
		struct stat info;
		if (stat(value, &info) != 0) throw CmdLineValueException(value, "dir not found");
		if ((info.st_mode & S_IFDIR) == 0)  throw CmdLineValueException(value, "is not a directory");
	}
	inline void validateFileExist(char* value) {
		struct stat info;
		if (stat(value, &info) != 0) throw CmdLineValueException(value, "file not found");
		if (info.st_mode & S_IFDIR)  throw CmdLineValueException(value, "file is directory");
	}

}