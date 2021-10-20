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
			temp = new ParameterTree(&(word[idx]));
			prev->addChild(temp);
			prev = temp;
		}
		return (root);
	}
	void           joinTree(ParameterTree* root, const char* word) {
		int idx = 1; // Here we know first word matches, so we check second letter
		ParameterTree* last = root;
		ParameterTree* act = root->getNext();
		if (act == nullptr) {
			last->addBranch(createTree(&(word[idx])));
			return;
		}
		bool done = false;
		while (!done) {
			if (act == nullptr) {
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
			last->addBranch(createTree(&(word[idx])));
			done = true;
		}
	}
		void add2tree(ParameterTree* root[], const char* word) {
		int pos = word[0] - ' ';
		if (root[pos] == nullptr) {
			root[pos] = createTree(word);
	//		cout << root[pos]->getWord() << endl;
		}
		else {
			joinTree(root[pos], word);
		}
	}
	char* makeChar(std::string str) {
		int len = (int) str.length() + 1;
		char* cstr = new char[len];
		strcpy_s(cstr, len, str.c_str());
		return (cstr);
	}
}