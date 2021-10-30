#include "pch.h"

#include "../cmdline/include/cmdline.hpp"
/*
TEST(Tree, same_word) {
	std::vector<cmdline::ParmItem> opts = { ParmItem("verbose", "..") };
	const char* argv[] = { "command", "/verbose", "." };
	cmdline::CmdLine cmdLine(opts);
	EXPECT_NO_THROW(cmdLine.parse(3, argv));
}
TEST(Tree, one_letter) {
	std::vector<cmdline::ParmItem> opts = { ParmItem("verbose", "..") };
	const char* argv[] = { "command", "/v", "." };
	cmdline::CmdLine cmdLine(opts);
	EXPECT_NO_THROW(cmdLine.parse(3, argv));
}
TEST(Tree, two_letter) {
	std::vector<cmdline::ParmItem> opts = { ParmItem("verbose", "..") };
	const char* argv[] = { "command", "/ve", "." };
	cmdline::CmdLine cmdLine(opts);
	EXPECT_NO_THROW(cmdLine.parse(3, argv));
}
TEST(Tree, two_branchs_full_1) {
	std::vector<cmdline::ParmItem> opts = { ParmItem("output", ".."),  ParmItem("outer", ".") };
	const char* argv[] = { "command", "/output", "." };
	cmdline::CmdLine cmdLine(opts);
	EXPECT_NO_THROW(cmdLine.parse(3, argv));
}
TEST(Tree, two_branchs_full_2) {
	std::vector<cmdline::ParmItem> opts = { ParmItem("output", ".."),  ParmItem("outer", ".") };
	const char* argv[] = { "command", "/outer", "." };
	cmdline::CmdLine cmdLine(opts);
	EXPECT_NO_THROW(cmdLine.parse(3, argv));
}
TEST(Tree, two_branchs_partial_1) {
	std::vector<cmdline::ParmItem> opts = { ParmItem("output", ".."),  ParmItem("outer", ".") };
	const char* argv[] = { "command", "/oute", "." };
	cmdline::CmdLine cmdLine(opts);
	EXPECT_NO_THROW(cmdLine.parse(3, argv));
}
TEST(Tree, two_branchs_partial_2) {
	std::vector<cmdline::ParmItem> opts = { ParmItem("output", ".."),  ParmItem("outer", ".") };
	const char* argv[] = { "command", "/outp", "." };
	cmdline::CmdLine cmdLine(opts);
	EXPECT_NO_THROW(cmdLine.parse(3, argv));
}



TEST(Tree, word_extent) {
	std::vector<cmdline::ParmItem> opts = { ParmItem("verbose", "..") };
	const char* argv[] = { "command", "/verboses", "." };
	cmdline::CmdLine cmdLine(opts);
	EXPECT_THROW(cmdLine.parse(3, argv), CmdLineException);
}
*/