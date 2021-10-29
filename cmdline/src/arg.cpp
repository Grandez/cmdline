#pragma once
#include "arg.hpp"
#include "tools.h"

using namespace std;
using namespace cmdline;

namespace _cmdline {
	Argument::Argument(Parm& parm) {
		name = strdup(parm.name);
		type = parm.type;
		multiple = parm.multiple;
		defValue = strdup(parm.value);
	}
	Argument::Argument(const char* name, const char* value) {
		this->name = name;
		this->defValue = strdup(value);
	}
	Argument::Argument(const char* name, const char *value, Source source) {
		if (source == Source::DEFAULT) {
			this->defValue = strdup(value);
		}
		else {
			if (values.size() == 0) this->first = strdup(value);
			this->values.emplace(value);
		}
		this->name = name;
		this->source = source;
	}
	Argument::Argument(const char* name, const char* value, Type type) {
		//this->name = name;
		//this->defValue = strdup(value);
		//this->source = Source::DEFAULT;
	}
	const char* Argument::getValue() { 
		return (first) ? first : defValue;
	}
	vector<string>  Argument::getValues() {
		vector<string> v(values.size());
		for (string val : values) v.push_back(val);
		return v;
	}

	bool Argument::getBoolean() {
		char* val = (first) ? first :defValue;

		if (val == nullptr)              return false;
		if (strlen(val) == 0)            return false;
		if (val[0] == '0')               return false;
		if (val[0] == '1')               return true;
		if (strcmp(val, "-1") == 0) return true;
		if (_stricmp(val, "no") == 0) return false;
		if (_stricmp(val, "false") == 0) return false;
		if (_stricmp(val, "yes") == 0) return true;
		if (_stricmp(val, "true") == 0) return true;
		if (_stricmp(val, "si") == 0) return true;
		return false;
	}
	Argument& Argument::initValues(vector<string> values) {
		first = strdup(values[0].c_str());
		this->values.clear();
		for (string s : values) this->values.emplace(s);
		return *this;
	}

	Argument& Argument::setFromEnv(const char* value) {
		if (values.size() == 0) first = strdup(value);
		this->values.emplace(std::string(value));
		this->source = Source::ENV;
		return *this;
	}
	Argument& Argument::setValue(const char *value) {
		first = strdup(value);
		this->values.emplace(value);
		return *this;
	}
	Argument& Argument::setValue(bool value) {
		string s = string(value ? "1" : "0");
		first = strdup(s.c_str());
		this->values.emplace(s);
		return *this;
	}
	Argument& Argument::setValue(std::string value) {
		first = strdup(value.c_str());
		this->values.emplace(value);
		return *this;
	}
	Argument& Argument::addValue(std::string value) {
		if (values.size() == 0) first = strdup(value.c_str());
		this->values.emplace(value);
		return *this;
	}
	Argument& Argument::addValues(vector<string> values) {
		if (values.size() == 0) first = strdup(values[0].c_str());
		for (string v : values) this->values.emplace(v);
		return *this;
	}

};
