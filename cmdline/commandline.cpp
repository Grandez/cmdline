#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <unordered_map>
#include <cstdlib>

#include "parmitem.hpp"
#include "commandline.hpp"
#include "cmdline_exceptions.hpp"
#include "parameter_tree.hpp"
#include "tools.h"
#include "validations.h"
#include "enums.h"
#include "option.hpp"

namespace cmdline {
	ParameterTree* rootOptions[128];
	ParameterTree* rootFlags[128];

	CommandLine::CommandLine(std::vector<ParmItem> parms) {
		std::fill_n(rootOptions, sizeof(rootOptions), nullptr);
		std::fill_n(rootFlags, sizeof(rootFlags), nullptr);
		loadDefaults(parms);
		loadEnv(options);
		loadEnv(flags);
		if (flags["help"].name.length() == 0) add2tree(rootFlags, "help");
	};
	CommandLine::CommandLine(std::vector<ParmItem> options, std::vector<std::pair<char *, bool>> flags) : CommandLine(options) {
		for (std::pair f : flags) this->flags.emplace(f.first, Option(f.first, f.second ? "1" : "0"));
		if (this->flags["help"].name.length() == 0) add2tree(rootFlags, "help");
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
				      prev = updateFlag(argv[i], argv[i], true);   break;
			case '-': in = argv[i]; 
				      if (in == std::string("-h") || in ==  std::string("--help"))  
				          prev = updateFlag((char *) "+help", prev, true);
					  else 
				         prev = updateFlag(argv[i], prev, false);
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
	std::unordered_map<std::string, std::string>  CommandLine::getDefaultOptions() {
		std::unordered_map<std::string, std::string> defs;
		std::unordered_map<std::string, ParmItem>::iterator it;
		for (it = defOptions.begin(); it != defOptions.end(); it++) {
			// defs.insert(it->second.name, it->second.value);
		}
		return defs;
	}
	std::unordered_map<std::string, bool>          CommandLine::getCurrentFlags(bool active) {
		std::unordered_map<std::string, bool> flg;
		/*
		for (std::string flag : flags) flg.emplace(std::string(flag), true);
		if (!active) flg.insert(defFlags.begin(), defFlags.end());
		return flg;
		*/
		return flg;
	}
	std::unordered_map<std::string, void*>          CommandLine::getCurrentOptions(bool all) {
		std::unordered_map<std::string, void*> opts; // = options;
		/*
		if (all) {
			std::map<std::string, void*> nopts;
			for (const std::pair<std::string, ParmItem>& parm : defOptions) {
				if (parm.second.value != nullptr) nopts.emplace(std::string(parm.first), (void*)strdup(parm.second.value));
			}
			opts.merge(nopts);
		}
		*/
		return opts;
	}

	/* *****************************************/
	/* Private 
	********************************************/
	char* CommandLine::addParameterToOptions(char* option, char* prev) {
		validateEntry(option, prev);
		return (checkOption(&(option[1])));
	}
	char *CommandLine::updateFlag(char* flag, char* prev, bool value) {
		char* ptr;
		ptr = strtok(flag, ",");
		while (ptr != nullptr) {
			updateFlagItem(ptr, prev, value);
			ptr = strtok(NULL, ",");
		}
		return nullptr;
	}
	void CommandLine::updateFlagItem(char* flag, char* prev, bool value) {
		std::string name;
		validateEntry(flag, prev);
		try {
     		Option* opt = findOption(&flags, checkFlag(&(flag[1])));
			opt->setValue(value);
		}
		catch (CmdLineException ex) {
			char newFlag[3] = "+ ";
			if (strlen(flag) == 2) throw;
			for (size_t i = 1; i < strlen(flag); i++) {
				newFlag[1] = flag[i];
				updateFlagItem(newFlag, prev, value);
			}
		}
	}
	inline char* CommandLine::addParameterToInput(char* input) {
		inputs.push_back(input);
		return (nullptr);
	}
	char* CommandLine::addValueToOption(char* value, char* option) {
		ParmItem def = defOptions.find(option)->second;
		validateValue(value, def.type);

		if (strlen(option) == 1) throw CmdLineException("Invalid Option", option);
		return (checkOption(&(option[1])));
	}
	char *CommandLine::checkOption(char* option) { return (checkParameter(rootOptions, option)); }
	char *CommandLine::checkFlag  (char* flag)   { return (checkParameter(rootFlags, flag)); }
	bool                    CommandLine::hasFlag(char* flag) {
		/*
		if (flags.find(flag) != flags.end()) return true;
		std::map<std::string, bool>::iterator it = defFlags.find(flag);
		return (it == defFlags.end()) ? false : true;
		*/
		return false;
	}
	char* CommandLine::checkParameter(ParameterTree* root[], char* parm) {
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
	void CommandLine::loadDefaults(std::vector<ParmItem> parms) {
		for (ParmItem p : parms) {
			Option option(p.name, p.value);
			std::unordered_map<std::string, Option>* map = (p.type == Type::FLAG) ? &flags : &options;
			ParameterTree** root = (p.type == Type::FLAG) ? rootFlags : rootOptions;
			map->insert_or_assign(p.name, option);
			add2tree(root, p.name);
		}
	}
	void CommandLine::loadEnv(std::unordered_map<std::string, Option> parms) {
		char* value;
		char key[255];
		const char *prfx;
		Option opt = options["env_preffix"];
		prfx = opt.name.c_str();
		std::unordered_map<std::string, Option>::iterator it;
		for (it = parms.begin(); it != parms.end(); it++) {
			sprintf(key, "%s_%s", prfx, it->second.name.c_str());
			value = std::getenv(key);
			if (value != nullptr) it->second.setFromEnv(value);
		}
	}

/*


//	template <typename T>  T  CommandLine::getOption(char* name)          {
//	}
	
	*/
}
