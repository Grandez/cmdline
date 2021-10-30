#pragma once

#include <unordered_map>

#include "parameter_tree.hpp"

using namespace std;

namespace _cmdline {
#ifdef _WIN32
   #define chdir(a) _chdir(a)
   #define getcwd(a, b) _getcwd(a, b)
#endif

    #define strdup(a) _cmdline::myStrdup(a)
	void  add2tree(ParameterTree* root[], const char* word);
	char* makeChar   (std::string str);
 	bool  makeBoolean(std::string value);
	char* strUpper(const char* str);

	vector<std::string> splitArgument(const char* parm);
	vector<std::string> tokenize(const char* src, const char* pat);
	vector<int>         tokenizeNumber(const char* src, const char* pat);
	char*               myStrdup(const char* s, int size);
	char*               myStrdup(const char* s);
}