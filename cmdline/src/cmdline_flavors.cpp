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
    CmdLineI& CmdLineI::GetInstance(int argc, char* argv[], cmdline::Parameters parms) {
		_parms = parms;
		_nargc = argc;
		_argv = (char**)calloc(argc, sizeof(char*));
		for (int i = 0; i < argc; i++) _argv[i] = _cmdline::strUpper(argv[i]);
		for (auto it : _parms) it.name = _cmdline::strUpper(it.name);
		return (CmdLineI&) CmdLine::GetInstance(argc, argv, _parms);
	}
	CmdLineS& CmdLineS::GetInstance(int argc, char* argv[], cmdline::Parameters parms) {
		return (CmdLineS&) CmdLine::GetInstance(argc, argv, parms, true, false);
	}
	CmdLineIS& CmdLineIS::GetInstance(int argc, char* argv[], cmdline::Parameters parms) {
		_parms = parms;
		_nargc = argc;
		_argv = (char**)calloc(argc, sizeof(char*));
		for (int i = 0; i < argc; i++) _argv[i] = _cmdline::strUpper(argv[i]);
		for (auto it : _parms) it.name = _cmdline::strUpper(it.name);
		return (CmdLineIS&) CmdLine::GetInstance(argc, argv, _parms, false, true);
	}
	CmdLineIS::~CmdLineIS() {
		_cleanClass();
	}


}
