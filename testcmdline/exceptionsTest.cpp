#include "pch.h"
#include <stdexcept>

#include "$tool.hpp"

TEST(Exceptions, mistype) {
	// outvut vs output
	tool.reset();
	Parameters  parms = { ParmOption("output", ".")};
	int argc = tool.addArg("/outvut", "..");
	CmdLine cmdline;
	try {
		cmdline = CmdLine::getInstance(tool.argc, tool.argv, parms);
		CmdLine::freeInstance();
	}
	catch (CmdLineException ex) {
		CmdLine::freeInstance();
		const char* msg = ex.what();
		EXPECT_TRUE(strstr(msg, "output"));
		EXPECT_TRUE(strstr(msg, "outvut"));
	}
}
TEST(Exceptions, overtype) {
	// outputs vs output
	tool.reset();
	Parameters  parms = { ParmOption("output", ".") };
	int argc = tool.addArg("/outputs", "..");
	CmdLine cmdline;
	try {
		cmdline = CmdLine::getInstance(tool.argc, tool.argv, parms);
		CmdLine::freeInstance();
	}
	catch (CmdLineException ex) {
		CmdLine::freeInstance();
		const char* msg = ex.what();
		EXPECT_TRUE(strstr(msg, "'outputs'"));
		EXPECT_TRUE(strstr(msg, "'output'"));
	}
}
TEST(Exceptions, notfound) {
	// pepe
	tool.reset();
	Parameters  parms = { ParmOption("output", ".") };
	int argc = tool.addArg("/pepe", "..");
	CmdLine cmdline;
	try {
		cmdline = CmdLine::getInstance(tool.argc, tool.argv, parms);
		CmdLine::freeInstance();
	}
	catch (CmdLineException ex) {
		CmdLine::freeInstance();
		EXPECT_EQ(1,1);
	}
}
