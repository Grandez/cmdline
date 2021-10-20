#pragma once
#include <string>
#include <map>

namespace cmdline {

    class ParameterTree {
    public:
        char letter;
        int  branchs = 0;
        ParameterTree() = delete;
        ParameterTree(ParameterTree&) = delete;
        ParameterTree(ParameterTree&&) = delete;
        ParameterTree(const char* parm) { letter = parm[0]; }
        void addBranch(ParameterTree* tree) { children.insert_or_assign(tree->letter, tree); branchs++; }
        std::string getName(const std::string parm, int pos = 1);
        char *getWord();
        ParameterTree* getNext();
        ParameterTree* getChild(char letter);
        void addChild(ParameterTree* child);
        bool hasChild(char letter);
        size_t numChildren() { return children.size(); }
        //    void setBranchs(int branchs) { childrens = std::max(childrens, branchs); }

    private:
        int sizeChildren = 0;
        char* word = 0x0;
        int wordSize = 0;
        std::map<char, ParameterTree*> children;

        char  *getWord(char* base, int sizeBase);
    };
}

