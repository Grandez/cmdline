#pragma once
#include <string>
#include <map>
#include <vector>

#include "parmitem.hpp"
#include "parameter_tree.hpp"

namespace cmdline {
	std::map<std::string, ParmItem> vector2map(std::vector<ParmItem> vect);
	void add2tree(cmdline::ParameterTree* root[], const char* word);
	char* makeChar(std::string str);
}