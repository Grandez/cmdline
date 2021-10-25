#pragma once

#include "common.h"
#include "commandline.hpp"

using namespace std;

namespace cmdline {

	class CmdLine {
	public:
		CmdLine() { commandLine = new CommandLine(); }
		CmdLine(vector<ParmItem> args)                                      { commandLine = new CommandLine(args); }
		CmdLine(vector<ParmItem> options, vector<Flag> flags)  { commandLine = new CommandLine(options, flags); }
		CmdLine(vector<Flag> flags, vector<ParmItem> options) { commandLine = new CommandLine(options, flags); }
		~CmdLine() { delete commandLine; }
		CmdLine& parse(const int argc, const char* argv[]) { commandLine->parse(argc, argv); return *this; }

		bool  hasFlag(const char* name) { return commandLine->hasFlag(name); };
		bool  hasFlag(string name)      { return commandLine->hasFlag(name.c_str()); };
		Flag  getFlag(string name)      { return commandLine->getFlag(name); }

		Flags   getDefaultFlags(bool all = true) { return (commandLine->getDefaultFlags(all)); };
		Flags   getCurrentFlags(bool set = true) { return (commandLine->getCurrentFlags(set)); };
		Options getDefaultOptions() { return (commandLine->getDefaultOptions()); };
		Options getCurrentOptions(bool all = false) { return (commandLine->getCurrentOptions(all)); };

//		vector<string>  getDefinition(const char* name) { return (commandLine->getDefinition(name)); };
//		Definitions     getDefinitions() { return (commandLine->getDefinitions()); };

//		template <typename T>  T  getOption(const char* name) { return (commandLine->getOption<T>(name)); };
//		template <typename T>  T  getOption(string name) { return (commandLine->getOption<T>(name)); };

	private:
		CommandLine *commandLine;
	};
}
