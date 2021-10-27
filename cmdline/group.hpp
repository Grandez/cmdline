#pragma once
#include <iostream>
#include <unordered_map>
#include <iterator>
using namespace std;

#include "arg.hpp"

namespace cmdline {
	class Group : public unordered_map<string, Argument> {
		char* name;
//		unordered_map<string, Argument> container;
		typedef unordered_map<string, Argument> container;
	public:
		
//		typedef typename iterator iterator;
//		typedef typename const_iterator const_iterator;
		Group& add(const char* name, Argument arg) {
			insert_or_assign(name, arg);
			return *this;
		}
		Group& add(Argument arg) {
			insert_or_assign(arg.name, arg);
			cout << "para" << size() << endl;
			return *this;
		}
		Argument* find(string what) {
			try {
				auto res = at(what);
				return &(at(what));
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

