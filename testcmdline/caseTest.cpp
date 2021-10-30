#include "pch.h"

#include "_global.hpp"

TEST(Case, option_01) {
	tool.reset();
	const char* opt1 = "output";
	Parameters  parms = { ParmOption(opt1, ".") };

	CmdLine cmdline = CmdLineI::getInstance(tool.argc, tool.argv, parms);
	EXPECT_TRUE(cmdline.hasOption(opt1));
	EXPECT_TRUE(cmdline.hasOption("OUTPUT"));
	EXPECT_TRUE(cmdline.hasOption("Output"));
	CmdLine::freeInstance();
}

TEST(Case, options_02) {
	tool.reset();
	const char* opt1 = "output";
	Parameters  parms = { ParmOption(opt1, ".") };
	int argc = tool.addArg("/output", "..");
	CmdLine cmdline = CmdLineI::getInstance(tool.argc, tool.argv, parms);

	EXPECT_TRUE(cmdline.hasOption(opt1));
	EXPECT_TRUE(cmdline.hasOption("OUTPUT"));
	EXPECT_TRUE(cmdline.hasOption("Output"));
	CmdLine::freeInstance();
}
TEST(Case, flag_01) {
	tool.reset();
	Parameters  parms = { ParmFlag("verbose", true)};

	CmdLine cmdline = CmdLineI::getInstance(tool.argc, tool.argv, parms);
	EXPECT_TRUE(cmdline.hasFlag("verbose"));
	EXPECT_TRUE(cmdline.hasFlag("VERBOSE"));
	CmdLine::freeInstance();
}

TEST(Case, flag_02) {
	tool.reset();
	Parameters  parms = { ParmFlag("verbose") };
	int argc = tool.addArg("+VERBOSE");

	CmdLine cmdline = CmdLineI::getInstance(tool.argc, tool.argv, parms);
	EXPECT_TRUE(cmdline.hasFlag("verbose"));
	EXPECT_TRUE(cmdline.hasFlag("VERBOSE"));
	CmdLine::freeInstance();
}
