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
	bool makeBoolean(char* value);
	bool makeBoolean(std::string value);
	Option* findOption(std::unordered_map<std::string, Option>* map, std::string what);
	Option* findOption(std::unordered_map<std::string, Option>* map, char *what);
	std::vector<std::string> splitParameter(char* parm);
	std::vector<std::string> tokenize(char* src, char* pat);
	std::vector<int>         tokenizeNumber(char* src, char* pat);
}