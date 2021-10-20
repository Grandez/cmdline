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

namespace cmdline {

	class CmdLine {
	public:
		CmdLine() = delete;
		CmdLine(std::vector<ParmItem> args)                                                { commandLine = new CommandLine(args); }
		CmdLine(std::vector<ParmItem> options, std::vector<std::pair<char *, bool>> flags) { commandLine = new CommandLine(options, flags); }

		int parse(const int argc, char* argv[]) { return (commandLine->parse(argc, argv)); }
		bool                   hasFlag(char* name)         { return (commandLine->hasFlag(name)); };
		std::map<char*, char*> getDefaultOptions()         { return (commandLine->getDefaultOptions()); };
		std::set<std::string>  getCurrentFlags()           { return (commandLine->getCurrentFlags()); };
		std::map<char*, char*> getCurrentOptions()         { return (commandLine->getCurrentOptions()); };
		template <typename T>  T  getOption(char* name)       { return (commandLine->getOption<T>(name)); };
		template <typename T>  T  getOption(std::string name) { return (commandLine->getOption<T>(name)); };

		std::map<std::string, bool>  getDefaultFlags() { return (commandLine->getDefaultFlags()); };

		std::string checkOption(char* parm) { return (commandLine->checkOption(parm)); }
		std::string checkFlag(char* parm)   { return (commandLine->checkFlag(parm)); }

	private:
		CommandLine* commandLine;
		
	};




 }


