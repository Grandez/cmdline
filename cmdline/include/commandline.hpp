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
		_CommandLine(int argc, char* argv[], Parameters parms);
		_CommandLine(int argc, char* argv[], Parameters parms, bool forward = false, bool strict = false);
		~_CommandLine();
		_CommandLine& parse(const int argc, const char* argv[]);
		// Flags
		bool  hasFlag(const char *flag);
		Flags getDefaultFlags(bool all);
		Flags getCurrentFlags(bool all);

		// Options
		template <typename T>
		const T       getOption         (const char* name);
		template <typename T>
		const T       getOption         (string name);
		template <typename T>
		vector<T>     getOptionValues   (const char* name);
		template <typename T>
		vector<T>     getOptionValues   (string name);
		Options       getDefaultOptions ();
		Options       getCurrentOptions ();


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
		bool   forward = false;
		bool   strict  = false;
		Group  options;
		Group  flags;
		Group  defines;

		std::unordered_map<std::string, Parm> defOptions;

		char* addValueToOption(const char* option, char* prev);
		char* updateFlag(const char* flag, const char* prev, bool value);
		void  updateFlagItem(const char* flag, const char* prev, bool value);
		char* updateOption(const char* option, char* value);
		char* updateDefinition(const char* def);
//		char* addParameterToInput(char* flag);
		char* checkOption(const char* parm);
		char* checkFlag(const char* parm);
		char* checkParameter(ParameterTree* root[], const char* parm);

		void updateFromEnv();
		void udpateArgsFromEnv(Group& parms, const char *prfx);
		void loadHelp();
		void preInit(Parameters parms, bool init = true);
		void postInit();
		Flags  getFlags(bool active, bool set);
	};
}

