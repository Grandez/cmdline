#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

#include "config.h"
#include "commandline.hpp"
#include "argument.hpp"
#include "tools.hpp"
#include "validations.hpp"
#include "cmdline_exceptions.hpp"
#include "defines.hpp"

#include "commandline_aux.hpp"

using namespace std;

namespace _cmdline {
constexpr auto OPTION_OR_DEFINITION = '/';
constexpr auto  FLAG_ACTIVE         =  '+';
constexpr auto  FLAG_INACTIVE       =  '-';

	ParameterTree* rootOptions[128];
	ParameterTree* rootFlags[128];
    char *programName = nullptr;
	void launchHelpIfActive(CommandLine *ptr) {
		int help = 0;
		HelpRequested *ex = nullptr;
		if (ptr->hasFlag("HELP")) help |= 2;
		if (ptr->hasFlag("help")) help |= 1;
		if (help) {
			Flags flags = ptr->getDefaultFlags(false);
			std::unordered_map<string, string> options = ptr->getDefaultOptions();
//			delete ptr;
		    if (help >= 2) throw new HelpDetailedRequested(strdup(programName), flags, options);
			throw new HelpSimpleRequested(strdup(programName), flags, options);
		}
	}
	                    CommandLine::CommandLine(int argc, const char** argv, Parameters parms, bool sensitive, bool strict) {
		std::cout << "Crea CommandLine\n";
		this->sensitive = sensitive;
		this->strict = strict;
		memset(&rootOptions, 0x0, sizeof(rootOptions));
		memset(&rootFlags, 0x0, sizeof(rootFlags));
        loadParameters(parms);
		updateValuesFromEnvironment();
		loadHelpFlags();
		parseCommandLine(argc, argv);
	}
	                    CommandLine::~CommandLine() {
		std::cout << "Delete CommandLine\n";
		for (int i = 0; i < 128; i++) {
			
			if (rootOptions[i]) {
				std::cout << "deleting option " << i << "\n";
				delete rootOptions[i];
			}
			if (rootFlags[i])  {
				std::cout << "deleting flag " << i << "\n";
				delete rootFlags[i];
			}
		}
		std::cout << "Fin Delete CommandLine\n";
	}
	vector<const char*> CommandLine::getArgs() {
		return inputs;
	}
	bool   CommandLine::hasFlag(const char* name) {
		Argument& opt = find(&flags, name);
		return makeBoolean(opt.getValue());
	}
	Flags  CommandLine::getDefaultFlags(bool allValues) { // Valores por defecto
		return getFlags(allValues, true);
	}
	Flags  CommandLine::getCurrentFlags(bool allValues) {
		return getFlags(allValues, false);
	}
	bool   CommandLine::hasOption(const char* name) {
		Argument& opt = find(&options, name);
		return (strlen(opt.getValue()) == 0 ? false : true);
	}
	bool   CommandLine::isOptionMultiple(const char* name) {
		Argument& opt = find(&options, name);
		return (opt.values.size() > 1);
	}
	vector<const char*> CommandLine::getOptionValues(const char* name) {
		Argument& opt = find(&options, name);
		return opt.getValues();
	}
	int    CommandLine::getOptionNumValues(const char* name) {
		Argument& opt = find(&options, name);
		return (int) opt.values.size();
	}
	const char* CommandLine::getOption(const char* name) {
		return getValue(&options, name);
	}
	unordered_map<string,string>  CommandLine::getDefaultOptions() {
		return getOptionsValue(true);
	}
	Options CommandLine::getCurrentOptions() {
//		return getOptionsValues(false);
		return Options();
	}
	bool    CommandLine::hasDefinition(const char* name) {
		Argument* opt = findPointer(&defines, name);
		return (opt == nullptr) ? false : true;
	}
	bool    CommandLine::isDefinitionMultiple(const char* name) {
		Argument& opt = find(&defines, name);
		return (opt.values.size() < 2 ? false : true);
	}
	vector<const char*>  CommandLine::getDefinitionValues(const char* name) {
		Argument& opt = find(&defines, name);
		return opt.getValues();
	}
	int      CommandLine::getDefinitionNumValues(const char* name) {
		Argument& opt = find(&defines, name);
		return (int) opt.values.size();
	}
	Options  CommandLine::getDefinitions() {
		Options opts;
		for (auto it = defines.begin(); it != defines.end(); it++){
			opts.emplace(it->second.name, it->second.getStringValues());
		}
        return opts;
	}
	unordered_map<string, string> CommandLine::getOptionsValue(bool def) {
		unordered_map<string, string> act;
		for (auto it : options) {
			act.emplace(it.first, it.second.getValue());
//			string str((def ? it.second.defValue : it.second.getValue()));
//			vector<string> v;
//			v.push_back(def ? it.second.defValue : it.second.getValue());
//			if (it.second.source != Source::AUTO) act.emplace(it.second.name, v);
		}
		return act;
	}
	cmdline::Type CommandLine::getType(const char *name) {
		Argument* opt = options.find(name);
		return opt->type;
	}
	
