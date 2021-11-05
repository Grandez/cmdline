#include <iostream>

#include "cmdline.hpp"
#include "commandline.hpp"
#include "types.hpp"
#include "validations.hpp"
#include "tools.hpp"

using namespace _cmdline;

namespace cmdline {
	/*
	class CmdLineImpl {
	public:
		_cmdline::CommandLine* _commandLine = new _cmdline::CommandLine();
		CmdLineImpl() {
			engine_ = new _cmdline::CommandLine();
		}
		~CmdLineImpl() {
			std::cout << "Destructor de CmdLineImpl\n";
			delete engine_;
		}

	private:
		  _cmdline::CommandLine* engine_;
	};
	*/
	_cmdline::CommandLine* _commandLine;

	CmdLine::CmdLine(int argc, char** argv, Parameters parms) {
		std::cout << "Crea\n";
		_commandLine = new _cmdline::CommandLine(argc, argv, parms, false, false);
	}
	CmdLine::~CmdLine() {
		std::cout << "Destruye\n";
	}
	vector<const char*> CmdLine::args() { return _commandLine->getArgs(); }

	bool  CmdLine::hasFlag(const char* name) { return _commandLine->hasFlag(name); };
	bool  CmdLine::hasFlag(string name) { return _commandLine->hasFlag(name.c_str()); };
	Flags CmdLine::getDefaultFlags(bool all) { return _commandLine->getDefaultFlags(all); };
	Flags CmdLine::getCurrentFlags(bool all) { return _commandLine->getCurrentFlags(all); };

	bool            CmdLine::hasOption(const char* name) { return _commandLine->hasOption(name); };
	bool            CmdLine::hasOption(string name) { return _commandLine->hasOption(name.c_str()); };
	bool            CmdLine::isOptionMultiple(const char* name) { return _commandLine->isOptionMultiple(name); };
	bool            CmdLine::isOptionMultiple(string name) { return _commandLine->isOptionMultiple(name.c_str()); };
	const char* CmdLine::getOption(const char* name) { return _commandLine->getOption(name); };

	vector<const char*>  CmdLine::getOptionValues(const char* name) { return _commandLine->getOptionValues(name); };
	vector<const char*>  CmdLine::getOptionValues(string name) { return getOptionValues(name.c_str()); };

	int         CmdLine::getOptionNumValues(const char* name) { return _commandLine->getOptionNumValues(name); };
	int         CmdLine::getOptionNumValues(string name) { return getOptionNumValues(name.c_str()); };
	Options     CmdLine::getDefaultOptions() { return _commandLine->getDefaultOptions(); };
	Options     CmdLine::getCurrentOptions() { return _commandLine->getDefaultOptions(); };

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

	vector<const char*>  CmdLine::getDefinitionValues(const char* name) { return _commandLine->getDefinitionValues(name); }
	vector<const char*>  CmdLine::getDefinitionValues(string name) { return getDefinitionValues(name.c_str()); }
	
	template <typename T> T CmdLine::castByNative(const char* value) {
		if constexpr (is_same<T, const char*>::value)      return value;
		if constexpr (is_same<T, char*>::value)            return (char*)value;

		if constexpr (is_same<T, TYPE_STRING>::value)       return string(value);
		if constexpr (is_same<T, TYPE_NUMBER>::value)       return _cmdline::validateNumber(value);
		if constexpr (is_same<T, TYPE_LONG>::value)         return _cmdline::validateNumber(value);
		if constexpr (is_same<T, TYPE_INT>::value)          return _cmdline::makeInteger(value);
		if constexpr (is_same<T, TYPE_DECIMAL>::value)      return _cmdline::validateDecimal(value);
		if constexpr (is_same<T, TYPE_FLOAT>::value)        return _cmdline::makeFloat(value);
		if constexpr (is_same<T, TYPE_DOUBLE>::value)       return _cmdline::validateDecimal(value);
		if constexpr (is_same<T, TYPE_DATE>::value)         return _cmdline::makeTm(value);
		if constexpr (is_same<T, TYPE_TIME>::value)         return _cmdline::makeTm(value);
		if constexpr (is_same<T, TYPE_DATETIME>::value)     return _cmdline::makeTm(value);
		if constexpr (is_same<T, TYPE_TMS>::value)          return _cmdline::validateTimestamp(value);
		if constexpr (is_same<T, TYPE_LONGNUMBER>::value)   return _cmdline::validateLongNumber(value);
		if constexpr (is_same<T, TYPE_LONGDECIMAL>::value)  return _cmdline::validateLongDecimal(value);
		if constexpr (is_same<T, TYPE_DIR>::value)          return _cmdline::validateFile(value);
		if constexpr (is_same<T, TYPE_FILE>::value)         return _cmdline::validateDir(value);
		if constexpr (is_same<T, TYPE_BOOL>::value) {
			if (value == 0x0) return false;
			return _cmdline::makeBoolean(value);
		}
		throw CmdLineInvalidTypeException(typeid(T).name());
	}

}