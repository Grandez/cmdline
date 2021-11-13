#include "pch.h"

TEST(Types, STRING) {
	tool.reset();
	const char* opt = "opt";

	Parameters  parms = { ParmOption(opt, (const char*)"123", Type::STRING) };
	CmdLine cmdline = CmdLine(tool.argc, tool.argv, parms);
	string res = cmdline.getOptionAs<TYPE_STRING>(opt);
	CmdLine::freeInstance();
	EXPECT_EQ(res, "123");
}
