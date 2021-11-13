#pragma once

#include <vector>
#include <string>
using namespace std;

namespace jggtools {
class sstring : public string {
public:

    sstring() : string() {}
    sstring(string str) : string(str) {};
    sstring(const sstring& obj) : string(obj) {}
    sstring(const char *src) : string(src) {}
    sstring(char *src)       : string(src) {}
    sstring(const string& str, size_type pos, size_type n) : string(str,pos,n) {}

    sstring&             ltrim();
    sstring&             rtrim();
    sstring&             trim();
    sstring&             toUpper();
    sstring&             toLower();
    sstring*     makeLower();
    sstring*     makeUpper();

    sstring*  toString();        
    const char*   toChar();
    char*         toArr();
    bool makeBoolean(const char* value);
    bool makeBoolean(sstring value);

    vector<char *>  tokenize(const char* pat);
    vector<sstring> tokenize(string pat);
/*
    void tokenizeFree(void **ptr);
    char** tokenize(const char* src, const char* pat);
    int** tokenizeNumber(const char* src, const char* pat);
*/
};
/*
#ifdef _WIN32
   #define chdir(a) _chdir(a)
   #define getcwd(a, b) _getcwd(a, b)
   #define strdup(a) myStrdup(a)
#endif

using namespace std;

namespace jggtools {
char*               myStrdup(const char* s, int size); 
char*               myStrdup(const char* s);
vector<char *>  tokenize(const char* src, const char* pat);
vector<string>  tokenize(string src, const char* pat);
vector<int>     tokenizeNumber(const char* src, const char* pat);
}*/	           
}