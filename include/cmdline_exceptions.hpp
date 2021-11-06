#pragma once
/**
 * Base class for cmdline exceptions
 *
 * As library process argument from command line it inherits from invalid_argument
 *
 * @param msg Text to show
 *
 */

#include <stdexcept>
#include <unordered_map>
#include <cstdarg>

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
		~CmdLineException() {};
//		CmdLineException(const CmdLineException& test) : invalid_argument(test) {};

		CmdLineException(const char* fmt, ...); 
		CmdLineException(char* txt);
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
		const char *name = nullptr;
		bool detailed = false;
		std::unordered_map<std::string, bool>        flags;
		std::unordered_map<std::string, std::string> options;

		HelpRequested() = delete;
	protected:
        HelpRequested(const char *programName, const char *txt, bool detailed
		                             , std::unordered_map<std::string, bool> flags
		                             , std::unordered_map<std::string, string> options);
	};
	class HelpSimpleRequested : public HelpRequested {
	public:
		HelpSimpleRequested( const char *programName
			                ,unordered_map<string,bool> flags  
		                    ,unordered_map<string,string> options);       
	};
	class HelpDetailedRequested : public HelpRequested {
	public:
		HelpDetailedRequested( const char *programName
			                  ,unordered_map<string,bool> flags  
		                      ,unordered_map<string,string> options);
	};
}