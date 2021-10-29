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
		_CommandLine(int argc, const char* argv[], Parameters parms);
		_CommandLine(int argc, const char* argv[], Parameters parms, bool forward = false, bool strict = false);
		~_CommandLine();
		// Flags
		bool  hasFlag(const char *flag);
		Flags getDefaultFlags(bool all);
		Flags getCurrentFlags(bool all);

		// Options
		bool           hasOption       (const char* name);
		bool           hasOption       (string name);
		bool           isOptionMultiple(const char* name);
		bool           isOptionMultiple(string name);
		const char*    getOption       (const char* name);
		const char*    getOption       (string name);
		template <typename T>
		const T         getOptionAs    (const char* name);
		template <typename T>
		const T         getOptionAs    (string name);
		vector<string>  getOptionValues(const char* name);
		vector<string>  getOptionValues(string name);
		template <typename T>
		vector<T>       getOptionValuesAs(const char* name);
		/*
		template <typename T>
		const vector<T> getOptionValuesAs(string name);
		*/
		Options         getDefaultOptions();
		Options         getCurrentOptions();

		bool            hasDefinition        (const char* def);
		bool            hasDefinition        (string def);
		bool            isDefinitionMultiple (const char* name);
		bool            isDefinitionMultiple (string name);
		char*           getDefinition        (const char* name);
		char*           getDefinition        (string name);
		vector<string>  getDefinitionValues  (const char* name);
		vector<string>  getDefinitionValues  (string name);

	private:
		std::list<const char*> inputs;
		bool   forward = false;
		bool   strict  = false;
		Group  options;
		Group  flags;
		Group  defines;

		std::unordered_map<std::string, Parm> defOptions;
		void  parse(const int argc, const char* argv[]);
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
		template <typename T>
		void checkType(T, Type type);
		template <typename T>
		T castValue(T, auto value);
		void checkAlreadySet(Group *group, const char* what);

	};
}

