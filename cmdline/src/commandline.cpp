
#include <iostream> // temp
#include <type_traits>

#include "common.h"
#include "parameter_tree.hpp"

#include "defines.hpp"
#include "cmdline_exceptions.hpp"
#include "validations.h"
#include "commandline.hpp"

using namespace std;
// using namespace cmdline;

namespace _cmdline {

   #ifndef ENV_PREFFIX
       #define ENV_PREFFIX "env_preffix"
    #endif

	ParameterTree* rootOptions[128];
	ParameterTree* rootFlags[128];

	_CommandLine::_CommandLine(int argc, char* argv[], Parameters parms) {
		preInit(parms);
		postInit();
	}
    _CommandLine::_CommandLine(int argc, char* argv[], Parameters parms, bool forward, bool strict) {
	    this->forward = forward;
	    this->strict = strict;
	    preInit(parms);
	    postInit();
    }
	_CommandLine::~_CommandLine() {
		for (int i = 0; i < 128; i++) {
			if (rootOptions[i] != nullptr) free(rootOptions[i]);
			if (rootFlags[i] != nullptr) free(rootFlags[i]);
		}
	}
	_CommandLine& _CommandLine::parse(const int argc, const char* argv[]) {
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
	bool  _CommandLine::hasDefinition(const char* flag) {
		return false;
	}

	bool  _CommandLine::hasFlag(const char* flag) {
		Argument* opt = flags.find(flag);
		if (opt == nullptr) return false;
		return makeBoolean(opt->getValue().c_str());
	}
	Flags  _CommandLine::getDefaultFlags(bool all) { // Valores por defecto
		return getFlags(all, false);
	}
	Flags _CommandLine::getCurrentFlags(bool all) {
		return getFlags(all, true);
	}


	Options  _CommandLine::getDefaultOptions() {
		Options act;
		Argument *opt;
		for (auto it : options) {
			opt = &it.second;
			if (opt->source != Source::AUTO) act.emplace(opt->name, opt->defvalue);
		}
		return act;
	}
	Options _CommandLine::getCurrentOptions(bool all) {
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

	template <typename T>  const T  _CommandLine::getOption(const char *name) {
		Argument* opt = options.find(name);
		if (opt == nullptr) throw CmdLineNotFoundException(name);
		//		if (typeid(T) == string) return "";
		//		if (typeid(T) == path) return "";
		return T(opt->getValue());
	}
	template <> const string _CommandLine::getOption(const char* name) {
		Argument* opt = options.find(name);
		if (opt == nullptr) throw CmdLineNotFoundException(name);

		return opt->getValue();
	}
	template <typename T>  const T  _CommandLine::getDefinition(const char* name) {
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
	const string _CommandLine::getDefinition(const char* name) {
		Argument* opt = defines.find(name);
		if (opt == nullptr) throw CmdLineNotFoundException(name);

		return opt->getValue();
	}

	const string _CommandLine::getDefinition2(const char* name) {
		Argument* opt = defines.find(name);
		if (opt == nullptr) throw CmdLineNotFoundException(name);
		return (*opt).getValue();
	}
	vector<string> _CommandLine::getVectorDefinition(const char* name) {
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
	
	char* _CommandLine::checkOption(const char* option) { return (checkParameter(rootOptions, option)); }
	char* _CommandLine::checkFlag(const char* flag) { return (checkParameter(rootFlags, flag)); }
	char* _CommandLine::checkParameter(ParameterTree* root[], const char* parm) {
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
	void _CommandLine::updateFromEnv() {
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
	void _CommandLine::udpateArgsFromEnv(Group &parms, const char*prfx) {
		char key[255];
		char* value;
//		Args::iterator it;

		for (auto it = parms.begin(); it != parms.end(); it++) {
			sprintf(key, "%s%s", prfx, it->second.name.c_str());
			value = getenv(key);
			if (value != nullptr) it->second.setFromEnv(value);
        }
	}
	char* _CommandLine::updateOption(const char* option, char* prev) {
		int pos = std::string(option).find("=");
		if (pos != std::string::npos) return updateDefinition(option);
		validateEntry(option, prev);
		return (checkOption(&(option[1])));
	}
	char* _CommandLine::updateDefinition(const char* value) {
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
	char* _CommandLine::updateFlag(const char* flag, const char* prev, bool value) {
		std::vector<std::string> flags = splitArgument(flag);
		for (std::string f : flags) updateFlagItem((char*)f.c_str(), prev, value);
		return nullptr;
	}
	void _CommandLine::updateFlagItem(const char* flag, const char* prev, bool value) {
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
	char *_CommandLine::addValueToOption(const char* value, char* option) {
		if (strlen(option) == 1) throw CmdLineException("Invalid Option", option);
		Argument* opt = options.find(option); // Exists!!!!
		validateValue(value, opt->type);
		if ( opt->multiple) (*opt).addValue(value);
		if (!opt->multiple) (*opt).setValue(value);
		return nullptr;
	}
	void _CommandLine::preInit(Parameters parms, bool init) {
		ParameterTree** root;

		if (init) {
			memset(&rootOptions, 0x0, sizeof(rootOptions));
			memset(&rootFlags, 0x0, sizeof(rootFlags));
		}
		for (Parm p : parms) {
			Argument option(p);
			Group& map  = (p.instanceOfFlag()) ? flags      : options;
			root = (p.instanceOfFlag()) ? rootFlags : rootOptions;
			map.add(p.name, option);
			add2tree(root, p.name);
		}
	}
	void _CommandLine::postInit() {
		updateFromEnv();
		loadHelp();
	}
	void _CommandLine::loadHelp() {
		Parameters flagHelp = { Parm("help", false) ,Parm("HELP", false) };
		Argument* arg = flags.find("help");
		if (arg != nullptr) return;
		preInit(flagHelp, false);
		arg = flags.find("help");
		arg->source = Source::AUTO;
		arg = flags.find("HELP");
		arg->source = Source::AUTO;
	}
	Flags  _CommandLine::getFlags(bool active, bool def) {
		Flags act;
		Argument* opt;
		bool value;
		for (auto it : flags) {
			opt = &it.second;
			value = makeBoolean((def) ? opt->defvalue : opt->getValue());
			if (opt->source != Source::AUTO && (active || value)) act.emplace(opt->name, value);
		}
		return act;
	}

}

#ifdef _SECURE_DEF_
  #undef _SECURE_DEF_
  #undef _CRT_SECURE_NO_WARNINGS_endif
#endif
