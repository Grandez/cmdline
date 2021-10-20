#pragma once
#include <string>
#include <map>
#include <vector>

#include "parmitem.hpp"
#include "parameter_tree.hpp"

/*
#undef _EXT_
#ifdef __TOOLS_CPP__
#define _EXT_
*/

namespace cmdline {

	std::map<std::string, ParmItem> vector2map(std::vector<ParmItem> vect);
	void add2tree(cmdline::ParameterTree* root[], const char* word);
	char* makeChar(std::string str);
}