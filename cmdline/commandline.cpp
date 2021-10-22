#include <vector>
#include <string>
#include <utility>
#include <algorithm>

#include "parmitem.hpp"
#include "commandline.hpp"
#include "cmdline_exceptions.hpp"
#include "parameter_tree.hpp"
#include "tools.h"
#include "validations.h"


namespace cmdline {
	cmdline::ParameterTree* rootOptions[128];
	cmdline::ParameterTree* rootFlags[128];

	CommandLine::CommandLine(std::vector<ParmItem> parms) {
		bool value;
		std::fill_n(rootOptions, sizeof(rootOptions), nullptr);
		std::fill_n(rootFlags, sizeof(rootFlags), nullptr);
		for (ParmItem p : parms) {
			if (p.type == FLAG) {
				value = (p.value[0] == '1') ? true : false;
				defFlags.insert_or_assign(std::string(p.name), value);
				add2tree(rootFlags, p.name);
			}
			else {
				defOptions.insert_or_assign(std::string(p.name), p);
				add2tree(rootOptions, p.name);
			}
		}
		if (defFlags.find("help") == defFlags.end()) add2tree(rootFlags, "help");
	};

	CommandLine::CommandLine(std::vector<cmdline::ParmItem> options, std::vector<std::pair<char *, bool>> flags) {
		this->defOptions = vector2map(options);
		for (std::pair f : flags) defFlags.insert_or_assign(f.first, f.second);
		for (size_t i = 0; i <  options.size(); i++) add2tree(rootOptions, options[i].name);
		add2tree(rootFlags, "help");
	};

	CommandLine::~CommandLine() {
		for (int i = 0; i < 128; i++) {
			if (rootOptions[i] != nullptr) free(rootOptions[i]);
			if (rootFlags[i] != nullptr) free(rootFlags[i]);
		}
	}
	CommandLine& CommandLine::parse(const int argc, char* argv[]) {
		std::string in;
		char* prev = nullptr;
		for (int i = 1; i < argc; i++) {
			switch (argv[i][0]) {
			case '/': prev = addParameterToOptions(argv[i], prev); break;
			case '+': if (prev != nullptr) throw CmdLineException("Missing value", prev);
				prev = addParameterToFlags(argv[i], argv[i]);   break;
			case '-': in = argv[i]; 
				      if (in == std::string("-h") || in ==  std::string("--help"))  
				          prev = addParameterToFlags((char *) "+help", prev);
					  else 
				         prev = removeParameterFromFlags(argv[i], prev);
				      break;   
			default:
				if (prev == NULL) {
					addParameterToInput(argv[i]);
				}
				else {
					addValueToOption(argv[i], prev);
				}
			}
		}
		if (hasFlag("help")) throw HelpRequested();
		return *this;
	}
	std::map<std::string, bool>          CommandLine::getCurrentFlags(bool active) {
		std::map<std::string, bool> flg;

		for (std::string flag : flags) flg.emplace(std::string(flag), true);
		if (!active) flg.insert(defFlags.begin(), defFlags.end());
		return flg;
	}
	std::map<std::string, void *>          CommandLine::getCurrentOptions(bool all) {
		std::map<std::string, void*> opts = options;
		if (all) {
			std::map<std::string, void*> nopts;
			for (const std::pair<std::string, ParmItem> &parm : defOptions) {
				if (parm.second.value != nullptr) nopts.emplace(std::string(parm.first), (void *) strdup(parm.second.value));
			}
			opts.merge(nopts);
		}
		return opts;
	}

	char*        CommandLine::checkOption(char* option) { return (checkParameter(rootOptions, option)); }
	char*        CommandLine::checkFlag(char* flag)     { return (checkParameter(rootFlags, flag));    }
	char*        CommandLine::addParameterToOptions(char* option, char* prev) {
		validateEntry(option, prev);
		return (checkOption(&(option[1])));
	}
	char*        CommandLine::addParameterToFlags(char* flag, char* prev) {
		std::string name;
		validateEntry(flag, prev);
		try {
			name = checkFlag(&(flag[1]));
			flags.emplace(name);
		}
		catch (CmdLineException ex) {
			char newFlag[3] = "+ ";
			if (strlen(flag) == 2) throw;
			for (size_t i = 1; i < strlen(flag); i++) {
				newFlag[1] = flag[i];
				addParameterToFlags(newFlag, prev);
			}
		}
		
		flags.emplace(name);
		return (nullptr);
	}
	char*        CommandLine::removeParameterFromFlags(char* flag, char* prev) {
		std::string name;
		validateEntry(flag, prev);
		
		try {
			name = checkFlag(&(flag[1]));
			flags.erase(name);
		}
		catch (CmdLineException ex) {
			char newFlag[3] = "- ";
			if (strlen(flag) == 2) throw;
			for (size_t i = 1; i < strlen(flag); i++) {
				newFlag[1] = flag[i];
				removeParameterFromFlags(newFlag, prev);
			}
		}
		return (nullptr);
	}
	inline char* CommandLine::addParameterToInput(char* input) {
		inputs.push_back(input);
		return (nullptr);
	}
	char*        CommandLine::addValueToOption(char* value, char* option) {
		ParmItem def = defOptions.find(option)->second;
		validateValue(value, def.type);

		if (strlen(option) == 1) throw CmdLineException("Invalid Option", option);
		return (checkOption(&(option[1])));
	}
	std::map<std::string, char*>  CommandLine::getDefaultOptions() {
		std::map<std::string, char *> defs;
		for (std::map<std::string, ParmItem>::iterator it = defOptions.begin(); it != defOptions.end(); it++) {
			std::cout << it->first << std::endl;
			//				 defs.insert(it->second.name, it->second.value);
		}
		return defs;
	}
	bool                    CommandLine::hasFlag(char* flag) { 
		if (flags.find(flag) != flags.end()) return true;
		std::map<std::string, bool>::iterator it = defFlags.find(flag);
		return (it == defFlags.end()) ? false : true;
	}
	char*        CommandLine::checkParameter(ParameterTree* root[], char* parm) {
		size_t idx = 0;
		ParameterTree* base = root[parm[0] - ' '];
		ParameterTree* prev = nullptr;
		//while (base != nullptr && base->letter == parm[idx]) {
		while (idx < strlen(parm) && base != nullptr) {
			prev = base;
			if (base->letter == parm[idx]) { //  && (idx + 1) < strlen(parm)) {
				base = base->getChild(parm[++idx]);
			}
			else {
				break;
			}
		}

		std::string str;
		if (idx == strlen(parm)) { // Parse completo
			switch (prev->numChildren()) {
			        case 0: return (parm);
					case 1: str = parm;
						str.append(prev->getNext()->getWord());
						return (makeChar(str));
					default: throw CmdLineParameterException(parm);
			}
		}
		if (prev == nullptr) throw CmdLineException(parm);  // primero
		// parm > parameter
		if (base == nullptr) throw CmdLineParameterException(parm, prev->getReversedWord());
		
		// Ha salido por base = nullptr
		
		if (prev->branchs > 1) throw CmdLineException("No definido con alternativa 2", "varias alernativa");
		if (prev->branchs == 1) throw CmdLineException("No definido con alternativa 1", "tipo");
		std::string ss(parm);
		ss.append(base->getWord());
		return (makeChar(ss));
	}

//	template <typename T>  T  CommandLine::getOption(char* name)          {
//	}
	

}
