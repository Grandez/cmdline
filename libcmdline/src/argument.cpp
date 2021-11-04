#pragma once
#include <string>
#include <algorithm>
#include <filesystem>
#include <ctime>

#include "argument.hpp"
#include "tools.hpp"
#include "validations.hpp"

#ifdef _WIN32
#pragma warning( disable : 4996 )
#endif

using namespace std;
using namespace cmdline;

namespace _cmdline {
	Argument::Argument(Parm *parm) {
		// Initial constructor. from default data
		name = string(parm->name);
		type = parm->type;
		multiple = parm->multiple;
		defValue = applyDefault(parm->value);
		validateDefault();
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
		validateDefault();
	}
	Argument::Argument(const char* name, const char* value) {
		this->name     = string(name);
		this->defValue = applyDefault(value); 
		validateDefault();
	}
	Argument::Argument(const char* name, const char *value, Source source) {
		if (source == Source::DEFAULT) {
			this->defValue = applyDefault(value);
		}
		else {
			if (values.size() == 0) this->first = string(value);
			this->values.emplace(value);
		}
		this->name = string(name);
		this->source = source;
		validateDefault();
	}
	Argument::Argument(const char* name, const char* value, Type type) : Argument(name, value) {
		this->type = type;
		validateDefault();
	}
	Argument::~Argument() {
		// if (defValue) free(defValue);
	}

	const char* Argument::getValue() { 
		return (first.length() > 0) ? first.c_str() : defValue.c_str();
	}
	vector<const char *>  Argument::getValues() {
		int i = 0;
		vector<const char*> v(values.size());
		for (string val : values) {
			v[i++] = strdup((val.c_str()));
		}
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
	Argument& Argument::makeUpper() {
		for_each(name.begin(), name.end(), [](char& c) { c = ::toupper(c);});
		return *this;
	}
	void Argument::validateDefault() {
		if (defValue.length() == 0) return;
		if (type == Type::STRING) return;
		validateValue(defValue.c_str(), type);
	}
	string Argument::applyDefault(const char* txt) {
		char aux[256] = "";
		if (txt != NULL && strlen(txt) > 0) return string(txt);
		std::time_t t = std::time(0);   
		std::tm* now = std::localtime(&t);
		switch (this->type) {
		       case Type::DATE: 
				    defaultDate(aux);
			        break;
		       case Type::TIME:
			        sprintf(aux, "%02d:%02d:%02d", now->tm_hour, now->tm_min, now->tm_sec);
			        break;
		       case Type::DATETIME:
			        sprintf(aux, "%04d-%02d-%02d %02d:%02d:%02d",
				                 now->tm_year + 1900, now->tm_mon + 1, now->tm_mday,
				                 now->tm_hour, now->tm_min, now->tm_sec);
			        break;
		       case Type::TMS:
			        sprintf(aux, "%04d-%02d-%02d-%02d:%02d:%02d.000000",
				    now->tm_year + 1900, now->tm_mon + 1, now->tm_mday,
				    now->tm_hour, now->tm_min, now->tm_sec);
			        break;
		       case Type::DIR:
		       case Type::DIR_EXISTS:
 				    strcpy(aux, (const char *) std::filesystem::current_path().string().c_str());
			        break;
		       case Type::BOOL:
			        aux[0] = '0'; aux[1] = 0x0;
			        break;
		       default:
			        if (txt == NULL) return string("");
			        return string(aux);
		}
		return (string(aux));
	}

};
