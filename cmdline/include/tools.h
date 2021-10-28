#pragma once

#include <unordered_map>

#include "parameter_tree.hpp"
#include "types.h"

using namespace std;

namespace _cmdline {
    #define strdup(a) myStrdup(a)
//	unordered_map<std::string, ParmItem> vector2map(vector<ParmItem> vect);
	void  add2tree(ParameterTree* root[], const char* word);
	char* makeChar   (std::string str);
 	bool  makeBoolean(std::string value);
	char* strUpper(const char* str);

//	Argument* findOption(Args* map, std::string what);

	vector<std::string> splitArgument(const char* parm);
	vector<std::string> tokenize(const char* src, const char* pat);
	vector<int>         tokenizeNumber(const char* src, const char* pat);
	char*               myStrdup(const char* s, int size);
	char*               myStrdup(const char* s);
}