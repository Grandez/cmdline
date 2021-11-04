#include <iostream>
#include <cstdarg>
#include <cstring>
#include <cstdio>

#include "cmdline_exceptions.hpp"

#ifdef _WIN32
#pragma warning( disable : 4996)
#endif

namespace cmdline {
	static std::string mountMessage(const char* fmt, va_list list) {
		char t[255];
		std::vsprintf(t, fmt, list);
		return std::string(t);
	}
	CmdLineException::CmdLineException(char* txt) : invalid_argument(txt) {};
	CmdLineException::CmdLineException(const char* fmt, ...) : invalid_argument("") {
		va_list args;
		va_start(args, fmt);
		std::string txt = mountMessage(fmt, args);
		this->invalid_argument::~invalid_argument();
		new (this) invalid_argument(txt); //
	}
	CmdLineParameterException::CmdLineParameterException(const char* fmt, ...) {
		va_list args;
		va_start(args, fmt);
		std::string txt = mountMessage(fmt, args);
		this->CmdLineException::~CmdLineException(); // destroy the base class
		new (this) CmdLineException((char*)txt.c_str()); //
	}
	CmdLineValueException::CmdLineValueException(const char* fmt, ...) {
		va_list args;
		va_start(args, fmt);
		std::string txt = mountMessage(fmt, args);
		this->CmdLineException::~CmdLineException(); // destroy the base class
		new (this) CmdLineException((char*)txt.c_str()); //
	}
	CmdLineDuplicateArgumentException::CmdLineDuplicateArgumentException(const char* fmt, ...) {
		va_list args;
		va_start(args, fmt);
		std::string txt = mountMessage(fmt, args);
		this->CmdLineException::~CmdLineException(); // destroy the base class
		new (this) CmdLineException((char*)txt.c_str()); //
	}
	CmdLineNotFoundException::CmdLineNotFoundException(const char* fmt, ...) : std::runtime_error("unchecked") {
		va_list args;
		va_start(args, fmt);
		std::string txt = mountMessage(fmt, args);
		this->runtime_error::~runtime_error(); // destroy the base class
		new (this) runtime_error((char*)txt.c_str()); //
	}
	CmdLineInvalidTypeException::CmdLineInvalidTypeException(const char* fmt, ...) : std::runtime_error("unchecked") {
		va_list args;
		va_start(args, fmt);
		std::string txt = mountMessage(fmt, args);
		this->runtime_error::~runtime_error(); // destroy the base class
		new (this) runtime_error((char*)txt.c_str()); //
	}
}

