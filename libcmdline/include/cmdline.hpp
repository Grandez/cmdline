#pragma once

#include <vector>

// #include <iostream>
#include "types.hpp"

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
		ParmOption(const char* name, const char* value, Type type, bool multiple = false) : Parm(name, value, type, multiple) {};
	};
	typedef std::vector<Parm>                 Parameters;

	class CmdLine {
	public:
		CmdLine(); 
		~CmdLine(); 
		// Arguments
		vector<const char*> args();

		// Flags control
		bool  hasFlag(const char* name);
		bool  hasFlag(string name);
		Flags getDefaultFlags(bool all = true);
		Flags getCurrentFlags(bool all = true);

		// Options control
		bool                 hasOption(const char* name);
		bool                 hasOption(string name);
		bool                 isOptionMultiple(const char* name);
		bool                 isOptionMultiple(string name);
		const char* getOption(const char* name);
		const char* getOption(string name) { return getOption(name.c_str()); }
		vector<const char*>  getOptionValues(const char* name);
		vector<const char*>  getOptionValues(string name);

		int       getOptionNumValues(const char* name);
		int       getOptionNumValues(string name);
		Options   getDefaultOptions();
		Options   getCurrentOptions();

		template <typename T> const T         getOptionAs(T t, const char* name) {
			return getOptionAs<T>(name);
		}
		template <typename T> const T         getOptionAs(const char* name) {
			const char* value = getOption(name);
			return castByNative<T>(value);
		}
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
		bool        hasDefinition(const char* def);
		bool        hasDefinition(string def);
		bool        isDefinitionMultiple(const char* name);
		bool        isDefinitionMultiple(string name);
		const char* getDefinition(const char* name);
		const char* getDefinition(string name);

		vector<const char*>  getDefinitionValues(const char* name);
		vector<const char*>  getDefinitionValues(string name);

	private:
		template <typename T> T castByNative(const char* value);
	};
}
