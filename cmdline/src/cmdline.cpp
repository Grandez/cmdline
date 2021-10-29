#pragma once
#include <vector>

#include "commandline.hpp"
#include "cmdline.hpp"

using namespace std;
using namespace _cmdline;

namespace cmdline {
	CmdLine* singleton_ = nullptr;
	_CommandLine* _commandLine;
	CmdLine::CmdLine(int argc, char* argv[], Parameters parms, bool forward, bool strict) {
		_commandLine = new _cmdline::_CommandLine(argc, argv, parms, forward, strict);
	}
	CmdLine CmdLine::GetInstance(int argc, char* argv[], Parameters parms) {
		if (singleton_ == nullptr) singleton_ = new CmdLine(argc, argv, parms);
		return *singleton_;
	}
	CmdLine CmdLine::GetInstance(Parameters parms, int argc, char* argv[]) {
		if (singleton_ == nullptr) singleton_ = new CmdLine(argc, argv, parms);
		return *singleton_;
	}

	CmdLine CmdLine::GetInstance(int argc, char* argv[], Parameters parms, bool forward, bool strict) {
		if (singleton_ == nullptr) singleton_ = new CmdLine(argc, argv, parms, forward, strict);
		return *singleton_;
	}

	//CmdLine::CmdLine() { CommandLine *commandLine = new CommandLine(); }
	// CmdLine::CmdLine() { _commandLine = new _cmdline::CommandLine(); }
	/*
	CmdLine::CmdLine(vector<ParmItem> args) { commandLine = new cmdline_::CommandLine(args); }
	CmdLine::CmdLine(vector<ParmItem> options, vector<Flag> flags) { commandLine = new CommandLine(options, flags); }
	CmdLine::CmdLine(vector<Flag> flags, vector<ParmItem> options) { commandLine = new CommandLine(options, flags); }
//	CmdLine::~CmdLine() { delete commandLine; }
	CmdLine& CmdLine::parse(const int argc, const char* argv[]) { commandLine->parse(argc, argv); return *this; }
	*/
		bool  CmdLine::hasFlag         (const char* name) { return _commandLine->hasFlag(name);         };
		bool  CmdLine::hasFlag         (string name)      { return _commandLine->hasFlag(name.c_str()); };
		Flags CmdLine::getDefaultFlags (bool all)         { return _commandLine->getDefaultFlags(all);  };
		Flags CmdLine::getCurrentFlags (bool all)         { return _commandLine->getCurrentFlags(all);  };

		bool            CmdLine::hasOption       (const char* name) { return _commandLine->hasOption(name); };
		bool            CmdLine::hasOption       (string name)      { return _commandLine->hasOption(name.c_str()); };
		bool            CmdLine::isOptionMultiple(const char* name) { return _commandLine->isOptionMultiple(name); };
		bool            CmdLine::isOptionMultiple(string name)      { return _commandLine->isOptionMultiple(name.c_str()); };
		const char*     CmdLine::getOption       (const char* name) { return _commandLine->getOption(name); };
		const char*     CmdLine::getOption       (string name)      { return _commandLine->getOption(name.c_str()); };
		template <typename T>
		const T         CmdLine::getOptionAs     (const char* name) { return _commandLine->getOption<T>(name.c_str()); };
		template <typename T>
		const T         CmdLine::getOptionAs     (string name)      { return _commandLine->getOption<T>(name.c_str()); };
		vector<string>  CmdLine::getOptionValues (const char* name) { return _commandLine->getOptionValues(name); };
		vector<string>  CmdLine::getOptionValues (string name)      { return _commandLine->getOptionValues(name.c_str()); };
		template <typename T>
		const vector<T> CmdLine::getOptionValuesAs(string name) { return _commandLine->getOptionValuesAs<T>(name.c_str()); };

		Options         CmdLine::getDefaultOptions() { return _commandLine->getDefaultOptions(); };
		Options         CmdLine::getCurrentOptions() { return _commandLine->getDefaultOptions(); };


//		const Flag  CmdLine::getFlag(const char* name) { return _commandLine->getFlag(name); }
//		const Flag  CmdLine::getFlag(string name) { return _commandLine->getFlag(name.c_str()); };
/*
		bool            CmdLine::hasDefinition(const char* def) { return _commandLine->hasDefinition(def); };

		template <typename T>  const T  CmdLine::getDefinition(const char* name) { return _commandLine->getDefinition<T>(name); };
		const string  CmdLine::getDefinition(const char* name) { return _commandLine->getDefinition2(name); };
		const vector<string>  CmdLine::getVectorDefinition(const char* name) { return _commandLine->getVectorDefinition(name); };
*/
}
