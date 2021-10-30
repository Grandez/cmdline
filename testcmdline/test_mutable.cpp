/*****************************************************************//**
 * \file   test_mutable.cpp
 * \brief  Test mutability of parameters
 * 
 * Parameters must be immutables
 * 
 * \author Grandez
 * \date   October 2021
 *********************************************************************/
#include "pch.h"
#include <map>
#include <stdexcept>

#include "../cmdline/include/cmdline.hpp"
/*
using namespace cmdline;
TEST(Immutables, definition) {
	const char* argv[10] = { "test","/def1=definition1" };
	CmdLine cmdline;
	cmdline.parse(2, argv);

	string str = cmdline.getDefinition((const char*)"def1");
	str.at(2) = 'p';
	string str2 = cmdline.getDefinition((const char*)"def1");

	EXPECT_EQ(str2, "definition1");
}
TEST(Immutables, option) {
	std::vector<cmdline::ParmItem> opts = { ParmItem("def1", "..") };
	const char* argv[10] = { "test","/def1", "definition1" };

	CmdLine cmdLine(opts);
	cmdLine.parse(3, argv);

	string str = cmdLine.getOption((const char*)"def1");
	str.at(2) = 'p';
	string str2 = cmdLine.getOption((const char*)"def1");

	EXPECT_EQ(str2, "definition1");
}
TEST(Defines, Vector_define) {
	const char* argv[10] = { "testcase", "/def1=define1,define2" };
	CmdLine cmdLine;
	cmdLine.parse(2, argv);
	vector<string> res = cmdLine.getVectorDefinition("def1");
	res[0] = string("pepe");
	vector<string> res2 = cmdLine.getVectorDefinition("def1");

	EXPECT_EQ(res[0], "define1");
}
*/