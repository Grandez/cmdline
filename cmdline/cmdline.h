#pragma once
/**
 * @brief Interface of command line parser
 * I do not like expose private members into interfaz 
 * so, "the real code is in CommandLine class
 * 
 * # Process
 * 
 * 1. Instanciate **CmdLine** with options and flags
 * 2. Parse the command line. When errors or help and exception will be thrown
 * 3. Query and use options and flags
 * 
 */

#include <vector>
#include <string>
#include <set>
#include <utility>
#include "parmitem.hpp"
#include "commandline.hpp"
#include "cmdline_exceptions.hpp"

namespace cmdline {

	class CmdLine {
	public:
		CmdLine() = delete;
		CmdLine(std::vector<ParmItem> args)                                                { commandLine = new CommandLine(args); }
		CmdLine(std::vector<ParmItem> options, std::vector<std::pair<char *, bool>> flags) { commandLine = new CommandLine(options, flags); }
		~CmdLine()                                                                         { delete commandLine;  }

		CmdLine& parse(const int argc, char* argv[]) {
			commandLine->parse(argc, argv);
			return *this;
		}
		bool                         hasFlag(char* name)         { return (commandLine->hasFlag(name)); };
		bool                         hasFlag(const char* name)   { return (commandLine->hasFlag(name)); };
		std::map<std::string, char*> getDefaultOptions()         { return (commandLine->getDefaultOptions()); };
		std::map<std::string, bool>  getDefaultFlags()           { return (commandLine->getDefaultFlags()); };
		std::map<std::string, void*> getCurrentOptions(bool all = false)    { return (commandLine->getCurrentOptions(all)); }; 
		std::map<std::string, bool>  getCurrentFlags(bool set = true)       { return (commandLine->getCurrentFlags(set)); };

//		template <typename T>  T  getOption(char* name)       { return (commandLine->getOption<T>(name)); };
//		template <typename T>  T  getOption(std::string name) { return (commandLine->getOption<T>(name)); };

		std::string checkOption(char* parm) { return (commandLine->checkOption(parm)); }
		std::string checkFlag(char* parm)   { return (commandLine->checkFlag(parm)); }

	private:
		CommandLine* commandLine;
		
	};




 }


