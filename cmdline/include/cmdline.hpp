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
//	    typedef pair<string, bool>               Flag;
	    typedef unordered_map<string, string>    Options;
	    //typedef pair<string, string>             Option;
//	    typedef unordered_map<string, vector<string>> Definitions;
		class Parm {
		public:
			const char* name;              // Name of parameter
			Type type = Type::STRING;  // Type
			const char* value;   // default value
			bool multiple;   // Allow multiple values?
			Parm() = delete;
			Parm(const char* name) {
				this->name = name;
				this->value = "true";
				this->type = Type::BOOL;
				this->multiple = false;
				this->instance = 2;
			}
			Parm(const char* name, const char* value) {
				this->name = name;
				this->value = value;
				this->multiple = false;
				this->instance = 1;
			}
			Parm(const char* name, const char* value, Type type, bool multiple = false) {
				this->name = name;
				this->value = value;
				this->type = type;
				this->multiple = multiple;
				this->instance = 1;
			}
			Parm(const char* name, bool value) {
				this->name = name;
				this->value = (char*)((value) ? "1" : "0");
				this->type = Type::BOOL;
				this->multiple = false;
				this->instance = 2;
			}
			bool instanceOfFlag()   { return instance == 2; }
			bool instanceOfOption() { return instance == 1; }
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
		static CmdLine GetInstance(int argc, char *argv[], Parameters parms = Parameters());
		static CmdLine GetInstance(Parameters parms, int argc, char* argv[]);
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
		template <typename T>  
		const T       getOption         (const char* name);
		template <typename T>  
		const T       getOption         (string name);
		template <typename T>
		vector<T>     getOptionValues   (const char* name);

		const string  getOption         (const char* name);
		Options       getDefaultOptions ();
		Options       getCurrentOptions ();

		bool  hasDefinition(const char* def);
//		const cmdline::Flag  getFlag(const char* name);// { return commandLine->getFlag(name); }
//		const cmdline::Flag  getFlag(string name);//      { return commandLine->getFlag(name.c_str()); };

//		bool            hasDefinition    (const char*def);//   { return (commandLine->hasDefinition(def)); };

		template <typename T>  const T  getDefinition(const char* name);// { return (commandLine->getDefinition<T>(name)); };
		const string  getDefinition(const char* name);// { return (commandLine->getDefinition2(name)); };
		const vector<string>  getVectorDefinition(const char* name);// { return (commandLine->getVectorDefinition(name)); };
	protected:
		static CmdLine GetInstance(int argc, char* argv[], Parameters parms, bool forward, bool strict);
	private:
		CmdLine(int argc, char* argv[], Parameters parms, bool forward = false, bool strict = false);
	};
	class CmdLineI : public CmdLine {
		
	public: 
		~CmdLineI();
		CmdLineI& GetInstance(int argc, char* argv[], Parameters parms);
	};
	class CmdLineS : public CmdLine {
	public:
		CmdLineS& GetInstance(int argc, char* argv[], Parameters parms);
	};
	class CmdLineIS : public CmdLineI {
	public:
		~CmdLineIS();
		CmdLineIS& GetInstance(int argc, char* argv[], Parameters parms);

	};
	class CmdLineI_forward : public CmdLine {

	};
	class CmdLineS_forward : public CmdLine {

	};
	class CmdLineIS_forward : public CmdLine {

	};



}
