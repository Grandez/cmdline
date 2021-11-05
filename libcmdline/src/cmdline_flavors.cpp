#include <cstdlib>
#include <ctype.h>

#include "tools.hpp"

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
	CmdLineI::CmdLineI(int argc, char** argv, cmdline::Parameters parms) : CmdLine(argc, argv, parms, true) {}
	CmdLineI::CmdLineI(int argc, char** argv, cmdline::Parameters parms, bool strict) : CmdLine(argc, argv, parms, true, strict) {}
    CmdLine CmdLineI::getInstance(int argc,  char** argv, cmdline::Parameters parms) {
		return CmdLine::pGetInstance(argc, argv, parms, true);
	}
	CmdLineS::CmdLineS(int argc, char** argv, cmdline::Parameters parms) : CmdLine(argc, argv, parms, false, true) {}
	CmdLineIS::CmdLineIS(int argc, char** argv, cmdline::Parameters parms) : CmdLineI(argc, argv, parms, true) {}
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
