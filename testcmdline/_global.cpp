#pragma once
#include "pch.h"

#include "_global.hpp"

	Tool::Tool() {
		argv = (char**) calloc(10, sizeof(char*));
		argv[0] = (char *) "test";
		argc = 1;
	}
	inline char* Tool::mystrdup(const char* str) {
#ifdef _WIN32
		return _strdup(str);
#else
		return strdup(str);
#endif
	}
	void Tool::reset() {
		for (int i = 1; i < argc; i++) free(argv[i]);
		argv[1] = 0x0;
		argc = 1;
	}
	int Tool::getArgc() {
		int argc = 0;
		while (argv[argc] != nullptr) argc++;
		this->argc = argc;
		return argc;
	}
	int Tool::addArg(const char* arg) {
		int i = getArgc();
		argv[i++] = mystrdup(arg);
		argv[i] = nullptr;
		argc++;
		return i;
	}
	int Tool::addArg(const char* name, const char* value) {
		int i = getArgc();
		argv[i++] = mystrdup(name);
		argv[i++] = mystrdup(value);
		argv[i] = nullptr;
		argc += 2;
		return i;
	}
