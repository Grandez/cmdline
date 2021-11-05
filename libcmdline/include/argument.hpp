#pragma once

#include <set>
#include "cmdline.hpp"
#include "types.hpp"

using namespace std;
using namespace cmdline;

namespace _cmdline {
	class Argument {
	public:
		string name;
		Source source   = Source::DEFAULT;
		Type   type     = Type::STRING;
		bool   multiple = false;
		string defValue;
		set<string> values; // avoid duplicates
		Argument() = delete;
		~Argument();
		Argument(Argument *arg);
		Argument(Parm *parm);
		Argument(const char *name, const char* value);
		Argument(const char *name, const char* value, Source source);
		Argument(const char* name, const char* value, Type type);
		Argument& setFromEnv(const char* value);
		Argument& setValue(bool value);
		Argument& setValue(const char* value);
		Argument& setValue(std::string value);
		Argument& addValue(std::string value);
		const char* getValue();
		vector<const char *>  getValues();
		vector<string>        getStringValues();
		bool            getBoolean();
		Argument&       initValues(vector<string> values);
		Argument&       makeUpper();
	protected:
		Argument&      addValues(vector<string> values);
	private:
		string first;
		void   validateDefault();
		string applyDefault(const char *);
	};
}
