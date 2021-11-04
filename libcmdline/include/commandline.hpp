#pragma once

#ifndef ENV_PREFFIX
#define ENV_PREFFIX "env_preffix"
#endif

#include "types.hpp"
#include "group.hpp"

using namespace cmdline;

namespace _cmdline {
	class CommandLine {
	public:
		CommandLine();
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

		Flags     getFlags(bool active, bool set);
		Argument& find(Group* group, const char* what);
		Argument* findPointer(Group* group, const char* what);
		const char* getValue(Group* group, const char* what);
		Options  getOptionsValue(bool def);
	};
}
