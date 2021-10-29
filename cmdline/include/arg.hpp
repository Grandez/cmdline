#pragma once
#include <set>
#include "cmdline.hpp"

using namespace std;
using namespace cmdline;

namespace _cmdline {
	class Argument {
	public:
		string name;
		Source source   = Source::DEFAULT;
		Type   type     = Type::STRING;
		bool   multiple = false;
		char* defValue = 0x0;
		set<string> values; // avoid duplicates
		Argument() = delete;
		Argument(Parm& parm);
		Argument(const char *name, const char* value);
		Argument(const char *name, const char* value, Source source);
		Argument(const char* name, const char* value, Type type);
		Argument& setFromEnv(const char* value);
		Argument& setValue(bool value);
		Argument& setValue(const char* value);
		Argument& setValue(std::string value);
		Argument& addValue(std::string value);
		const char* getValue();
		vector<string>  getValues();
		/*
			m_buff = make_unique<unsigned char*[]>(size);
			std::unique_ptr<char **, arrayDeleter> _ptr = ;
			_ptr. = (char**)malloc((values.size() + 1) * sizeof(char*));
			char** pValues = (char **) malloc((values.size() + 1) * sizeof(char*));
			int i = 0;
			for (i = 0; i < values.size(); i++) pValues[i] = strdup(values[i].c_str());
			pValues[i] = 0x0;
//			_ptr = make_unique<char **, arrayDeleter>(pValues);
//			return values; 
		}
		*/
		bool           getBoolean();
		Argument& initValues(vector<string> values);
	protected:
		Argument&      addValues(vector<string> values);
	private:
		char* first = 0x0;
		struct arrayDeleter {
			void operator()(char ** data) { 
				int i = 0;
				if (data == 0x0) return;
				while (data[i]) free(data[i++]);
			}
		};
	};
}
