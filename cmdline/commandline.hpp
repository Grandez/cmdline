#pragma once

#ifndef ENV_PREFFIX
   #define ENV_PREFFIX "env_preffix"
#endif

#include "common.h"

#include "parmitem.hpp"
#include  "group.hpp"

using namespace std;

namespace cmdline {
	class CommandLine {
	public:
		CommandLine();
		CommandLine(vector<ParmItem> parms);
		CommandLine(vector<ParmItem> options, vector<Flag> flags);
		CommandLine(vector<Flag> flags, vector<ParmItem> options) : CommandLine(options, flags) {};
		~CommandLine();
		CommandLine& parse(const int argc, const char* argv[]);
		bool  hasFlag(const char *flag);
		const Flag  getFlag(const char *name);
		Flags getDefaultFlags(bool all);
		Flags getCurrentFlags(bool active = true);
		Options getDefaultOptions();
		Options getCurrentOptions(bool all = false);
		bool hasDefinition(const char*);
//		std::vector<std::string> getDefinition(const char* name);
//		Definitions  getDefinitions();


		template <typename T>  
		const T  getOption(const char *name);
		template <typename T>  
		const T  getDefinition(const char* name);
		const string  getDefinition2(const char* name);
		vector<string> getVectorDefinition(const char* name);
	private:
		std::list<const char*> inputs;
		Group  options;
		Group  flags;
		Group  defines;

		std::unordered_map<std::string, ParmItem> defOptions;

		char* addValueToOption(const char* option, char* prev);
		char* updateFlag(const char* flag, const char* prev, bool value);
		void  updateFlagItem(const char* flag, const char* prev, bool value);
		char* updateOption(const char* option, char* value);
		char* updateDefinition(const char* def);
		char* addParameterToInput(char* flag);
		char* checkOption(const char* parm);
		char* checkFlag(const char* parm);
		char* checkParameter(ParameterTree* root[], const char* parm);

		void updateFromEnv();
		void udpateArgsFromEnv(Group& parms, const char *prfx);
		void loadHelp();
		void preInit(vector<ParmItem> parms, bool init = true);
		void postInit();
	};
}

