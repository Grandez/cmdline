#pragma once
#include <stdexcept>
#include <unordered_map>
#include <cstdarg>
#ifndef __CMDLINE_EXCEPTIONS__
#define __CMDLINE_EXCEPTIONS__
namespace cmdline {
	class CmdLineNotFoundException : public std::runtime_error {
	public:
		CmdLineNotFoundException() = delete;
		CmdLineNotFoundException(const char* fmt, ...);
	};
	class CmdLineInvalidTypeException : public std::runtime_error {
	public:
		CmdLineInvalidTypeException() = delete;
		CmdLineInvalidTypeException(const char* fmt, ...);
	};

	class CmdLineException : public std::invalid_argument {
	public:
		CmdLineException() : invalid_argument("") {};
		CmdLineException(const char* fmt, ...); 
		CmdLineException(char* txt);
		~CmdLineException() {};
        string type;
	};

	class CmdLineParameterException : public CmdLineException {
	public:
		CmdLineParameterException() = delete;
		CmdLineParameterException(const char* fmt, ...);
	};
	class CmdLineValueException : public CmdLineException {
	public:
		CmdLineValueException() = delete;
		CmdLineValueException(const char* fmt, ...);
	};
	class CmdLineDuplicateArgumentException : public CmdLineException {
	public:
		CmdLineDuplicateArgumentException() = delete;
		CmdLineDuplicateArgumentException(const char* fmt, ...);
	};

	 // Exception indicating HELP has been requested

	class HelpRequested : public CmdLineException {
	public:
		const char *name;
		bool detailed = false;
		std::unordered_map<std::string, bool>        flags;
		std::unordered_map<std::string, std::string> options;

		HelpRequested() = delete;
		~HelpRequested();
	protected:
        HelpRequested(const char * programName, const char *txt, bool detailed
		                             , std::unordered_map<std::string, bool> flags
		                             , std::unordered_map<std::string, string> options);
	};
	class HelpSimpleRequested : public HelpRequested {
	public:
		HelpSimpleRequested( char * programName
			                ,unordered_map<string,bool> flags  
		                    ,unordered_map<string,string> options);       
	};
	class HelpDetailedRequested : public HelpRequested {
	public:
		HelpDetailedRequested( const char * programName
			                  ,unordered_map<string,bool> flags  
		                      ,unordered_map<string,string> options);
	};
}
#endif