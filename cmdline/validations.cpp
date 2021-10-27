#define _VALIDATIONS_CODE_

#include <filesystem>
#include <regex>

#include "types.h"
/*
#include <stdio.h>      
#include <stdlib.h>     

#include <iostream>
#include <vector>
#include <locale>
#include <iomanip>
#include <sstream>
#include <iterator>

#include <time.h>

#include <cstdlib>
#include <errno.h>

#include "sal.h"
#include "tools.h"
#include "validations.h"


*/
#include "common.h"
#include "arg.hpp"
#include "cmdline_exceptions.hpp"

using namespace std;

namespace cmdline {
	void        validateEntry     (const char* parm, const char* prev) {
		if (strlen(parm) == 1) throw CmdLineException("Invalid Option", parm);
		//if (prev != nullptr) throw CmdLineException("Missing value", prev);
	}
	void        validateNumber    (const char* value) {
		try {
			size_t pos;
            stoll(string(value), &pos, 0);
			if (strlen(value) != pos) throw exception("expected number");
		}
		catch (exception ex) {
			throw CmdLineValueException(value, "expected number");
		}
	}
	void        validateDecimal   (const char* value) {
		try {
			size_t pos;
			long double ld;
			long double *pld = &ld;
			stold(string(value), &pos);
			if (strlen(value) != pos) throw exception("expected decimal");
		}
		catch (exception ex) {
			throw CmdLineValueException(value, "expected decimal");
		}
	}
	vector<int> validateTime      (const char* value) {
		regex pat{ "^[0-9]{1,2}:[0-9]{1,2}:[0-9]{1,2}$" };
		bool match = regex_search(value, pat);
		if (!match) throw CmdLineValueException(value, "invalid time");
		vector<int> res = tokenizeNumber(value, (char*)":");
		if (res[0] < 0 || res[0] > 23) throw CmdLineValueException(value, "invalid time");
		for (int i = 1; i < 3; i++) 
			if (res[i] < 0 || res[i] > 59) throw CmdLineValueException(value, "invalid time");
		return res;
	}
	int         isLeap            (int year) {
		if (year < 100) year += 2000;
		if (year % 4) return 28;
		if ((year % 100) == 0) return ((year % 400) == 0 ? 29 : 28);
		return 29;
	}
	void        validateDateValue (const char *value, vector<int> dt) {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		int day;

		if (dt[0] < 1 || dt[0] > 31) throw CmdLineValueException(value, "invalid date");
		if (dt[1] < 1 || dt[1] > 12) throw CmdLineValueException(value, "invalid date");
		day = (dt[1] == 2) ? isLeap(dt[2]) : days[dt[1] - 1];
		if (dt[0] > day) throw CmdLineValueException(value, "invalid date");
	}
	vector<int> validateDate      (const char* value, int fmt = -1) {
		time_base::dateorder d;
		vector<int> dt(3);
		regex pat1{ "^[0-9]{1,2}[/-]{1}[0-9]{1,2}[/-]{1}[0-9]{2,4}$" };
		regex pat2{ "^[0-9]{2,4}[/-]{1}[0-9]{1,2}[/-]{1}[0-9]{1,2}$" };
		regex pat;
		d = (fmt == -1) ? use_facet<time_get<char>>(locale()).date_order() 
			            : static_cast<time_base::dateorder>(fmt);

		switch (d) {
        		case time_base::no_order: 
		        case time_base::dmy: 
				case time_base::mdy: pat = pat1; break;
				default:                  pat = pat2;
		}
		bool match = regex_search(value, pat);
		if (!match) throw CmdLineValueException(value, "invalid date");
		vector<int> res = tokenizeNumber(value, (char*)"[/-]");
		switch (d) {
		       case time_base::dmy: dt = { res[0], res[1], res[2] }; break;
		       case time_base::mdy: dt = { res[1], res[0], res[2] }; break;
		       case time_base::ymd: dt = { res[2], res[1], res[0] }; break;
		       case time_base::ydm: dt = { res[2], res[0], res[1] }; break;
		       default:                  dt = { res[0], res[1], res[2] };
		}
		validateDateValue(value, dt);
		return dt;
	}
	vector<int> validateDateTime  (const char* value) {
		vector<int> res;
		// Revisited. More clean by pieces
		vector<string> pieces = tokenize(value, "[ \t]+");
		if (pieces.size() != 2) throw CmdLineValueException(value, "invalid datetime");
		try {
			vector<int> dt = validateDate(pieces[0].c_str());
			vector<int> tm = validateTime(pieces[1].c_str());
			res.reserve(dt.size() + tm.size());
			res.insert(res.end(), dt.begin(), dt.end());
			res.insert(res.end(), tm.begin(), tm.end());
		}
		catch(exception ex) {
			throw CmdLineValueException(value, "invalid datetime");
		}
		return res;
	}
	vector<int> validateTimestamp (const char* value) {
		vector<int> res;
		// timestamp es yyyy-mm-dd[- ]hh:MM:SS.nnnnnn
		vector<int> dt, tm;
		long ss;
		vector<string> pieces = tokenize(value, "-|[ \t]+");
		int npieces = pieces.size();
		if (npieces != 2 && npieces != 4) throw CmdLineValueException(value, "invalid timestamp");
		try {
			int iTime = (npieces == 2) ? 1 : 3;
			if (npieces == 2) dt = validateDate(pieces[0].c_str(), time_base::ymd);
			if (npieces != 2) {
				char strdt[11];
				sprintf(strdt, "%s-%s-%s", pieces[0].c_str(), pieces[1].c_str(), pieces[2].c_str());
				dt = validateDate(strdt, time_base::ymd);
			}
			vector<string> tt = tokenize(pieces[iTime].c_str(), "\\.");
			if (tt.size() != 2) throw CmdLineValueException(value, "invalid timestamp");
			tm = validateTime(tt[0].c_str());
			ss = stol(tt[1]);
			res.reserve(dt.size() + tm.size());
			res.insert(res.end(), dt.begin(), dt.end());
			res.insert(res.end(), tm.begin(), tm.end());
			res.push_back(ss);
		}
		catch (exception ex) {
			throw CmdLineValueException(value, "invalid timestamp");
		}
		return res;
	}
	void        validateDir       (const char* value) {
	//	^ (((\\\\([^ \\ / :\ * \ ? "\|<>\. ]+))|([a-zA-Z]:\\))(([^\\/:\*\?"\ | <>\.] *)([\\] *))*)$
		string start = "^";
		string drive = "(? <drive>[a - z] : ) ?";
		string path  = "(? <path>(? : [\\] ? (? : [\\w !#() - ] + | [.]{ 1,2 }) + ) * [\\]) ?";
		string end   = "$";
		regex pat{ start + drive + path + end};
		bool match = regex_search(value, pat);
		if (!match) throw CmdLineValueException(value, "expected path");
	}
	void        validateFile      (const char* value) {
		struct stat info;
		filesystem::path p = filesystem::path(value);
		if (stat((const char*)p.c_str(), &info) != 0) throw CmdLineValueException(value, "is not a file");
		if ((info.st_mode & S_IFREG) == 0)  throw CmdLineValueException(value, "is not a file");
	}
	void        validateDirExist  (const char* value) {
		struct stat info;
		validateDir(value);
		filesystem::path p = filesystem::path(value);
		
		if (stat((const char *) p.c_str(), &info) != 0) throw CmdLineValueException(value, "dir not found");
		if ((info.st_mode & S_IFDIR) == 0)  throw CmdLineValueException(value, "is not a directory");
	}
	void        validateFileExist (const char* value) {
		struct stat info;
		if (stat(value, &info) != 0) throw CmdLineValueException(value, "file not found");
		if (info.st_mode & S_IFDIR)  throw CmdLineValueException(value, "file is directory");
	}
	void        validateValue     (const char* value, Type type) {
		switch (type) {
		        case Type::NUMBER:      validateNumber(value); break;
		        case Type::DECIMAL:     validateDecimal(value); break;
		        case Type::DATE:        validateDate(value); break;
		        case Type::TIME:        validateTime(value); break;
				case Type::DATETIME:    validateDateTime(value); break;
				case Type::TMS:         validateTimestamp(value); break;
		        case Type::DIR:         validateDir(value); break;
		        case Type::FILE:        validateFile(value); break;
		        case Type::DIR_EXISTS:  validateDirExist(value); break;
		        case Type::FILE_EXISTS: validateFileExist(value); break;
		}
		// return obj;
	}
}