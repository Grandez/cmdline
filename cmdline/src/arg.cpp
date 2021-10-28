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
		defvalue = strdup(parm.value);
		values.push_back(defvalue);
	}
	Argument::Argument(const char* name, const char* value) {
		this->name = name;
		this->values.push_back(std::string(value));
		this->defvalue = strdup(value);
	}
	Argument::Argument(const char* name, const char *value, Source source) {
		this->name = name;
		this->values.push_back(value);
		this->source = source;
	}
	Argument::Argument(const char* name, const char* value, Type type) {
		this->name = name;
		this->values.push_back(value);
		this->source = Source::DEFAULT;
	}

	bool Argument::getBoolean() {
		char* val = (char*) values[0].c_str();

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
	Argument& Argument::setFromEnv(const char* value) {
		this->values.push_back(std::string(value));
		this->source = Source::ENV;
		return *this;
	}
	Argument& Argument::setValue(const char *value) {
		this->values[0] = value;
		return *this;
	}
	Argument& Argument::setValue(bool value) {
		this->values[0] = string(value ? "1" : "0");
		return *this;
	}
	Argument& Argument::setValue(std::string value) {
		this->values[0] = value;
		return *this;
	}
	Argument& Argument::addValue(std::string value) {
		this->values.push_back(value);
		return *this;
	}
	Argument& Argument::addValues(vector<string> values) {
		this->values.resize(this->values.size() + values.size());
		this->values.insert(this->values.end(), values.begin(), values.end());
		return *this;
	}

};
