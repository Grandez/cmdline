//#include <algorithm>
//#include <unordered_map>
//#include <cstdlib>
//
//// #include <boost/scoped_ptr.hpp>
//
#include "commandline.hpp"

//#include "parmitem.hpp"

#include "cmdline_exceptions.hpp"
#include "parameter_tree.hpp"
#include "tools.h"
#include "validations.h"
#include "enums.h"
#include "option.hpp"

namespace cmdline {
	ParameterTree* rootOptions[128];
	ParameterTree* rootFlags[128];

	CommandLine::CommandLine() {
		std::vector<cmdline::ParmItem> flagHelp = { cmdline::ParmItem("help", false) };
		loadDefaults(flagHelp);
	}
	CommandLine::CommandLine(std::vector<ParmItem> parms) {
		std::vector<cmdline::ParmItem> flagHelp = { cmdline::ParmItem("help", false) };

		std::fill_n(rootOptions, sizeof(rootOptions), nullptr);
		std::fill_n(rootFlags, sizeof(rootFlags), nullptr);
		loadDefaults(parms);
		loadEnv(options);
		loadEnv(flags);
		Option *opt = findOption(&flags, "help");
		if (opt == nullptr) loadDefaults(flagHelp);
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
			case '/': prev = updateOption(argv[i], prev); break;
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
					inputs.push_back(argv[i]);
				}
				else {
					addValueToOption(argv[i], prev);
				}
			}
		}
		if (hasFlag("help")) throw HelpRequested();
		return *this;
	}
	template <typename T>  T  CommandLine::getOption(std::string name) {
		Option *opt = findOption(&options, name);
//		if (typeid(T) == std::string) return "";
//		if (typeid(T) == path) return "";
		return T(opt->getValue());
		/*
#include <type_traits>

		template <typename T>
		void foo() {
			if constexpr (std::is_same_v<T, path>) {
				// use type specific operations... 
			}
		}
		*/
	}
	template <> std::string CommandLine::getOption<std::string>(std::string name) {
		Option* opt = findOption(&options, name);
		return opt->getValue();
	}
	std::pair<std::string, bool>  CommandLine::getFlag(std::string name) {
		Option* opt = findOption(&flags, name);
		return std::pair<std::string, bool>(opt->name, makeBoolean(opt->getValue()));
	}
	bool                    CommandLine::hasFlag(char* flag) {
		Option* opt = findOption(&flags, flag);
		if (opt == nullptr) return false;
		return makeBoolean(opt->getValue().c_str());
	}
	std::unordered_map<std::string, bool>  CommandLine::getDefaultFlags(bool all) {
		std::unordered_map<std::string, bool> act;
		Option opt;
		bool val;
		for (auto it : flags) {
			opt = it.second;
			if (all) {
				act.emplace(opt.name, makeBoolean(opt.defvalue));
			}
			else {
				val = makeBoolean(opt.defvalue);
				if (val) act.emplace(opt.name, makeBoolean(opt.defvalue));
			}
		}
		return act;
	}
	std::unordered_map<std::string, std::string>  CommandLine::getDefaultOptions() {
		std::unordered_map<std::string, std::string> act;
		for (auto it : options) {
			if (strcmp(it.first.c_str(), ENV_PREFFIX) != 0) act.emplace(it.first, it.second.defvalue);
		}
		return act;
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
	std::vector<std::string>                     CommandLine::getDefinition(const char* name) {
		Option* opt = findOption(&defines, name);
		if (opt == nullptr) return std::vector<std::string>();
		return opt->getValues();
	}
	std::unordered_map<std::string, std::vector<std::string>>  CommandLine::getDefinitions() {
		std::unordered_map<std::string, std::vector<std::string>> defs;
		Option opt;
		for (auto it : defines) {
			opt = it.second;
			defs.emplace(it.second.name, it.second.getValues());
		}
		return defs;
	}

	/* *****************************************/
	/* Private 
	********************************************/
	char* CommandLine::updateOption(char* option, char* prev) {
		int pos = std::string(option).find("=");
		if ( pos != std::string::npos) return updateDefinition(option, pos);
		validateEntry(option, prev);
		return (checkOption(&(option[1])));
	}
	char* CommandLine::updateDefinition(char *def, int pos) {
		bool pending = false;
		std::string prev;
		std::string name = std::string(def).substr(0, pos-1);
		std::vector<std::string> defs = splitParameter(&(def[pos+1]));
		for (std::string value : defs) {
			Option* opt = findOption(&defines, name);
			enum class Source { DEFAULT, ENV, CMDLINE };
			if (opt == nullptr) defines.emplace(name, Option(name, value, cmdline::Source::CMDLINE));
//		    if (opt != nullptr) opt->setValue(value);
		}
		return nullptr;
	}
	char *CommandLine::updateFlag(char* flag, char* prev, bool value) {
		std::vector<std::string> flags = splitParameter(flag);
		for (std::string f : flags) updateFlagItem((char *) f.c_str(), prev, value);
		return nullptr;
	}
	void CommandLine::updateFlagItem(char* flag, char* prev, bool value) {
		std::string name;
		validateEntry(flag, prev);
		try {
     		Option* opt = findOption(&flags, checkFlag(&(flag[1])));
//			opt->setValue(value);
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
	char* CommandLine::addValueToOption(char* value, char* option) {
		if (strlen(option) == 1) throw CmdLineException("Invalid Option", option);
		ParmItem def = defOptions.find(option)->second;
		validateValue(value, def.type);
		Option* opt = findOption(&options, option);
//		if (def.multiple) opt->addValue(value);
//		if (!def.multiple) opt->setValue(value);
		return (checkOption(&(option[1])));
	}

	char *CommandLine::checkOption(char* option) { return (checkParameter(rootOptions, option)); }
	char *CommandLine::checkFlag  (char* flag)   { return (checkParameter(rootFlags, flag)); }
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
		Option opt = options[ENV_PREFFIX];
		prfx = opt.name.c_str();
		std::unordered_map<std::string, Option>::iterator it;
		for (it = parms.begin(); it != parms.end(); it++) {
			sprintf(key, "%s_%s", prfx, it->second.name.c_str());
			value = std::getenv(key);
			if (value != nullptr) it->second.setFromEnv(value);
		}
	}
}
