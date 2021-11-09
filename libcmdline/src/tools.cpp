#define _CRT_SECURE_NO_WARNINGS

#include <regex>
#include <ctime>
#include <locale>
#include <cctype>

#include "tools.hpp"
#include "parameter_tree.hpp"
#include "cmdline_exceptions.hpp"

using namespace std;
using namespace cmdline;

namespace _cmdline {
	char _upper[64] = "";
	ParameterTree* createTree(const char* word) {
		ParameterTree* root = new ParameterTree(word);
		ParameterTree* prev = root;
		ParameterTree* temp = NULL;
		for (size_t idx = 1; idx < strlen(word); idx++) {
			temp = new ParameterTree(&(word[idx]), prev);
			prev->addChild(temp);
			prev = temp;
		}
        prev->last = true; 
		return (root);
	}
	ParameterTree *joinTree(ParameterTree* root, const char* word) {
		int idx = 1; // Here we know first word matches, so we check second letter
        root->branchs++;
		ParameterTree* last = root;
		ParameterTree* act = root->getNext();
		if (act == nullptr) {
            last->branchs++;
			last->addBranch(createTree(&(word[idx])));
			return last;
		}
		bool done = false;
		while (!done) {
			if (act == nullptr) {
                last->branchs++;
				last->addBranch(createTree(&(word[idx])));
				done = true;
				continue;
			}
			if (act->letter == word[idx]) {
                act->branchs++; 
				last = act;
				act = act->getNext();
				idx++;
				continue;
			}
            if (word[idx] == 0x0) {
                last->last = true;
            } else {
			    last->addBranch(createTree(&(word[idx])));
            }
			done = true;
		}
		return last;
	}
	void add2tree(ParameterTree* root[], const char* word) {
		ParameterTree* last   = nullptr;
		ParameterTree* parent = nullptr;
		int pos = word[0] - ' ';
		if (root[pos] == nullptr) {
			root[pos] = createTree(word);
		}
		else {
			last = joinTree(root[pos], word);
			parent = last->parent;
			while (parent) {
				parent->branchs = max(parent->branchs, last->branchs);
				parent = parent->parent;
			}
		}
	}
	char* makeChar(string str) {
		int len = (int) str.length() + 1;
		char* cstr = new char[len];
		strcpy_s(cstr, len, str.c_str());
		return (cstr);
	}
	bool makeBoolean(const char* value) {
		string str(strUpper(value));
		if (str.compare("0") == 0)     return false;
		if (str.compare("FALSE") == 0) return false;
		if (str.compare("NO") == 0)    return false;
		return true;
	}
	bool makeBoolean(string value) { 
		return makeBoolean(value.c_str());
	}
	char* makeUpper(const char* str) {
		
		size_t i;
		for (i = 0; i < strlen(str); i++) _upper[i] = toupper(str[i]);
		_upper[i] = 0x0;
		return _upper;
	}

	vector<string> splitArgument(const char* parm) {
		char* parse = strdup(parm);
		char* next_token = NULL;
		char* token = nullptr;
		char* tmp = nullptr;;
		bool quote = false;
		vector<char*> toks;
		vector<string> toks2;

		token = strtok_s(parse, ",", &next_token);
		while (token) {
			toks.push_back(token);
			token = strtok_s(NULL, ",", &next_token);
		}

		for (char* t : toks) {
			if (t[0] == '"') {
				tmp = strdup(&(t[1]));
				quote = (tmp[strlen(tmp) - 1] == '\"') ? false : true;
				if (tmp[strlen(tmp) - 1] == '\"') tmp[strlen(tmp) - 1] = 0x0;
				toks2.push_back(tmp);
			}
			else {
				if (quote) {
					toks2[toks2.size()-1].append(",");
					if (t[strlen(t) - 1] == '"') {
						t[strlen(t) - 1] = 0x0;
						quote = false;
					}
					toks2[toks2.size() - 1].append(strdup(t));
				}
				else {
					toks2.push_back(strdup(t));
				}
			}
		}
		free(parse);
		if (quote) {
			throw CmdLineException("Missing comma");
		}
		return toks2;
	}
	vector<string> tokenize(const char* src, const char* pat) {
		string str(src);
		regex reg(pat);

		sregex_token_iterator iter(str.begin(), str.end(), reg, -1);
		sregex_token_iterator end;
		vector<string> vec(iter, end);
		return vec;
	}
	vector<int> tokenizeNumber(const char* src, const char* pat) {
		vector<int> res;
		vector<string> vec = tokenize(src, pat);
		for (string s : vec) res.push_back(stoi(s));
		return res;
	}

	char* strUpper(const char* str) {
		char* tmp = strdup(str);
		for (size_t i = 0; i < strlen(str); i++) tmp[i] = toupper(tmp[i]);
		return tmp;
	}

	// From http ://www.olivierlanglois.net/idioms_for_using_cpp_in_c_programs.html
	// Variant #1
	char* myStrdup(const char* s, int size) {
		++size;
		char* res = static_cast<char*>(malloc(size));
		if (!res) throw runtime_error("No memory");
		memcpy(res, s, size);
		 return res;
	}

	// Variant #2
	char* myStrdup(const char* s) {
		return myStrdup(s, (int) strlen(s));
	}
	void defaultDate(char *aux) {
		std::time_t t = std::time(0);
		std::tm* now = std::localtime(&t);
		time_base::dateorder d = use_facet<time_get<char>>(locale()).date_order();
		switch (d) {
		       case time_base::mdy: 
			        sprintf(aux, "%02d/%02d/%04d", now->tm_mon, now->tm_mday + 1, now->tm_year + 1900);
					break;
		       case time_base::ymd: 
				    sprintf(aux, "%04d/%02d/%02d", now->tm_year, now->tm_mon + 1, now->tm_mday);
					break;
		       case time_base::ydm: 
				    sprintf(aux, "%04d/%02d/%02d", now->tm_year, now->tm_mday, now->tm_mon + 1);
					break;
			   default:
			        sprintf(aux, "%02d/%02d/%04d", now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
		}
	}
    vector<string>      vectorChar2String(vector<const char *> data) {
        vector<string> res;
        for (int i = 0; i < data.size(); i++) {
             res.push_back(data[i]);
        }  
        return res;
    }
}