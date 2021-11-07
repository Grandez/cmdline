#pragma once

#include <vector>
#include "types.hpp"
#include "validations.hpp"
#include "cmdline_exceptions.hpp"

#ifndef __CLASS_CMDLINE__
#define __CLASS_CMDLINE__

#ifdef _WIN32
#pragma warning( disable : 4244)
#endif

namespace cmdline {
	/**
	 * Generic Class to define defined flags and options
	 *
	 * A parm has 4 properties:
	 * \property name Name of parameter
	 * \property value Default value for the parameter
	 * \property type Type of parameter according Type enum
	 * \property multiple Parameter supports multiple values?
	 * 
	 * Parm(const char* name) : Default for Flag
	 * Parm(const char* name, const char* value): Default for option
	 * Parm(const char* name, bool value) : Define Flag with false or true
     * Parm(const char* name, const char* value, Type type, bool multiple = false) : Detailed definition
	 *
	 */
	class Parm {
	public:
		const char* name;              // Name of parameter
		Type type = Type::STRING;  // Type
		char* value;   // default value
		bool multiple = false;   // Allow multiple values?
		Parm() = delete ; // { name = nullptr; } // default
		Parm(const char* name);
		Parm(const char* name, const char* value);
		Parm(const char* name, const char* value, Type type, bool multiple = false);
		Parm(const char* name, bool value);
		bool instanceOfFlag();
		bool instanceOfOption();
	private:
		int instance = 0;

	};
	/**
	 * Utility subclass for defining Flags
	 *
	 * Parm(const char* name) : Name,false
	 * Parm(const char* name, const char* value): name/value (false/true)
	 *
	 */
	class ParmFlag : public Parm {
	public:
		ParmFlag() = delete;
		ParmFlag(const char* name) : Parm(name, true) {};
		ParmFlag(const char* name, bool active) : Parm(name, active) {};
	};
	/**
	 * Utility subclass for defining Options
	 *
	 * Parm(const char* name, const char* value): name/value (false/true)
	 *
	 */
	class ParmOption : public Parm {
	public:
		ParmOption() = delete;
		ParmOption(const char* name, const char* value) : Parm(name, value) {};
		ParmOption(const char* name, Type type) : Parm(name, NULL, type) {}
		ParmOption(const char* name, const char* value, bool multiple) : Parm(name, value, Type::STRING, multiple) {};
		ParmOption(const char* name, Type type, bool multiple) : Parm(name, NULL, type, multiple) {};
		ParmOption(const char* name, const char* value, Type type,  bool multiple = false) : Parm(name, value, type, multiple) {};
	};
	typedef std::vector<Parm>                 Parameters;
	class CmdLine {
	public:
		CmdLine() {};
		CmdLine(int argc, const char **argv, Parameters parms); 
		~CmdLine(); 
//		static CmdLine *getInstance(int argc, char** argv, Parameters parms = Parameters());
		static CmdLine *getInstance(int argc, char* argv[], Parameters parms = Parameters());
//		static CmdLine *getInstance(int argc, const char* argv[], Parameters parms = Parameters());
		static CmdLine *getInstance(int argc, const char** argv, Parameters parms = Parameters());
		static CmdLine *getInstance(Parameters parms, int argc, const char** argv);
		static void freeInstance();  // Just for test
		// Arguments
		vector<const char*> args();

		// Flags control
		bool  hasFlag(const char* name);
		bool  hasFlag(string name);
		Flags getDefaultFlags(bool all = true);
		Flags getCurrentFlags(bool all = true);

		// Options control
		Type                 getType(const char* name); 
		bool                 hasOption(const char* name);
		bool                 hasOption(string name);
		bool                 isOptionMultiple(const char* name);
		bool                 isOptionMultiple(string name);
		const char*          getOption(const char* name);
		const char*          getOption(string name) { return getOption(name.c_str()); }
		vector<const char*>  getOptionValues(const char* name);
		vector<const char*>  getOptionValues(string name);

		int       getOptionNumValues(const char* name);
		int       getOptionNumValues(string name);
		unordered_map<string,string>   getDefaultOptions();
		Options   getCurrentOptions();
		/*
		template <typename T> const T         getOptionAs(T t, const char* name) {
			return getOptionAs<T>(name);
		}*/
		template <typename T> T         getOptionAs(const char* name);
		/*
		{
			const char* value = getOption(name);
			return castByNative<T>(value);
		}
		*/
		template <typename T> const T         getOptionAs(string name) { return getOptionAs<T>(name.c_str()); }
		template <typename T> const vector<T> getOptionValuesAs(string name) { return getOptionValuesAs<T>(name.c_str()); };
		template <typename T> const vector<T> getOptionValuesAs(const char* name);
		/*
		template <typename T> const vector<T> getOptionValuesAs(const char* name) {
			vector<T> res;
			vector<const char*> str = _commandLine.getOptionValues(name);
			res.reserve(str.size);
			for (const char* val : str) {
				res.push_back(castValue<T>(val));
			}
			return res;
		}
		*/
// Definitions
		bool                 hasDefinition(const char* def);
		bool                 hasDefinition(string def);
		bool                 isDefinitionMultiple(const char* name);
		bool                 isDefinitionMultiple(string name);
		const char*          getDefinition(const char* name);
		const char*          getDefinition(string name);
		Options              getDefinitions();
		int                  getDefinitionNumValues(const char* name);
		int                  getDefinitionNumValues(string name);
		vector<const char*>  getDefinitionValues(const char* name);
		vector<const char*>  getDefinitionValues(string name);
	protected:
		static CmdLine *pGetInstance(int argc, const char** argv, Parameters parms, bool sensitive = false, bool strict = false);
		CmdLine(int argc, const char** argv, Parameters parms, bool sensitive, bool strict);
		CmdLine(int argc, const char **argv, Parameters parms, bool sensitive);
	};
	class CmdLineI : public CmdLine {
	public:
		CmdLineI(int argc, const char** argv, Parameters parms);
		CmdLineI(int argc, const char** argv, cmdline::Parameters parms, bool strict);
		static CmdLine* getInstance(int argc, const char** argv, Parameters parms);
		~CmdLineI();
	};
	class CmdLineS : public CmdLine {
	public:
		CmdLineS(int argc, const char** argv, Parameters parms);
		static CmdLine* getInstance(int argc, const char** argv, Parameters parms);
	};
	class CmdLineIS : public CmdLineI {
	public:
		CmdLineIS(int argc, const char** argv, Parameters parms);
		~CmdLineIS();
		static CmdLine* getInstance(int argc, const char** argv, Parameters parms);
	};

}
#endif