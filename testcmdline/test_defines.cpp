#include "pch.h"
#include <map>
#include <stdexcept>

#include "../cmdline/include/cmdline.hpp"
/*
using namespace cmdline;
TEST(Defines, Define_01) {
	const char* argv[10] = { "testcase", "/def1=define1" };
	CmdLine cmdLine;
	EXPECT_NO_THROW(cmdLine.parse(2, argv));
}
TEST(Defines, Define_02) {
	const char* argv[10] = { "testcase", "/def1=define1", "/def2=define2" };
	CmdLine cmdLine;
	EXPECT_NO_THROW(cmdLine.parse(3, argv));
}
TEST(Defines, Define_03) {
	const char* argv[10] = { "testcase", "/def1=define1", "/def1=define2" };
	CmdLine cmdLine;
	EXPECT_NO_THROW(cmdLine.parse(3, argv));
}
TEST(Defines, Define_04) {
	const char* argv[10] = { "testcase", "/def1=define1", "/def2=define21,define22,define23" };
	CmdLine cmdLine;
	EXPECT_NO_THROW(cmdLine.parse(3, argv));
}
TEST(Defines, Define_05) {
	const char* argv[10] = { "testcase", "/def1=\"define 1\"", "/def2=define21,define22,define23" };
	CmdLine cmdLine;
	EXPECT_NO_THROW(cmdLine.parse(3, argv));
}

TEST(Defines, Define_KO_1) {
	// missing value or definition
	const char* argv[10] = { "testcase", "/define1" };
	CmdLine cmdLine;
	EXPECT_THROW(cmdLine.parse(2, argv), CmdLineException);
}
TEST(Defines, Define_KO_2) {
	// missing name
	const char* argv[10] = { "testcase", "/=define1" };
	CmdLine cmdLine;
	EXPECT_THROW(cmdLine.parse(2, argv), CmdLineParameterException);
}
TEST(Defines, Define_KO_3) {
	// malformed
	const char* argv[10] = { "testcase", "/def1=define1=define2" };
	CmdLine cmdLine;
	EXPECT_THROW(cmdLine.parse(2, argv), CmdLineParameterException);
}
TEST(Defines, Vector_1) {
	const char* argv[10] = { "testcase", "/def1=define1" };
	CmdLine cmdLine;
	cmdLine.parse(2, argv);
	vector<string> res = cmdLine.getVectorDefinition("def1");
	EXPECT_EQ(res.size(), 1);
}
TEST(Defines, Vector_2) {
	// malformed
	const char* argv[10] = { "testcase", "/def1=define1,define2" };
	CmdLine cmdLine;
	cmdLine.parse(2, argv);
	vector<string> res = cmdLine.getVectorDefinition("def1");
	EXPECT_EQ(res.size(), 2);
}
*/