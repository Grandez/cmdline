#include <iostream>
#include "config.h"

#include "cmdline.hpp"
#include "commandline.hpp"
#include "types.hpp"
#include "validations.hpp"
#include "tools.hpp"

using namespace NS2;

namespace NS1 {
	CmdLine* singleton_ = nullptr;
	static bool instance = false;  // Allow constructor only in test
	void CmdLine::destroyInstance(CmdLine* CmdLine) { 
         singleton_ = nullptr; 
    }
	NS2::CommandLine* _commandLine;

	CmdLine::CmdLine(int argc, const char** argv, Parameters parms) {
		_commandLine = new NS2::CommandLine(argc, argv, parms, false, false);
	}
	CmdLine::CmdLine(int argc, const char** argv, Parameters parms, bool sensitive, bool strict) {
		_commandLine = new NS2::CommandLine(argc, argv, parms, sensitive, strict);
	}
	CmdLine::~CmdLine() {
//		std::cout << "Destruye\n";
	}
	CmdLine* CmdLine::getInstance(Parameters parms, int argc,  const char**  argv) {
		NS1::instance = true;
		if (singleton_ == nullptr) singleton_ = new CmdLine(argc, argv, parms);
		return singleton_;
	}
	CmdLine* CmdLine::getInstance(int argc, const char** argv, Parameters parms) {
		NS1::instance = true;
		if (singleton_ == nullptr) singleton_ = new CmdLine(argc, argv, parms);
		return singleton_;
	}
	CmdLine* CmdLine::getInstance(int argc, char* argv[], Parameters parms) {
		return getInstance(argc, (const char**) argv, parms);
	}

	CmdLine* CmdLine::pGetInstance(int argc,  const char**  argv, Parameters parms, bool sensitive, bool strict) {
		NS1::instance = true;
		if (singleton_ == nullptr) singleton_ = new CmdLine(argc, argv, parms, sensitive, strict);
		return singleton_;
	}

	vector<const char*> CmdLine::args() { return _commandLine->getArgs(); }

	bool  CmdLine::hasFlag(const char* name) { return _commandLine->hasFlag(name); };
	bool  CmdLine::hasFlag(string name) { return _commandLine->hasFlag(name.c_str()); };
	Flags CmdLine::getDefaultFlags(bool all) { return _commandLine->getDefaultFlags(all); };
	Flags CmdLine::getCurrentFlags(bool all) { return _commandLine->getCurrentFlags(all); };
	Type            CmdLine::getType(const char* name) { return _commandLine->getType(name); };
	bool            CmdLine::hasOption(const char* name) { return _commandLine->hasOption(name); };
	bool            CmdLine::hasOption(string name) { return _commandLine->hasOption(name.c_str()); };
	bool            CmdLine::isOptionMultiple(const char* name) { return _commandLine->isOptionMultiple(name); };
	bool            CmdLine::isOptionMultiple(string name) { return _commandLine->isOptionMultiple(name.c_str()); };
	const char* CmdLine::getOption(const char* name) { return _commandLine->getOption(name); };

	vector<const char*>  CmdLine::getOptionValues(const char* name) { return _commandLine->getOptionValues(name); };
	vector<const char*>  CmdLine::getOptionValues(string name) { return getOptionValues(name.c_str()); };

	int         CmdLine::getOptionNumValues(const char* name) { return _commandLine->getOptionNumValues(name); };
	int         CmdLine::getOptionNumValues(string name) { return getOptionNumValues(name.c_str()); };
	unordered_map<string, string> CmdLine::getDefaultOptions() { return _commandLine->getDefaultOptions(); };
	Options     CmdLine::getCurrentOptions() { return _commandLine->getCurrentOptions(); };

	template <typename T> const vector<T> getOptionValuesAs(const char* name) {
		vector<T> res;
		vector<const char*> str = _commandLine->getOptionValues(name);
		res.reserve(str.size);
		for (const char* val : str) {
			res.push_back(castValue<T>(val));
		}
		return res;
	}
	bool        CmdLine::hasDefinition(const char* def) { return _commandLine->hasDefinition(def); }
	bool        CmdLine::hasDefinition(string def) { return hasDefinition(def.c_str()); }
	bool        CmdLine::isDefinitionMultiple(const char* name) { return _commandLine->isDefinitionMultiple(name); }
	bool        CmdLine::isDefinitionMultiple(string name) { return isDefinitionMultiple(name.c_str()); }
	const char* CmdLine::getDefinition(const char* name) { return _commandLine->getDefinition(name); }
	const char* CmdLine::getDefinition(string name) { return getDefinition(name.c_str()); }
	int         CmdLine::getDefinitionNumValues(const char* name) { return _commandLine->getDefinitionNumValues(name); }
	int         CmdLine::getDefinitionNumValues(string name) { return getDefinitionNumValues(name.c_str()); }
	Options     CmdLine::getDefinitions() { return _commandLine->getDefinitions(); }


	vector<const char*>  CmdLine::getDefinitionValues(const char* name) { return _commandLine->getDefinitionValues(name); }
	vector<const char*>  CmdLine::getDefinitionValues(string name) { return getDefinitionValues(name.c_str()); }
	/*
	template <typename T> T CmdLine::castByNative(const char* value) {
		if constexpr (is_same<T, const char*>::value)      return value;
		if constexpr (is_same<T, char*>::value)            return (char*)value;

		if constexpr (is_same<T, TYPE_STRING>::value)       return string(value);
		if constexpr (is_same<T, TYPE_NUMBER>::value)       return NS2::validateNumber(value);
		if constexpr (is_same<T, TYPE_LONG>::value)         return NS2::validateNumber(value);
		if constexpr (is_same<T, TYPE_INT>::value)          return NS2::makeInteger(value);
		if constexpr (is_same<T, TYPE_DECIMAL>::value)      return NS2::validateDecimal(value);
		if constexpr (is_same<T, TYPE_FLOAT>::value)        return NS2::makeFloat(value);
		if constexpr (is_same<T, TYPE_DOUBLE>::value)       return NS2::validateDecimal(value);
		if constexpr (is_same<T, TYPE_DATE>::value)         return NS2::makeTm(value);
		if constexpr (is_same<T, TYPE_TIME>::value)         return NS2::makeTm(value);
		if constexpr (is_same<T, TYPE_DATETIME>::value)     return NS2::makeTm(value);
		if constexpr (is_same<T, TYPE_TMS>::value)          return NS2::validateTimestamp(value);
		if constexpr (is_same<T, TYPE_LONGNUMBER>::value)   return NS2::validateLongNumber(value);
		if constexpr (is_same<T, TYPE_LONGDECIMAL>::value)  return NS2::validateLongDecimal(value);
		if constexpr (is_same<T, TYPE_DIR>::value)          return NS2::validateFile(value);
		if constexpr (is_same<T, TYPE_FILE>::value)         return NS2::validateDir(value);
		if constexpr (is_same<T, TYPE_BOOL>::value) {
			if (value == 0x0) return false;
			return NS2::makeBoolean(value);
		}
		throw NS1InvalidTypeException(typeid(T).name());
	}
	*/
}