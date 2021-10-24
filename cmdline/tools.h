#pragma once
#include <string>
#include <unordered_map>
#include <vector>

#include "parmitem.hpp"
#include "parameter_tree.hpp"
#include "option.hpp"

namespace cmdline {
	std::unordered_map<std::string, ParmItem> vector2map(std::vector<ParmItem> vect);
	void add2tree(cmdline::ParameterTree* root[], const char* word);
	char* makeChar(std::string str);
	inline bool makeBoolean(char* value);
	inline bool makeBoolean(std::string value);
	Option* findOption(std::unordered_map<std::string, Option>* map, std::string what);
	Option* findOption(std::unordered_map<std::string, Option>* map, char *what);
	std::vector<std::string> splitParameter(char* parm);
}