	// /////////////////////////////////////////////////////////////
	// PRIVATES
	// /////////////////////////////////////////////////////////////
	void  CommandLine::parseCommandLine(int argc, const char** argv) {
		 programName = strdup(argv[0]);
		 char *configFile = configFileInCommandLine(argc, argv);
		 if (configFile) processConfigFile(configFile);

		 char firstLetter;
		 char parmName[64] = "";
		 char* prevToken = nullptr;

		 for (int idxArgument = 1; idxArgument < argc; idxArgument++) {
		      firstLetter = getFirstCharacter(argv[idxArgument]);
			  if (isParameter(firstLetter)) {
				  copyParameterInUpperCase(argv[idxArgument], sensitive, parmName);
			   }
			   switch (firstLetter) {
			           case OPTION_OR_DEFINITION: 
                            if (isConfigFile(argc, argv, idxArgument, sensitive)) {
                                idxArgument++;
                                break;
                            }
                            prevToken = processOptionOrDefinition(argv[idxArgument], prevToken); 
                            break;
			           case FLAG_ACTIVE:           
                            activeFlag   (argv[idxArgument], prevToken); 
                            prevToken = nullptr;
                            break;
			           case FLAG_INACTIVE:   
				            if (!updateFlagHelp(argv[idxArgument], prevToken)) {
				                inactiveFlag (argv[idxArgument], prevToken); 
                            }
                            prevToken = nullptr;
				            break;
			          default:                 
				           if (prevToken == nullptr) 
                               addToInputs(argv[idxArgument]);
				           if (prevToken != nullptr) {
                               addValueToOption(argv[idxArgument], prevToken);
                               prevToken = nullptr;
                           }
			   }
		 }
		launchHelpIfActive(this);
	}
    char* CommandLine::processOptionOrDefinition(const char *argv, char *prevToken) {
   	     char *optionName;
   	     size_t pos = std::string(argv).find("=");
   	     if (pos != std::string::npos) return processDefinition(argv);
   	     validateEntry(argv, prevToken);
   	     optionName = checkOption(&(argv[1]));
   	     if (strict) checkAlreadySet(&options, prevToken);
   	     return optionName;
   }
    char* CommandLine::processDefinition(const char *argv) {
   	     const char* ptr = &(argv[1]);
   	     vector<string> toks = tokenize(ptr, "=");
   	     if (toks.size() != 2)      throw cmdline::CmdLineParameterException(INV_DEFINITION, argv);
   	     if (toks[0].length() == 0) throw cmdline::CmdLineParameterException(INV_DEFINITION, argv);
   	     Argument* def = defines.find(toks[0]);
   	     if (def == nullptr) def = new Define(toks[0].c_str());
   	     def->addValues(splitArgument(toks[1].c_str()));
   	     defines.add(def);
   	     return nullptr;
   }
    char* CommandLine::activeFlag(const char *flag, char *prev) {
         std::vector<std::string> flags = splitArgument(flag);
         for (std::string f : flags) updateFlagItem((char*)f.c_str(), prev, true);
         return nullptr;
   }
    char* CommandLine::inactiveFlag(const char *flag, char *prev) {
   	     std::vector<std::string> flags = splitArgument(flag);
   	     for (std::string f : flags) updateFlagItem((char*)f.c_str(), prev, false);
   	     return nullptr;
   }
    void  CommandLine::updateFlagItem(const char* flag, const char* prev, bool value) {
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
    void  CommandLine::addToInputs(const char *arg) {
	        inputs.push_back(strdup(arg));
    }
    char* CommandLine::addValueToOption(const char* value, char* option) {
         if (strlen(option) == 1) throw CmdLineException(ERR_INV_OPTION, option);
         Argument* opt = options.find(option); // Exists!!!!
         validateValue(value, opt->type);
         if (opt->multiple)  (*opt).addValue(value);
         if (!opt->multiple) (*opt).setValue(value);
         return nullptr;
   }

	char* CommandLine::updateOption(const char* option, char* prev) {
          size_t pos = std::string(option).find("=");
		  if (pos != std::string::npos) return updateDefinition(option);
		  validateEntry(option, prev);
		  return (checkOption(&(option[1])));
	}
	char* CommandLine::updateDefinition(const char* value) {
	      const char* ptr = &(value[1]);
		  vector<string> toks = tokenize(ptr, "=");
		  if (toks.size() != 2)      throw CmdLineParameterException(INV_DEFINITION, value);
		  if (toks[0].length() == 0) throw CmdLineParameterException(INV_DEFINITION, value);
		  Argument* def = defines.find(toks[0]);
		  if (def == nullptr) def = new Define(toks[0].c_str());
		  def->addValues(splitArgument(toks[1].c_str()));
		  defines.add(def);
		  return nullptr;
	}
	char* CommandLine::updateFlag(const char* flag, const char* prev, bool value) {
		std::vector<std::string> flags = splitArgument(flag);
		for (std::string f : flags)
			updateFlagItem((char*)f.c_str(), prev, value);
		return nullptr;
	}

	Flags CommandLine::getFlags(bool active, bool defaultValues) {
          Flags act;
          bool value;
          for (auto it : flags) {
          	value = makeBoolean((defaultValues) ? it.second.defValue : it.second.getValue());
          	if (it.second.source != Source::AUTO && (active || value)) act.emplace(it.second.name, value);
          }
          return act;
	}

	Argument& CommandLine::find(Group* group, const char* what) {
         char* ptr = (char*)what;
         if (sensitive) ptr = makeUpper(what);
         Argument* arg = group->find(ptr);
         if (arg == nullptr) throw CmdLineNotFoundException(ERR_NOT_FND, what);
         return *arg;
	}
	Argument* CommandLine::findPointer(Group* group, const char* what) {
         char* ptr = (char*)what;
         if (sensitive) ptr = makeUpper(what);
         return group->find(ptr);
	}

	const char* CommandLine::getValue(Group* grp, const char* name) {
        Argument& opt = find(grp, name);
        return opt.getValue();
	}
	void  CommandLine::loadParameters(Parameters parms) {
		ParameterTree** root;

		for (Parm p : parms) {
			Argument option(&p);
			if (sensitive) option.makeUpper();
			bool isFlag = (p.instanceOfFlag() || p.type == Type::FLAG) ? true : false;
			Group* map = (isFlag) ? &flags : &options;
			root       = (isFlag) ? rootFlags : rootOptions;
			map->add(option.name, &option);
			add2tree(root, option.name.c_str());
		}
	}
	void  CommandLine::loadHelpFlags() {
		Parameters flagsHelp = { Parm("help", false) ,Parm("HELP", false) };
		Argument* arg = flags.find("help");
		if (arg != nullptr) return;
		loadParameters(flagsHelp);
		if (!sensitive) {
			arg = flags.find("help");
			arg->source = Source::AUTO;
		}
		arg = flags.find("HELP");
		arg->source = Source::AUTO;
	}
	void  CommandLine::updateValuesFromEnvironment() {
		char key[255];
		char* p = (char*)"";
		Argument* arg = options.find(ENV_PREFFIX);
		if (arg != nullptr) {
			sprintf(key, "%s_", arg->name.c_str());
			p = strdup(key);
		}
		udpateArgsFromEnv(options, p);
		udpateArgsFromEnv(flags, p);
		if (arg != nullptr) free(p);
	}
	void  CommandLine::udpateArgsFromEnv(Group& parms, const char* prfx) {
		char key[255];
		char* value;
		for (auto it = parms.begin(); it != parms.end(); it++) {
			sprintf(key, "%s%s", prfx, it->second.name.c_str());
			value = getenv(key);
			if (value != nullptr) it->second.setFromEnv(value);
		}
	}
	void  CommandLine::checkAlreadySet(Group* group, const char* what) {
		Argument* arg = findPointer(group, what);
		if (arg != nullptr && (arg->values.size() && !arg->multiple)) {
				throw CmdLineDuplicateArgumentException(ERR_ARG_DUP, what);
		}
	}
	char* CommandLine::checkOption(const char* option) { return (checkParameter(rootOptions, option)); }
	char* CommandLine::checkFlag(const char* flag)     { return (checkParameter(rootFlags, flag)); }
	char* CommandLine::checkParameter(ParameterTree* root[], const char* parm) {
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
			default: throw new CmdLineParameterException(ERR_ARG_ERR, parm);
		}
			}
			if (prev == nullptr) throw new CmdLineException(TXT_ARG_NFND, parm);  // primero
			if (idx < strlen(parm) && prev->branchs == 0) { // overtype
				throw new CmdLineException(TXT_ARG_NFND1, parm, prev->getReversedWord());
			}
			// Ha salido por base = nullptr

