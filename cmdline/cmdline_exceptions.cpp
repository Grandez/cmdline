#include <cstdarg>
#include <cstring>

#include "cmdline_exceptions.hpp"

#ifdef _WIN32
#pragma warning( disable : 6386 34)
#endif

// NOTE Code is duplicate because I don't know how
// Corrrectly call to foo(fmt, ...) from other fo1(fmt,...)
namespace cmdline {
	typedef struct _buff {
		char* data = new char[256];
		int size = 128;
		void incSize() {
			size += 128;
			delete data;
			data = new char[size];
		}
	} Buffer;
	CmdLineException::CmdLineException(const char* fmt, ...) : invalid_argument("") {
		Buffer buffer;
		va_list args;
		int res = buffer.size;
		do {
			if (res < 0) buffer.incSize();
			va_start(args, fmt);
			res = vsnprintf(buffer.data, buffer.size, fmt, args);
			va_end(args);
		} while (res < 0);
		str <= buffer.data;
    }
	const char* CmdLineException::what() noexcept {
		return str.toString().c_str();
	}
	CmdLineParameterException::CmdLineParameterException(const char* fmt, ...) {
		Buffer buffer;
		va_list args;
		int res = buffer.size;
		do {
			if (res < 0) buffer.incSize();
			va_start(args, fmt);
			res = vsnprintf(buffer.data, buffer.size, fmt, args);
			va_end(args);
		} while (res < 0);
		str <= buffer.data;
	}
	CmdLineValueException::CmdLineValueException(const char* fmt, ...) {
		Buffer buffer;
		va_list args;
		int res = buffer.size;
		do {
			if (res < 0) buffer.incSize();
			va_start(args, fmt);
			res = vsnprintf(buffer.data, buffer.size, fmt, args);
			va_end(args);
		} while (res < 0);
		str <= buffer.data;
	}
	CmdLineDuplicateArgumentException::CmdLineDuplicateArgumentException(const char* fmt, ...) {
		Buffer buffer;
		va_list args;
		int res = buffer.size;
		do {
			if (res < 0) buffer.incSize();
			va_start(args, fmt);
			res = vsnprintf(buffer.data, buffer.size, fmt, args);
			va_end(args);
		} while (res < 0);
		str <= buffer.data;
	}
	CmdLineNotFoundException::CmdLineNotFoundException(const char* fmt, ...) : runtime_error("") {
		Buffer buffer;
		va_list args;
		int res = buffer.size;
		do {
			if (res < 0) buffer.incSize();
			va_start(args, fmt);
			res = vsnprintf(buffer.data, buffer.size, fmt, args);
			va_end(args);
		} while (res < 0);
		str <= buffer.data;
	}
	const char* CmdLineNotFoundException::what() noexcept {
		return str.toString().c_str();
	}

	CmdLineInvalidTypeException::CmdLineInvalidTypeException(const char* fmt, ...) : runtime_error("") {
		Buffer buffer;
		va_list args;
		int res = buffer.size;
		do {
			if (res < 0) buffer.incSize();
			va_start(args, fmt);
			res = vsnprintf(buffer.data, buffer.size, fmt, args);
			va_end(args);
		} while (res < 0);
		str <= buffer.data;
	}
	const char* CmdLineInvalidTypeException::what() noexcept {
		return str.toString().c_str();
	}
}

