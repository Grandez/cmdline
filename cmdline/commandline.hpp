#pragma once

#include <list>
#include <set>

#include "sal.h"
#include "parmitem.hpp"
#include "parameter_tree.hpp"

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

		std::map<std::string, bool>        getDefaultFlags() { return (defFlags); }
		std::map<std::string, std::string> getDefaultOptions();
		std::map<std::string, bool>        getCurrentFlags(bool active = true);
		std::map<std::string, void*>       getCurrentOptions(bool all = false);
//		template <typename T>  T  getOption(char* name);
	private:
		std::list<char*> inputs;
		std::map<std::string, void *> options;
		std::set<std::string> flags;
		std::map<std::string, ParmItem> defOptions;
		std::map<std::string, bool> defFlags;
	
		char* addParameterToOptions(char* option, char* prev);
		char* addParameterToFlags(char* flag, char* prev);
		char* addValueToOption(char* option, char* value);
		char* addParameterToInput(char* flag);
		char *removeParameterFromFlags(char* flag, char* prev);
		char *checkParameter(ParameterTree* root[], char* parm);
		char *checkOption(char* parm);
		char *checkFlag(char* parm);


	};

}
