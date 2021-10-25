#include "tools.h"
#include <map>
#include <string.h>
#include <vector>
#include "cmdline.h"
#include <regex>

#include "cmdline_exceptions.hpp"

namespace cmdline {

	std::unordered_map<std::string, ParmItem> vector2map(std::vector<ParmItem> vect) {
		std::unordered_map<std::string, ParmItem> mmap;
		for (size_t i = 0; i < vect.size(); i++) mmap.insert_or_assign(vect[i].name, vect[i]);
		return (mmap);
    }
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
				parent->branchs = std::max(parent->branchs, last->branchs);
				parent = parent->parent;
			}
		}
	}
	char* makeChar(std::string str) {
		int len = (int) str.length() + 1;
		char* cstr = new char[len];
		strcpy_s(cstr, len, str.c_str());
		return (cstr);
	}
	bool makeBoolean(std::string value) { return makeBoolean((char*)value.c_str()); }
	bool makeBoolean(char* value) {
		//TODO Launch exception on invalid entry
		if (value == nullptr)              return false;
		if (strlen(value) == 0)            return false;
		if (value[0] == '0')               return false;
		if (value[0] == '1')               return true;
		if (strcmp(value, "-1")      == 0) return true;
		if (_stricmp(value, "no"   ) == 0) return false;
		if (_stricmp(value, "false") == 0) return false;
		if (_stricmp(value, "yes"  ) == 0) return true;
		if (_stricmp(value, "true" ) == 0) return true;
		if (_stricmp(value, "si"   ) == 0) return true;
		return false;
	}

	Option* findOption(std::unordered_map<std::string, Option>* map, char* what) {
		return findOption(map, std::string(what));
	}
	Option* findOption(std::unordered_map<std::string, Option>* map, std::string what) {
		try {
			return &map->at(what);
		}
		catch (std::out_of_range ex) {
			return (Option*) nullptr;
		}
	}
	std::vector<std::string> splitParameter(char* parm) {
		char* parse = strdup(parm);
		char* next_token = NULL;
		char* token = nullptr;
		char* tmp = nullptr;;
		bool quote = false;
		std::vector<char*> toks;
		std::vector<std::string> toks2;

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
	std::vector<std::string> tokenize(char* src, char* pat) {
		std::string str(src);

		std::regex reg(pat);

		std::sregex_token_iterator iter(str.begin(), str.end(), reg, -1);
		std::sregex_token_iterator end;
		std::vector<std::string> vec(iter, end);
		return vec;
	}
	std::vector<int> tokenizeNumber(char* src, char* pat) {
		std::vector<int> res;
		std::vector<std::string> vec = tokenize(src, pat);
		for (std::string s : vec) res.push_back(std::stoi(s));
		return res;
	}

}