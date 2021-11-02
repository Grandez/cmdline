#include "pch.h"

#include "$tool.hpp"

TEST(Options, options_01) {
	tool.reset();
	const char* opt1 = "output";
	Parameters  parms = { ParmOption(opt1, ".")};

	CmdLine cmdline = CmdLine::getInstance(tool.argc, tool.argv, parms);
	bool opt = cmdline.hasOption(opt1);
	const char* res = cmdline.getOption(opt1);
	CmdLine::freeInstance();
	EXPECT_TRUE(opt);
	EXPECT_EQ(strcmp(res, "."), 0);
}
TEST(Options, options_02) {
	tool.reset();
	const char* opt1 = "output";
	Parameters  parms = { ParmOption(opt1, ".") };
	int argc = tool.addArg("/output", "..");
	CmdLine cmdline = CmdLine::getInstance(tool.argc, tool.argv, parms);
	bool opt = cmdline.hasOption(opt1);
	const char* res = cmdline.getOption(opt1);
	CmdLine::freeInstance();
	EXPECT_TRUE(opt);
	EXPECT_EQ(strcmp(res, ".."), 0);
}
TEST(Options, options_03) {
	// Opcion simple. Se debe sobreescribir
	tool.reset();
	const char* opt1 = "output";
	Parameters  parms = { ParmOption(opt1, ".") };
	int argc = tool.addArg("/output", "..");
	argc = tool.addArg("/output", "....");
	CmdLine cmdline = CmdLine::getInstance(tool.argc, tool.argv, parms);
	bool opt = cmdline.hasOption(opt1);
	const char* res = cmdline.getOption(opt1);
	CmdLine::freeInstance();
	EXPECT_TRUE(opt);
	EXPECT_EQ(strcmp(res, "...."), 0);
}
TEST(Options, options_04) {
	// Opcion multiple. No se debe sobreescribir
	tool.reset();
	const char* opt1 = "output";
	Parameters  parms = { ParmOption(opt1, ".", true) };
	int argc = tool.addArg("/output", "..");
	argc = tool.addArg("/output", "....");
	CmdLine cmdline = CmdLine::getInstance(tool.argc, tool.argv, parms);
	bool opt = cmdline.hasOption(opt1);
	int n = cmdline.getOptionNumValues(opt1);
	CmdLine::freeInstance();
	EXPECT_TRUE(opt);
	EXPECT_EQ  (n, 2);
}
TEST(Options, options_05) {
	// Opcion multiple. Mismo valor. Se debe sobreescribir
	tool.reset();
	const char* opt1 = "output";
	Parameters  parms = { ParmOption(opt1, ".", true) };
	int argc = tool.addArg("/output", "....");
	argc = tool.addArg("/output", "....");
	CmdLine cmdline = CmdLine::getInstance(tool.argc, tool.argv, parms);
	bool opt = cmdline.hasOption(opt1);
	int  n   = cmdline.getOptionNumValues(opt1);
	CmdLine::freeInstance();
	EXPECT_TRUE(opt);
	EXPECT_EQ(n, 1);
}
