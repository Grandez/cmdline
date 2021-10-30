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
		_cmdline::_CommandLine::Attr attr = _cmdline::_CommandLine::Attr(true, false, false);
		return CmdLine::getInstance(argc, argv, parms, &attr);
	}
	CmdLine CmdLineS::getInstance(int argc,  char** argv, cmdline::Parameters parms) {
		_cmdline::_CommandLine::Attr attr = _cmdline::_CommandLine::Attr(false, true, false);
		return CmdLine::getInstance(argc, argv, parms, &attr);
	}
	CmdLine CmdLineIS::getInstance(int argc,  char** argv, cmdline::Parameters parms) {
		_cmdline::_CommandLine::Attr attr = _cmdline::_CommandLine::Attr(true, true, false);
		return CmdLine::getInstance(argc, argv, parms, &attr);
	}
	CmdLineIS::~CmdLineIS() {
		_cleanClass();
	}
}
