#pragma once
#include "common.h"

#include "arg.hpp"

using namespace std;
using namespace cmdline;

namespace cmdline {
	Argument::Argument() {
		cout << "Crea OptionTpl" << endl;
	}
	Argument::Argument(std::string name, char* value) : source(Source::DEFAULT) {
		this->name = name;
		this->values.push_back(std::string(value));
		this->defvalue = strdup(value);
	}
	Argument::Argument(const char* name, const char* value) : source(Source::DEFAULT) {
		this->name = std::string(name);
		this->values.push_back(std::string(value));
		this->defvalue = strdup(value);
	}
	Argument::Argument(std::string name, std::string value, Source source) {
		this->name = name;
		this->values.push_back(value);
		this->source = source;
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

	Argument& Argument::setValue(bool value) {
		this->values.push_back(std::string(value ? "1" : "0"));
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


};
