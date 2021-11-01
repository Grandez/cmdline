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
#include "msg_locale.h"
#include "stringbuffer.hpp"
#include <cstdarg>

using namespace jggtools;

namespace cmdline {
	class CmdLineNotFoundException : public std::runtime_error {
		jggtools::stringbuffer str;
	public:
		CmdLineNotFoundException() = delete;
		CmdLineNotFoundException(const char* fmt, ...);
		const char* what() noexcept;
	};
	class CmdLineInvalidTypeException : public std::runtime_error {
		jggtools::stringbuffer str;
	public:
		CmdLineInvalidTypeException() = delete;
		CmdLineInvalidTypeException(const char* fmt, ...);
		const char* what() noexcept;
	};

	class CmdLineException : public std::invalid_argument {
	public:
		CmdLineException() : invalid_argument("") {};
		~CmdLineException()  {};
		CmdLineException(const CmdLineException& test) : invalid_argument(test) {};

		CmdLineException(const char* fmt, ...); 
		const char* what() noexcept;
	protected:
		jggtools::stringbuffer str;
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
		HelpRequested() : CmdLineException(TXT_HELP) {};
	};
	class HelpDetailedRequested : public CmdLineException {
	public:
		HelpDetailedRequested() : CmdLineException(TXT_HELP_DETAIL) {};
	};
}