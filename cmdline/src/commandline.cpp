
#include <iostream> // temp
#include <type_traits>
#include <chrono>
#include <any>
#include <utility>

#include "parameter_tree.hpp"

#include "tools.h"
#include "defines.hpp"
#include "cmdline_exceptions.hpp"
#include "validations.h"
#include "commandline.hpp"
#include "msg_locale.h"

//#pragma warning( disable : 4390 34; once : 4385; error : 164 )

#ifdef _WIN32
#pragma warning( disable : 4390 )
#endif

using namespace std;
using namespace cmdline;

namespace _cmdline {

   #ifndef ENV_PREFFIX
       #define ENV_PREFFIX "env_preffix"
    #endif

	ParameterTree* rootOptions[128];
	ParameterTree* rootFlags[128];
	char _upper[64] = "";

	char* makeUpper(const char* str) {
		size_t i;
		for (i = 0; i < strlen(str); i++) _upper[i] = toupper(str[i]);
		_upper[i] = 0x0;
		return _upper;
	}
	_CommandLine::_CommandLine(int argc,  char**  argv, Parameters parms) {
		preInit(parms);
		postInit();
		parse(argc, argv);
	}
    _CommandLine::_CommandLine(int argc,  char**  argv, Parameters parms, void* attr) {
		Attr* p = (Attr*)attr;
    	this->attr.sensitive = p->sensitive;
		this->attr.strict    = p->strict;
		this->attr.forward   = p->forward;
	    preInit(parms);
	    postInit();
		parse(argc, argv);
    }
	vector<const char*> _CommandLine::getArgs() {
		return inputs;
	}
	void _CommandLine::parse(int argc, char** argv) {
		char c;
		char szOpt[64] = "";
		std::string in;
		char* prev = nullptr;
		for (int i = 1; i < argc; i++) {
			c = argv[i][0];

			if (c == '/' || c == '+' || c == '-') {
				strcpy(szOpt, argv[i]);
				if (attr.sensitive) {
					for (size_t j = 0; j < strlen(szOpt); j++) szOpt[j] = toupper(szOpt[j]);
				}
			}
			switch (argv[i][0]) {
			case '/': 
				prev = updateOption(szOpt, prev); 
				if (attr.strict) checkAlreadySet(&options, prev);
				break;
			case '+': if (prev != nullptr) throw CmdLineException(ERR_ARG_MISSING, prev);
				prev = updateFlag(szOpt, argv[i], true);   break;
			case '-': in = string(szOpt);
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
	}
	bool _CommandLine::hasFlag(const char* name) {
		Argument& opt = find(&flags, name);
		return makeBoolean(opt.getValue());
	}
	Flags  _CommandLine::getDefaultFlags(bool all) { // Valores por defecto
		return getFlags(all, false);
	}
	Flags _CommandLine::getCurrentFlags(bool all) {
		return getFlags(all, true);
	}
	bool _CommandLine::hasOption(const char* name) {
		Argument& opt = find(&options, name);
		return (strlen(opt.getValue()) == 0 ? false : true);
	}
	bool _CommandLine::hasOption(string name) {
		return hasOption(name.c_str());
	}
	bool _CommandLine::isOptionMultiple(const char* name) {
		Argument& opt = find(&options, name);
		return (opt.values.size() > 1);
	}
	bool _CommandLine::isOptionMultiple(string name) {
		return isOptionMultiple(name.c_str());
	}
	vector<const char*> _CommandLine::getOptionValues(const char* name) {
		Argument& opt = find(&options, name);
		return opt.getValues();
	}
	int    _CommandLine::getOptionNumValues(const char* name) {
		Argument& opt = find(&options, name);
		return opt.values.size();
	}
	const char* _CommandLine::getOption(const char* name) {
		return getValue(&options, name);
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
		
		Argument& opt = find(&options, name);
		for (auto it : opt.getValues()) {
			data.push_back(castValue<T>(cls, opt->type, it));
		}
		return data;
	};
	bool            _CommandLine::hasDefinition(const char* name) {
		Argument* opt = findPointer(&defines, name);
		return (opt == nullptr) ? false : true;
    }
	bool            _CommandLine::hasDefinition(string name) { 
		return hasDefinition(name.c_str());
	}
	bool            _CommandLine::isDefinitionMultiple(const char* name) { 
		Argument& opt = find(&defines, name);
		return (opt.values.size() < 2 ? false : true);
    }
	bool            _CommandLine::isDefinitionMultiple(string name) { 
		return isDefinitionMultiple(name.c_str()); 
	}
	vector<const char  *>  _CommandLine::getDefinitionValues(const char* name) { 
		Argument& opt = find(&defines, name);
		return opt.getValues();
    }

	//////////////////////////////////////////////////////////////////
	
	char* _CommandLine::checkOption       (const char* option) { return (checkParameter(rootOptions, option)); }
	char* _CommandLine::checkFlag         (const char* flag)     { return (checkParameter(rootFlags, flag)); }
	char* _CommandLine::checkParameter    (ParameterTree* root[], const char* parm) {
		size_t idx = 0;
		ParameterTree* base = root[parm[0] - ' '];
		ParameterTree* prev = nullptr;

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
			default: throw CmdLineParameterException(ERR_ARG_ERR, parm);
			}
		}
		if (prev == nullptr) throw CmdLineException(TXT_ARG_NFND, parm);  // primero
		if (idx < strlen(parm) && prev->branchs == 0) { // overtype
			throw CmdLineException(TXT_ARG_NFND1, parm, prev->getReversedWord());
		}
		// Ha salido por base = nullptr

		if (prev->branchs == 1) { 
			char * next = prev->getWord();
			char* base = prev->getReversedWord();
			base[strlen(base) - 1] = 0x0;
			throw CmdLineException(TXT_ARG_NFND2, parm, base, next);
		}
		if (prev->branchs > 1) {
			throw CmdLineException(TXT_ARG_NFND3, parm);
		}
//		if (base == nullptr) throw CmdLineParameterException(parm, prev->getReversedWord());

		std::string ss(parm);
		ss.append(base->getWord());
		return (makeChar(ss));
	}
	void  _CommandLine::updateFromEnv     () {
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
	void  _CommandLine::udpateArgsFromEnv (Group &parms, const char*prfx) {
		char key[255];
		char* value;
		for (auto it = parms.begin(); it != parms.end(); it++) {
			sprintf(key, "%s%s", prfx, it->second.name.c_str());
			value = getenv(key);
			if (value != nullptr) it->second.setFromEnv(value);
        }
	}
	char* _CommandLine::updateOption      (const char* option, char* prev) {
		int pos = std::string(option).find("=");
		if (pos != std::string::npos) return updateDefinition(option);
		validateEntry(option, prev);
		return (checkOption(&(option[1])));
	}
	char* _CommandLine::updateDefinition  (const char* value) {
		const char* ptr = &(value[1]);
		vector<string> toks = tokenize(ptr, "=");
		if (toks.size() != 2)      throw CmdLineParameterException(INV_DEFINITION, value);
		if (toks[0].length() == 0) throw CmdLineParameterException(INV_DEFINITION, value);
		Argument *def = defines.find(toks[0]);
		if (def == nullptr) def = new Define(toks[0].c_str());
		def->initValues(splitArgument(toks[1].c_str()));
		defines.add(def);
		return nullptr;
	}
	char* _CommandLine::updateFlag        (const char* flag, const char* prev, bool value) {
		std::vector<std::string> flags = splitArgument(flag);
		for (std::string f : flags) updateFlagItem((char*)f.c_str(), prev, value);
		return nullptr;
	}
	void  _CommandLine::updateFlagItem    (const char* flag, const char* prev, bool value) {
		std::string name;
		validateEntry(flag, prev);
		try {
			Argument* opt = flags.find(checkFlag(&(flag[1])));
			opt->setValue(value);
		}
		catch (exception ex) {
			char newFlag[3] = "+ ";
			if (strlen(flag) == 2) throw;
			for (size_t i = 1; i < strlen(flag); i++) {
				newFlag[1] = flag[i];
				updateFlagItem(newFlag, prev, value);
			}
		}
	}
	char* _CommandLine::addValueToOption  (const char* value, char* option) {
		if (strlen(option) == 1) throw CmdLineException(ERR_INV_OPTION, option);
		Argument* opt = options.find(option); // Exists!!!!
		validateValue(value, opt->type);
		if ( opt->multiple) (*opt).addValue(value);
		if (!opt->multiple) (*opt).setValue(value);
		return nullptr;
	}
	void  _CommandLine::preInit           (Parameters parms, bool init) {
		ParameterTree** root;

		if (init) {
			memset(&rootOptions, 0x0, sizeof(rootOptions));
			memset(&rootFlags, 0x0, sizeof(rootFlags));
		}
		for (Parm p : parms) {
			Argument option(&p);
			if (attr.sensitive) option.makeUpper();
			Group *map  = (p.instanceOfFlag()) ? &flags : &options;
			root = (p.instanceOfFlag()) ? rootFlags : rootOptions;
			map->add(option.name, &option);
			add2tree(root, option.name.c_str());
		}
	}
	void  _CommandLine::postInit          () {
		updateFromEnv();
		loadHelp();
	}
	void  _CommandLine::loadHelp          () {
		Parameters flagHelp = { Parm("help", false) ,Parm("HELP", false) };
		Argument* arg = flags.find("help");
		if (arg != nullptr) return;
		preInit(flagHelp, false);
		if (!attr.sensitive) {
			arg = flags.find("help");
			arg->source = Source::AUTO;
		}
		arg = flags.find("HELP");
		arg->source = Source::AUTO;
	}
	Flags _CommandLine::getFlags          (bool active, bool def) {
		Flags act;
		bool value;
		for (auto it : flags) {
			value = makeBoolean((def) ? it.second.defValue : it.second.getValue());
			if (it.second.source != Source::AUTO && (active || value)) act.emplace(it.second.name, value);
		}
		return act;
	}
	Argument& _CommandLine::find(Group *group, const char* what) {
		char* ptr = (char *) what;
		if (attr.sensitive) ptr = makeUpper(what);
		Argument* arg = group->find(ptr);
		if (arg == nullptr) throw CmdLineNotFoundException(ERR_NOT_FND, what);
		return *arg;
	}
	Argument* _CommandLine::findPointer(Group *group, const char* what) {
		char* ptr = (char *) what;
		if (attr.sensitive) ptr = makeUpper(what);
		return group->find(ptr);
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
		if (expected.length() > 0) throw CmdLineInvalidTypeException(ERR_INV_TYPE, expected);
	}
	template <typename T>
	T _CommandLine::castValue(auto value) {
		size_t pos;
		string::size_type sz;
		if (is_same<T, int>::value) 
			return any_cast<int>(value);
		if (is_same<T, long>::value) return validateNumber(value); 
//			long l = stol(string(value), &pos, 0);
//			return any_cast<long>(value);
//		}
		if (is_same<T, float>::value) return any_cast<float>(value);
		if (is_same<T, double>::value) return any_cast<double>(value);
//		if (!is_same<T, struct tm>::value) return any_cast<struct tm>(value);
//		if (!is_same<T, filesystem::path>::value) return std::any_cast<filesystem::path>(value);
//		return std::any_cast<string>(value);
		return NULL;
	}
	Options _CommandLine::getOptionsValue(bool def) {
		Options act;
		for (auto it : options) {
			if (it.second.source != Source::AUTO) act.emplace(it.second.name, (def ? it.second.defValue : it.second.getValue()));
		}
		return act;
	}
	void    _CommandLine::checkAlreadySet(Group *group, const char* what) {
		Argument* arg = findPointer(group, what);
		if (arg != nullptr) {
			if (arg->values.size() && !arg->multiple) 
				throw CmdLineDuplicateArgumentException(ERR_ARG_DUP, what);
		}
	}
	const char* _CommandLine::getValue(Group *grp, const char* name) {
		Argument& opt = find(grp, name);
		return opt.getValue();
	}
}

#ifdef _SECURE_DEF_
  #undef _SECURE_DEF_
  #undef _CRT_SECURE_NO_WARNINGS_endif
#endif
