#ifdef _WIN32
   #include "sys/timeb.h"
#else
   #include <sys/time.h>
#endif

#include <iomanip>
#include <sstream>

#include "timestamp.hpp"


#include <time.h>
#include <regex>
#include "sstring.hpp"


#ifdef _WIN32
#pragma warning( disable : 4996 )
#endif
#include <iomanip>

namespace jggtools {
   Timestamp::Timestamp() {
      time_t now = time(0);
      ptm = gmtime(&now);
#ifndef _WIN32
      struct timeval pTimeval;
      gettimeofday (&pTimeval, NULL);
#endif
   }
	int    Timestamp::isLeap(int year) {
		if (year < 100) year += 2000;
		if (year % 4) return 28;
		if ((year % 100) == 0) return ((year % 400) == 0 ? 29 : 28);
		return 29;
	}
	void   Timestamp::validateDateValue (string str, vector<int> dt) {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		int day;

		if (dt[0] < 1 || dt[0] > 31) throw new invalid_argument(str + ": Is not a valid date " );
		if (dt[1] < 1 || dt[1] > 12) throw new invalid_argument(str + ": Is not a valid date " );
		day = (dt[1] == 2) ? isLeap(dt[2]) : days[dt[1] - 1];
		if (dt[0] > day) throw new invalid_argument(str + ": Is not a valid date " );
	}
    struct tm * Timestamp::validateDate(const char *str, int fmt) {

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
        char strDate[11];
		sprintf(strDate, "%04d/%02d/%02d", dt[2], dt[1], dt[0]);
		return makeDateTime(strDate, 0x0);

    }
	struct tm*  Timestamp::validateTime      (const char* str) {
		char strTime[9];
		regex pat{ "^[0-9]{1,2}:[0-9]{1,2}:[0-9]{1,2}$" };
		bool match = regex_search(str, pat);
		if (!match) throw new invalid_argument(string(str) + ": Is not a valid time " );
		vector<int> res = tokenizeNumber(str, (char*)":");
		if (res[0] < 0 || res[0] > 23) throw new invalid_argument(string(str) + ": Is not a valid time " );
		for (int i = 1; i < 3; i++) 
			if (res[i] < 0 || res[i] > 59) throw new invalid_argument(string(str) + ": Is not a valid time " );
		sprintf(strTime, "%02d:%02d:%02d", res[0], res[1], res[2]);
		return makeDateTime(0x0, strTime);
	}
	struct tm* Timestamp::makeDateTime(char* sdate, char* stime) {
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

	vector<int> Timestamp::tokenizeNumber(const char* src, const char* pat) {
		vector<int> res;
        sstring ss(src); 
		vector<sstring> vec = ss.tokenize(string(pat));
		for (sstring s : vec) res.push_back(stoi(s));
		return res;
	}


}