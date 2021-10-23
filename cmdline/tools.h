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
	bool validateBoolean(char* value);
	Option* findOption(std::unordered_map<std::string, Option>* map, std::string what);
}