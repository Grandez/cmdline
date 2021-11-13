#include "time.hpp"
#include <time.h>
#include <regex>

#include "sstring.hpp"
#ifdef _WIN32
#pragma warning( disable : 4996 )
#endif

namespace jggtools {

   Time::Time() {
      time_t now = time(0);
      tm *gmtm = gmtime(&now);
      this->hour  = gmtm->tm_hour;
      this->min   = gmtm->tm_min;
      this->second   = gmtm->tm_sec;
   }
   Time::Time(const Time& from) {
      this->hour = from.hour;
      this->min = from.min;
      this->second  = from.second;
   }
   Time::Time(string str) {
       Time(str.c_str());
   }
   Time::Time(const char *str) {
        validateTime(str);
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