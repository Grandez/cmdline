#pragma once

#include "common.h"
#include "commandline.hpp"
#include "cmdline_exceptions.hpp"

using namespace std;

namespace cmdline {
	#ifndef __TYPES__
        #define __TYPES__
		enum class Type { FLAG, STRING, NUMBER, DECIMAL, DATE, TIME, DATETIME, TMS, DIR, DIR_EXISTS, FILE, FILE_EXISTS };
		enum class Source { DEFAULT, ENV, CMDLINE, AUTO };
#include "arg.hpp"
/*
		class Argument {
		public:
			string name;
			Source source = Source::DEFAULT;
			Type   type = Type::STRING;
			char* defvalue = 0x0;
			vector<string> values;
			Argument() = delete;
			Argument(const char* name, const char* value);
			Argument(const char* name, const char* value, Source source);
			Argument& setFromEnv(const char* value);
			Argument& setValue(bool value);
			Argument& setValue(std::string value);
			Argument& addValue(std::string value);
			string         getValue() { return values[0]; }
			vector<string> getValues() { return values; }
			string         letValue() { return string(values[0]); }
			vector<string> letValues() { return vector<string>(values); }
			bool           getBoolean();
		private:

		};
*/
	typedef unordered_map<string, Argument>  Args;
	typedef unordered_map<string, bool>      Flags;
	typedef pair<string, bool>               Flag;
	typedef unordered_map<string, string>    Options;
	typedef pair<string, string>             Option;
	typedef unordered_map<string, vector<string>> Definitions;
#endif
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
		const Flag  getFlag(const char* name) { return commandLine->getFlag(name); }
		const Flag  getFlag(string name)      { return commandLine->getFlag(name.c_str()); };

		Flags           getDefaultFlags(bool all = true) { return (commandLine->getDefaultFlags(all)); };
		Flags           getCurrentFlags(bool set = true) { return (commandLine->getCurrentFlags(set)); };
		Options         getDefaultOptions() { return (commandLine->getDefaultOptions()); };
		Options         getCurrentOptions(bool all = false) { return (commandLine->getCurrentOptions(all)); };
		bool            hasDefinition    (const char*def)   { return (commandLine->hasDefinition(def)); };

		template <typename T>  const T  getOption(const char* name) { return (commandLine->getOption<T>(name)); };
		template <typename T>  const T  getOption(string name)      { return getOption<T>(name.c_str()); };
		const string                    getOption(const char* name) { return getOption<string>(name); }
		template <typename T>  const T  getDefinition(const char* name) { return (commandLine->getDefinition<T>(name)); };
		const string  getDefinition(const char* name) { return (commandLine->getDefinition2(name)); };
		const vector<string>  getVectorDefinition(const char* name) { return (commandLine->getVectorDefinition(name)); };

	private:
		CommandLine *commandLine;
	};
}
