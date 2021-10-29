
#include <iostream> // temp
#include <type_traits>
#include <chrono>
#include "parameter_tree.hpp"

#include "tools.h"
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
			case '/': 
				prev = updateOption(argv[i], prev); 
				if (strict) checkAlreadySet(options, prev);
				break;
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
	bool  _CommandLine::hasDefinition(const char* name) {
		return false;
	}

	bool  _CommandLine::hasFlag(const char* name) {
		Argument* opt = find(flags, name);
		return makeBoolean(opt->getValue());
	}
	Flags  _CommandLine::getDefaultFlags(bool all) { // Valores por defecto
		return getFlags(all, false);
	}
	Flags _CommandLine::getCurrentFlags(bool all) {
		return getFlags(all, true);
	}

	bool _CommandLine::hasOption(const char* name) {
		Argument* opt = find(options, name);
		return (strlen(opt->getValue()) == 0 ? false : true);
	}
	bool _CommandLine::hasOption(string name) {
		return hasOption(name.c_str());
	}
	bool _CommandLine::isOptionMultiple(const char* name) {
		Argument* opt = find(options, name);
		return (opt->values.size() > 1);
	}
	bool _CommandLine::isOptionMultiple(string name) {
		return isOptionMultiple(name.c_str());
	}
	const char* _CommandLine::getOption(const char* name) {
		Argument* opt = find(options, name);
		return opt->getValue();
	}
	const char* _CommandLine::getOption(string name) {
		return getOption(name.c_str());
	}
	vector<string> _CommandLine::getOptionValues(const char* name) { 
		Argument* opt = find(options, name);
		return opt->getValues();
	}
	vector<string> _CommandLine::getOptionValues(string name) { 
		return getOptionValues(name.c_str()); 
	}

	template <typename T>
	const T _CommandLine::getOptionAs(const char* name) {
		T cls;
		Argument* opt = find(options, name);
		return castValue<T>(cls, opt->type, opt->getValue());
//		checkType(T, Type type);
//		auto value = any(getValue(opt->getValue(), opt->type));
//		return  castValue(value, opt->type);
    }
	template <typename T>
	const T _CommandLine::getOptionAs(string name) {
		return getOptionAs<T>(name.c_str());
	}

	Options  _CommandLine::getDefaultOptions() {
		return getOptionsValue(true);
	}
	Options _CommandLine::getCurrentOptions() {
		return getOptionsValue(false);
	}
	template <typename T>
	vector<T> _CommandLine::getOptionValuesAs(const char *name) { 
		T cls;
		vector<T> data;
		
		Argument* opt = find(options, name);
		for (auto it : opt->getValues()) {
			data.push_back(castValue<T>(cls, opt->type, it));
		}
		return data;
	};
	/*
	template <typename T>
	vector<T> _CommandLine::getOptionValuesAs(string name) {
		return getOptionValuesAs<T>(name.c_str());
	};
	*/
	/*
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
	*/
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
			value = makeBoolean((def) ? opt->defValue : opt->getValue());
			if (opt->source != Source::AUTO && (active || value)) act.emplace(opt->name, value);
		}
		return act;
	}
	Argument* _CommandLine::find(Group where, const char* what) {
		Argument* arg = where.find(what);
		if (arg == nullptr) throw CmdLineNotFoundException(what);
		return arg;
	}
	template <typename T>
	void _CommandLine::checkType(T, Type type) {
		string expected("");
		switch (type) {
		case cmdline::Type::NUMBER:  if (!is_same<T, int> && !is_same<T, long>) expected = "number";break;
		case cmdline::Type::DECIMAL: if (!is_same<T, float> && !is_same<T, double>) expected = "decimal"; break;
		case cmdline::Type::DATE:   if (!is_same<T, struct tm>) expected = "date";break;
		case cmdline::Type::TIME:   if (!is_same<T, struct tm>) expected = "time";break;
		case cmdline::Type::DATETIME: if (!is_same<T, struct tm>) expected = "datetiem"; break;
		case cmdline::Type::TMS:      if (!is_same<T, chrono::time_point>) expected = "timestamp";break;
		case cmdline::Type::DIR:
		case cmdline::Type::DIR_EXISTS: if (!is_same<T, filesystem::path>) expected = "directory";break;
		case cmdline::Type::FILE:
		case cmdline::Type::FILE_EXISTS: if (!is_same<T, filesystem::path>) expected = "file";break;
		default: expected = "";
		}
		if (expected.length() > 0) throw CmdLineInvalidTypeException("expected " + expected);
	}
	template <typename T>
	T _CommandLine::castValue(T, auto value) {
		if (is_same<T, int>) return any_cast<int>(value);
		if (is_same<T, long>) return any_cast<long>(value);
		if (is_same<T, float>) return any_cast<float>(value);
		if (is_same<T, double>) return any_cast<double>(value);
		if (!is_same<T, struct tm *>) return any_cast<struct tm *>(value);
		if (!is_same<T, filesystem::path>) return any_cast<filesystem::path>(value);
		return any_cast<string>(value);
	}
	Options  _CommandLine::getOptionsValue(bool def) {
		Options act;
			Argument* opt;
			for (auto it : options) {
				opt = &it.second;
				if (opt->source != Source::AUTO) act.emplace(opt->name, (def ? opt->defValue : opt->getValue()));
			}
		return act;

	}
	void _CommandLine::checkAlreadySet(Group where, const char* what) {
		Argument* arg = find(where, what);
		if (arg != nullptr) {
			if (arg->values.size() && !arg->multiple) throw CmdLineDuplicateArgumentException(what);
		}
	}
}

#ifdef _SECURE_DEF_
  #undef _SECURE_DEF_
  #undef _CRT_SECURE_NO_WARNINGS_endif
#endif
