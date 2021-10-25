#pragma once

#include <list>
//#include <set>
#include <vector>
#include <utility>
#include <unordered_map>

#include "sal.h"
#include "parmitem.hpp"
#include "parameter_tree.hpp"

#include "option.hpp"

#ifndef ENV_PREFFIX
   #define ENV_PREFFIX "env_preffix"
#endif

namespace cmdline {
	class CommandLine {
	public:
		CommandLine();
		CommandLine(std::vector<ParmItem> parms);
		CommandLine(std::vector<ParmItem> options, std::vector<std::pair<char*, bool>> flags);
		~CommandLine();
		
		CommandLine& parse(const int argc, char* argv[]);

		bool                    hasFlag(char* flag);
		bool                    hasFlag(const char* flag) { return hasFlag((char*) flag); }
		std::pair<std::string, bool>                 getFlag(std::string name);
		std::unordered_map<std::string, bool>        getDefaultFlags(bool all);
		std::unordered_map<std::string, std::string> getDefaultOptions();
		std::unordered_map<std::string, bool>        getCurrentFlags(bool active = true);
		std::unordered_map<std::string, void*>       getCurrentOptions(bool all = false);
		std::vector<std::string>                     getDefinition(const char* name);
		std::unordered_map<std::string, std::vector<std::string>>  getDefinitions();

		template <typename T>  T  getOption(std::string name);
		
	private:
		std::list<char*> inputs;
		std::unordered_map<std::string, Option>   options;
		std::unordered_map<std::string, Option>   flags;
		std::unordered_map<std::string, Option>   defines;
		std::unordered_map<std::string, ParmItem> defOptions;
		std::unordered_map<std::string, bool>     defFlags;

		char* addValueToOption(char* option, char* prev);
		char* updateFlag(char* flag, char* prev, bool value);
		void  updateFlagItem(char* flag, char* prev, bool value);
		char* updateOption(char* option, char* value);
		char* updateDefinition(char* def, int pos);
		char* addParameterToInput(char* flag);
		char* checkOption(char* parm);
		char* checkFlag(char* parm);
		char* checkParameter(ParameterTree* root[], char* parm);
		void  loadDefaults(std::vector<ParmItem> parms);
		void  loadEnv(std::unordered_map<std::string, Option> parms);
	};

}
