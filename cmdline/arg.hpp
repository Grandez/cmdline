#pragma once
#include <string>
#include  <unordered_map>
#include "types.h"
#include "tools.h"
#include "parmitem.hpp"

using namespace std;

namespace cmdline {
	class Argument {
	public:
		string name;
		Source source   = Source::DEFAULT;
		Type   type     = Type::STRING;
		bool   multiple = false;
		char* defvalue = 0x0;
		vector<string> values;
		Argument() = delete;
		Argument(ParmItem& parm);
		Argument(const char *name, const char* value);
		Argument(const char *name, const char* value, Source source);
		Argument(const char* name, const char* value, Type type);
		Argument& setFromEnv(const char* value);
		Argument& setValue(bool value);
		Argument& setValue(const char* value);
		Argument& setValue(std::string value);
		Argument& addValue(std::string value);
		const string         getValue()  { return values[0]; }
		const vector<string> getValues() { return values; }
		string         letValue()  { return string(values[0]); }
		vector<string> letValues() { return vector<string>(values); }
		bool           getBoolean();
		Argument& initValues(vector<string> values) {
			this->values = values;
			return *this;
		}
	protected:
		Argument&      addValues(vector<string> values);
	};

	typedef unordered_map<string, Argument>  Args;
	typedef unordered_map<string, bool>      Flags;
	typedef pair<const string, bool>         Flag;
	typedef unordered_map<string, string>    Options;
	typedef pair<string, string>             Option;
	typedef unordered_map<string, vector<string>> Definition;

}
