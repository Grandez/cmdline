// #include <iostream>
#include <string>
// #include <sstream>

#include "parameter_tree.hpp"


namespace cmdline {
	void ParameterTree::addChild(ParameterTree* child) {
		children.insert_or_assign(child->letter, child);
		branchs = (int)children.size();
	}

	char * cmdline::ParameterTree::getWord() {
		char* word = (char*)calloc(16, sizeof(char));
		word[0] = letter;

		if (children.size() == 0) return (word);
		return (children.begin()->second->getWord(word, 16));
	}

	char * ParameterTree::getWord(char* word, int sizeBase) {
		int pos = (int)strlen(word);
		if (pos == sizeBase) {
			sizeBase += 16;
			word = (char*)realloc(word, sizeBase);
		}
		word[pos] = letter;
		word[pos + 1] = 0x0;
		if (children.size() == 0) return (word);
		return (children.begin()->second->getWord(word, sizeBase));
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

	std::string ParameterTree::getName(const std::string parm, int pos) {
		// Recibre help
		// h existe, es el propio
	/*
		// La cadena se ha acabado pero no hay duda
		if (parm.at(pos + 1) == 0x0 && this->branchs == 1) return (concatena lo anterior y lo siguiente)
		if (this->hasChild(parm.at(pos))) {
			getName(parm, pos + 1);
		}
		*/
		return (" ");
	}
}