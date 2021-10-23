#include "pch.h"
#include <map>
#include <stdexcept>
#include <regex>

#include "../cmdline/cmdline.h"

using namespace cmdline;

/*
TEST(Defaults, Flags_2) {
	std::vector<cmdline::ParmItem> flags = {
		 cmdline::ParmItem("output", true)
		,cmdline::ParmItem("outer", true)
	};
	cmdline::CmdLine cmdLine(flags);
	std::map<std::string, bool> mflags = cmdLine.getDefaultFlags();
	std::map<std::string, void *> mOptions = cmdLine.getDefaultOptions();
	EXPECT_EQ(mflags.size(), flags.size());
}
*/
