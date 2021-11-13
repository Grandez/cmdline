#pragma once

#include <vector>
#include <string>

#include "timestamp.hpp"

using namespace std;

namespace jggtools {
class Date : public Timestamp{
public:
   int year;
   int month;
   int day;
   Date();
   Date(const Date&);
   Date(string str     , int fmt = -1);
   Date(const char *str, int fmt = -1);


};
}
