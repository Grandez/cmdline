// #define _VALIDATIONS_CODE_
#ifdef _WIN32
#pragma warning(disable : 4996)
#endif


#include <ctime>
#include <cstring>
#include <cstdio>
#include <iomanip>
#include <string>
#include <regex>
#include <filesystem>
#include <direct.h>
#include <vector>

#include "cmdline.hpp"
#include "tools.hpp"
#include "cmdline_exceptions.hpp"
#include "validations.hpp"
#include "msg_locale.hpp"

/*

#include "types.h"

*/

using namespace std;
using namespace cmdline;

namespace _cmdline {
	// Decimals are tried two times: Using comma and point as decimal sign
	// Internal functions
	struct tm* makeDateTime(char* sdate, char* stime) {
		struct tm* tt;
		struct tm now;
		struct tm res;

		time_t t = std::time(0);
		tt = std::localtime(&t);
		memcpy(&now, tt, sizeof(tm));

		if (!sdate) {
			memcpy(&res, &now, sizeof(tm));
		}
		else {
			std::istringstream ss(sdate);
			ss >> get_time(&res, "%Y/%m/%d");
			res.tm_hour = now.tm_hour;
			res.tm_min  = now.tm_min;
			res.tm_sec  = now.tm_sec;
		}

		if (stime) {
			vector<int> tt = tokenizeNumber(stime, ":");
			res.tm_hour = tt[0];
			res.tm_min  = tt[1];
			res.tm_sec  = tt[2];
		}
		tt = (struct tm *) malloc(sizeof(struct tm));
		memcpy(tt, &res, sizeof(struct tm));
		return tt;
	}
	int         isLeap(int year) {
		if (year < 100) year += 2000;
		if (year % 4) return 28;
		if ((year % 100) == 0) return ((year % 400) == 0 ? 29 : 28);
		return 29;
	}
	double      validateDecimal2(const char* value) {
		double res;
		try {
			size_t pos;
			double* pld = &res;
			res = stod(string(value), &pos);
			if (strlen(value) != pos) throw exception("");
		}
		catch (exception ex) {
			throw CmdLineValueException(TXT_VAL_EXPECTED, value, TXT_DECIMAL);
		}
		return res;
	}
	long double validateLongDecimal2(const char* value) {
		long double res;
		try {
			size_t pos;
			long double* pld = &res;
			stod(string(value), &pos);
			if (strlen(value) != pos) throw exception("");
		}
		catch (exception ex) {
			throw CmdLineValueException(TXT_VAL_EXPECTED, value, TXT_LONGDECIMAL);
		}
		return res;
	}
	// Public functions
	void        validateEntry     (const char* parm, const char* prev) {
		if (strlen(parm) == 1) throw CmdLineException(ERR_INV_OPTION, parm);
		//if (prev != nullptr) throw CmdLineException("Missing value", prev);
	}
	long        validateNumber    (const char* value) {
		long res;
		try {
			size_t pos;
            res = stol(string(value), &pos, 0);
			if (strlen(value) != pos) throw exception("");
		}
		catch (exception ex) {
			throw CmdLineValueException(TXT_VAL_EXPECTED, value, TXT_NUMBER);
		}
		return res;
	}
	long long   validateLongNumber(const char* value) {
		long long res;
		try {
			size_t pos;
			res = stoll(string(value), &pos, 0);
			if (strlen(value) != pos) throw exception("");
		}
		catch (exception ex) {
			throw CmdLineValueException(TXT_VAL_EXPECTED, value, TXT_LONGNUMBER);
		}
		return res;
	}
	double      validateDecimal   (const char* value) {
		double res;
		char* tmp = strdup(value);
		try {
			res = validateDecimal2(tmp);
			free(tmp);
			return res;
		}
		catch (exception ex) {
			for (size_t i = 0; i < strlen(tmp); i++) {
				switch (tmp[i]) {
					case ',': tmp[i] = '.'; break;
					case '.': tmp[i] = ','; break;
				}
			}
			try {
				res = validateDecimal2(tmp);
				free(tmp);
				return res;
			}
			catch (exception ex) {
				throw CmdLineValueException(TXT_VAL_EXPECTED, value, TXT_DECIMAL);
			}
		}
	}
	long double validateLongDecimal(const char* value) {
		long double res;
		char* tmp = strdup(value);

		try {
			res = validateLongDecimal2(tmp);
			free(tmp);
			return res;
		}
		catch (exception ex) {
			for (size_t i = 0; i < strlen(tmp); i++) {
				switch (tmp[i]) {
				case ',': tmp[i] = '.'; break;
				case '.': tmp[i] = ','; break;
				}
			}
			try {
				res = validateLongDecimal2(tmp);
				free(tmp);
				return res;
			}
			catch (exception ex) {
				throw CmdLineValueException(TXT_VAL_EXPECTED, value, TXT_LONGDECIMAL);
			}
		}
	}
	struct tm*  validateTime      (const char* value) {
		char strTime[9];
		regex pat{ "^[0-9]{1,2}:[0-9]{1,2}:[0-9]{1,2}$" };
		bool match = regex_search(value, pat);
		if (!match) throw CmdLineValueException(TXT_VAL_EXPECTED, value, TXT_TIME);
		vector<int> res = tokenizeNumber(value, (char*)":");
		if (res[0] < 0 || res[0] > 23) throw CmdLineValueException(TXT_VAL_INVALID, value);
		for (int i = 1; i < 3; i++) 
			if (res[i] < 0 || res[i] > 59) throw CmdLineValueException(TXT_VAL_INVALID, value);
		sprintf(strTime, "%02d:%02d:%02d", res[0], res[1], res[2]);
		return makeDateTime(0x0, strTime);
	}
	void        validateDateValue (const char *value, vector<int> dt) {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		int day;

		if (dt[0] < 1 || dt[0] > 31) throw CmdLineValueException(TXT_VAL_INVALID, value);
		if (dt[1] < 1 || dt[1] > 12) throw CmdLineValueException(TXT_VAL_INVALID, value);
		day = (dt[1] == 2) ? isLeap(dt[2]) : days[dt[1] - 1];
		if (dt[0] > day) throw CmdLineValueException(TXT_VAL_INVALID, value);
	}
	struct tm*  validateDate      (const char* value, int fmt) {
		char strDate[11];
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
		if (!match) throw CmdLineValueException(TXT_VAL_EXPECTED, value, TXT_DATE);
		vector<int> res = tokenizeNumber(value, (char*)"[/-]");
		switch (d) {
		       case time_base::dmy: dt = { res[0], res[1], res[2] }; break;
		       case time_base::mdy: dt = { res[1], res[0], res[2] }; break;
		       case time_base::ymd: dt = { res[2], res[1], res[0] }; break;
		       case time_base::ydm: dt = { res[2], res[0], res[1] }; break;
		       default:                  dt = { res[0], res[1], res[2] };
		}
		validateDateValue(value, dt);
		sprintf(strDate, "%04d/%02d/%02d", dt[2], dt[1], dt[0]);
		return makeDateTime(strDate, 0x0);
	}
	struct tm*  validateDateTime  (const char* value) {
		struct tm* tmDate;
		struct tm* tmTime;
		char szDate[11];
		char szTime[10];
		vector<int> res;
		// Revisited. More clean by pieces
		vector<string> pieces = tokenize(value, "[ \t]+");
		if (pieces.size() != 2) throw CmdLineValueException(TXT_VAL_EXPECTED, value, TXT_DATETIME);
		try {
			tmDate = validateDate(pieces[0].c_str(), time_base::ymd);
			tmTime = validateTime(pieces[1].c_str());
			sprintf(szDate, "%04d/%02d/%02d", tmDate->tm_year + 1900, tmDate->tm_mon + 1, tmDate->tm_mday);
			sprintf(szTime, "%02d:%02d:%02d", tmTime->tm_hour, tmTime->tm_min, tmTime->tm_sec);
		}
		catch(exception ex) {
			throw CmdLineValueException(TXT_VAL_INVALID, value);
		}
		return makeDateTime(szDate,szTime);
	}
	char *      validateTimestamp (const char* value) {
		vector<int> res;
		// timestamp es yyyy-mm-dd[- ]hh:MM:SS.nnnnnn
		struct tm *tmDate, *tmTime;
		vector<string> pieces = tokenize(value, "-|[ \t]+");
		int npieces = pieces.size();
		if (npieces != 2 && npieces != 4) throw CmdLineValueException(TXT_VAL_EXPECTED, value, TXT_TMS);
		try {
			int iTime = (npieces == 2) ? 1 : 3;
			if (npieces == 2) tmDate = validateDate(pieces[0].c_str(), time_base::ymd);
			if (npieces != 2) {
				char strdt[11];
				sprintf(strdt, "%s-%s-%s", pieces[0].c_str(), pieces[1].c_str(), pieces[2].c_str());
				tmDate = validateDate(strdt, time_base::ymd);
			}
			vector<string> tt = tokenize(pieces[iTime].c_str(), "\\.");
			if (tt.size() != 2) throw CmdLineValueException(TXT_VAL_EXPECTED, value, TXT_TMS);
			tmTime = validateTime(tt[0].c_str());
			validateNumber(tt[1].c_str());
		}
		catch (exception ex) {
			throw CmdLineValueException(TXT_VAL_INVALID, value);
		}
		return (char *) value;
	}
	filesystem::path        validateDir       (const char* value) {
		// If is not a valid path, chdir return -1
		// Some times chdir returns 0 but not change the directory
		char old[256];
		char tmp[256];
		int rc, rc2;
		char* ptr = getcwd(old, 256);
		if (strcmp(value, ".") == 0) return filesystem::path(old);
		if (strcmp(value, old) == 0) return filesystem::path(old);
		rc = _chdir(value);
		if (rc) throw CmdLineValueException(TXT_VAL_EXPECTED, value, TXT_DIR );
		ptr = getcwd(tmp, 256);
		rc = chdir(old);
        #ifdef _WIN32 // Windows is case insensitive
		    rc2 = strcmpi(old, tmp);
        #else
		    rc2 = strcmp(old, tmp);
        #endif

		if (rc2 == 0) throw CmdLineValueException(TXT_VAL_EXPECTED, value, TXT_DIR);
		return filesystem::path(value);
	}
	filesystem::path        validateDirExist(const char* value) {
		struct stat info;
		validateDir(value);
		int rc = stat(value, &info);
		if (stat(value, &info) != 0) throw CmdLineValueException(TXT_VAL_EXPECTED, value, TXT_NO_DIR);
		unsigned short mask = info.st_mode & S_IFDIR;
		mask ^= 16384; // 100 0000 0000 0000
		if (mask == 0)          throw CmdLineValueException(TXT_VAL_EXPECTED, value, TXT_DIR_NOTFND);
		//if ((info.st_mode & S_IFDIR) == 0)               throw CmdLineValueException(value, "is not a directory");
		return filesystem::path(value);
	}
	filesystem::path        validateFile      (const char* value) {
		try {
			return filesystem::path(value);
		}
		catch (exception ex) {
			throw CmdLineValueException(TXT_VAL_EXPECTED, value, TXT_FILE);
		}
	}
	filesystem::path        validateFileExist (const char* value) {
		struct stat info;
		filesystem::path p = validateFile(value);
		if (stat(value, &info) != 0) throw CmdLineValueException(TXT_VAL_EXPECTED, value, TXT_FILE_NOTFND);
		if (info.st_mode & S_IFDIR)  throw CmdLineValueException(TXT_VAL_EXPECTED, value, TXT_FILE_DIR);
		return p;
	}
	void        validateValue     (const char* value, Type type) {
		switch (type) {
		        case Type::NUMBER:      validateNumber(value);      break;
				case Type::LONGNUMBER:  validateLongNumber(value);  break;
		        case Type::DECIMAL:     validateDecimal(value);     break;
				case Type::LONGDECIMAL: validateLongDecimal(value); break;
		        case Type::DATE:        validateDate(value);        break;
		        case Type::TIME:        validateTime(value);        break;
				case Type::DATETIME:    validateDateTime(value);    break;
				case Type::TMS:         validateTimestamp(value);   break;
		        case Type::DIR:         validateDir(value);         break;
		        case Type::FILE:        validateFile(value);        break;
		        case Type::DIR_EXISTS:  validateDirExist(value);    break;
		        case Type::FILE_EXISTS: validateFileExist(value);   break;
		}
		// return obj;
	}
	template <typename T>
	T        getValue(const char* value, Type type) {
		switch (type) {
		case Type::NUMBER:      return validateNumber(value);
		case Type::DECIMAL:     return validateDecimal(value);
		case Type::DATE:        return validateDate(value);
		case Type::TIME:        return validateTime(value);
		case Type::DATETIME:    return validateDateTime(value);
		case Type::TMS:         return validateTimestamp(value);
		case Type::DIR:         return validateDir(value);
		case Type::FILE:        return validateFile(value);
		case Type::DIR_EXISTS:  return validateDirExist(value);
		case Type::FILE_EXISTS: return validateFileExist(value);
		}
		return value;
		// return obj;
	}
	template <typename T>
	void checkValue(auto value) {
		if (value < numeric_limits<T>::min() || value > numeric_limits<T>::max()) {
			throw CmdLineInvalidTypeException(typeid(T).name());
		}
	}
	int  makeInteger(const char *value) {
		long lvalue = validateNumber(value);
		checkValue<int>(lvalue);
		return (int) lvalue;
	}
	float  makeFloat(const char* value) {
		double dvalue = validateDecimal(value);
		checkValue<float>(dvalue);
		return (float) dvalue;
	}
	struct tm makeTm(const char *value) {
		// Como date, time y datetime son tm
		// Parseamos
		// datetime > 10
		// date puede ser > 8
		// si es menor y tiene : es hora, si no tiempo
		struct tm* ptr = nullptr;
		struct tm t;
		unsigned int len = strlen(value);
		if (len > 10) {
			ptr = validateDateTime(value);
		}
		else {
			if (len > 8) {
				ptr = validateDate(value);
			}
			else {
				string str(value);
				if (str.find(':') != std::string::npos) {
					ptr = validateTime(value);
				}
				else {
					ptr = validateDate(value);
				}
			}
		}
		memcpy(&t, ptr, sizeof(struct tm));
		return t;
	}
}