#include "date.hpp"
#include <time.h>
#include <regex>

#include "sstring.hpp"

#ifdef _WIN32
#pragma warning( disable : 4996 )
#endif

namespace jggtools {
	int         isLeap(int year) {
		if (year < 100) year += 2000;
		if (year % 4) return 28;
		if ((year % 100) == 0) return ((year % 400) == 0 ? 29 : 28);
		return 29;
	}
	void        validateDateValue (string str, vector<int> dt) {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		int day;

		if (dt[0] < 1 || dt[0] > 31) throw new invalid_argument(str + ": Is not a valid date " );
		if (dt[1] < 1 || dt[1] > 12) throw new invalid_argument(str + ": Is not a valid date " );
		day = (dt[1] == 2) ? isLeap(dt[2]) : days[dt[1] - 1];
		if (dt[0] > day) throw new invalid_argument(str + ": Is not a valid date " );
	}
/*
    struct tm *validateDate() {
		char strDate[11];
		time_base::dateorder d;
		vector<int> dt(3);
		regex pat1{ "^[0-9]{1,2}[/-]{1}[0-9]{1,2}[/-]{1}[0-9]{2,4}$" };
		regex pat2{ "^[0-9]{2,4}[/-]{1}[0-9]{1,2}[/-]{1}[0-9]{1,2}$" };
		regex pat;
		d = use_facet<time_get<char>>(locale()).date_order();
		switch (d) {
        		case time_base::no_order: 
		        case time_base::dmy: 
				case time_base::mdy: pat = pat1; break;
				default:                  pat = pat2;
		}
		bool match = regex_search(str, pat);
		if (!match) throw new invalid_argument(string(str) + ": Is not a valid date " );
        sstring sDate = sstring(str);
		vector<char *> res = sDate.tokenize((const char*)"[/-]");
        vector<int> iDate(3);
        for (int i = 0; i < 3; i++) iDate[i] = stoi(res[i++]); 
		switch (d) {
		       case time_base::dmy: dt = { iDate[0], iDate[1], iDate[2] }; break;
		       case time_base::mdy: dt = { iDate[1], iDate[0], iDate[2] }; break;
		       case time_base::ymd: dt = { iDate[2], iDate[1], iDate[0] }; break;
		       case time_base::ydm: dt = { iDate[2], iDate[0], iDate[1] }; break;
		       default:             dt = { iDate[0], iDate[1], iDate[2] };
		}
		validateDateValue(string(str), dt);
    }
*/
   Date::Date() {
      time_t now = time(0);
      tm *gmtm = gmtime(&now);
      this->year  = gmtm->tm_year + 1900;
      this->month = gmtm->tm_mon;
      this->day   = gmtm->tm_mday;
   }
   Date::Date(const Date& old) {
      this->day = old.day;
      this->month = old.month;
      this->year  = old.year;
   }
   Date::Date(string str, int fmt) {
       Date(str.c_str(), fmt);
   }
   Date::Date(const char *str, int fmt) {
        validateDate(str, fmt);
/*
		char strDate[11];
		time_base::dateorder d;
		vector<int> dt(3);
		regex pat1{ "^[0-9]{1,2}[/-]{1}[0-9]{1,2}[/-]{1}[0-9]{2,4}$" };
		regex pat2{ "^[0-9]{2,4}[/-]{1}[0-9]{1,2}[/-]{1}[0-9]{1,2}$" };
		regex pat;
		d = use_facet<time_get<char>>(locale()).date_order();
		switch (d) {
        		case time_base::no_order: 
		        case time_base::dmy: 
				case time_base::mdy: pat = pat1; break;
				default:                  pat = pat2;
		}
		bool match = regex_search(str, pat);
		if (!match) throw new invalid_argument(string(str) + ": Is not a valid date " );
        sstring sDate = sstring(str);
		vector<char *> res = sDate.tokenize((const char*)"[/-]");
        vector<int> iDate(3);
        for (int i = 0; i < 3; i++) iDate[i] = stoi(res[i++]); 
		switch (d) {
		       case time_base::dmy: dt = { iDate[0], iDate[1], iDate[2] }; break;
		       case time_base::mdy: dt = { iDate[1], iDate[0], iDate[2] }; break;
		       case time_base::ymd: dt = { iDate[2], iDate[1], iDate[0] }; break;
		       case time_base::ydm: dt = { iDate[2], iDate[0], iDate[1] }; break;
		       default:             dt = { iDate[0], iDate[1], iDate[2] };
		}
		validateDateValue(string(str), dt);
*/
	}

}