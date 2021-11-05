#pragma once

#ifndef ENV_PREFFIX
#define ENV_PREFFIX "env_preffix"
#endif

#include "types.hpp"
#include "group.hpp"
#include "parameter_tree.hpp"

using namespace cmdline;

namespace _cmdline {
	class CommandLine {
	public:
		CommandLine(int argc, char** argv, Parameters parms, bool sensitive, bool strict);
		~CommandLine();

		vector<const char*> getArgs();
		// Flags
		bool  hasFlag(const char* flag);
		Flags getDefaultFlags(bool all);
		Flags getCurrentFlags(bool all);

		// Options
		int                 getOptionNumValues(const char* name);
		bool                hasOption(const char* name);
		bool                isOptionMultiple(const char* name);
		Options             getDefaultOptions();
		Options             getCurrentOptions();
		const char* getOption(const char* name);
		vector<const char*> getOptionValues(const char* name);

		// Definitions
		bool                 hasDefinition(const char* def);
		bool                 isDefinitionMultiple(const char* name);
		const char* getDefinition(const char* name) { return getValue(&defines, name); }
		vector<const char*>  getDefinitionValues(const char* name);

	private:
		vector<const char*> inputs;
		bool   sensitive = false;
		bool   strict = false;
		Group  options;
		Group  flags;
		Group  defines;
		void  parse(const int argc, char** argv);
		char* addValueToOption(const char* option, char* prev);
		char* checkOption(const char* option);
		char* checkFlag(const char* flag);
		char* checkParameter(ParameterTree* root[], const char* parm);
		void  checkAlreadySet(Group* group, const char* what);

		char* updateFlag(const char* flag, const char* prev, bool value);
		void  updateFlagItem(const char* flag, const char* prev, bool value);
		char* updateOption(const char* option, char* value);
		char* updateDefinition(const char* def);
		void  updateFromEnv();
		void  udpateArgsFromEnv(Group& parms, const char* prfx);

		Flags     getFlags(bool active, bool set);
		Argument& find(Group* group, const char* what);
		Argument* findPointer(Group* group, const char* what);
		const char* getValue(Group* group, const char* what);
		Options  getOptionsValue(bool def);
		void preInit(Parameters parms, bool init = true);
		void  postInit();
		void  loadHelp();
		
	};
}
