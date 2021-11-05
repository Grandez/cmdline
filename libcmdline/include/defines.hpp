#pragma once

#include "argument.hpp"

using namespace std;

namespace _cmdline {
	class Define : public Argument {
	public:
		Define() = delete;
		Define(const char* name, const char* value) : Argument(name, value) {};
		Define(const char* name) : Argument(name, "") {
			// Incomplete definition
			pName = strdup(name);
		}
		~Define() {
			if (pName) free(pName);
		}
		void initValues(vector<string> values) {
			Argument::name = strdup(pName);
			Argument::addValues(values);
		}

	private:
		char* pName = NULL;
	};

}

