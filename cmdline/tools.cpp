#include <regex>
#include <cstdlib>
#include <unordered_map>
#include <string>

#include "arg.hpp"
#include "parmitem.hpp"
#include "cmdline_exceptions.hpp"

using namespace std;
using namespace cmdline;

namespace cmdline {
	/*
	unordered_map<string, ParmItem> vector2map(vector<ParmItem> vect) {
		unordered_map<string, ParmItem> mmap;
		mmap.begin();
		for (size_t i = 0; i < vect.size(); i++) mmap.insert_or_assign(vect[i].name, vect[i]);
		return (mmap);
    }
	*/
	ParameterTree* createTree(const char* word) {
		ParameterTree* root = new ParameterTree(word);
		ParameterTree* prev = root;
		ParameterTree* temp = NULL;
		for (size_t idx = 1; idx < strlen(word); idx++) {
			temp = new ParameterTree(&(word[idx]), prev);
			prev->addChild(temp);
			prev = temp;
		}
		return (root);
	}
	ParameterTree *joinTree(ParameterTree* root, const char* word) {
		int idx = 1; // Here we know first word matches, so we check second letter
		ParameterTree* last = root;
		ParameterTree* act = root->getNext();
		if (act == nullptr) {
			last->addBranch(createTree(&(word[idx])));
			return last;
		}
		bool done = false;
		while (!done) {
			if (act == nullptr) {
				last->addBranch(createTree(&(word[idx])));
				done = true;
				continue;
			}
			if (act->letter == word[idx]) {
				last = act;
				act = act->getNext();
				idx++;
				continue;
			}
			last->addBranch(createTree(&(word[idx])));
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
	bool makeBoolean(string value) { 
		char * val = (char*) value.c_str();

		if (val == nullptr)              return false;
		if (strlen(val) == 0)            return false;
		if (value[0] == '0')               return false;
		if (value[0] == '1')               return true;
		if (strcmp(val, "-1")      == 0) return true;
		if (_stricmp(val, "no"   ) == 0) return false;
		if (_stricmp(val, "false") == 0) return false;
		if (_stricmp(val, "yes"  ) == 0) return true;
		if (_stricmp(val, "true" ) == 0) return true;
		if (_stricmp(val, "si"   ) == 0) return true;
		return false;
	}
	/*
	Argument* findOption(Args* map, string what) {
		try {
			auto res = map->at(what);
			return &(map->at(what));
		}
		catch (out_of_range ex) {
			return (Option*) nullptr;
		}
	}
	*/
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
		return myStrdup(s, strlen(s));
	}

}