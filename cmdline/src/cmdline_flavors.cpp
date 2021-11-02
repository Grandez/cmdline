#include <cstdlib>
#include <ctype.h>

#include "tools.h"

#include "cmdline.hpp"
#include "commandline.hpp"

namespace cmdline {
	char** _argv = nullptr;
	int    _nargc;
	Parameters _parms;

	void _cleanClass() {
		for (int i = 0; i < _nargc; i++) free(_argv[i]);
//		for (auto it : _parms) free((void *) it.name);
	}
	CmdLineI::~CmdLineI() {
		_cleanClass();
	}
    CmdLine CmdLineI::getInstance(int argc,  char** argv, cmdline::Parameters parms) {
		return CmdLine::pGetInstance(argc, argv, parms, true);
	}
	CmdLine CmdLineS::getInstance(int argc,  char** argv, cmdline::Parameters parms) {
		return CmdLine::pGetInstance(argc, argv, parms, false, true);
	}
	CmdLine CmdLineIS::getInstance(int argc,  char** argv, cmdline::Parameters parms) {
		return CmdLine::pGetInstance(argc, argv, parms, true, true);
	}
	CmdLineIS::~CmdLineIS() {
		_cleanClass();
	}
}
