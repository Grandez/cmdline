#pragma once
#include <string>
#include <vector>

#include "sal.h"
#include "enums.h"
#include "option.hpp"

namespace cmdline {
	Option::Option() {

	}
	Option::Option(std::string name, char* value) : source(Source::DEFAULT) {
		this->name = name;
		this->values.push_back(std::string(value));
		this->defvalue = strdup(value);
	}
	Option::Option(const char* name, const char* value) : source(Source::DEFAULT) {
		this->name = std::string(name);
		this->values.push_back(std::string(value));
		this->defvalue = strdup(value);
	}
	Option::Option(std::string name, std::string value, Source source) {
		this->name = name;
		this->values.push_back(value);
		this->source = source;
	}
	Option& Option::setFromEnv(const char* value) {
		this->values.push_back(std::string(value));
		this->source = Source::ENV;
		return *this;
	}
	/*
	inline Option& Option::setValue(bool value) {
		this->values.push_back(std::string(value ? "1" : "0"));
		return *this;
	}
	inline Option& Option::setValue(std::string value) {
		this->values[0] = value;
		return *this;
	}
	inline Option& Option::addValue(std::string value) {
		this->values.push_back(value);
		return *this;
	}
*/
};
