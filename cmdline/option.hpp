#pragma once

#include <string>
#include <vector>

#include "sal.h"
#include "enums.h"

namespace cmdline {
	class Option {
	public:
		std::string name;
		Source source = Source::DEFAULT;
		char* defvalue = 0x0;;
		Option();
		Option(std::string name, char* value); 
		Option(const char* name, const char* value);
		Option(std::string name, std::string value, Source source);
		Option& setFromEnv(const char* value);
		//inline Option& setValue(bool value);
		//inline Option& setValue(std::string value);
		//inline Option& addValue(std::string value);
		inline std::string getValue() { return values[0]; }
		inline std::vector<std::string> getValues() { return values; }
		inline std::string letValue() { return std::string(values[0]); }
		inline std::vector<std::string> letValues() { return std::vector<std::string>(values); }
	private:
		std::vector<std::string> values;
	};
}
