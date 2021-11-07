#include "tools.hpp"
#include "parameter_tree.hpp"
#include <iostream>

using namespace std;

namespace _cmdline {
	ParameterTree& ParameterTree::addChild(ParameterTree* child) {
		children.insert_or_assign(child->letter, child);
		branchs = (int)children.size();
		return* this;
	}
	ParameterTree& ParameterTree::addBranch(ParameterTree* tree) {
		children.insert_or_assign(tree->letter, tree);
		branchs++;
		return *this;
	}
	char * ParameterTree::getWord() {
		if (word) free(word);
		char* word = (char*) calloc(16, sizeof(char));
		if (word) word[0] = letter;

		if (children.size() == 0) return (word);
		return (children.begin()->second->getWord(word, 16));
	}
	char* ParameterTree::getWord(char* word, int sizeBase) {
		int pos = (int)strlen(word);
		if (pos == sizeBase) {
			sizeBase += 16;
			if (word) word = (char*) realloc(word, sizeBase);
		}
		if (word) {
			word[pos] = letter;
			word[pos + 1] = 0x0;
		}
		if (children.size() == 0) return (word);
		return (children.begin()->second->getWord(word, sizeBase));
	}
	char* ParameterTree::getReversedWord() {
		char* word = (char*)calloc(16, sizeof(char));
		if (word != nullptr) word[0] = letter;
		if (parent != nullptr) word = parent->getReversedWord(word, 16);
	    std::string str(strdup(word));
		free(word);
		std::reverse(str.begin(), str.end());
		return strdup(str.c_str());
	}
	char * ParameterTree::getReversedWord(char* word, int sizeBase) {
		int pos = (int)strlen(word);
		if (pos == sizeBase) {
			sizeBase += 16;
			if (word) word = (char*) realloc(word, sizeBase);
		}
		if (word) {
			word[pos] = letter;
			word[pos + 1] = 0x0;
			if (parent != nullptr) word = parent->getReversedWord(word, 16);
		}
		return (word);
	}
	ParameterTree* ParameterTree::getNext() {
		if (children.size() == 0) return nullptr;
		return (children.begin()->second);
	}
	bool ParameterTree::hasChild(char letter) {
		auto it = children.find(letter);
		return (it == children.end() ? false : true);
	}
	ParameterTree* ParameterTree::getChild(char letter) {
		auto it = children.find(letter);
		return (it == children.end() ? nullptr : it->second);
	}
	ParameterTree::~ParameterTree() {
		std::cout << "detructor del arbol\n";
		if (word) free(word);
		for (auto it : children) {
			delete it.second;
		}
	}
}