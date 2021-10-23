#pragma once
#include "enums.h"

namespace cmdline {
	class ParmItem {
	public:
		const char* name;              // Name of parameter
		Type type;  // Type
		const char* value;   // default value
		bool multiple;   // Allow multiple values?
		ParmItem() = delete;
		ParmItem(const char* name) { 
			this->name = name; 
			this->value = nullptr;
			this->type = Type::STRING;
			this->multiple = false;
	    }
		ParmItem(char* name, char *value) { 
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