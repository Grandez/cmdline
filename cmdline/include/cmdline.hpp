#pragma once
#include <vector>
#include <unordered_map>

#include "cmdline_exceptions.hpp"

using namespace std;
namespace cmdline_ { class CommandLine; } // Forward declaration

namespace cmdline {

	#ifndef __CMDLINE_TYPES__
        #define __CMDLINE_TYPES__
		enum class Type   { STRING, BOOL, NUMBER, DECIMAL, DATE, TIME, DATETIME, TMS, DIR, DIR_EXISTS, FILE, FILE_EXISTS };
		enum class Source { DEFAULT, ENV, CMDLINE, CODE, AUTO };

	    typedef unordered_map<string, bool>      Flags;
	    typedef unordered_map<string, string>    Options;
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
			ParmFlag(const char* name)              : Parm(name, true) {};
			ParmFlag(const char* name, bool active) : Parm(name, active) {};
		};
		class ParmOption : public Parm {
		public:
			ParmOption() = delete;
			ParmOption(const char* name, const char* value)                                   : Parm(name, value) {};
			ParmOption(const char* name, const char* value, Type type)                        : Parm(name, value, type) {};
			ParmOption(const char* name, const char* value, bool multiple)                    : Parm(name, value, Type::STRING, multiple) {};
			ParmOption(const char* name, const char* value, Type type, bool multiple = false) : Parm(name, value, type, multiple) {};
		};

		typedef vector<Parm>                 Parameters;
    #endif
	class CmdLine {
	public:
		static CmdLine GetInstance(int argc, const char *argv[], Parameters parms = Parameters());
		static CmdLine GetInstance(Parameters parms, int argc, const char* argv[]);
		/*
		CmdLine();
		CmdLine(vector<ParmItem> args);//                                      { commandLine = new CommandLine(args); }
		CmdLine(vector<ParmItem> options, vector<cmdline::Flag> flags);//  { commandLine = new CommandLine(options, flags); }
		CmdLine(vector<cmdline::Flag> flags, vector<ParmItem> options);// { commandLine = new CommandLine(options, flags); }
		// ~CmdLine();// { delete commandLine; }
		CmdLine& parse(const int argc, const char* argv[]);// { commandLine->parse(argc, argv); return *this; }
		*/
		// Flags control
		bool  hasFlag         (const char* name);
		bool  hasFlag         (string name);
		Flags getDefaultFlags (bool all = true);
		Flags getCurrentFlags (bool all = true);

		// Options control
		bool            hasOption        (const char* name);
		bool            hasOption        (string name);
		bool            isOptionMultiple (const char* name);
		bool            isOptionMultiple (string name);
		const char *    getOption        (const char* name);
		const char*     getOption        (string name);
		template <typename T>  
		const T         getOptionAs      (const char* name);
		template <typename T>
		const T         getOptionAs     (string name);
		vector<string>  getOptionValues (const char* name);
		vector<string>  getOptionValues (string name);
		template <typename T>
		const vector<T> getOptionValuesAs(string name);

		Options         getDefaultOptions ();
		Options         getCurrentOptions ();

		// Definitions
		bool            hasDefinition(const char* def);
		bool            hasDefinition(string def);
		bool            isDefinitionMultiple(const char* name);
		bool            isDefinitionMultiple(string name);
		char*           getDefinition(const char* name);
		char*           getDefinition(string name);
		vector<string>  getDefinitionValues(const char* name);
		vector<string>  getDefinitionValues(string name);
		
/*
		template <typename T>  const T  getDefinition(const char* name);// { return (commandLine->getDefinition<T>(name)); };
		const string  getDefinition(const char* name);// { return (commandLine->getDefinition2(name)); };
		const vector<string>  getVectorDefinition(const char* name);// { return (commandLine->getVectorDefinition(name)); };
*/
	protected:
		static CmdLine GetInstance(int argc, const char* argv[], Parameters parms, bool forward, bool strict);
	private:
		CmdLine(int argc, const char* argv[], Parameters parms, bool forward = false, bool strict = false);
	};
	class CmdLineI : public CmdLine {
		
	public: 
		~CmdLineI();
		CmdLineI& GetInstance(int argc, const char* argv[], Parameters parms);
	};
	class CmdLineS : public CmdLine {
	public:
		CmdLineS& GetInstance(int argc, const char* argv[], Parameters parms);
	};
	class CmdLineIS : public CmdLineI {
	public:
		~CmdLineIS();
		CmdLineIS& GetInstance(int argc, const char* argv[], Parameters parms);

	};
	class CmdLineI_forward : public CmdLine {

	};
	class CmdLineS_forward : public CmdLine {

	};
	class CmdLineIS_forward : public CmdLine {

	};



}
