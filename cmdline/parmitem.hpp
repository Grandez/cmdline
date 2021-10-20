#pragma once
namespace cmdline {

	enum parmType { FLAG, STRING, NUMBER, DECIMAL, DATE, TIME, DIR, DIR_EXISTS, FILE, FILE_EXISTS };
	class ParmItem {
	public:
		char* name;              // Name of parameter
		parmType type = STRING;  // Type
		char* value = nullptr;   // default value
		bool multiple = false;   // Allow multiple values?
		ParmItem() = delete;
		ParmItem(char* name) { this->name = name; }
		ParmItem(char* name, char *value) { 
			this->name = name; 
			this->value = value;
		}
		ParmItem(char* name, char* value, parmType type, bool multiple = false) { 
			this->name = name; 
			this->value = value;
			this -> type = type;
			this->multiple = multiple;
		}
		ParmItem(char* name, bool value) {
			this->name = name;
			this->value = (char *) ((value) ? "1" : "0");
			this->type = FLAG;
			this->multiple = false;
		}

	};
}