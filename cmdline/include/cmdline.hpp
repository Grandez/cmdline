#pragma once
#pragma warning(disable : 4390  4244)
/*
#include <string>
#include <vector>
#include <unordered_map>
#include <filesystem>
#include "cmdline_exceptions.hpp"
#include "validations.h"
#include <any>
*/
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
		Parm() { name = nullptr; } // default
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
		ParmOption(const char* name, Type type)         : Parm(name, NULL, type) {}
		ParmOption(const char* name, const char* value, bool multiple) : Parm(name, value, Type::STRING, multiple) {};
		ParmOption(const char* name, const char* value, Type type, bool multiple = false) : Parm(name, value, type, multiple) {};
	};
	typedef vector<Parm>                 Parameters;
	class CmdLine {
	public:
		CmdLine()                 { _commandLine = nullptr; };
		CmdLine(int argc, char** argv, Parameters parms, bool sensitive = false, bool strict = false);
		static CmdLine getInstance(int argc, char** argv, Parameters parms = Parameters());
		static CmdLine getInstance(Parameters parms, int argc, char** argv);
		static void    freeInstance(); // For tests ONLY
		// Arguments
		vector<const char*> args();

		// Flags control
		bool  hasFlag(const char* name);
		bool  hasFlag(string name);
		Flags getDefaultFlags(bool all = true);
		Flags getCurrentFlags(bool all = true);

		// Options control
		bool                 hasOption        (const char* name);
		bool                 hasOption        (string name);
		bool                 isOptionMultiple (const char* name);
		bool                 isOptionMultiple (string name);
		const char*          getOption        (const char* name);
		const char*          getOption        (string name)          { return getOption(name.c_str()); }
		vector<const char*>  getOptionValues  (const char* name);
		vector<const char*>  getOptionValues  (string name);

		int       getOptionNumValues (const char* name);
		int       getOptionNumValues (string name);
		Options   getDefaultOptions  ();
		Options   getCurrentOptions  ();

		template <typename T> const T         getOptionAs(T t, const char* name) {
			return getOptionAs<T>(name);
/*
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
*/
		}
		template <typename T> const T         getOptionFromType(Type t, const char* name) {
			switch (t) {
			case Type::STRING: return getOptionAs<string>(name);
			case Type::CHAR: return getOptionAs<const char*>(name);
			case Type::BOOL: return getOptionAs<bool>(name);
			case Type::NUMBER: return getOptionAs<long>(name);
			};
			throw CmdLineInvalidTypeException("nada");
		}
		/*
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
		*/
		template <typename T> const T         getOptionAs(const char* name) {
			const char* value = getOption(name);
			return castByNative<T>(value);
		}
		template <typename T> const T         getOptionAs(string name)      { return getOptionAs<T>(name.c_str()); }
		template <typename T> const vector<T> getOptionValuesAs(string name) { return getOptionValuesAs<T>(name.c_str()); };
		template <typename T> const vector<T> getOptionValuesAs(const char* name) {
			vector<T> res;
			vector<const char *> str = _commandLine.getOptionValues(name);
			res.reserve(str.size);
			for (const char* val : str) {
				res.push_back(castValue<T>(val));
			}
			return res;
		}

		// Definitions
		bool        hasDefinition(const char* def);
		bool        hasDefinition(string def);
		bool        isDefinitionMultiple(const char* name);
		bool        isDefinitionMultiple(string name);
		const char* getDefinition(const char* name);
		const char* getDefinition(string name);

		vector<const char*>  getDefinitionValues(const char* name);
		vector<const char*>  getDefinitionValues(string name);
	protected:
		static CmdLine pGetInstance(int argc, char** argv, Parameters parms, bool sensitive = false, bool strict = false);
//		CmdLine(int argc, char** argv, Parameters parms, bool sensitive = false, bool strict = false);
	private:
		_cmdline::_CommandLine* _commandLine;
//		CmdLine(int argc, char** argv, Parameters parms, bool sensitive, bool strict);
//		CmdLine(int argc, char** argv, Parameters parms);
		template <typename T> T castValue(const char* value) {
			if constexpr (is_same<T, cmdline::Type>::value) return castByType<T>(value);
			return castByNative<T>(value);
		}
		template <typename T> T castByNative(const char *value) {
			if constexpr (is_same<T, const char*>::value)      return value;
			if constexpr (is_same<T, char*>::value)            return (char *) value;

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
		auto castValueType(Type t, const char* value) {
			if (t == Type::STRING) return string(value);
			/*
			if constexpr (is_same<t, Type::STRING>::value)       return string(value);
			if constexpr (is_same<T, Type::CHAR>::value)         return value;
			if constexpr (is_same<T, Type::NUMBER>::value)       return _cmdline::validateNumber(value);
			if constexpr (is_same<T, Type::DECIMAL>::value)      return _cmdline::validateDecimal(value);
			if constexpr (is_same<T, Type::DATE>::value)         return _cmdline::makeTm(value);
			if constexpr (is_same<T, Type::TIME>::value)         return _cmdline::makeTm(value);
			if constexpr (is_same<T, Type::DATETIME>::value)     return _cmdline::makeTm(value);
			if constexpr (is_same<T, Type::TMS>::value)          return _cmdline::validateTimestamp(value);
			if constexpr (is_same<T, Type::LONGNUMBER>::value)   return _cmdline::validateLongNumber(value);
			if constexpr (is_same<T, Type::LONGDECIMAL>::value)  return _cmdline::validateLongDecimal(value);
			if constexpr (is_same<T, Type::DIR>::value)          return _cmdline::validateFile(value);
			if constexpr (is_same<T, Type::FILE>::value)         return _cmdline::validateDir(value);
			if constexpr (is_same<T, Type::DIR_EXISTS>::value)   return _cmdline::validateFile(value);
			if constexpr (is_same<T, Type::FILE_EXISTS>::value)  return _cmdline::validateDir(value);
			*/
			throw CmdLineInvalidTypeException("Nda"); // typeid(T).name());
		}
	};
	class CmdLineI : public CmdLine {
	public:
		CmdLineI(int argc, char** argv, Parameters parms);
		CmdLineI(int argc, char** argv, cmdline::Parameters parms, bool strict);
		static CmdLine getInstance(int argc, char** argv, Parameters parms);
		~CmdLineI();
	};
	class CmdLineS : public CmdLine {
	public:
		CmdLineS(int argc, char** argv, Parameters parms);
		static CmdLine getInstance(int argc, char** argv, Parameters parms);
	};
	class CmdLineIS : public CmdLineI {
	public:
		CmdLineIS(int argc, char** argv, Parameters parms);
		~CmdLineIS();
		static CmdLine getInstance(int argc, char** argv, Parameters parms);
	};
}
