#pragma once

//#include "common.h"
// #include "arg.hpp"

using namespace std;

namespace cmdline {
#ifndef __TYPES__
    #define __TYPES__
	enum class Type { FLAG, STRING, NUMBER, DECIMAL, DATE, TIME, DATETIME, TMS, DIR, DIR_EXISTS, FILE, FILE_EXISTS };
	enum class Source { DEFAULT, ENV, CMDLINE, AUTO };
#endif

	class ParmItem {
	public:
		const char* name;              // Name of parameter
		Type type = Type::STRING;  // Type
		const char* value;   // default value
		bool multiple;   // Allow multiple values?
		ParmItem() = delete;
		ParmItem(const char* name) { 
			this->name = name;
			this->value = "true";
			this->type = Type::FLAG;
			this->multiple = false;
	    }
		ParmItem(const char* name, const char *value) { 
			this->name = name; 
			this->value = value;
			this->type = Type::STRING;
			this->multiple = false;
		}
		ParmItem(const char* name, const char* value, Type type, bool multiple = false) { 
			this->name = name; 
			this->value = value;
			this -> type = type;
			this->multiple = multiple;
		}
		ParmItem(const char* name, bool value) {
			this->name = name;
			this->value = (char *) ((value) ? "1" : "0");
			this->type = Type::FLAG;
			this->multiple = false;
		}

	};
	class FlagItem : public ParmItem {
	public:
		FlagItem() = delete;
		FlagItem(const char* name) : ParmItem(name, true) {};
		FlagItem(const char* name, bool active) : ParmItem(name, active) {};
	};
	class OptionItem : public ParmItem {
	public:
		OptionItem() = delete;
		OptionItem(const char* name, const char *value)            : ParmItem(name, value) {};
		OptionItem(const char* name, const char* value, Type type) : ParmItem(name, value, type) {};
		OptionItem(const char* name, const char* value, bool multiple)                    : ParmItem(name, value, Type::STRING, multiple) {};
		OptionItem(const char* name, const char* value, Type type, bool multiple = false) : ParmItem(name, value, type, multiple) {};
	};

}