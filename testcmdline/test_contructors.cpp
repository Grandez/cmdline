#include "pch.h"
#include <map>
#include <stdexcept>
#include <regex>

#include "../cmdline/cmdline.h"

using namespace std;
using namespace cmdline;

TEST(Constructors, empty) {
	cmdline::CmdLine cmdLine;
	Flags flags = cmdLine.getDefaultFlags();
	EXPECT_EQ(flags.size(), 1); // Help
}
TEST(Constructors, flag_help) {
	std::vector<cmdline::ParmItem> iflags = {
	 cmdline::ParmItem("help", false)
	};

	cmdline::CmdLine cmdLine(iflags);
	Flags flags = cmdLine.getDefaultFlags();
	EXPECT_EQ(flags.size(), 1);
}
TEST(Constructors, Flags_1) {
	std::vector<cmdline::ParmItem> flags = {
		 cmdline::ParmItem("output", true)
	};
	cmdline::CmdLine cmdLine(flags);
	Flags mflags = cmdLine.getDefaultFlags();
	Options mOptions = cmdLine.getDefaultOptions();
	EXPECT_EQ(mflags.size(), flags.size() + 1); // help implicit
	EXPECT_EQ(mOptions.size(), 0);
}
TEST(Constructors, Flags_2) {
	std::vector<cmdline::ParmItem> flags = {
		 cmdline::ParmItem("output", true)
		,cmdline::ParmItem("outer", true)
	};
	cmdline::CmdLine cmdLine(flags);
	std::unordered_map<std::string, bool> mFlags = cmdLine.getDefaultFlags();
	std::unordered_map<std::string, std::string> mOptions = cmdLine.getDefaultOptions();
	EXPECT_EQ(mFlags.size(), flags.size() + 1); // help implicit
	EXPECT_EQ(mOptions.size(), 0);
}
TEST(Constructors, Flags_with_help) {
	std::vector<cmdline::ParmItem> flags = {
		 cmdline::ParmItem("output", true)
		,cmdline::ParmItem("outer", true)
		,cmdline::ParmItem("help", false)
	};
	cmdline::CmdLine cmdLine(flags);
	Flags   mFlags   = cmdLine.getDefaultFlags();
	Options mOptions = cmdLine.getDefaultOptions();
	EXPECT_EQ(mFlags.size(), flags.size());
	EXPECT_EQ(mOptions.size(), 0);
}
TEST(Constructors, getHelp) {
	std::vector<cmdline::ParmItem> flags = {
		 cmdline::ParmItem("output", true)
		,cmdline::ParmItem("outer", true)
	};
	cmdline::CmdLine cmdLine(flags);
	std::pair<std::string, bool>  pair = cmdLine.getFlag("help");
	EXPECT_EQ(pair.first, "help");
}
TEST(Constructors, HelpDefined) {
	std::vector<cmdline::ParmItem> flags = {
		 cmdline::ParmItem("output", true)
		,cmdline::ParmItem("outer", true)
	};
	cmdline::CmdLine cmdLine(flags);
	std::pair<std::string, bool>  pair = cmdLine.getFlag("help");
	EXPECT_FALSE(pair.second);
}
TEST(Constructors, HelpExplicit) {
	std::vector<cmdline::ParmItem> iflags = {
		 cmdline::ParmItem("help", false)
		,cmdline::ParmItem("outer", "..")
	};
	cmdline::CmdLine cmdLine(iflags);
	Flags flags = cmdLine.getDefaultFlags();
	EXPECT_EQ(flags.size(), 1);
}
TEST(Constructors, option_1) {
	std::vector<cmdline::ParmItem> opts = {
		 cmdline::ParmItem("outer", "..")
	};
	cmdline::CmdLine cmdLine(opts);
	Flags flags     = cmdLine.getDefaultFlags();
	Options options = cmdLine.getDefaultOptions();
	EXPECT_EQ(flags.size(),   1);
	EXPECT_EQ(options.size(), 1);
}
TEST(Constructors, option_and_flags_mixed) {
	std::vector<cmdline::ParmItem> opts = {
		  cmdline::ParmItem("outer", "..")
		 ,cmdline::ParmItem("verbose")
	};
	cmdline::CmdLine cmdLine(opts);
	Flags flags = cmdLine.getDefaultFlags();
	Options options = cmdLine.getDefaultOptions();
	EXPECT_EQ(flags.size(), 2);
	EXPECT_EQ(options.size(), 1);
}
TEST(Constructors, option_and_flags) {
	vector<cmdline::ParmItem> opts = {
		  ParmItem("outer", "..")
	};
	vector<Flag> flgs = {
		Flag("help", false)
	};
	cmdline::CmdLine cmdLine(opts, flgs);
	Flags flags = cmdLine.getDefaultFlags();
	Options options = cmdLine.getDefaultOptions();
	EXPECT_EQ(flags.size(),  1);
	EXPECT_EQ(options.size(), 1);
}
TEST(Constructors, option_and_flags_invert) {
	vector<cmdline::ParmItem> opts = {
		  cmdline::ParmItem("outer", "..")
	};
	vector<Flag> flgs = {
		pair<const char*, bool>("help", false)
	};
	cmdline::CmdLine cmdLine(flgs, opts);
	Flags flags = cmdLine.getDefaultFlags();
	Options options = cmdLine.getDefaultOptions();
	EXPECT_EQ(flags.size(), 1);
	EXPECT_EQ(options.size(), 1);
}
TEST(Constructors, option_repeat) {
	std::vector<cmdline::ParmItem> opts = {
		 cmdline::ParmItem("outer", "..")
        ,cmdline::ParmItem("outer", "other")
	};
	cmdline::CmdLine cmdLine(opts);
	Flags flags = cmdLine.getDefaultFlags();
	Options options = cmdLine.getDefaultOptions();
	EXPECT_EQ(flags.size(), 1);
	EXPECT_EQ(options.size(), 1);
}