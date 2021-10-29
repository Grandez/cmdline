#pragma once
#include "arg.hpp"
#include "tools.h"

using namespace std;
using namespace cmdline;

namespace _cmdline {
	Argument::Argument(Parm *parm) {
		// Initial constructor. from default data
		name = string(parm->name);
		type = parm->type;
		multiple = parm->multiple;
		defValue = string(parm->value);
	}
	Argument::Argument(Argument *arg) {
		// Copy contructor
		this->name = string(arg->name);
		this->type = arg->type;
		this->multiple = arg->multiple;
		if (arg->first.length()    > 0) this->first    = string(arg->first);
		if (arg->defValue.length() > 0) this->defValue = string(arg->defValue);
		if (arg->values.size() > 0) {
			for (string s : arg->values) this->values.insert(s);
		}
	}
	Argument::Argument(const char* name, const char* value) {
		this->name     = string(name);
		this->defValue = string(value);
	}
	Argument::Argument(const char* name, const char *value, Source source) {
		if (source == Source::DEFAULT) {
			this->defValue = string(value);
		}
		else {
			if (values.size() == 0) this->first = string(value);
			this->values.emplace(value);
		}
		this->name = string(name);
		this->source = source;
	}
	Argument::Argument(const char* name, const char* value, Type type) : Argument(name, value) {
		this->type = type;
	}
	Argument::~Argument() {
		// if (defValue) free(defValue);
	}

	const char* Argument::getValue() { 
		return (first.length() > 0) ? first.c_str() : defValue.c_str();
	}
	vector<string>  Argument::getValues() {
		vector<string> v(values.size());
		for (string val : values) v.push_back(val);
		return v;
	}

	bool Argument::getBoolean() {
		string val = (first.length() > 0) ? first : defValue;

		if (val.length() == 0)         return false;
		if (val.at(0) == '0')          return false;
		if (val.at(0) == '1')          return true;
		if (val.compare("-1")    == 0) return true;
		if (val.compare("no")    == 0) return false;
		if (val.compare("false") == 0) return false;
		if (val.compare("yes")   == 0) return true;
		if (val.compare("true")  == 0) return true;
		if (val.compare("si")    == 0) return true;
		return false;
	}
	Argument& Argument::initValues(vector<string> values) {
		first = string(values[0]);
		this->values.clear();
		for (string s : values) this->values.emplace(s);
		return *this;
	}

	Argument& Argument::setFromEnv(const char* value) {
		if (values.size() == 0) first = string(value);
		this->values.emplace(std::string(value));
		this->source = Source::ENV;
		return *this;
	}
	Argument& Argument::setValue(const char *value) {
		first = string(value);
		this->values.emplace(value);
		return *this;
	}
	Argument& Argument::setValue(bool value) {
		string s = string(value ? "1" : "0");
		first = string(s);
		this->values.emplace(s);
		return *this;
	}
	Argument& Argument::setValue(std::string value) {
		first = string(value);
		this->values.emplace(value);
		return *this;
	}
	Argument& Argument::addValue(std::string value) {
		if (values.size() == 0) first = string(value);
		this->values.emplace(value);
		return *this;
	}
	Argument& Argument::addValues(vector<string> values) {
		if (values.size() == 0) first = string(values[0]);
		for (string v : values) this->values.emplace(v);
		return *this;
	}

};
