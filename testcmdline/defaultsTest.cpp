#include "pch.h"

#include "$tool.hpp"

TEST(Defaults, Flags_2) {
	Parameters  parms = { 
		ParmFlag("output", true)
	   ,ParmFlag("outer", true) 
	};
	tool.reset();
	CmdLine cmdline = CmdLine::getInstance(tool.argc, tool.argv, parms);
	Flags mflags    = cmdline.getDefaultFlags();
	CmdLine::freeInstance();
	EXPECT_EQ(mflags.size(), parms.size());
}
TEST(Defaults, Flags_3) {
	Parameters  parms = { 
		 ParmFlag("output", true)
		,ParmFlag("outer",  true)
		,ParmFlag("verbose", true)
	};
	tool.reset();
	CmdLine cmdline = CmdLine(tool.argc, tool.argv, parms);
	Flags mflags = cmdline.getDefaultFlags();
	EXPECT_EQ(mflags.size(), parms.size());
}

TEST(Defaults, Flags_0) {
	tool.reset();
	Parameters  parms;
	CmdLine cmdline = CmdLine(tool.argc, tool.argv, parms);
	Flags mparms = cmdline.getDefaultFlags();
	EXPECT_EQ(mparms.size(), parms.size());
}
TEST(Defaults, Options_0) {
	tool.reset();
	Parameters  parms;
	CmdLine cmdline = CmdLine(tool.argc, tool.argv, parms);
	Options mparms = cmdline.getDefaultOptions();
	EXPECT_EQ(mparms.size(), parms.size());
}
/*
TEST(Defaults, Options_0) {
	Parameters  parms{
		ParmOption("hour", Type::TIME)
	};
	CmdLine cmdline = CmdLine::getInstance(tool.argc, tool.argv, parms);
	Options mparms = cmdline.getDefaultOptions();
	CmdLine::freeInstance();
	EXPECT_EQ(mflags.size(), parms.size());
}
*/