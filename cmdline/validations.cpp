#define _VALIDATIONS_CODE_
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* strtoll */

#include <iostream>
#include <vector>
#include <locale>
#include <iomanip>
#include <sstream>
#include <iterator>
#include <regex>
#include <time.h>
#include <filesystem>
#include <cstdlib>
#include <errno.h>

#include "sal.h"
#include "tools.h"
#include "validations.h"
#include "cmdline_exceptions.hpp"


namespace cmdline {
	void        validateEntry(const char* parm, const char* prev) {
		if (strlen(parm) == 1) throw CmdLineException("Invalid Option", parm);
		//if (prev != nullptr) throw CmdLineException("Missing value", prev);
	}
	void  validateNumber(const char* value) {
		try {
			size_t pos;
            std::stoll(std::string(value), &pos, 0);
			if (strlen(value) != pos) throw std::exception("expected number");
		}
		catch (std::exception ex) {
			throw CmdLineValueException(value, "expected number");
		}
	}
	void validateDecimal(const char* value) {
		try {
			size_t pos;
			long double ld;
			long double *pld = &ld;
			std::stold(std::string(value), &pos);
			if (strlen(value) != pos) throw std::exception("expected decimal");
		}
		catch (std::exception ex) {
			throw CmdLineValueException(value, "expected decimal");
		}
	}
	std::vector<int> validateTime(const char* value) {
		std::regex pat{ "^[0-9]{1,2}:[0-9]{1,2}:[0-9]{1,2}$" };
		std::tm t;
		memset(&t, 0, sizeof(tm));
		bool match = std::regex_search(value, pat);
		if (!match) throw CmdLineValueException(value, "invalid time");
		std::vector<int> res = tokenizeNumber(value, (char*)":");
		if (res[0] < 0 || res[0] > 23) throw CmdLineValueException(value, "invalid time");
		for (int i = 1; i < 3; i++) 
			if (res[i] < 0 || res[i] > 59) throw CmdLineValueException(value, "invalid time");
		return res;
	}

	int isLeap(int year) {
		if (year < 100) year += 2000;
		if (year % 4) return 28;
		if ((year % 100) == 0) return ((year % 400) == 0 ? 29 : 28);
		return 29;
	}
	void validateDateValue(const char *value, std::vector<int> dt) {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		int day;

		if (dt[0] < 1 || dt[0] > 31) throw CmdLineValueException(value, "invalid date");
		if (dt[1] < 1 || dt[1] > 12) throw CmdLineValueException(value, "invalid date");
		day = (dt[1] == 2) ? isLeap(dt[2]) : days[dt[1] - 1];
		if (dt[0] > day) throw CmdLineValueException(value, "invalid date");
	}
	std::vector<int> validateDate(const char* value) {
		std::vector<int> dt(3);
		std::regex pat1{ "^[0-9]{1,2}[/-]{1}[0-9]{1,2}[/-]{1}[0-9]{2,4}$" };
		std::regex pat2{ "^[0-9]{2,4}[/-]{1}[0-9]{1,2}[/-]{1}[0-9]{1,2}$" };
		std::regex pat;
		std::time_base::dateorder d = std::use_facet<std::time_get<char>>(
			std::locale()
			).date_order();
		switch (d) {
        		case std::time_base::no_order: 
		        case std::time_base::dmy: 
				case std::time_base::mdy: pat = pat1; break;
				default:                  pat = pat2;
		}
		bool match = std::regex_search(value, pat);
		if (!match) throw CmdLineValueException(value, "invalid date");
		std::vector<int> res = tokenizeNumber(value, (char*)"[/-]");
		switch (d) {
		       case std::time_base::dmy: dt = { res[0], res[1], res[2] }; break;
		       case std::time_base::mdy: dt = { res[1], res[0], res[2] }; break;
		       case std::time_base::ymd: dt = { res[2], res[1], res[0] }; break;
		       case std::time_base::ydm: dt = { res[2], res[0], res[1] }; break;
		       default:                  dt = { res[0], res[1], res[2] };
		}
		validateDateValue(value, dt);
		return dt;
	}
	std::vector<int> validateDateTime(const char* value) {
		std::vector<int> dt(3);
		std::regex pat { "^([0-9]{2,4}[/-]{1}[0-9]{1,2}[/-]{1}[0-9]{1,2}[ \t]+)([0-9]{1,2}:[0-9]{1,2}:[0-9]{1,2})$" };
		bool match = std::regex_search(value, pat);
		if (!match) throw CmdLineValueException(value, "invalid date time");
		std::vector<int> res = tokenizeNumber(value, (char*)"[/-: \t]");
		dt[0] = res[2];
		dt[1] = res[1];
		dt[2] = res[0];
        
		try {
			validateDateValue(value, dt);
			std::vector<string> str = tokenize(value, (char*)"[ \t]");
			validateTime(str[1].c_str());
		}
		catch(exception ex) {
			throw CmdLineValueException(value, "invalid datetime");
		}
		return res;
	}
	std::vector<int> validateTimestamp(const char* value) {
		std::vector<string> str = tokenize(value, (char*)"\.");
		std::vector<int> res;
		if (str.size() != 2) throw CmdLineValueException(value, "invalid timestamp");
		try {
			res = validateDateTime(str[0].c_str());
			validateNumber(str[1].c_str());
			res.push_back(stol(str[1]));
		}
		catch (exception ex) {
			throw CmdLineValueException(value, "invalid timestamp");
		}
		return res;
	}

	void validateDir(const char* value) {
	//	^ (((\\\\([^ \\ / :\ * \ ? "\|<>\. ]+))|([a-zA-Z]:\\))(([^\\/:\*\?"\ | <>\.] *)([\\] *))*)$
		std::string start = "^";
		std::string drive = "(? <drive>[a - z] : ) ?";
		std::string path  = "(? <path>(? : [\\] ? (? : [\\w !#() - ] + | [.]{ 1,2 }) + ) * [\\]) ?";
		std::string end   = "$";
		std::regex pat{ start + drive + path + end};
		bool match = std::regex_search(value, pat);
		if (!match) throw CmdLineValueException(value, "expected path");
	}
	inline void  validateFile(const char* value) {
		struct stat info;
		std::filesystem::path p = std::filesystem::path(value);
		if (stat((const char*)p.c_str(), &info) != 0) throw CmdLineValueException(value, "is not a file");
		if ((info.st_mode & S_IFREG) == 0)  throw CmdLineValueException(value, "is not a file");
	}
	inline void validateDirExist(const char* value) {
		struct stat info;
		validateDir(value);
		std::filesystem::path p = std::filesystem::path(value);
		
		if (stat((const char *) p.c_str(), &info) != 0) throw CmdLineValueException(value, "dir not found");
		if ((info.st_mode & S_IFDIR) == 0)  throw CmdLineValueException(value, "is not a directory");
	}
	inline void  validateFileExist(const char* value) {
		struct stat info;
		if (stat(value, &info) != 0) throw CmdLineValueException(value, "file not found");
		if (info.st_mode & S_IFDIR)  throw CmdLineValueException(value, "file is directory");
	}

	void          validateValue(const char* value, cmdline::Type type) {
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