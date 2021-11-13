#pragma once

#include <vector>
#include <string>

#include "timestamp.hpp"

using namespace std;

namespace jggtools {
class Time : public Timestamp {
public:
   int hour;
   int min;
   int second;
   Time();
   Time(const Time&);
   Time(string str);
   Time(const char *str);


};
}
