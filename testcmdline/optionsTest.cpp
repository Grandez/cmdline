#include "pch.h"

#include "_global.hpp"

TEST(Options, options_01) {
	tool.reset();
	const char* opt1 = "output";
	Parameters  parms = { ParmOption(opt1, ".")};

	CmdLine cmdline = CmdLine::getInstance(tool.argc, tool.argv, parms);
	EXPECT_TRUE(cmdline.hasOption(opt1));
	const char* res = cmdline.getOption(opt1);
	EXPECT_EQ(strcmp(res, "."), 0);
	CmdLine::freeInstance();
}

TEST(Options, options_02) {
	tool.reset();
	const char* opt1 = "output";
	Parameters  parms = { ParmOption(opt1, ".") };
	int argc = tool.addArg("/output", "..");
	CmdLine cmdline = CmdLine::getInstance(tool.argc, tool.argv, parms);

	EXPECT_TRUE(cmdline.hasOption(opt1));
	const char* res = cmdline.getOption(opt1);
	EXPECT_EQ(strcmp(res, ".."), 0);
	CmdLine::freeInstance();
}
