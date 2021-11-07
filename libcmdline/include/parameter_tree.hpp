#pragma once
#include <string>
#include <unordered_map>

namespace _cmdline {

    class ParameterTree {
    public:
        char letter;
        int  branchs = 0; // Maximum of branchs along all children
        ParameterTree *parent = nullptr;
        ParameterTree() = delete;
        ParameterTree(ParameterTree&) = delete;
        ParameterTree(ParameterTree&&) = delete;
        ParameterTree(const char* parm, ParameterTree* parent = nullptr) { 
            letter = parm[0]; 
            this->parent = parent;  
        }
        ~ParameterTree();
        ParameterTree&  addBranch(ParameterTree* tree);
        char*           getWord();
        char*           getReversedWord();
        ParameterTree*  getNext();
        ParameterTree*  getChild(char letter);
        ParameterTree*  setParent(ParameterTree* parent) { this->parent = parent; };
        ParameterTree&  addChild(ParameterTree* child);
        bool            hasChild(char letter);
        size_t          numChildren() { return children.size(); }
    private:
        int sizeChildren = 0;
        char* word = 0x0;
        int wordSize = 0;
        std::unordered_map<char, ParameterTree*> children;

        char *getWord(char* base, int sizeBase);
        char *getReversedWord(char* base, int sizeBase);
    };
}