			if (prev->branchs == 1) {
				char* next = prev->getWord();
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

    void  CommandLine::processConfigFile (char *fname) {
    }
    bool  CommandLine::updateFlagHelp    (const char *arg, char *prev) {
         char *flag = checkKeywordHelp(arg);
         if (flag == nullptr) return false;
         updateFlag(flag, prev, true);
         return true;
    }
}
/*
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
    _CommandLine::_CommandLine(int argc,  char**  argv, Parameters parms, bool sensitive, bool strict) {
		this->sensitive = sensitive;
		this->strict    = strict;
	    preInit(parms);
	    postInit();
		parse(argc, argv);
    }
	vector<const char*> _CommandLine::getArgs() {
		return inputs;
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
	bool _CommandLine::isOptionMultiple(const char* name) {
		Argument& opt = find(&options, name);
		return (opt.values.size() > 1);
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
	bool            _CommandLine::hasDefinition(const char* name) {
		Argument* opt = findPointer(&defines, name);
		return (opt == nullptr) ? false : true;
    }
	bool            _CommandLine::isDefinitionMultiple(const char* name) { 
		Argument& opt = find(&defines, name);
		return (opt.values.size() < 2 ? false : true);
    }
	vector<const char  *>  _CommandLine::getDefinitionValues(const char* name) { 
		Argument& opt = find(&defines, name);
		return opt.getValues();
    }

	//////////////////////////////////////////////////////////////////


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
		if (sensitive) ptr = makeUpper(what);
		Argument* arg = group->find(ptr);
		if (arg == nullptr) throw CmdLineNotFoundException(ERR_NOT_FND, what);
		return *arg;
	}
	Argument* _CommandLine::findPointer(Group *group, const char* what) {
		char* ptr = (char *) what;
		if (sensitive) ptr = makeUpper(what);
		return group->find(ptr);
	}
	template <typename T>
	void _CommandLine::checkType(T, Type type) {
		string expected("");
		switch (type) {
		case Type::NUMBER:  if (!is_same<T, int> && !is_same<T, long>) expected = "number";break;
		case Type::DECIMAL: if (!is_same<T, float> && !is_same<T, double>) expected = "decimal"; break;
		case Type::DATE:   if (!is_same<T, struct tm>) expected = "date";break;
		case Type::TIME:   if (!is_same<T, struct tm>) expected = "time";break;
		case Type::DATETIME: if (!is_same<T, struct tm>) expected = "datetiem"; break;
		case Type::TMS:      if (!is_same<T, chrono::time_point>) expected = "timestamp";break;
		case Type::DIR:
		case Type::DIR_EXISTS: if (!is_same<T, filesystem::path>) expected = "directory";break;
		case Type::FILE:
		case Type::FILE_EXISTS: if (!is_same<T, filesystem::path>) expected = "file";break;
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
	const char* _CommandLine::getValue(Group *grp, const char* name) {
		Argument& opt = find(grp, name);
		return opt.getValue();
	}
}
*/