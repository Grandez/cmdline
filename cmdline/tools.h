#pragma once

#include <string>
#include <unordered_map>

#include "arg.hpp"
#include "parmitem.hpp"
#include "parameter_tree.hpp"

using namespace std;
using namespace cmdline;

namespace cmdline {
	unordered_map<string, ParmItem> vector2map(vector<ParmItem> vect);
	void add2tree(ParameterTree* root[], const char* word);
	char* makeChar(string str);
 	bool makeBoolean(string value);

//	Argument* findOption(Args* map, std::string what);

	vector<string> splitParameter(const char* parm);
	vector<string> tokenize(const char* src, char* pat);
	vector<int>    tokenizeNumber(const char* src, char* pat);
}