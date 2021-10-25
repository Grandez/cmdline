#include "pch.h"

#include "../cmdline/cmdline.h"

TEST(Tree, same_word) {
	std::vector<cmdline::ParmItem> opts = {
		  cmdline::ParmItem("verbose", "..")
	};
	char* argv[] = { "command", "/verbose", "." };
	cmdline::CmdLine cmdLine(opts);
	cmdLine.parse(3, argv);
	cmdLine.getOption("verbose")
	Flags flags = cmdLine.getDefaultFlags();
	Options options = cmdLine.getDefaultOptions();
	EXPECT_EQ(flags.size(), 2);
	EXPECT_EQ(options.size(), 1);
}

