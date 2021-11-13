#pragma once

#include <vector>
#include <string>
using namespace std;

namespace jggtools {
   class Timestamp {
   public:
      Timestamp();
   protected:
      struct tm *ptm = nullptr;
      struct tm * validateDate(const char *str, int fmt);
      struct tm*  validateTime(const char* value);
      vector<int> tokenizeNumber(const char* src, const char* pat);
      struct tm* makeDateTime(char* sdate, char* stime);
      int year  = 0;
      int month = 0;
      int day   = 0;
      int hour  = 0;
      int min   = 0;
      int sec   = 0;
      unsigned int micro;
   private:
    static int sMicro;
	int  isLeap(int year);
	void validateDateValue (string str, vector<int> dt);
   };

}
