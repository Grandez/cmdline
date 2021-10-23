#pragma once

#include <list>
#include <set>
#include <unordered_map>

#include "sal.h"
#include "parmitem.hpp"
#include "parameter_tree.hpp"
#include "option.hpp"

namespace cmdline {
	class CommandLine {
	public:
		CommandLine() = delete;
		CommandLine(std::vector<ParmItem> parms);
		CommandLine(std::vector<ParmItem> options, std::vector<std::pair<char *, bool>> flags);
		~CommandLine();

		CommandLine& parse(const int argc, char* argv[]);
		
		bool                    hasFlag(char* flag);
		bool                    hasFlag(const char* flag) { return hasFlag((char*) flag); }

		std::unordered_map<std::string, bool>        getDefaultFlags() { return (defFlags); }
		std::unordered_map<std::string, std::string> getDefaultOptions();
		std::unordered_map<std::string, bool>        getCurrentFlags(bool active = true);
		std::unordered_map<std::string, void*>       getCurrentOptions(bool all = false);
//		template <typename T>  T  getOption(char* name);
	private:
		std::list<char*> inputs;
		std::unordered_map<std::string, Option> options;
		std::unordered_map<std::string, Option> flags;
		std::unordered_map<std::string, ParmItem> defOptions;
		std::unordered_map<std::string, bool> defFlags;
	
		char* addParameterToOptions(char* option, char* prev);
		char* updateFlag(char* flag, char* prev, bool value);
		void         updateFlagItem(char* flag, char* prev, bool value);
		char* addValueToOption(char* option, char* value);
		char* addParameterToInput(char* flag);
		char *checkParameter(ParameterTree* root[], char* parm);
		char *checkOption(char* parm);
		char *checkFlag(char* parm);
		void  loadDefaults(std::vector<ParmItem> parms);
		void  loadEnv(std::unordered_map<std::string, Option> parms);

	};

}
