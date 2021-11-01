#include <cstdarg>
#include "cmdline_exceptions.hpp"

#ifdef _WIN32
#pragma warning( disable : 6386 34)
#endif

namespace cmdline {
	CmdLineException::CmdLineException(const char* fmt, ...) : invalid_argument("") {
		va_list args;
		if (isPattern(fmt)) {
			int res = bufferSize;
			do {
				if (res < 0) {
					this->bufferSize += 256;
					this->buffer = new char(bufferSize);
				}
				va_start(args, fmt);
				res = vsnprintf(this->buffer, bufferSize, fmt, args);
				va_end(args);
			} while (res < 0);
			str <= buffer;
			//JGG No se por que falla
			//va_start(args, fmt);
			//mountMessage(fmt, args);
			//va_end(args, fmt);
		}
		setSuper();
    }
	CmdLineException::CmdLineException(const char* fmt, va_list args) : invalid_argument("") {
		mountMessage(fmt, args);
		setSuper();
	}

	inline bool CmdLineException::isPattern(const char* fmt) {
		int i = 0;
		if (fmt == 0x0) return false;
		while (fmt[i] != 0x0) if (fmt[i++] == '%') return true;
		return false;
	}
	inline void CmdLineException::setSuper() {
		this->invalid_argument::~invalid_argument();
		new (this) invalid_argument(str.toString());
	}

	void CmdLineException::mountMessage(const char *fmt, va_list args) {
		int res = bufferSize;
		do {
			if (res < -1) {
				bufferSize += 256;
				this->buffer = new char(bufferSize);
			}
			int size = sizeof(buffer);
			va_start(args, fmt);
			res = vsnprintf(this->buffer, bufferSize, fmt, args);
			va_end(args);
		} while (res < 0);

	}
	CmdLineParameterException::CmdLineParameterException(const char* fmt, ...) {
		va_list args;
		va_start(args, fmt);
		CmdLineException(fmt, args);
		va_end(args);
	}
	CmdLineValueException::CmdLineValueException(const char* fmt, ...) {
		va_list args;
		va_start(args, fmt);
		CmdLineException(fmt, args);
		va_end(args);
	}
	CmdLineDuplicateArgumentException::CmdLineDuplicateArgumentException(const char* fmt, ...) {
		va_list args;
		va_start(args, fmt);
		CmdLineException(fmt, args);
		va_end(args);
	}
	CmdLineNotFoundException::CmdLineNotFoundException(const char* fmt, ...) : runtime_error("") {
		va_list args;
		jggtools::stringbuffer str;
		char* buffer = new char[256];
		int  bufferSize = 256;
		va_start(args, fmt);
		vsnprintf(buffer, bufferSize, fmt, args);
		va_end(args);
		this->runtime_error::~runtime_error();
		new (this) runtime_error((const char *) buffer);
	}
	CmdLineInvalidTypeException::CmdLineInvalidTypeException(const char* fmt, ...) : runtime_error("") {
		va_list args;
		jggtools::stringbuffer str;
		char* buffer = new char[256];
		int  bufferSize = 256;
		va_start(args, fmt);
		vsnprintf(buffer, bufferSize, fmt, args);
		va_end(args);
		this->runtime_error::~runtime_error();
		new (this) runtime_error((const char *)buffer);
	}
}