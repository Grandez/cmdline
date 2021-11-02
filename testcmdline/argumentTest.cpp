#include "pch.h"

#include "$tool.hpp"
TEST(Arguments, arg_0) {
	tool.reset();
	Parameters  parms;
	CmdLine cmdline = CmdLine(tool.argc, tool.argv, parms);
	EXPECT_EQ(cmdline.args().size(), 0);
}

TEST(Arguments, arg_1) {
	tool.reset();
	tool.addArg("arg1");
	Parameters  parms;
	CmdLine cmdline = CmdLine(tool.argc, tool.argv, parms);
	EXPECT_EQ(cmdline.args().size(), 1);
}
TEST(Arguments, arg_2) {
	tool.reset();
	tool.addArg("arg1", "arg2");
	Parameters  parms;
	CmdLine cmdline = CmdLine(tool.argc, tool.argv, parms);
	EXPECT_EQ(cmdline.args().size(), 2);
}
TEST(Arguments, arg_quoted) {
	tool.reset();
	tool.addArg("arg1", "\"arg2 split\"");
	Parameters  parms;
	CmdLine cmdline = CmdLine(tool.argc, tool.argv, parms);
	EXPECT_EQ(cmdline.args().size(), 2);
}
TEST(Arguments, arg_mixed) {
	tool.reset();
	Parameters  parms = {
		ParmFlag("output", true)
	   ,ParmFlag("outer", true)
	};
	tool.addArg("+output", "arg1");
	tool.addArg("+outer", "\"arg2 split\"");

	CmdLine cmdline = CmdLine(tool.argc, tool.argv, parms);
	EXPECT_EQ(cmdline.args().size(), 2);
}

