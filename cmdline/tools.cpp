#include "tools.h"
#include <map>
#include <string>
#include <vector>
#include "cmdline.h"

#include "parameter_tree.hpp"

namespace cmdline {

	std::map<std::string, ParmItem> vector2map(std::vector<ParmItem> vect) {
		std::map<std::string, ParmItem> mmap;
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
//				act->branchs++;
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
}