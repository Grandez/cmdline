
#include <iostream> // temp
#include <type_traits>

#ifndef _CRT_SECURE_NO_WARNINGS
#define _SECURE_DEF_
#define _CRT_SECURE_NO_WARNINGS

#endif

#include "common.h"
#include "parameter_tree.hpp"
#include "validations.h"
#include "cmdline_exceptions.hpp"
#include "arg.hpp"
#include "commandline.hpp"

using namespace std;
using namespace cmdline;

namespace cmdline {

   #ifndef ENV_PREFFIX
       #define ENV_PREFFIX "env_preffix"
    #endif

	ParameterTree* rootOptions[128];
	ParameterTree* rootFlags[128];

	Argument* findOption(Args* map, string what) {
		try {
			auto res = map->at(what);
			return &(map->at(what));
		}
		catch (out_of_range ex) {
			return (Argument*) nullptr;
		}
	}

	CommandLine::CommandLine() {
		memset(&rootOptions, 0x0, sizeof(rootOptions));
		memset(&rootFlags, 0x0, sizeof(rootFlags));
	//	fill_n(rootOptions, sizeof(rootOptions), nullptr);
	//	fill_n(rootFlags, sizeof(rootFlags), nullptr);
		loadHelp();
	}
	CommandLine::CommandLine(vector<ParmItem> parms) {
		preInit(parms);
		postInit();
	};
	CommandLine::CommandLine(vector<ParmItem> options, vector<Flag> flags)  {
		preInit(options);
		for (auto f : flags) {
 			 this->flags.emplace(f.first, Argument(f.first, (char *) (f.second ? "1" : "0")));
		}
		updateFromEnv();
		loadHelp();
	};
	CommandLine::~CommandLine() {
		for (int i = 0; i < 128; i++) {
			if (rootOptions[i] != nullptr) free(rootOptions[i]);
			if (rootFlags[i] != nullptr) free(rootFlags[i]);
		}
	}
	CommandLine& CommandLine::parse(const int argc, const char* argv[]) {
		std::string in;
		char* prev = nullptr;
		for (int i = 1; i < argc; i++) {
			switch (argv[i][0]) {
			case '/': prev = updateOption(argv[i], prev); break;
			case '+': if (prev != nullptr) throw CmdLineException("Missing value", prev);
				prev = updateFlag(argv[i], argv[i], true);   break;
			case '-': in = argv[i];
				if (in == std::string("-h") || in == std::string("--help"))
					prev = updateFlag((char*)"+help", prev, true);
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
		if (hasFlag("HELP")) throw HelpDetailedRequested();
		if (hasFlag("help")) throw HelpRequested();
		return *this;
	}
	bool  CommandLine::hasFlag(const char* flag) {
		Argument* opt = findOption(&flags, flag);
		if (opt == nullptr) return false;
		return makeBoolean(opt->getValue().c_str());
	}
	const Flag  CommandLine::getFlag(const char* flag) {
		Argument* opt = findOption(&flags, flag);
		if (opt == nullptr) throw CmdLineNotFoundException(flag);
		return Flag(opt->name, opt->getBoolean());
	}

	Flags  CommandLine::getDefaultFlags(bool all) {
		Flags act;
		Argument opt;
		for (auto it : flags) {
			opt = it.second;
			if (opt.source != Source::AUTO && (all || opt.getBoolean())) {
			    act.emplace(opt.name, makeBoolean(opt.defvalue));
			}
		}
		return act;
	}
	Flags CommandLine::getCurrentFlags(bool active) {
		Flags flg;
		for (auto it : flags) {
			if (!active || it.second.getBoolean()) flg.emplace(it.second.name, it.second.getBoolean());
		}
		return flg;
	}
	Options  CommandLine::getDefaultOptions() {
		Options act;
		Argument opt;
		for (auto it : options) {
			opt = it.second;
			if (opt.source != Source::AUTO) act.emplace(opt.name, opt.defvalue);
		}
		return act;
	}
	Options CommandLine::getCurrentOptions(bool all) {
		Options opts; // = options;
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

	template <typename T>  const T  CommandLine::getOption(const char *name) {
		Argument* opt = findOption(&options, name);
		if (opt == nullptr) throw CmdLineNotFoundException(name);
		//		if (typeid(T) == string) return "";
		//		if (typeid(T) == path) return "";
		return T(opt->getValue());
	}
	template <> const string CommandLine::getOption(const char* name) {
		Argument* opt = findOption(&options, name);
		if (opt == nullptr) throw CmdLineNotFoundException(name);

		return opt->getValue();
	}


	/*
	template <typename T>
			void foo() {
				if constexpr (is_same_v<T, path>) {
					// use type specific operations...
				}
			}
			*/
	//////////////////////////////////////////////////////////////////
	
	char* CommandLine::checkOption(const char* option) { return (checkParameter(rootOptions, option)); }
	char* CommandLine::checkFlag(const char* flag) { return (checkParameter(rootFlags, flag)); }
	char* CommandLine::checkParameter(ParameterTree* root[], const char* parm) {
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
			case 0: return (strdup(parm));
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
	void CommandLine::updateFromEnv() {
		char key[255];
		char* p = (char*)"";
		Argument *arg = findOption(&options, ENV_PREFFIX);
		if (arg != nullptr) {
			sprintf(key, "%s_", arg->name.c_str());
			p = strdup(key);
		}
		udpateArgsFromEnv(options, p);
		udpateArgsFromEnv(flags, p);
		if (arg != nullptr) free(p);
	}
	void CommandLine::udpateArgsFromEnv(Args &parms, const char*prfx) {
		char key[255];
		char* value;
		Args::iterator it;

		for (it = parms.begin(); it != parms.end(); it++) {
			sprintf(key, "%s%s", prfx, it->second.name.c_str());
			value = getenv(key);
			if (value != nullptr) it->second.setFromEnv(value);
        }
	}
	char* CommandLine::updateOption(const char* option, char* prev) {
		int pos = std::string(option).find("=");
		if (pos != std::string::npos) return updateDefinition(option, pos);
		validateEntry(option, prev);
		return (checkOption(&(option[1])));
	}
	char* CommandLine::updateDefinition(const char* def, int pos) {
		bool pending = false;
		std::string prev;
		std::string name = std::string(def).substr(0, pos - 1);
		std::vector<std::string> defs = splitParameter(&(def[pos + 1]));
		/*
		for (std::string value : defs) {
			Option* opt = findOption(&defines, name);
			enum class Source { DEFAULT, ENV, CMDLINE };
			if (opt == nullptr) defines.emplace(name, Option(name, value, cmdline::Source::CMDLINE));
			//		    if (opt != nullptr) opt->setValue(value);
		}
		*/
		return nullptr;
	}
	char* CommandLine::updateFlag(const char* flag, const char* prev, bool value) {
		std::vector<std::string> flags = splitParameter(flag);
		for (std::string f : flags) updateFlagItem((char*)f.c_str(), prev, value);
		return nullptr;
	}
	void CommandLine::updateFlagItem(const char* flag, const char* prev, bool value) {
		std::string name;
		validateEntry(flag, prev);
		try {
			Argument* opt = findOption(&flags, checkFlag(&(flag[1])));
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
	char* CommandLine::addValueToOption(const char* value, char* option) {
		if (strlen(option) == 1) throw CmdLineException("Invalid Option", option);
		ParmItem def = defOptions.find(option)->second;
		validateValue(value, def.type);
		Argument* opt = findOption(&options, option);
		//		if (def.multiple) opt->addValue(value);
		//		if (!def.multiple) opt->setValue(value);
		return (checkOption(&(option[1])));
	}
	void CommandLine::loadHelp() {
		vector<ParmItem> flagHelp = { ParmItem("help", false) ,ParmItem("HELP", false) };
		Argument* arg = findOption(&flags, "help");
		if (arg != nullptr) return;
		preInit(flagHelp, false);
		arg = findOption(&flags, "help");
		arg->source = Source::AUTO;
		arg = findOption(&flags, "HELP");
		arg->source = Source::AUTO;
	}
	void CommandLine::preInit(vector<ParmItem> parms, bool init) {
		if (init) {
			memset(&rootOptions, 0x0, sizeof(rootOptions));
			memset(&rootFlags, 0x0, sizeof(rootFlags));

//			fill_n(rootOptions, sizeof(rootOptions), nullptr);
//			fill_n(rootFlags, sizeof(rootFlags), nullptr);
		}
		for (ParmItem p : parms) {
			Argument option(p.name, p.value);
			Args* map = (p.type == Type::FLAG) ? &flags : &options;
			map->emplace(p.name, Argument(option));
			ParameterTree** root = (p.type == Type::FLAG) ? rootFlags : rootOptions;
			add2tree(root, p.name);
		}
	}
	void CommandLine::postInit() {
		updateFromEnv();
		loadHelp();
	}

}

#ifdef _SECURE_DEF_
  #undef _SECURE_DEF_
  #undef _CRT_SECURE_NO_WARNINGS_endif
#endif
