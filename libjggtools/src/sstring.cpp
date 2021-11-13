#include <cctype>
#include <regex>

#include "sstring.hpp"

namespace jggtools {
   sstring&     sstring::ltrim() {
        int i = 0;
        while (at(i) == ' ' || at(i) == '\t' || at(i) == '\r') i++;
        assign(substr(i));
        return *this;
     }
   sstring&     sstring::rtrim() {
        size_t i;
        bool done = false;
        for (i = this->length() - 1; i > -1; i--) {
             switch(at(i)) {
                case ' ':
                case '\t': 
                case '\r':
                case '\n': break;
                default: done = true;
             }
             if (done) break;
        }
        assign(substr(0, i));
        return *this;     
   }
   sstring&     sstring::trim() {
         return ltrim().rtrim();
     }
   sstring&     sstring::toUpper() {
      for (size_t i = 0; i < length(); i++) at(i) = toupper(at(i));
      return *this;
   }
   sstring&     sstring::toLower() {
      for (size_t i = 0; i < length(); i++) at(i) = tolower(at(i));
      return *this;
   }
   sstring*     sstring::toString() {
         return new sstring(*this);
    }
   char*        sstring::toArr() {
      char *res = 0x0;
      res = (char *) malloc(length() + 1);
      if (res == 0x0) {
          errno = ENOMEM;
          return 0x0;
      }
      memcpy(res, c_str(), length());
      res[length()] = 0x0; 
      return res;
    }
   sstring*     sstring::makeLower() {
      sstring *str = new sstring(*this);
      str->toLower();
      return str;
   }
   sstring*     sstring::makeUpper() {
      sstring *str = new sstring(*this);
      str->toUpper();
      return str;
   }
   const char*  sstring::toChar() {
         return c_str();
    }

   vector<char *>  sstring::tokenize(const char* pat) {
	  vector<sstring> toks = tokenize(string(pat));
      vector<char *> res(toks.size());
      for (size_t i = 0; i < toks.size(); i++) res.at(i) = (char *) toks[i].c_str();
	  return res;
    }
   vector<sstring> sstring::tokenize(string pat) {
	     regex reg(pat);
         sregex_token_iterator iter(begin(), end(), reg, -1);
         sregex_token_iterator end;
         vector<string> vec(iter, end);
         vector<sstring> res;
         for (size_t i = 0; i < vec.size(); i++) res.push_back(sstring(vec[i]));
	     return vector<sstring>();
    }
   bool sstring::makeBoolean(const char* value) {
        if (value == 0x0) return false;
        char c = value[0];
        if (c == '0' || c == 'n' || c == 'N' || c == 'f' || c == 'F') return false; 
		return true;
	}
   bool sstring::makeBoolean(sstring value) { 
		return makeBoolean(value.c_str());
	}
}