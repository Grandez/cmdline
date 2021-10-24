#define _VALIDATIONS_CODE_

#include <iostream>
#include <vector>
#include <locale>
#include <iomanip>
#include <sstream>
#include <iterator>
#include <regex>
#include <time.h>
#include <filesystem>

#include "sal.h"
#include "validations.h"
#include "cmdline_exceptions.hpp"


namespace cmdline {

	void        validateEntry(char* parm, char* prev) {
		if (strlen(parm) == 1) throw CmdLineException("Invalid Option", parm);
		//if (prev != nullptr) throw CmdLineException("Missing value", prev);
	}

	inline void  validateNumber(char* value) {
		char* p;
		long converted = strtol(value, &p, 0);
		if (*p) throw CmdLineValueException(value, "expected number");
		//return new long(converted);
	}
	
	inline void validateDecimal(char* value) {
		char* p;
		double val;
		try {
			val = std::strtod(value, &p);
		}
		catch (std::exception ex) {
			throw CmdLineValueException(value, "expected decimal");
		}
		if (*p) throw CmdLineValueException(value, "expected decimal");
		//return new double(val);
	}
	//JGG Rehacer
	inline void validateTime(char* value) {
		std::regex pat{ "[0-9]{1,2}:[0-9]{1,2}:[0-9]{1,2}" };
		std::tm t;
		memset(&t, 0, sizeof(tm));
		bool match = std::regex_search(value, pat);
		if (!match) throw CmdLineValueException(value, "expected time");
		
		const std::string& ss = std::string(value);
		std::istringstream str(ss);
		str >> std::get_time(&t, "%H:%M:%S");
		if (str.fail()) throw CmdLineValueException(value, "expected time");
		std::time_t time = mktime(&t);
		//return new std::time_t(time);
		//return new std::string(value);
	}
	inline void validateDate(char* value) {
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
		//return new std::string(value);
	}
	inline void validateDir(char* value) {
		std::string start = "^";
		std::string drive = "(? <drive>[a - z] : ) ?";
		std::string path  = "(? <path>(? : [\\] ? (? : [\\w !#() - ] + | [.]{ 1,2 }) + ) * [\\]) ?";
		std::string end   = "$";
		std::regex pat{ start + drive + path + end};
		bool match = std::regex_search(value, pat);
		if (!match) throw CmdLineValueException(value, "expected path");
	}
	inline void  validateFile(char* value) {
		struct stat info;
		std::filesystem::path p = std::filesystem::path(value);
		if (stat((const char*)p.c_str(), &info) != 0) throw CmdLineValueException(value, "dir not found");
		if ((info.st_mode & S_IFREG) == 0)  throw CmdLineValueException(value, "is not a file");
	}
	inline void validateDirExist(char* value) {
		struct stat info;
		validateDir(value);
		std::filesystem::path p = std::filesystem::path(value);
		
		if (stat((const char *) p.c_str(), &info) != 0) throw CmdLineValueException(value, "dir not found");
		if ((info.st_mode & S_IFDIR) == 0)  throw CmdLineValueException(value, "is not a directory");
	}
	inline void  validateFileExist(char* value) {
		struct stat info;
		if (stat(value, &info) != 0) throw CmdLineValueException(value, "file not found");
		if (info.st_mode & S_IFDIR)  throw CmdLineValueException(value, "file is directory");
	}

	void          validateValue(char* value, cmdline::Type type) {
		/*
		void* obj = value;
		switch (type) {
		        case cmdline::NUMBER:      validateNumber(value); break;
		        case cmdline::DECIMAL:     validateDecimal(value); break;
		        case cmdline::DATE:        validateDate(value); break;
		        case cmdline::TIME:        validateTime(value); break;
		        case cmdline::DIR:         validateDir(value); break;
		        case cmdline::FILE:        validateFile(value); break;
		        case cmdline::DIR_EXISTS:  validateDirExist(value); break;
		        case cmdline::FILE_EXISTS: validateFileExist(value); break;
		}
		// return obj;
		*/
	}

}