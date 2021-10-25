#pragma once
#include <string>
#include <unordered_map>
#include "tools.h"

/*

#include "common.h"
#include <string>
*/
using namespace std;

namespace cmdline {
#ifndef __TYPES__
#define __TYPES__
	enum class Type { FLAG, STRING, NUMBER, DECIMAL, DATE, TIME, DIR, DIR_EXISTS, FILE, FILE_EXISTS };
	enum class Source { DEFAULT, ENV, CMDLINE };
#endif
	class Argument {
	public:
		string name;
		Source source;
		char* defvalue = 0x0;;
		Argument();
		Argument(string name, char* value);
		Argument(const char* name, const char* value);
		Argument(string name, string value, Source source);
		Argument& setFromEnv(const char* value);
		Argument& setValue(bool value);
		Argument& setValue(std::string value);
		Argument& addValue(std::string value);
		string         getValue()  { return values[0]; }
		vector<string> getValues() { return values; }
		string         letValue()  { return string(values[0]); }
		vector<string> letValues() { return vector<string>(values); }
		bool           getBoolean();
	private:
		vector<string> values;
	};

	typedef unordered_map<string, Argument>  Args;
	typedef unordered_map<string, bool>      Flags;
	typedef pair<string, bool>               Flag;
	typedef unordered_map<string, string>    Options;
	typedef pair<string, string>             Option;
	typedef unordered_map<string, vector<string>> Definitions;

}
