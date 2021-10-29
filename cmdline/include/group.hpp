#pragma once
#include <iostream>
#include <unordered_map>
#include <iterator>
using namespace std;

#include "arg.hpp"

namespace _cmdline {
	class Group : public unordered_map<string, Argument> {
		char* name;
	public:
		Group& add(const char* name, Argument *arg) {
			insert_or_assign(name, Argument(arg));
			return *this;
		}
		Group& add(Argument *arg) {
			insert_or_assign(arg->name, Argument(arg));
			cout << "para" << size() << endl;
			return *this;
		}
		Argument* find(string what) {
			try {
				auto res = at(what);
				return &(at(what));

//				return &(at(what));
			}
			catch (out_of_range ex) {
				return (Argument*) nullptr;
			}
		}
		Argument* operator[](string what) { return find(what); }
		// inline iterator begin() noexcept { return container.begin(); }
		// inline const_iterator cbegin() const noexcept { return vec.cbegin(); }
		// inline iterator end() noexcept { return vec.end(); }
		// inline const_iterator cend() const noexcept { return vec.cend(); }

	};
}

