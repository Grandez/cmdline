#include "pch.h"
#include <map>
#include <stdexcept>
#include <regex>

#include "../cmdline/cmdline.hpp"

using namespace std;
using namespace cmdline;

TEST(Constructors, empty) {
	// No flags, no options
	CmdLine cmdLine;
	Flags   flags   = cmdLine.getDefaultFlags();
	Options options = cmdLine.getDefaultOptions();
	EXPECT_EQ(flags.size(),   0);
	EXPECT_EQ(options.size(), 0);
}

TEST(Constructors, Flags_1) {
	// 1 flag, 0 options
	vector<ParmItem> iflags = {
		 ParmItem("verbose")
	};
	CmdLine cmdLine(iflags);
	Flags   flags   = cmdLine.getDefaultFlags();
	Options options = cmdLine.getDefaultOptions();
	EXPECT_EQ(flags.size(), iflags.size());
	EXPECT_EQ(options.size(), 0);
}

TEST(Constructors, Flags_2) {
	// 2 flags. Note that second arg is boolean, so is aflag
	std::vector<cmdline::ParmItem> iflags = {
		 cmdline::ParmItem("output", true)
		,cmdline::ParmItem("outer", true)
	};
	cmdline::CmdLine cmdLine(iflags);
	Flags   flags = cmdLine.getDefaultFlags();
	Options options = cmdLine.getDefaultOptions();
	EXPECT_EQ(flags.size(), iflags.size());
	EXPECT_EQ(options.size(), 0);
}
TEST(Constructors, Flags_with_help) {
	// Help is not auto inserted
	std::vector<cmdline::ParmItem> iflags = {
		 cmdline::ParmItem("output", true)
		,cmdline::ParmItem("outer", true)
		,cmdline::ParmItem("help", false)
	};
	cmdline::CmdLine cmdLine(iflags);
	Flags   flags   = cmdLine.getDefaultFlags();
	Options options = cmdLine.getDefaultOptions();
	EXPECT_EQ(flags.size(), flags.size());
	EXPECT_EQ(options.size(), 0);
}

TEST(Constructors, getHelp) {
	//Help exists
	std::vector<cmdline::ParmItem> flags = {
		 cmdline::ParmItem("output", true)
		,cmdline::ParmItem("outer", true)
	};
	cmdline::CmdLine cmdLine(flags);
	Flag flag = cmdLine.getFlag("help");
	EXPECT_EQ(flag.first, "help");
}
TEST(Constructors, getHELP) {
	// HELP Exists
	std::vector<cmdline::ParmItem> flags = {
		 cmdline::ParmItem("output", true)
		,cmdline::ParmItem("outer", true)
	};
	cmdline::CmdLine cmdLine(flags);
	Flag flag = cmdLine.getFlag("HELP");
	EXPECT_EQ(flag.first, "HELP");
}
TEST(Constructors, HelpExplicit) {
	// Can get Help status
	vector<cmdline::ParmItem> iflags = {
		 ParmItem("help", false)
		,ParmItem("outer", "..")
	};
	CmdLine cmdLine(iflags);
	Flags flags = cmdLine.getDefaultFlags(true);
	EXPECT_EQ(flags.size(), 1);
}

TEST(Constructors, option_1) {
	// 1 Options cause arg 2 is not boolean
	std::vector<cmdline::ParmItem> opts = {
		 cmdline::ParmItem("outer", "..")
	};
	cmdline::CmdLine cmdLine(opts);
	Flags flags     = cmdLine.getDefaultFlags();
	Options options = cmdLine.getDefaultOptions();
	EXPECT_EQ(flags.size(),   0);
	EXPECT_EQ(options.size(), 1);
}
TEST(Constructors, option_and_flags_mixed) {
	// Options and flags in same vector
	vector<ParmItem> opts = {
		  ParmItem("outer", "..")
		 ,ParmItem("verbose")
	};
	CmdLine cmdLine(opts);
	Flags flags     = cmdLine.getDefaultFlags();
	Options options = cmdLine.getDefaultOptions();
	EXPECT_EQ(flags.size(),   1);
	EXPECT_EQ(options.size(), 1);
}
TEST(Constructors, option_and_flags) {
	// 2 parms: one for options and other for flags
	vector<ParmItem> opts = {
		  ParmItem("outer", "..")
	};
	vector<Flag> flgs = {
		Flag("verbose", false)
	};
	CmdLine cmdLine(opts, flgs);
	Flags   flags   = cmdLine.getDefaultFlags();
	Options options = cmdLine.getDefaultOptions();
	EXPECT_EQ(flags.size(),   1);
	EXPECT_EQ(options.size(), 1);
}
TEST(Constructors, option_and_flags_invert) {
	// 2 parms: one for options and other for flags
	// first flags
	vector<ParmItem> opts = {
		   ParmItem("outer", "..")
	};
	vector<Flag> flgs = {
		Flag("verbose", true)
	};
	cmdline::CmdLine cmdLine(flgs, opts);
	Flags   flags   = cmdLine.getDefaultFlags();
	Options options = cmdLine.getDefaultOptions();
	EXPECT_EQ(flags.size(), 1);
	EXPECT_EQ(options.size(), 1);
}
TEST(Constructors, option_repeat) {
	// outer must be appears only one time
	vector<ParmItem> opts = {
		 ParmItem("outer", "..")
        ,ParmItem("outer", "other")
	};
	CmdLine cmdLine(opts);
	Flags   flags   = cmdLine.getDefaultFlags();
	Options options = cmdLine.getDefaultOptions();
	EXPECT_EQ(flags.size(), 0);
	EXPECT_EQ(options.size(), 1);
}

TEST(Constructors, option_repeat_value) {
	// outer must be other
	vector<ParmItem> opts = {
		 ParmItem("outer", "..")
		,ParmItem("outer", "other")
	};
	CmdLine cmdLine(opts);
	Flags   flags   = cmdLine.getDefaultFlags();
	Options options = cmdLine.getDefaultOptions();
	string str = cmdLine.getOption("outer");
	EXPECT_EQ(flags.size(), 0);
	EXPECT_EQ(options.size(), 1);
	EXPECT_EQ(str, "other");
}
