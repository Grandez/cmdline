#pragma once

#include "arg.hpp"

using namespace std;

namespace cmdline {
	class Define : public Argument {
	public:
		Define() = delete;
		Define(const char* name, const char* value) : Argument(name, value, Type::DEFINE) {};
		Define(const char* name) : Argument(name, "") {
 		   // Incomplete definition
			pName = strdup(name);
		}
		~Define() {
			if (pName) free(pName);
		}
		void initValues(vector<string> values) {
			Argument::type = Type::DEFINE;
			Argument::name = strdup(pName);
			Argument::addValues(values);
		}
		
	private:
		char* pName = NULL;
	};

}

