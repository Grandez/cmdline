
#include <iostream> // temp
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
		cout << "Crea";
		vector<ParmItem> flagHelp = { ParmItem("help", false) };
		loadDefaults(flagHelp);
	}
	CommandLine::CommandLine(vector<ParmItem> parms) {
		vector<ParmItem> flagHelp = { ParmItem("help", false) };

		fill_n(rootOptions, sizeof(rootOptions), nullptr);
		fill_n(rootFlags, sizeof(rootFlags), nullptr);
		loadDefaults(parms);
		loadEnv(options);
		loadEnv(flags);
		Argument* opt = findOption(&flags, "help");
		if (opt == nullptr) loadDefaults(flagHelp);
	};
	CommandLine::CommandLine(vector<ParmItem> options, vector<Flag> flags) : CommandLine(options) {
		for (auto f : flags) {
//CHECK			this->flags.emplace(f.first, Argument(f.first, f.second ? "1" : "0"));
		}
		if (this->flags["help"].name.length() == 0) add2tree(rootFlags, "help");
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
		if (hasFlag("help")) throw HelpRequested();
		return *this;
	}
	bool  CommandLine::hasFlag(const char* flag) {
		Argument* opt = findOption(&flags, flag);
		if (opt == nullptr) return false;
		return makeBoolean(opt->getValue().c_str());
	}

	Flags  CommandLine::getDefaultFlags(bool all) {
		Flags act;
		Argument opt;
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
	Flags CommandLine::getCurrentFlags(bool active) {
		Flags flg;
		for (auto it : flags) {
			if (!active || it.second.getBoolean()) flg.emplace(it.second.name, it.second.getBoolean());
		}
		return flg;
	}
	Options  CommandLine::getDefaultOptions() {
		Options act;
		/*
		for (auto it : options) {
			if (strcmp(it.first.c_str(), ENV_PREFFIX) != 0) act.emplace(it.first, it.second.defvalue);
		}
		*/
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
	/*
	template <typename T>  T  CommandLine::getOption(string name) {
		Argument* opt = findOption(&options, name);
		//		if (typeid(T) == string) return "";
		//		if (typeid(T) == path) return "";
		return T(opt->getValue());
	}
	*/	/*
	#include <type_traits>

			template <typename T>
			void foo() {
				if constexpr (is_same_v<T, path>) {
					// use type specific operations...
				}
			}
			*/
/*
	template <> string CommandLine::getOption<string>(string name) {
		Argument* opt = findOption(&options, name);
		return opt->getValue();
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

	void CommandLine::loadDefaults(vector<ParmItem> parms) {
		for (ParmItem p : parms) {
			Argument option(p.name, p.value);
			Args& map = (p.type == Type::FLAG) ? flags : options;
			map.emplace(p.name, Argument(option));
			ParameterTree** root = (p.type == Type::FLAG) ? rootFlags : rootOptions;
			add2tree(root, p.name);
		}
	}
	void CommandLine::loadEnv(Args parms) {
		char* value;
		char key[255];
		const char *prfx = options[ENV_PREFFIX].name.c_str();
		Args::iterator it;

		for (it = parms.begin(); it != parms.end(); it++) {
			sprintf(key, "%s_%s", prfx, it->second.name.c_str());
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

}

#ifdef _SECURE_DEF_
  #undef _SECURE_DEF_
  #undef _CRT_SECURE_NO_WARNINGS_endif
#endif
