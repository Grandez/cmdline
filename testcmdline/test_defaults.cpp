#include "pch.h"
#include <map>
#include <stdexcept>
#include <regex>

#include "../cmdline/cmdline.h"

using namespace cmdline;

TEST(Defaults, Flags_2) {
	std::vector<cmdline::ParmItem> flags = {
		 cmdline::ParmItem("output", true)
		,cmdline::ParmItem("outer", true)
	};
	cmdline::CmdLine cmdLine(flags);
	std::map<std::string, bool> mflags = cmdLine.getDefaultFlags();
	EXPECT_EQ(mflags.size(), flags.size());
}
TEST(Defaults, Flags_3) {
	std::vector<cmdline::ParmItem> flags = {
		 cmdline::ParmItem("output", true)
		,cmdline::ParmItem("outer", true)
		,cmdline::ParmItem("verbose", true)
	};
	cmdline::CmdLine cmdLine(flags);
	std::map<std::string, bool> mflags = cmdLine.getDefaultFlags();
	EXPECT_EQ(mflags.size(), flags.size());
}

TEST(Defaults, Flags_0) {
	std::vector<cmdline::ParmItem> flags;
	cmdline::CmdLine cmdLine(flags);
	std::map<std::string, bool> mflags = cmdLine.getDefaultFlags();
	EXPECT_EQ(mflags.size(), 0);
}
