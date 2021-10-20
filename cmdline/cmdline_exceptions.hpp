#pragma once
#include <iostream>
#include <stdexcept>

namespace cmdline {
	/**
	 * Base class for cmdline exceptions
	 *
	 * As library process argument from command line it inherits from invalid_argument
	 *
	 * @param msg Text to show
	 *
	 */

	class CmdLineException : public std::invalid_argument {
	public:
		CmdLineException() = delete;
		CmdLineException(const std::string& msg) : invalid_argument(msg) { message = (char*)msg.c_str(); }
		CmdLineException(const char* msg) : invalid_argument(msg) { message = (char*)msg; }
		CmdLineException(const char* msg, const char* input) : invalid_argument(msg) {
			message = (char*)msg;
			parm = (char*)input;
		}
		CmdLineException(const char* msg, const char* input, const char* alt) : invalid_argument(msg) {
			message = (char*)msg;
			parm = (char*)input;
			this->alt = (char*)alt;
		}

	protected:
		char* message = (char*)"exceptions en library";
		char* parm = (char*)"";
		char* alt = (char*)"";
	};
	class CmdLineValueException : public CmdLineException {
	public:
		CmdLineValueException() = delete;
		CmdLineValueException(const char* value, const char* desired) : CmdLineException("Invalid value") {
			parm = (char*)value;
			alt = (char*)desired;
		}
	};
	/**
	 * Exception indicating HELP has been rquested
	 */
	class HelpRequested : public CmdLineException {
	public:
		HelpRequested() : CmdLineException("Help requested") {};
	};

}