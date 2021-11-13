#pragma once

#ifndef ENV_PREFFIX
#define ENV_PREFFIX "env_preffix"
#endif

#include "types.hpp"
#include "group.hpp"
#include "parameter_tree.hpp"

using namespace NS1;

namespace NS2 {
	class CommandLine {
	public:
		CommandLine(int argc, const char** argv, Parameters parms, bool sensitive, bool strict);
		~CommandLine();

		vector<const char*> getArgs();
		Type getType(const char *name);
		// Flags
		bool  hasFlag(const char* flag);
		Flags getDefaultFlags(bool all);
		Flags getCurrentFlags(bool all);

		// Options
		int                 getOptionNumValues(const char* name);
		bool                hasOption(const char* name);
		bool                isOptionMultiple(const char* name);
		Options             getCurrentOptions();
		const char*         getOption(const char* name);
		vector<const char*> getOptionValues(const char* name);
		unordered_map<string, string>   getDefaultOptions();
		// Definitions
		bool                 hasDefinition(const char* def);
		bool                 isDefinitionMultiple(const char* name);
		int                  getDefinitionNumValues(const char* name);

		const char*          getDefinition(const char* name) { return getValue(&defines, name); }
		vector<const char*>  getDefinitionValues(const char* name);
		Options              getDefinitions();

	private:
		vector<const char*> inputs;
		bool   sensitive = false;
		bool   strict = false;
		Group  options;
		Group  flags;
		Group  defines;
		void  parseCommandLine(const int argc, const char** argv);
		char* addValueToOption(const char* option, char* prev);
		char* checkOption(const char* option);
		char* checkFlag(const char* flag);
		char* checkParameter(ParameterTree* root[], const char* parm);
		void  checkAlreadySet(Group* group, const char* what);

		char* updateFlag(const char* flag, const char* prev, bool value);
		void  updateFlagItem(const char* flag, const char* prev, bool value);
		char* updateOption(const char* option, char* value);
		char* updateDefinition(const char* def);
		void  updateValuesFromEnvironment();
		void  udpateArgsFromEnv(Group& parms, const char* prfx);

		Flags       getFlags(bool active, bool set);
		Argument&   find(Group* group, const char* what);
		Argument*   findPointer(Group* group, const char* what);
		const char* getValue(Group* group, const char* what);
		unordered_map<string,string>     getOptionsValue(bool def);
        void       loadParameters(Parameters parms);
		void        loadHelpFlags();
		
       void  processConfigFile(char *fname);
       char* processOptionOrDefinition(const char *argv, char *prevToken);
       char* processDefinition(const char *argv);
       char* activeFlag(const char *flag, char *prev);
       char* inactiveFlag(const char *flag, char *prev);
       void  addToInputs(const char *arg);
       bool  updateFlagHelp(const char *arg, char *prev);
       vector<string> configFilesInCommandLine(int argc, const char **argv, bool sensitive);
	};
}
