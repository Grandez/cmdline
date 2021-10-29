#include <cstdlib>
#include <ctype.h>

#include "tools.h"

#include "cmdline.hpp"


namespace cmdline {
	char** _argv = nullptr;
	int    _nargc;
	Parameters _parms;

	void _cleanClass() {
		for (int i = 0; i < _nargc; i++) free(_argv[i]);
		for (auto it : _parms) free((void *) it.name);
	}
	CmdLineI::~CmdLineI() {
		_cleanClass();
	}
    CmdLine CmdLineI::GetInstance(int argc, const char* argv[], cmdline::Parameters parms) {
		_parms = parms;
		_nargc = argc;
		_argv = (char**)calloc(argc, sizeof(char*));
		for (int i = 1; i < argc; i++) if (_argv) _argv[i] = _cmdline::strUpper(argv[i]);
		for (auto it : _parms) it.name = _cmdline::strUpper(it.name);
		return CmdLine::GetInstance(argc, argv, _parms);
	}
	CmdLine CmdLineS::GetInstance(int argc, const char* argv[], cmdline::Parameters parms) {
		return CmdLine::GetInstance(argc, argv, parms, true, false);
	}
	CmdLine CmdLineIS::GetInstance(int argc, const char* argv[], cmdline::Parameters parms) {
		_parms = parms;
		_nargc = argc;
		_argv = (char**)calloc(argc, sizeof(char*));
		for (int i = 1; i < argc; i++) if (_argv) _argv[i] = _cmdline::strUpper(argv[i]);
		for (auto it : _parms) it.name = _cmdline::strUpper(it.name);
		return CmdLine::GetInstance(argc, argv, _parms, false, true);
	}
	CmdLineIS::~CmdLineIS() {
		_cleanClass();
	}
}
