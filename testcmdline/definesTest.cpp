/**
 * @file definesTest.cpp
 * @author Grandez
 * @date   09/2021
 * @brief Test for definitions
 *
  */

#include "pch.h"
#include "$tool.hpp"

TEST(Defines, Define_01) {
	tool.reset();
	int argc = tool.addArg("/def1=define1");
	Parameters  parms;
	CmdLine cmdline = CmdLine(tool.argc, tool.argv, parms);
	EXPECT_NO_THROW(cmdline.hasDefinition("def1"));
}
TEST(Defines, Define_02) {
	tool.reset();
	int argc = tool.addArg("/def1=define1");
	argc = tool.addArg("/def2=define2");
	Parameters  parms;
	CmdLine cmdline = CmdLine(tool.argc, tool.argv, parms);
	EXPECT_NO_THROW(cmdline.hasDefinition("def1"));
	EXPECT_NO_THROW(cmdline.hasDefinition("def2"));
}
TEST(Defines, Define_03) {
	tool.reset();
	int argc = tool.addArg("/def1=define1");
	argc = tool.addArg("/def1=define2");
	Parameters  parms;
	CmdLine cmdline = CmdLine(tool.argc, tool.argv, parms);
	EXPECT_NO_THROW(cmdline.hasDefinition("def1"));
}
TEST(Defines, Define_multiple) {
	tool.reset();
	int argc = tool.addArg("/def1=define1");
	argc = tool.addArg("/def2=define21,define22,define23");
	Parameters  parms;
	CmdLine cmdline = CmdLine(tool.argc, tool.argv, parms);
	EXPECT_FALSE(cmdline.isDefinitionMultiple("def1"));
	EXPECT_TRUE (cmdline.isDefinitionMultiple("def2"));
}
TEST(Defines, Define_quoted) {
	tool.reset();
	int argc = tool.addArg("/def1=\"define 1\"");
	argc = tool.addArg("/def2=define21,define22,define23");
	Parameters  parms;
	CmdLine cmdline = CmdLine(tool.argc, tool.argv, parms);
	const char* res = cmdline.getDefinition("def1");
	EXPECT_EQ(strcmp(res,"define 1"), 0);
}
TEST(Defines, Define_KO_1) {
	tool.reset();
	int argc = tool.addArg("/define1");
	Parameters  parms;
	EXPECT_THROW(CmdLine(tool.argc, tool.argv, parms), CmdLineException);
}
TEST(Defines, Define_KO_2) {
	tool.reset();
	int argc = tool.addArg("/= define1");
	Parameters  parms;
	EXPECT_THROW(CmdLine(tool.argc, tool.argv, parms), CmdLineParameterException);
}
TEST(Defines, Define_KO_3) {
	tool.reset();
	int argc = tool.addArg("/def1=define1=define2");
	Parameters  parms;
	EXPECT_THROW(CmdLine(tool.argc, tool.argv, parms), CmdLineParameterException);
}
TEST(Defines, Define_multiple_1) {
	tool.reset();
	Parameters  parms;
	int argc = tool.addArg("/def1=define1,define2");
	
	CmdLine cmdline = CmdLine(tool.argc, tool.argv, parms);
	vector<const char*> defs = cmdline.getDefinitionValues("def1");
	EXPECT_EQ(defs.size(), 2);
}
TEST(Defines, Define_multiple_2) {
	tool.reset();
	Parameters  parms;
	int argc = tool.addArg("/def1=define1","/def1=define2");

	CmdLine cmdline = CmdLine(tool.argc, tool.argv, parms);
	vector<const char*> defs = cmdline.getDefinitionValues("def1");
	EXPECT_EQ(defs.size(), 2);
}

/*
TEST(Defines, Vector_1) {
	tool.reset();
	int argc = tool.addArg("/def1=define1");
	Parameters  parms;
	CmdLine cmdline = CmdLine::getInstance(tool.argc, tool.argv, parms);
	EXPECT_EQ(strcmp(cmdline.getDefinition("def1"), "define1"), 0);
	CmdLine::freeInstance();
}
TEST(Defines, Vector_2) {
	tool.reset();
	int argc = tool.addArg("/def1=define1,define2");
	Parameters  parms;
	CmdLine cmdline = CmdLine::getInstance(tool.argc, tool.argv, parms);
	EXPECT_TRUE(cmdline.isDefinitionMultiple("def1"));
	CmdLine::freeInstance();
}
TEST(Defines, Vector_3) {
	tool.reset();
	int argc = tool.addArg("/def1=define1,define2");
	Parameters  parms;
	CmdLine cmdline = CmdLine::getInstance(tool.argc, tool.argv, parms);
	vector<const char*> defs = cmdline.getDefinitionValues("def1");
	EXPECT_EQ(strcmp(defs[0], "define1"), 0);
	CmdLine::freeInstance();
}
*/