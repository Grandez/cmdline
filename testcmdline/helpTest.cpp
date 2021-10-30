#include "pch.h"
#include <map>
#include <stdexcept>
#include <regex>

#include "_global.hpp"

TEST(Help, help_no) {
	tool.reset();
	Parameters parms;
	
	EXPECT_NO_THROW(CmdLine::getInstance(tool.argc, tool.argv, parms));
	CmdLine::freeInstance();
}
TEST(Help, help_short) {
	tool.reset();
	Parameters parms;
	tool.addArg("-h" );
	
	EXPECT_THROW(CmdLine::getInstance(tool.argc, tool.argv, parms), HelpRequested);
	CmdLine::freeInstance();
}
TEST(Help, help_long) {
	tool.reset();
	Parameters parms;
	tool.addArg("--help");

	EXPECT_THROW(CmdLine::getInstance(tool.argc, tool.argv, parms), HelpRequested);
	CmdLine::freeInstance();
}
