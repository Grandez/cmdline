#pragma once

#include <unordered_map>

#include "parameter_tree.hpp"
#include "msg_locale.hpp"
using namespace std;

namespace _cmdline {
#ifdef _WIN32
   #define chdir(a) _chdir(a)
   #define getcwd(a, b) _getcwd(a, b)
   #define strdup(a) _cmdline::myStrdup(a)
#endif

	void  add2tree(ParameterTree* root[], const char* word);
	char* makeChar   (std::string str);
	bool  makeBoolean(const char *value);
 	bool  makeBoolean(std::string value);
	char* makeUpper(const char* str);
	char* strUpper(const char* str);

	vector<std::string> splitArgument(const char* parm);
	vector<std::string> tokenize(const char* src, const char* pat);
	vector<int>         tokenizeNumber(const char* src, const char* pat);
	char*               myStrdup(const char* s, int size); /*!< @private */
	char*               myStrdup(const char* s);           /*!< @private */
	void                defaultDate(char* aux);
}