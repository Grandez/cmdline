
#include <iostream> // temp
#include <type_traits>
#include <list>

#include "common.h"
#include "parameter_tree.hpp"
/*


#include "arg.hpp"

*/

#include "defines.hpp"
#include "cmdline_exceptions.hpp"
#include "validations.h"
#include "commandline.hpp"

using namespace std;
// using namespace cmdline;

namespace cmdline {

   #ifndef ENV_PREFFIX
       #define ENV_PREFFIX "env_preffix"
    #endif

	ParameterTree* rootOptions[128];
	ParameterTree* rootFlags[128];
	CommandLine::CommandLine() {
		memset(&rootOptions, 0x0, sizeof(rootOptions));
		memset(&rootFlags, 0x0, sizeof(rootFlags));
        loadHelp();
	}
	CommandLine::CommandLine(vector<ParmItem> parms) {
		preInit(parms);
		postInit();
	};
	CommandLine::CommandLine(vector<ParmItem> options, vector<Flag> flags)  {
		preInit(options);
		for (auto f : flags) {
 			 this->flags.emplace(f.first, Argument(f.first.c_str(), (char *) (f.second ? "1" : "0")));
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
				prev = (in == std::string("-h") || in == std::string("--help")) ?
				     	updateFlag((char*)"+help", prev, true) :
					    updateFlag(argv[i], prev, false);
				break;
			default:
				if (prev == NULL) inputs.push_back(argv[i]);
				if (prev != NULL) prev = addValueToOption(argv[i], prev);
			}
		}
		if (hasFlag("HELP")) throw HelpDetailedRequested();
		if (hasFlag("help")) throw HelpRequested();
		return *this;
	}
	bool  CommandLine::hasFlag(const char* flag) {
		Argument* opt = flags.find(flag);
		if (opt == nullptr) return false;
		return makeBoolean(opt->getValue().c_str());
	}
	const Flag  CommandLine::getFlag(const char* flag) {
		Argument* opt = flags.find(flag);
		if (opt == nullptr) throw CmdLineNotFoundException(flag);
		return Flag(opt->name, opt->getBoolean());
	}

	Flags  CommandLine::getDefaultFlags(bool all) {
		Flags act;
		Argument *opt;
		for (auto it : flags) {
			opt = &it.second;
			if (opt->source != Source::AUTO && (all || opt->getBoolean())) {
			    act.emplace(opt->name, makeBoolean(opt->defvalue));
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
		Argument *opt;
		for (auto it : options) {
			opt = &it.second;
			if (opt->source != Source::AUTO) act.emplace(opt->name, opt->defvalue);
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
		Argument* opt = options.find(name);
		if (opt == nullptr) throw CmdLineNotFoundException(name);
		//		if (typeid(T) == string) return "";
		//		if (typeid(T) == path) return "";
		return T(opt->getValue());
	}
	template <> const string CommandLine::getOption(const char* name) {
		Argument* opt = options.find(name);
		if (opt == nullptr) throw CmdLineNotFoundException(name);

		return opt->getValue();
	}
	template <typename T>  const T  CommandLine::getDefinition(const char* name) {
		Argument* opt = options.find(name);
		if (opt == nullptr) throw CmdLineNotFoundException(name);
		const vector<string> values = opt->getValues();
		if (typeid(T) == vector) return values; 
		if (typeid(T) == list)	 return list<string>(values.begin(), values.end());
//		if (typeid(T) == (char[]))	 return opt->getValue().c_str();
		throw CmdLineInvalidTypeException(typeid(T).name());
		try {
			return T(opt->getValues());
		}
		catch (exception ex) {
			throw CmdLineInvalidTypeException(typeid(T).name());
		}
	}
	template <> 
	const string CommandLine::getDefinition(const char* name) {
		Argument* opt = defines.find(name);
		if (opt == nullptr) throw CmdLineNotFoundException(name);

		return opt->getValue();
	}

	const string CommandLine::getDefinition2(const char* name) {
		Argument* opt = defines.find(name);
		if (opt == nullptr) throw CmdLineNotFoundException(name);
		return (*opt).getValue();
	}
	vector<string> CommandLine::getVectorDefinition(const char* name) {
		Argument* opt = defines.find(name);
		if (opt == nullptr) throw CmdLineNotFoundException(name);
		return (*opt).getValues();
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
			if (base->letter != parm[idx]) break;
			base = base->getChild(parm[++idx]);
		}

		std::string str;
		if (idx == strlen(parm)) { // Parsing full done
			switch (prev->numChildren()) {
			case 0: return (strdup(parm));
			case 1: str = parm;
				str.append(prev->getNext()->getWord());
				return (makeChar(str));
			default: throw CmdLineParameterException(parm);
			}
		}
		if (prev == nullptr) throw CmdLineException(parm);  // primero
		if (base == nullptr) throw CmdLineParameterException(parm, prev->getReversedWord());

		// Ha salido por base = nullptr

		if (prev->branchs > 1)  throw CmdLineException("No definido con alternativa 2", "varias alernativa");
		if (prev->branchs == 1) throw CmdLineException("No definido con alternativa 1", "tipo");
		std::string ss(parm);
		ss.append(base->getWord());
		return (makeChar(ss));
	}
	void CommandLine::updateFromEnv() {
		char key[255];
		char* p = (char*)"";
		Argument *arg = options.find(ENV_PREFFIX);
		if (arg != nullptr) {
			sprintf(key, "%s_", arg->name.c_str());
			p = strdup(key);
		}
		udpateArgsFromEnv(options, p);
		udpateArgsFromEnv(flags, p);
		if (arg != nullptr) free(p);
	}
	void CommandLine::udpateArgsFromEnv(Group &parms, const char*prfx) {
		char key[255];
		char* value;
//		Args::iterator it;

		for (auto it = parms.begin(); it != parms.end(); it++) {
			sprintf(key, "%s%s", prfx, it->second.name.c_str());
			value = getenv(key);
			if (value != nullptr) it->second.setFromEnv(value);
        }
	}
	char* CommandLine::updateOption(const char* option, char* prev) {
		int pos = std::string(option).find("=");
		if (pos != std::string::npos) return updateDefinition(option);
		validateEntry(option, prev);
		return (checkOption(&(option[1])));
	}
	char* CommandLine::updateDefinition(const char* value) {
		const char* ptr = &(value[1]);
		vector<string> toks = tokenize(ptr, "=");
		if (toks.size() != 2)      throw CmdLineParameterException("Invalid definition", value);
		if (toks[0].length() == 0) throw CmdLineParameterException("Invalid definition", value);
		Argument *def = defines.find(toks[0]);
		if (def == nullptr) def = new Define(toks[0].c_str());
		def->initValues(splitArgument(toks[1].c_str()));
		defines.add(*def);
		return nullptr;
	}
	char* CommandLine::updateFlag(const char* flag, const char* prev, bool value) {
		std::vector<std::string> flags = splitArgument(flag);
		for (std::string f : flags) updateFlagItem((char*)f.c_str(), prev, value);
		return nullptr;
	}
	void CommandLine::updateFlagItem(const char* flag, const char* prev, bool value) {
		std::string name;
		validateEntry(flag, prev);
		try {
			Argument* opt = flags.find(checkFlag(&(flag[1])));
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
	char *CommandLine::addValueToOption(const char* value, char* option) {
		if (strlen(option) == 1) throw CmdLineException("Invalid Option", option);
		Argument* opt = options.find(option); // Exists!!!!
		validateValue(value, opt->type);
		if ( opt->multiple) (*opt).addValue(value);
		if (!opt->multiple) (*opt).setValue(value);
		return nullptr;
	}
	void CommandLine::loadHelp() {
		vector<ParmItem> flagHelp = { ParmItem("help", false) ,ParmItem("HELP", false) };
		Argument* arg = flags.find("help");
		if (arg != nullptr) return;
		preInit(flagHelp, false);
		arg = flags.find("help");
		arg->source = Source::AUTO;
		arg = flags.find("HELP");
		arg->source = Source::AUTO;
	}
	void CommandLine::preInit(vector<ParmItem> parms, bool init) {
		if (init) {
			memset(&rootOptions, 0x0, sizeof(rootOptions));
			memset(&rootFlags, 0x0, sizeof(rootFlags));
		}
		for (ParmItem p : parms) {
			Argument option(p);
			Group& map = (p.type == Type::FLAG) ? flags : options;
			map.add(p.name, option);
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
