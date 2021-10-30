#pragma once
#include <vector>

#include "commandline.hpp"
#include "cmdline.hpp"

using namespace std;
using namespace _cmdline;

namespace cmdline {
	CmdLine* singleton_ = nullptr;
	_CommandLine* _commandLine;
	void CmdLine::freeInstance() { singleton_ = nullptr; }
	CmdLine::CmdLine(int argc,  char**  argv, Parameters parms) {
		_commandLine = new _cmdline::_CommandLine(argc, argv, parms);
	}
    CmdLine::CmdLine(int argc,  char**  argv, Parameters parms, void *attr) {
        _commandLine = new _cmdline::_CommandLine(argc, argv, parms, attr);
	}
	CmdLine CmdLine::getInstance(Parameters parms, int argc,  char**  argv) {
		if (singleton_ == nullptr) singleton_ = new CmdLine(argc, argv, parms);
		return *singleton_;
	}
	CmdLine CmdLine::getInstance(int argc,  char**  argv, Parameters parms) {
		if (singleton_ == nullptr) singleton_ = new CmdLine(argc, argv, parms);
		return *singleton_;
	}

	CmdLine CmdLine::getInstance(int argc,  char**  argv, Parameters parms, void* attr) {
		if (singleton_ == nullptr) singleton_ = new CmdLine(argc, argv, parms, attr);
		return *singleton_;
	}

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

		bool            CmdLine::hasDefinition(const char* def)         { return _commandLine->hasDefinition(def);         }
		bool            CmdLine::hasDefinition(string def)              { return _commandLine->hasDefinition(def);         }
		bool            CmdLine::isDefinitionMultiple(const char* name) { return _commandLine->isDefinitionMultiple(name); }
		bool            CmdLine::isDefinitionMultiple(string name)      { return _commandLine->isDefinitionMultiple(name); }
		char*           CmdLine::getDefinition(const char* name)        { return _commandLine->getDefinition(name);        }
		char*           CmdLine::getDefinition(string name)             { return _commandLine->getDefinition(name);        }
		vector<string>  CmdLine::getDefinitionValues(const char* name)  { return _commandLine->getDefinitionValues(name);  }
		vector<string>  CmdLine::getDefinitionValues(string name)       { return _commandLine->getDefinitionValues(name);  }

//		const Flag  CmdLine::getFlag(const char* name) { return _commandLine->getFlag(name); }
//		const Flag  CmdLine::getFlag(string name) { return _commandLine->getFlag(name.c_str()); };
/*
		bool            CmdLine::hasDefinition(const char* def) { return _commandLine->hasDefinition(def); };

		template <typename T>  const T  CmdLine::getDefinition(const char* name) { return _commandLine->getDefinition<T>(name); };
		const string  CmdLine::getDefinition(const char* name) { return _commandLine->getDefinition2(name); };
		const vector<string>  CmdLine::getVectorDefinition(const char* name) { return _commandLine->getVectorDefinition(name); };
*/
}
