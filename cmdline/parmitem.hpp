#pragma once
namespace cmdline {

	enum parmType { FLAG, STRING, NUMBER, DECIMAL, DATE, TIME, DIR, DIR_EXISTS, FILE, FILE_EXISTS };
	class ParmItem {
	public:
		const char* name;              // Name of parameter
		parmType type;  // Type
		const char* value;   // default value
		bool multiple;   // Allow multiple values?
		ParmItem() = delete;
		ParmItem(const char* name) { 
			this->name = name; 
			this->value = nullptr;
			this->type = STRING;
			this->multiple = false;
	    }
		ParmItem(char* name, char *value) { 
			this->name = name; 
			this->value = value;
			this->type = STRING;
			this->multiple = false;
		}
		ParmItem(const char* name, char* value, parmType type, bool multiple = false) { 
			this->name = name; 
			this->value = value;
			this -> type = type;
			this->multiple = multiple;
		}
		ParmItem(const char* name, bool value) {
			this->name = name;
			this->value = (char *) ((value) ? "1" : "0");
			this->type = FLAG;
			this->multiple = false;
		}

	};
}