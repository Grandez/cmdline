#pragma once

#ifndef ENV_PREFFIX
   #define ENV_PREFFIX "env_preffix"
#endif

#include "parameter_tree.hpp"
#include  "group.hpp"

using namespace std;

namespace _cmdline {
	class _CommandLine {
	public:
		_CommandLine(int argc,  char**  argv, Parameters parms, bool sensitive = false, bool strict = false);
		vector<const char*> getArgs();
		// Flags
		bool  hasFlag(const char *flag);
		Flags getDefaultFlags(bool all);
		Flags getCurrentFlags(bool all);

		// Options
		int                 getOptionNumValues(const char* name);
		bool                hasOption        (const char* name);
		bool                isOptionMultiple (const char* name);
		Options             getDefaultOptions();
		Options             getCurrentOptions();
		const char*         getOption        (const char* name);
		vector<const char*> getOptionValues  (const char* name);
		
		// Definitions
		bool                 hasDefinition        (const char* def);
		bool                 isDefinitionMultiple (const char* name);
		const char*          getDefinition        (const char* name) { return getValue(&defines, name); }
		vector<const char*>  getDefinitionValues  (const char* name);

	private:
		vector<const char*> inputs;
		bool   sensitive = false;
		bool   strict = false;
		Group  options;
		Group  flags;
		Group  defines;

		std::unordered_map<std::string, Parm> defOptions;
		void  parse(const int argc,  char** argv);
		char* addValueToOption(const char* option, char* prev);
		
		char* updateFlag(const char* flag, const char* prev, bool value);
		void  updateFlagItem(const char* flag, const char* prev, bool value);
		char* updateOption(const char* option, char* value);
		char* updateDefinition(const char* def);
//		char* addParameterToInput(char* flag);
		char* checkOption(const char* parm);
		char* checkFlag(const char* parm);
		char* checkParameter(ParameterTree* root[], const char* parm);
		Options  getOptionsValue(bool def);
		void updateFromEnv();
		void udpateArgsFromEnv(Group& parms, const char *prfx);
		void loadHelp();
		void preInit(Parameters parms, bool init = true);
		void postInit();
		Flags  getFlags(bool active, bool set);
		Argument& find         (Group *group, const char* what);
		Argument* findPointer  (Group *group, const char* what);
		const char* getValue   (Group* group, const char* what);
		template <typename T>
		void checkType(T, Type type);
		template <typename T>
		T castValue(auto value);
		void checkAlreadySet(Group *group, const char* what);
	};
}

