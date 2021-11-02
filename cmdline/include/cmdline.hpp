#pragma once
#pragma warning(disable : 4390  4244)

#include <string>
#include <vector>
#include <unordered_map>
#include <filesystem>
#include "cmdline_exceptions.hpp"
#include "validations.h"
#include "types.h"

using namespace std;
namespace _cmdline { 
	class _CommandLine; 
	class Argument;
} // Forward declaration

namespace cmdline {
	class Parm {
	public:
		const char* name;              // Name of parameter
		Type type = Type::STRING;  // Type
		char* value;   // default value
		bool multiple;   // Allow multiple values?
		Parm() = delete;
		Parm(const char* name);
		Parm(const char* name, const char* value);
		Parm(const char* name, const char* value, Type type, bool multiple = false);
		Parm(const char* name, bool value);
		bool instanceOfFlag();
		bool instanceOfOption();
	private:
		int instance = 0;

	};

	class ParmFlag : public Parm {
	public:
		ParmFlag() = delete;
		ParmFlag(const char* name) : Parm(name, true) {};
		ParmFlag(const char* name, bool active) : Parm(name, active) {};
	};
	class ParmOption : public Parm {
	public:
		ParmOption() = delete;
		ParmOption(const char* name, const char* value) : Parm(name, value) {};
		ParmOption(const char* name, const char* value, bool multiple) : Parm(name, value, Type::STRING, multiple) {};
		ParmOption(const char* name, const char* value, Type type, bool multiple = false) : Parm(name, value, type, multiple) {};
	};
	typedef vector<Parm>                 Parameters;
	class CmdLine {
	public:
		CmdLine() {};
		static CmdLine getInstance(int argc, char** argv, Parameters parms = Parameters());
		static CmdLine getInstance(Parameters parms, int argc, char** argv);
		static void    freeInstance(); // For tests ONLY
		vector<const char*> args();
		// Flags control
		bool  hasFlag(const char* name);
		bool  hasFlag(string name);
		Flags getDefaultFlags(bool all = true);
		Flags getCurrentFlags(bool all = true);

		// Options control
		bool            hasOption(const char* name);
		bool            hasOption(string name);
		bool            isOptionMultiple(const char* name);
		bool            isOptionMultiple(string name);
		const char* getOption(const char* name);
		const char* getOption(string name);

		template <typename T>
		const T         getOptionAs(const char* name) {
			const char* value = getOption(name);
			return castValue<T>(value);
			//			_cmdline::castValue2<T>(value);
			//			_cmdline::Argument& opt = _commandLine->find(&options, name);
			//			
			//			return T(value);
						// return _commandLine->getOptionAs<T>(name); 
		}
		template <typename T>
		const T         getOptionAs(string name);
		vector<const char*>  getOptionValues(const char* name);
		vector<const char*>  getOptionValues(string name);

		int             getOptionNumValues(const char* name);
		int             getOptionNumValues(string name);

		template <typename T>
		const vector<T> getOptionValuesAs(string name);

		Options         getDefaultOptions();
		Options         getCurrentOptions();

		// Definitions
		bool            hasDefinition(const char* def);
		bool            hasDefinition(string def);
		bool            isDefinitionMultiple(const char* name);
		bool            isDefinitionMultiple(string name);
		const char* getDefinition(const char* name);
		const char* getDefinition(string name);

		vector<const char*>  getDefinitionValues(const char* name);
		vector<const char*>  getDefinitionValues(string name);
	protected:
		static CmdLine pGetInstance(int argc, char** argv, Parameters parms, bool sensitive = false, bool strict = false);
	private:
		_cmdline::_CommandLine* _commandLine;
		CmdLine(int argc, char** argv, Parameters parms, bool sensitive, bool strict);
		CmdLine(int argc, char** argv, Parameters parms);
		template <typename T>
		T castValue(const char* value) {
			if constexpr (is_same<T, const char*>::value)      return value;
			if constexpr (is_same<T, char*>::value)            return (char*)value;

			if constexpr (is_same<T, CMD_STRING>::value)       return string(value);
			if constexpr (is_same<T, CMD_NUMBER>::value)       return _cmdline::validateNumber(value);
			if constexpr (is_same<T, CMD_LONG>::value)         return _cmdline::validateNumber(value);
			if constexpr (is_same<T, CMD_INT>::value)          return _cmdline::makeInteger(value);
			if constexpr (is_same<T, CMD_DECIMAL>::value)      return _cmdline::validateDecimal(value);
			if constexpr (is_same<T, CMD_FLOAT>::value)        return _cmdline::makeFloat(value);
			if constexpr (is_same<T, CMD_DOUBLE>::value)       return _cmdline::validateDecimal(value);
			if constexpr (is_same<T, CMD_DATE>::value)         return _cmdline::makeTm(value);
			if constexpr (is_same<T, CMD_TIME>::value)         return _cmdline::makeTm(value);
			if constexpr (is_same<T, CMD_DATETIME>::value)     return _cmdline::makeTm(value);
			if constexpr (is_same<T, CMD_TMS>::value)          return _cmdline::validateTimestamp(value);
			if constexpr (is_same<T, CMD_LONGNUMBER>::value)   return _cmdline::validateLongNumber(value);
			if constexpr (is_same<T, CMD_LONGDECIMAL>::value)  return _cmdline::validateLongDecimal(value);
			if constexpr (is_same<T, CMD_DIR>::value)          return _cmdline::validateFile(value);
			if constexpr (is_same<T, CMD_FILE>::value)         return _cmdline::validateDir(value);
			throw CmdLineInvalidTypeException(typeid(T).name());
		}
	};
	class CmdLineI : public CmdLine {
	public:
		static CmdLine getInstance(int argc, char** argv, Parameters);
		~CmdLineI();
	};
	class CmdLineS : public CmdLine {
	public:
		static CmdLine getInstance(int argc, char** argv, Parameters parms);
	};
	class CmdLineIS : public CmdLineI {
	public:
		~CmdLineIS();
		static CmdLine getInstance(int argc, char** argv, Parameters parms);
	};
}
