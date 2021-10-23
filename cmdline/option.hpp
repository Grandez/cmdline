#pragma once
#include <string>

#include "sal.h"
#include "enums.h"

namespace cmdline {
	class Option {
	public:
		std::string name;
		char* value;
		Source source;
		char* defvalue;
		Option() {
			value = nullptr;
		}
		Option(std::string name, char* value)       : source(Source::DEFAULT) { this->name = name; this->value = value; }
		Option(const char *name, const char* value) : source(Source::DEFAULT) { this->name = std::string(name); this->value = strdup(value); }
		inline Option& setFromEnv(const char* value) {
			this->value = strdup(value);
			return *this;
		}
		inline Option& setValue(bool value) { 
			this->value = (char *) ((value) ? "1" : "0"); 
			return *this;
	    }
	};
}
