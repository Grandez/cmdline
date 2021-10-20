#pragma once
#include <vector>
#include <list>
#include <map>
#include <set>
#include<string>
#include <utility>

#include "parmitem.hpp"
#include "parameter_tree.hpp"

namespace cmdline {
	class CommandLine {
	public:
		CommandLine() = delete;
		CommandLine(std::vector<ParmItem> parms);
		CommandLine(std::vector<ParmItem> options, std::vector<std::pair<char *, bool>> flags);
		int parse(const int argc, char* argv[]);
		bool                    hasFlag(char* flag) { return (flags.find(flag) != flags.end()); }
		char* checkOption(char* option);
		char* checkFlag(char* flag);
		std::map<std::string, bool>   getDefaultFlags() { return (defFlags); }
		std::set<std::string>   getCurrentFlags() { return (flags); }
		std::map<char*, char*>  getDefaultOptions() {
			std::map<char*, char*> defs;
			for (std::map<std::string, ParmItem>::iterator it = defOptions.begin(); it != defOptions.end(); ++it) defs.insert(it->second.name, it->second.value);
			return defs;
		}
		std::map<char*, char*>  getCurrentOptions() { return options; }


	private:
		std::list<char*> inputs;
		std::map<char*, char*> options;
		std::set<std::string> flags;
		std::map<std::string, ParmItem> defOptions;
		std::map<std::string, bool> defFlags;

		void  validateValue(char* value, char* option);
		char* addParameterToOptions(char* option, char* prev);
		char* addParameterToFlags(char* flag, char* prev);
		char* addValueToOption(char* option, char* value);
		inline char* addParameterToInput(char* flag);
		char *removeParameterFromFlags(char* flag, char* prev);
		char *checkParameter(ParameterTree* root[], char* parm);
		template <class T>
        T     getParameter(char* name);

	};

}
