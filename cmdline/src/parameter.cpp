#include "tools.h"
#include  "cmdline.hpp"

namespace cmdline {
	Parm::Parm(const char* name) {
		this->name = name;
		this->value = strdup("true");
		this->type = Type::BOOL;
		this->multiple = false;
		this->instance = 2;
	}
	Parm::Parm(const char* name, const char* value) {
		this->name = name;
		this->value = strdup(value);
		this->multiple = false;
		this->instance = 1;
	}
	Parm::Parm(const char* name, const char* value, Type type, bool multiple) {
		this->name = name;
		this->value = strdup(value);
		this->type = type;
		this->multiple = multiple;
		this->instance = 1;
	}
	Parm::Parm(const char* name, bool value) {
		this->name = name;
		this->value = strdup(value ? "1" : "0");
		this->type = Type::BOOL;
		this->multiple = false;
		this->instance = 2;
	}
	bool Parm::instanceOfFlag() { return instance == 2; }
	bool Parm::instanceOfOption() { return instance == 1; }
};