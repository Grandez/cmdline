#include <vector>
#include <string>
#include <utility>

#include "parmitem.hpp"
#include "commandline.hpp"
#include "cmdline_exceptions.hpp"
#include "parameter_tree.hpp"
#include "tools.h"
#include "validations.h"


namespace cmdline {

	cmdline::ParameterTree* rootOptions[128] = { nullptr };
	cmdline::ParameterTree* rootFlags[128] = { nullptr };
	CommandLine::CommandLine(std::vector<ParmItem> parms) {
		bool value;
		for (ParmItem p : parms) {
			if (p.type == FLAG) {
				value = (p.value[0] == '1') ? true : false;
				defFlags.insert_or_assign(std::string(p.name), value);
			}
			else {
				defOptions.insert_or_assign(std::string(p.name), p);
			}
		}
		add2tree(rootFlags, "help");
	};
	CommandLine::CommandLine(std::vector<cmdline::ParmItem> options, std::vector<std::pair<char *, bool>> flags) {
		this->defOptions = vector2map(options);
		for (std::pair f : flags) defFlags.insert_or_assign(f.first, f.second);
		for (int i = 0; i < options.size(); i++) add2tree(rootOptions, options[i].name);
		add2tree(rootFlags, "help");
	};
	int CommandLine::parse(const int argc, char* argv[]) {
		char* prev = nullptr;
		for (int i = 0; i < argc; i++) {
			switch (argv[i][0]) {
			case '/': prev = addParameterToOptions(argv[i], prev); break;
			case '+': prev = addParameterToFlags(argv[i], prev);   break;
			case '-': prev = removeParameterFromFlags(argv[i], prev);
			default:
				if (prev == NULL) {
					addParameterToInput(argv[i]);
				}
				else {
					addValueToOption(argv[i], prev);
				}
			}
		}
		//	checkParameter(rootOptions, "pepe");
		return 0;
	}
	
	char*        CommandLine::checkOption(char* option) {
		return (checkParameter(rootOptions, option));
	}
	char*        CommandLine::checkFlag(char* flag) {
		return (checkParameter(rootFlags, flag));
	}
	char*        CommandLine::addParameterToOptions(char* option, char* prev) {
		validateEntry(option, prev);
		return (checkOption(&(option[1])));
	}
	char*        CommandLine::addParameterToFlags(char* flag, char* prev) {
		validateEntry(flag, prev);
		std::string name = checkFlag(&(flag[1]));
		flags.insert(name);
		return (nullptr);
	}
	char*        CommandLine::removeParameterFromFlags(char* flag, char* prev) {
		validateEntry(flag, prev);
		std::string name = checkFlag(&(flag[1]));
		flags.erase(name);
		return (nullptr);
	}
	inline char* CommandLine::addParameterToInput(char* input) {
		inputs.push_back(input);
		return (nullptr);
	}
	char*        CommandLine::addValueToOption(char* value, char* option) {
		validateValue(value, option);
		if (strlen(option) == 1) throw CmdLineException("Invalid Option", option);
		return (checkOption(&(option[1])));
	}
	void         CommandLine::validateValue(char* value, char* option) {
		ParmItem def = defOptions.find(option)->second;
		switch (def.type) {
		case cmdline::NUMBER: validateNumber(value); break;
		case cmdline::DECIMAL: validateDecimal(value); break;
		case cmdline::DATE: validateDate(value); break;
		case cmdline::TIME: validateTime(value); break;
		case cmdline::DIR: validateDir(value); break;
		case cmdline::FILE: validateFile(value); break;
		case cmdline::DIR_EXISTS: validateDirExist(value); break;
		case cmdline::FILE_EXISTS: validateFileExist(value); break;
		}
	}
	char*        CommandLine::checkParameter(ParameterTree* root[], char* parm) {
		int idx = 0;
		ParameterTree* base = root[parm[0] - ' '];
		ParameterTree* prev = nullptr;

		while (idx < strlen(parm) && base != nullptr) {
			prev = base;
			base = (base->letter == parm[idx]) ? base->getChild(parm[idx + 1]) : nullptr;
			idx++;
		}

		if (idx == strlen(parm)) { // Parse completo
			if (base == nullptr) return (parm);
		    std::string str(parm);
			str.append(base->getWord());
			return (makeChar(str));
		}

		// Ha salido por base = nullptr
		if (prev == nullptr) throw CmdLineException("No existe");  // primero
		if (prev->branchs > 1) throw CmdLineException("No definido con alternativa 2", "varias alernativa");
		if (prev->branchs == 1) throw CmdLineException("No definido con alternativa 1", "tipo");
		std::string ss(parm);
		ss.append(base->getWord());
		return (makeChar(ss));
	}

	template <typename T>  T  CommandLine::getOption(char* name)          {}
	template <typename T>  T  CommandLine::getOption(std::string name) { getOption<T>(name.c_str()};

}
