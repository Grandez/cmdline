#pragma once
#include <vector>

#include "commandline.hpp"
#include "cmdline.hpp"

using namespace std;
using namespace _cmdline;

namespace cmdline {
	CmdLine* singleton_ = nullptr;
//	_CommandLine* _commandLine;
	void CmdLine::freeInstance() { singleton_ = nullptr; }
	CmdLine::CmdLine(int argc,  char**  argv, Parameters parms) {
		_commandLine = new _cmdline::_CommandLine(argc, argv, parms);
	}
	CmdLine::CmdLine(int argc, char** argv, Parameters parms, bool sensitive, bool strict) {
		_commandLine = new _cmdline::_CommandLine(argc, argv, parms, sensitive, strict);
	}
	CmdLine CmdLine::getInstance(Parameters parms, int argc,  char**  argv) {
		if (singleton_ == nullptr) singleton_ = new CmdLine(argc, argv, parms);
		return *singleton_;
	}
	CmdLine CmdLine::getInstance(int argc, char** argv, Parameters parms) {
		if (singleton_ == nullptr) singleton_ = new CmdLine(argc, argv, parms);
		return *singleton_;
	}
	CmdLine CmdLine::pGetInstance(int argc,  char**  argv, Parameters parms, bool sensitive, bool strict) {
		if (singleton_ == nullptr) singleton_ = new CmdLine(argc, argv, parms, sensitive, strict);
		return *singleton_;
	}
	vector<const char*> CmdLine::args() { return _commandLine->getArgs(); }

		bool  CmdLine::hasFlag         (const char* name) { return _commandLine->hasFlag(name);         };
		bool  CmdLine::hasFlag         (string name)      { return _commandLine->hasFlag(name.c_str()); };
		Flags CmdLine::getDefaultFlags (bool all)         { return _commandLine->getDefaultFlags(all);  };
		Flags CmdLine::getCurrentFlags (bool all)         { return _commandLine->getCurrentFlags(all);  };

		bool            CmdLine::hasOption       (const char* name) { return _commandLine->hasOption(name); };
		bool            CmdLine::hasOption       (string name)      { return _commandLine->hasOption(name.c_str()); };
		bool            CmdLine::isOptionMultiple(const char* name) { return _commandLine->isOptionMultiple(name); };
		bool            CmdLine::isOptionMultiple(string name)      { return _commandLine->isOptionMultiple(name.c_str()); };
		const char*     CmdLine::getOption       (const char* name) { return _commandLine->getOption(name); };

//		template <typename T>
//		const T         CmdLine::getOptionAs     (const char* name) { return _commandLine->getOptionAs<T>(name); };
//		template <typename T>
//		const T         CmdLine::getOptionAs     (string name)      { return _commandLine->getOptionAs<T>(name.c_str()); };
		vector<const char*>  CmdLine::getOptionValues (const char* name) { return _commandLine->getOptionValues(name); };
		vector<const char*>  CmdLine::getOptionValues (string name)      { return getOptionValues(name.c_str()); };

		int             CmdLine::getOptionNumValues (const char* name) { return _commandLine->getOptionNumValues(name); };
		int             CmdLine::getOptionNumValues (string name)      { return getOptionNumValues(name.c_str()); };

		template <typename T>
		const vector<T> CmdLine::getOptionValuesAs(string name) { return _commandLine->getOptionValuesAs<T>(name.c_str()); };

		Options         CmdLine::getDefaultOptions() { return _commandLine->getDefaultOptions(); };
		Options         CmdLine::getCurrentOptions() { return _commandLine->getDefaultOptions(); };

		bool            CmdLine::hasDefinition(const char* def)         { return _commandLine->hasDefinition(def);         }
		bool            CmdLine::hasDefinition(string def)              { return _commandLine->hasDefinition(def);         }
		bool            CmdLine::isDefinitionMultiple(const char* name) { return _commandLine->isDefinitionMultiple(name); }
		bool            CmdLine::isDefinitionMultiple(string name)      { return _commandLine->isDefinitionMultiple(name); }
		const char* CmdLine::getDefinition(const char* name) { return _commandLine->getDefinition(name); }
		const char* CmdLine::getDefinition(string name) { return getDefinition(name.c_str()); }

		vector<const char*>  CmdLine::getDefinitionValues(const char* name)  { return _commandLine->getDefinitionValues(name);  }
		vector<const char*>  CmdLine::getDefinitionValues(string name)       { return getDefinitionValues(name.c_str());        }
}
