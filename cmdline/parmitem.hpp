#pragma once

#include "common.h"
#include "arg.hpp"

using namespace std;

namespace cmdline {
#ifndef __TYPES__
    #define __TYPES__
	enum class Type { FLAG, STRING, NUMBER, DECIMAL, DATE, TIME, DIR, DIR_EXISTS, FILE, FILE_EXISTS };
	enum class Source { DEFAULT, ENV, CMDLINE };
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
		ParmItem(const char* name, char* value, Type type, bool multiple = false) { 
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
}