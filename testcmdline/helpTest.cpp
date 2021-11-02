#include "pch.h"
#include <map>
#include <stdexcept>
#include <regex>

#include "$tool.hpp"

TEST(Help, help_no) {
	tool.reset();
	Parameters parms;
	
	EXPECT_NO_THROW(CmdLine(tool.argc, tool.argv, parms));
}
TEST(Help, help_short) {
	tool.reset();
	Parameters parms;
	tool.addArg("-h" );
	
	EXPECT_THROW(CmdLine(tool.argc, tool.argv, parms), HelpRequested);
}
TEST(Help, help_long) {
	tool.reset();
	Parameters parms;
	tool.addArg("--help");

	EXPECT_THROW(CmdLine(tool.argc, tool.argv, parms), HelpRequested);
}
