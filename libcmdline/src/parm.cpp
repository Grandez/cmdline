#include "tools.hpp"
#include  "cmdline.hpp"

namespace cmdline {
	Parameter::Parameter(const char* name) {
		this->name     = name;
		this->value    = strdup("1");
		this->type     = Type::BOOL;
		this->multiple = false;
		this->instance = 2;
	}
	Parameter::Parameter(const char* name, const char* value) {
		this->name     = name;
		this->value    = (value == NULL) ? NULL : strdup(value);
		this->multiple = false;
		this->instance = 1;
	}
	Parameter::Parameter(const char* name, const char* value, Type type, bool multiple) {
		this->name     = name;
		this->value    = (value == NULL) ? NULL : strdup(value);
		this->type     = type;
		this->multiple = multiple;
		this->instance = 1;
	}
	Parameter::Parameter(const char* name, bool value) {
		this->name     = name;
		this->value    = strdup(value ? "1" : "0");
		this->type     = Type::BOOL;
		this->multiple = false;
		this->instance = 2;
	}
	bool Parameter::instanceOfFlag() { return instance == 2; }
	bool Parameter::instanceOfOption() { return instance == 1; }
};