#pragma once
#include <iostream>
#include <exception>

class CmdLineException : public std::exception {
public:
	CmdLineException() = default;
	CmdLineException(const char* msg) { message = (char*)msg; }
	CmdLineException(const char* msg, const char* input) {
		message = (char*)msg;
		parm = (char*)input;
	}
	CmdLineException(const char* msg, const char* input, const char* alt) {
		message = (char*)msg;
		parm = (char*)input;
		this->alt = (char*)alt;
	}

	const char* what() const throw()
	{
		return message;
	}
protected:
	char* message = (char *) "exceptions en library";
	char* parm = (char*) "";
	char* alt = (char*) "";
};

class CmdLineValueException : public CmdLineException {
public:
	CmdLineValueException() = delete;
	CmdLineValueException(const char* value, const char* desired) {
		parm = (char*)value;
		alt = (char*)desired;
	}
};

class HelpException : public CmdLineException {
public:
	HelpException(const char* msg) { message = (char*)msg; }
	HelpException(const char* msg, const char* alt) { message = (char*)msg; }
	const char* what() const throw()
	{
		return message;
	}
private:
	char* message;

};

