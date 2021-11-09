#include <iostream>
#include <cstdarg>
#include <cstring>
#include <cstdio>
#include <filesystem>
#include "msg_locale.hpp"
#include "types.hpp"
#include "cmdline_exceptions.hpp"

#ifdef _WIN32
#pragma warning( disable : 4996)
#endif

namespace cmdline {
	std::string mountMessage(const char* fmt, va_list list) {
		char t[255];
		std::vsprintf(t, fmt, list);
		return std::string(TXT_ERROR).append(t);
	}
	CmdLineException::CmdLineException(char* txt) : invalid_argument(txt) {};
	CmdLineException::CmdLineException(const char* fmt, ...) : invalid_argument("") {
		va_list args;
		va_start(args, fmt);
        std::string txt = mountMessage(fmt, args);
        va_end(args);
		this->invalid_argument::~invalid_argument();
		new (this) invalid_argument(txt);
        type = "CmdLineException";
	}
	CmdLineParameterException::CmdLineParameterException(const char* fmt, ...) {
		va_list args;
		va_start(args, fmt);
		std::string txt = mountMessage(fmt, args);
		this->CmdLineException::~CmdLineException(); // destroy the base class
		new (this) CmdLineException((char*)txt.c_str()); 
        type = "CmdLineParameterException";
	}
	CmdLineValueException::CmdLineValueException(const char* fmt, ...) {
		va_list args;
		va_start(args, fmt);
		std::string txt = mountMessage(fmt, args);
		this->CmdLineException::~CmdLineException(); // destroy the base class
		new (this) CmdLineException((char*)txt.c_str()); 
        type = "CmdLineValueException";
	}
	CmdLineDuplicateArgumentException::CmdLineDuplicateArgumentException(const char* fmt, ...) {
		va_list args;
		va_start(args, fmt);
		std::string txt = mountMessage(fmt, args);
		this->CmdLineException::~CmdLineException(); // destroy the base class
		new (this) CmdLineException((char*)txt.c_str());
        type = "CmdLineDuplicateArgumentException";
	}
	CmdLineNotFoundException::CmdLineNotFoundException(const char* fmt, ...) : std::runtime_error("unchecked") {
		va_list args;
		va_start(args, fmt);
		std::string txt = mountMessage(fmt, args);
		this->runtime_error::~runtime_error(); // destroy the base class
		new (this) runtime_error((char*)txt.c_str());
	}
	CmdLineInvalidTypeException::CmdLineInvalidTypeException(const char* fmt, ...) : std::runtime_error("unchecked") {
		va_list args;
		va_start(args, fmt);
		std::string txt = mountMessage(fmt, args);
		this->runtime_error::~runtime_error(); // destroy the base class
		new (this) runtime_error((char*)txt.c_str()); //
	}
        HelpRequested::HelpRequested(const char *programName, const char *txt, bool detailed
		                             , std::unordered_map<std::string, bool> flags
		                             , std::unordered_map<std::string, string> options)

		: CmdLineException(txt) {
		filesystem::path fs(programName);
		this->name = strdup(fs.filename().string().c_str());
		this->detailed = detailed;
		this->flags   =  flags;
		this->options = options;
	};
     HelpRequested::~HelpRequested() {
		 cout << "delete HelpRequested\n";
		 free((void *) name);
	 }
	HelpSimpleRequested::HelpSimpleRequested( char* programName
		                                     ,unordered_map<string,bool> flags  
		                                     ,unordered_map<string,string> options)       
		                : HelpRequested(programName, TXT_HELP, false, flags, options) {};
	HelpDetailedRequested::HelpDetailedRequested( const char *programName
		                                         ,unordered_map<string,bool> flags  
		                                         ,unordered_map<string,string> options)
		                 : HelpRequested(programName, TXT_HELP_DETAIL, true, flags, options) {};
}

