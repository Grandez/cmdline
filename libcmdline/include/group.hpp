#pragma once
#include <iostream>
#include <unordered_map>
#include <iterator>
using namespace std;

#include "argument.hpp"

namespace NS2 {
	class Group : public unordered_map<string, Argument> {
	public:
		Group& add(const char* name, Argument *arg) {
			insert_or_assign(name, Argument(arg));
			return *this;
		}
		Group& add(string name, Argument* arg) {
			insert_or_assign(name.c_str(), Argument(arg));
			return *this;
		}

		Group& add(Argument *arg) {
			insert_or_assign(arg->name, Argument(arg));
			cout << "para" << size() << endl;
			return *this;
		}
		Argument* find(string what) {
			try {
				return &(at(what));
			}
			catch (out_of_range ex) {
				return (Argument*) nullptr;
			}
		}
		Argument* operator[](string what) { return find(what); }
	};
}

