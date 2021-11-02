#include "pch.h"

#include "$tool.hpp"

TEST(Case, option_01) {
	tool.reset();
	const char* opt1 = "output";
	Parameters  parms = { ParmOption(opt1, ".") };

	CmdLine cmdline = (CmdLine) CmdLineI(tool.argc, tool.argv, parms);
	EXPECT_TRUE(cmdline.hasOption(opt1));
	EXPECT_TRUE(cmdline.hasOption("OUTPUT"));
	EXPECT_TRUE(cmdline.hasOption("Output"));
}

TEST(Case, options_02) {
	tool.reset();
	const char* opt1 = "output";
	Parameters  parms = { ParmOption(opt1, ".") };
	int argc = tool.addArg("/output", "..");
	CmdLine cmdline = (CmdLine) CmdLineI(tool.argc, tool.argv, parms);

	EXPECT_TRUE(cmdline.hasOption(opt1));
	EXPECT_TRUE(cmdline.hasOption("OUTPUT"));
	EXPECT_TRUE(cmdline.hasOption("Output"));
}
TEST(Case, flag_01) {
	tool.reset();
	Parameters  parms = { ParmFlag("verbose", true)};
	int argc = tool.addArg("+VERBOSE");

	CmdLine cmdline = (CmdLine) CmdLineI(tool.argc, tool.argv, parms);
	bool flag1 = cmdline.hasFlag("verbose");
	bool flag2 = cmdline.hasFlag("Verbose");
	EXPECT_TRUE(flag1);
	EXPECT_TRUE(flag2);
	
}

TEST(Case, flag_02) {
	tool.reset();
	Parameters  parms = { ParmFlag("verbose") };
	int argc = tool.addArg("+VERBOSE");

	CmdLine cmdline = (CmdLine) CmdLineI(tool.argc, tool.argv, parms);
	EXPECT_TRUE(cmdline.hasFlag("verbose"));
	EXPECT_TRUE(cmdline.hasFlag("VERBOSE"));
}
